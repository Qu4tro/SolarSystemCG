#include "SceneParser.h"

#include <iostream>

using namespace tinyxml2;

bool hasValue(XMLNode* node, const char* str){
    return strcmp(node -> Value(), str) == 0;
}

fTriple parse_point(XMLNode* point){
    assert(point -> NoChildren());
    XMLElement* element = point -> ToElement();
    float X = 0;
    float Y = 0;
    float Z = 0;
    assert(element -> QueryFloatAttribute("X", &X) != XML_WRONG_ATTRIBUTE_TYPE && "X should be float");
    assert(element -> QueryFloatAttribute("Y", &Y) != XML_WRONG_ATTRIBUTE_TYPE && "Y should be float");
    assert(element -> QueryFloatAttribute("Z", &Z) != XML_WRONG_ATTRIBUTE_TYPE && "Z should be float");
    /* std::cout << fTriple(X, Y, Z).toString(); */
    return fTriple(X, Y, Z);

}

Command* parse_translate(XMLNode* translate){
    XMLElement* element = translate -> ToElement();
    assert(element != nullptr);

    float X = 0;
    float Y = 0;
    float Z = 0;
    assert(element -> QueryFloatAttribute("X", &X) != XML_WRONG_ATTRIBUTE_TYPE && "X should be float");
    assert(element -> QueryFloatAttribute("Y", &Y) != XML_WRONG_ATTRIBUTE_TYPE && "Y should be float");
    assert(element -> QueryFloatAttribute("Z", &Z) != XML_WRONG_ATTRIBUTE_TYPE && "Z should be float");


    float ttime = 0;
    XMLError r = element -> QueryFloatAttribute("time", &ttime);
    if (r == XML_NO_ATTRIBUTE){
        assert(translate -> NoChildren());
        return new Translate(X, Y, Z);

    } else if (r == XML_SUCCESS) {
        XMLNode* current = translate -> FirstChild();
        std::vector<fTriple> points;
        while (current != nullptr){
            if (hasValue(current, "point")){
                points.push_back(parse_point(current));
            } else {
                assert(0 && "Unexpected element inside translate (expected points).");
            }

            current = current -> NextSibling();
        }
        return new TranslateT(ttime, points);

    } else if (r == XML_WRONG_ATTRIBUTE_TYPE){
        assert(0 && "time should be float");
    } else {
        assert(0 && "Can't have both angle and time");
    }
}

Command* parse_rotate(XMLNode* rotate){
    assert(rotate -> NoChildren());
    XMLElement* element = rotate -> ToElement();
    assert(element != nullptr);

    float axisX = 0;
    float axisY = 0;
    float axisZ = 0;
    assert(element -> QueryFloatAttribute("axisX", &axisX) != XML_WRONG_ATTRIBUTE_TYPE && "axisX should be float");
    assert(element -> QueryFloatAttribute("axisY", &axisY) != XML_WRONG_ATTRIBUTE_TYPE && "axisY should be float");
    assert(element -> QueryFloatAttribute("axisZ", &axisZ) != XML_WRONG_ATTRIBUTE_TYPE && "axisZ should be float");


    float rtime = 0;
    float angle = 0;
    XMLError r1 = element -> QueryFloatAttribute("time", &rtime);
    XMLError r2 = element -> QueryFloatAttribute("angle", &angle);
    if (r1 == XML_WRONG_ATTRIBUTE_TYPE || r2 == XML_WRONG_ATTRIBUTE_TYPE){
        assert(0 && "time/angle should be float");
    } else if (r1 == XML_NO_ATTRIBUTE) {
        return new Rotate(angle, axisX, axisY, axisZ);

    } else if (r2 == XML_NO_ATTRIBUTE){
        return new RotateT(rtime, axisX, axisY, axisZ);

    } else {
        assert(0 && "Can't have both angle and time");
    }
}

Command* parse_scale(XMLNode* scale){
    assert(scale -> NoChildren());
    XMLElement* element = scale -> ToElement();
    float X = 1;
    float Y = 1;
    float Z = 1;
    assert(element -> QueryFloatAttribute("X", &X) != XML_WRONG_ATTRIBUTE_TYPE && "X should be float");
    assert(element -> QueryFloatAttribute("Y", &Y) != XML_WRONG_ATTRIBUTE_TYPE && "Y should be float");
    assert(element -> QueryFloatAttribute("Z", &Z) != XML_WRONG_ATTRIBUTE_TYPE && "Z should be float");
    return new Scale(X, Y, Z);
}

