//
//  GlobalsLoader.h
//  SwarmGL
//
//  Created by Pascal Weiß on 15.07.15.
//  Copyright (c) 2015 Pascal Weiß. All rights reserved.
//


#include "GlobalsLoader.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "Globals.h"


void GlobalsLoader::readFile(std::string filename, char txt[]) {
    std::string line;
    std::string aux;
    std::ifstream myfile (filename);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            if (DEBUG_FLAG)
                std::cout << line << '\n';
            aux.append(line);
            aux.append(" ");
//            txt.append(' ');
        }
        myfile.close();
        std::strcpy(txt, aux.c_str());
    }
    
    else std::cout << "Unable to open file";

}
    
void GlobalsLoader::loadGlobals() {
    char source[400];
    GlobalsLoader::readFile("Globals.json", source);
    
    
    char *endptr;
    JsonValue value;
    JsonAllocator allocator;
    int status = jsonParse(source, &endptr, &value, allocator);
    if (status != JSON_OK) {
        std::cout << "Failed to read Globals.json\n";
        exit(EXIT_FAILURE);
    }
    for (auto i : value) {
        if (strcmp(i->key, "NUMBER_OF_PARTICLES") == 0) {
            NUMBER_OF_PARTICLES = (int)i->value.toNumber();
        }
        else if (strcmp(i->key, "DIMENSION_LENGTH") == 0) {
            DIMENSION_LENGTH = (int)i->value.toNumber();
        }
//        else if (strcmp(i->key, "PARTICLE_INFLUENCE") == 0) {
//            PARTICLE_INFLUENCE = (double)i->value.toNumber();
//        }
        else if (strcmp(i->key, "PARTICLE_LENGTH") == 0) {
            PARTICLE_LENGTH = (float)i->value.toNumber();
        }
        else if (strcmp(i->key, "DEBUG_FLAG") == 0) {
            DEBUG_FLAG = (int)i->value.toNumber();
        }
        else if (strcmp(i->key, "PANIC_THRESHOLD") == 0) {
            PANIC_THRESHOLD = (int)i->value.toNumber();
        }
        else if (strcmp(i->key, "VELOCITY") == 0) {
            VELOCITY = (float)i->value.toNumber();
        }
        else if (strcmp(i->key, "PANIC_VELOCITY") == 0) {
            PANIC_VELOCITY = (float)i->value.toNumber();
        }
        else if (strcmp(i->key, "OPENNESS") == 0) {
            OPENNESS = (float)i->value.toNumber();
        }
        else if (strcmp(i->key, "PANIC_PROBABILITY") == 0) {
            PANIC_PROBABILITY = (float)i->value.toNumber();
        }
    }
}

