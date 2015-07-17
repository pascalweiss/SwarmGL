/**
 SwarmGL
 =======
 GlobalsLoader.h
 
 Loads the configuration file 'Globals.json', and parses 
 it to the global values, defined in Globals.h
 
 @author Tom Bisson, Pascal Weiß
 @date 16.07.2015
 */

#include <string>
#include "gason.h"

class GlobalsLoader {
    
public:
    /**
     Loads the configuration file 'Globals.json', and parses
     it to the global values, defined in Globals.h.
     */
    static void loadGlobals();
    
private:
    static void readFile(std::string filename, char txt[]);
};