Command* parse_color(XMLNode* color){
    assert(color -> NoChildren());
    XMLElement* element = color -> ToElement();
    int R = 255;
    int G = 255;
    int B = 255;
    assert(element -> QueryIntAttribute("R", &R) != XML_WRONG_ATTRIBUTE_TYPE && "Color components should be ints [0..255]");
    assert(element -> QueryIntAttribute("G", &G) != XML_WRONG_ATTRIBUTE_TYPE && "Color components should be ints [0..255]");
    assert(element -> QueryIntAttribute("B", &B) != XML_WRONG_ATTRIBUTE_TYPE && "Color components should be ints [0..255]");
    return new Color(R, G, B);

}

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

Command* parse_model(XMLNode* model){
    assert(model -> NoChildren());
    XMLElement* element = model -> ToElement();
    std::string filename(element -> Attribute("file"));

    // check if file exists TODO
    Model* m = nullptr;
    if (hasEnding(filename, ".obj")){
        /* m = new Model_obj(filename); */
        assert(0 && "Not implemented");
    } else if (hasEnding(filename, ".stl")) { 
        /* m = new Model_stl(filename); */
        assert(0 && "Not implemented");
    } else if (hasEnding(filename, ".3d")) {
        m = new Model_3D(filename);
    } else {
        assert(0 && "Wrong filetype");
    }
    m -> load();

    return new DrawModel(m);

}

void parse_models(XMLNode* models, std::vector<Command*>& commands){
    XMLNode* current = models -> FirstChild();
    while (current != nullptr){
        if (hasValue(current, "model")){
            commands.push_back(parse_model(current));
        } else if (hasValue(current, "color")){
            parse_color(current);
        } else {
            assert(0 && "Unexpected element inside models.");
        }

        current = current -> NextSibling();
    }
}

void parse_group(XMLNode* group, std::vector<Command*>& commands){

    bool modelsFound = false;
    bool groupsFound = false;

    commands.push_back(new EnterContext());
    XMLNode* current = group -> FirstChild();
    while (current != nullptr){
        if (hasValue(current, "translate")){
            assert(modelsFound == false && "Geometric transformation after models.");
            assert(groupsFound == false && "Geometric transformation after group.");
            commands.push_back(parse_translate(current));

        } else if (hasValue(current, "rotate")){
            assert(modelsFound == false && "Geometric transformation after models.");
            assert(groupsFound == false && "Geometric transformation after group.");
            commands.push_back(parse_rotate(current));

        } else if (hasValue(current, "scale")){
            assert(modelsFound == false && "Geometric transformation after models.");
            assert(groupsFound == false && "Geometric transformation after group.");
            commands.push_back(parse_scale(current));

        } else if (hasValue(current, "color")){
            commands.push_back(parse_color(current));

        } else if (hasValue(current, "models")){
            assert(modelsFound == false && "More than one models tag inside group.");
            modelsFound = true;
            parse_models(current, commands);

        } else if (hasValue(current, "group")){
            groupsFound = true;
            parse_group(current, commands);

        } else {
            assert(0 && "Unexpected element inside scene.");
        }

        current = current -> NextSibling();
    }


    commands.push_back(new ExitContext());
}

std::vector<Command*> parse_scene(char* filename){

    XMLDocument xmlDoc;
    xmlDoc.LoadFile(filename);

    XMLNode* scene = xmlDoc.FirstChild();
    assert(scene != nullptr && "Document is empty.");
    assert(scene -> NextSibling() == nullptr && "Unexpected element after scene.");
    assert(scene -> FirstChild() != nullptr && "Scene is empty.");

    std::vector<Command*> commands;

    XMLNode* current = scene -> FirstChild();
    while (current != nullptr){
        if (hasValue(current, "group")){
            parse_group(current, commands);
        } else {
            assert(0 && "Unexpected element inside scene.");
        }

        current = current -> NextSibling();
    }

    return commands;
}

/* int main(int argc, char* argv[]){ */

/*     /1* parse(argv[1]); *1/ */
/*     for(auto it: parse(argv[1])){; */
/*         std::cout << it -> toString(); */
/*     } */

/*     return 0; */
/* } */
