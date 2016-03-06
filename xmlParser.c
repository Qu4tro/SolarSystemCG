#include "xmlParser.h"

void load_scene(char* xml_filename);

char** getModels(char *xml_filename) {

    xmlDocPtr doc;  
    xmlNodePtr curr;
    xmlChar *modelFile;
    xmlAttrPtr attr;

    int n = 0;
    char** filenames;

    // TODO: DTD
    doc = xmlParseFile(xml_filename);
    if (doc == NULL ) {
        fprintf(stderr,"Error! Couldn't parse doc. \n");
        return NULL;
    }

    // Get scene node
    curr = xmlDocGetRootElement(doc);
    if (curr == NULL) {
        fprintf(stderr,"Document is Empty\n");
        xmlFreeDoc(doc);
        return NULL;
    }
    
    filenames = malloc(sizeof(char*) * 1000); //TODO

    curr = curr->xmlChildrenNode;
    while (curr != NULL) {

        attr = xmlHasProp(curr, (const xmlChar*)"file");
        if (attr != NULL){
            modelFile = xmlGetProp(curr, (const xmlChar*)"file");
            filenames[n++] = strdup((char*) modelFile);
            xmlFree(modelFile);
        }

        curr = curr->next;
    }

    /*free the document */
    xmlFreeDoc(doc);
    xmlCleanupParser(); 

    filenames[n] = NULL;

    return filenames;
} 
