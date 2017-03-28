#include "XML.h"


typedef enum {word, sep, lbracket, rbracket} Symbol;
Symbol sym;
char peek = 0;
std::string current = "";
std::vector<std::string> currentElement;

std::string get_after(std::vector<std::string> xs, std::string x){
    auto it = find(xs.begin(), xs.end(), x);
    if (it == xs.end()){
        return "";
    } else {
        auto index = std::distance(xs.begin(), it);
        if (index + 1 >= xs.size()){
            return "";
        } else {
            return xs.at(index + 1);
        }
    }
}

void parse_element(EngineState& state, std::vector<std::string> element){

    std::string value;
    float val;

    if (std::find(element.begin(), element.end(), "group") != element.end()){
        if (std::find(element.begin(), element.end(), "/") != element.end()){
            state.addSceneCommand(new ExitContext());
        } else {
            state.addSceneCommand(new EnterContext());
        }

    } else if (std::find(element.begin(), element.end(), "translate") != element.end()){
        Translate* t = new Translate();
        value = get_after(element, std::string("X"));
        t->X = (value != "") ? stof(value) : 0;

        value = get_after(element, std::string("Y"));
        t->Y = (value != "") ? stof(value) : 0;

        value = get_after(element, std::string("Z"));
        t->Z = (value != "") ? stof(value) : 0;
        state.addSceneCommand(t);

    } else if (std::find(element.begin(), element.end(), "rotate") != element.end()){
        Rotate* r = new Rotate();

        value = get_after(element, std::string("angle"));
        r->angle = (value != "") ? stof(value) : 0;

        value = get_after(element, std::string("axisX"));
        r->axisX = (value != "") ? stof(value) : 0;

        value = get_after(element, std::string("axisY"));
        r->axisY = (value != "") ? stof(value) : 0;

        value = get_after(element, std::string("axisZ"));
        r->axisZ = (value != "") ? stof(value) : 0;
        state.addSceneCommand(r);

    } else if (std::find(element.begin(), element.end(), "scale") != element.end()){ 
        Scale* s = new Scale();

        value = get_after(element, std::string("X"));
        s->X = (value != "") ? stof(value) : 1;

        value = get_after(element, std::string("Y"));
        s->Y = (value != "") ? stof(value) : 1;

        value = get_after(element, std::string("Z"));
        s->Z = (value != "") ? stof(value) : 1;

        state.addSceneCommand(s);

    } else if (std::find(element.begin(), element.end(), "model") != element.end()){
        DrawModel* m = new DrawModel();
        value = get_after(element, std::string("file"));
        if (value != ""){
            m -> vertices = readModel(value);
            state.addSceneCommand(m);
        }
        value = get_after(element, std::string("stl"));
        if (value != ""){
            m -> vertices = readSTL(value);
            state.addSceneCommand(m);
        }

    }

}

void error(std::string err){
    std::cout << "Error!\n";
    std::cout << err;
    exit(1);
}

int special_char(char c){
    return (c == '>' || c == '<' || c == '/' || c == '=' || isspace(c) || c == '"');
}

void next_token(FILE* fp){
    char c = (peek) ? peek : getc(fp);
    peek = 0;
    current.clear();

    if (c == '<'){
        sym = lbracket;
        current.push_back(c);

    } else if (c == '>'){
        sym = rbracket;
        current.push_back(c);

    } else if (c == '/'){
        sym = word;
        current.push_back(c);

    } else if (c == '=' || isspace(c)){
        sym = sep;
        next_token(fp);

    } else if (c == '"'){
        sym = word;
        while ((c = getc(fp)) != EOF){
            if (c == '"') {
                return;
            }
            current.push_back(c);
        }
        error("End of string unexpected.");
    } else {
        sym = word;
        current.push_back(c);
        while ((c = getc(fp)) != EOF){
            if (special_char(c)){
                peek = c; 
                return;
            }
            current.push_back(c);
        }
    }
}

void nextsym(FILE* fp){
    next_token(fp);
    if (sym == word){
        currentElement.push_back(current);
    }

}

int accept(FILE* fp, Symbol s) {
    if (sym == s) {
        nextsym(fp);
        return 1;
    }
    return 0;
}

int expect(FILE* fp, Symbol s) {
    if (accept(fp, s))
        return 1;
    error("expect: unexpected symbol");
    return 0;
}

void words(FILE* fp){
    expect(fp, word);
    while (accept(fp, word)){
        ;
    }
}

void element(FILE* fp, EngineState& state){
    currentElement.clear();
    expect(fp, lbracket);
    words(fp);
    expect(fp, rbracket);
    
    parse_element(state, currentElement);
}


void parse(FILE* fp, EngineState& state) {
    nextsym(fp);
    while (sym == lbracket){
        element(fp, state);
    }
}

