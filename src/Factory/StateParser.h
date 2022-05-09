#ifndef __STATEPARSER__
#define __STATEPARSER__

#include <iostream>
#include <string>
#include <vector>
#include <tinyxml2.h>

class GameObject;

class StateParser
{
public:
    bool parseState(const char* stateFile, std::string stateID,
    std::vector<GameObject*> *pObjects,
    std::vector<std::string> *pTexIDs);

private:
    void parseObjects(tinyxml2::XMLElement* pStateRoot,
    std::vector<GameObject*> *pObjects);

    void parseTextures(tinyxml2::XMLElement* pStateRoot,
    std::vector<std::string> *pTexIDs);
};

#endif