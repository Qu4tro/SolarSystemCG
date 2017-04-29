#include "XML.h"


typedef enum {word, sep, lbracket, rbracket} Symbol;
Symbol sym;
char peek = 0;
std::string current = "";
std::vector<std::string> currentElement;

std::string get_raw(std::vector<std::string> element, std::string key){
    auto it = find(element.begin(), element.end(), key);
    if (it == element.end()){
        return "";
    } else {
        unsigned index = std::distance(element.begin(), it);
        if (index + 1 >= element.size()){
            return "";
        } else {
            return element.at(index + 1);
        }
    }
}

float get_float(std::vector<std::string> element, std::string key, float defaultV){
    std::string value = get_raw(element, key);
    if (value == ""){
        return defaultV; 
    } else {
        return stof(value);
    }
}

void parse_element(EngineState& state, std::vector<std::string> element){

    std::string value;

    if (std::find(element.begin(), element.end(), "group") != element.end()){
        if (std::find(element.begin(), element.end(), "/") != element.end()){
            state.addSceneCommand(new ExitContext());
        } else {
            state.addSceneCommand(new EnterContext());
        }

    } else if (std::find(element.begin(), element.end(), "translate") != element.end()){
        state.addSceneCommand(new Translate(get_float(element, "X", 1),
                                            get_float(element, "Y", 1),
                                            get_float(element, "Z", 1)
                             ));
        
    } else if (std::find(element.begin(), element.end(), "rotate") != element.end()){
        state.addSceneCommand(new Rotate(get_float(element, "angle", 0),
                                         get_float(element, "axisX", 0),
                                         get_float(element, "axisY", 0),
                                         get_float(element, "axisZ", 0)
                             ));

    } else if (std::find(element.begin(), element.end(), "scale") != element.end()){ 
        state.addSceneCommand(new Scale(get_float(element, "X", 1),
                                        get_float(element, "Y", 1),
                                        get_float(element, "Z", 1)
                                        ));
        
    } else if (std::find(element.begin(), element.end(), "color") != element.end()){ 
        state.addSceneCommand(new Color(get_float(element, "R", 1),
                                        get_float(element, "G", 1),
                                        get_float(element, "B", 1)
                                        ));
        
    } else if (std::find(element.begin(), element.end(), "model") != element.end()){
        value = get_raw(element, std::string("file"));
        DrawModel* m = new DrawModel(value);
        state.addSceneCommand(m);
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

void element(FILE* fp){
    currentElement.clear();
    expect(fp, lbracket);
    words(fp);
    expect(fp, rbracket);
}


void parse(FILE* fp, EngineState& state) {
    nextsym(fp);
    while (sym == lbracket){
        element(fp);
        parse_element(state, currentElement);
    }
}

