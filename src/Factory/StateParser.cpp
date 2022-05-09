#include "StateParser.h"
#include "GameObjectFactory.h"
#include "../TextureManager.h"
#include "../Game.h"

bool StateParser::parseState(const char* stateFile, std::string stateID,
std::vector<GameObject*> *pObjects,
std::vector<std::string> *pTexIDs)
{
    // Create the XML document
    tinyxml2::XMLDocument xmlDoc;

    // Load the state file
    if(xmlDoc.LoadFile(stateFile) != tinyxml2::XML_SUCCESS)
    {
        std::cerr << "XML failed to load, error=" << xmlDoc.ErrorStr() << "\n";
        return false;
    }

    // Get the root element
    tinyxml2::XMLElement* pRoot = xmlDoc.RootElement();

    // Pre declare the states root node
    tinyxml2::XMLElement* pStateRoot = nullptr;

    // Get this states root node and assign it to pStateRoot
    for(tinyxml2::XMLElement* e=pRoot->FirstChildElement(); e != nullptr; e=e->NextSiblingElement())
    {
        if(e->Value() == stateID) { pStateRoot = e; }
    }

    // Pre declare the texture root
    tinyxml2::XMLElement* pTexRoot = nullptr;

    // Get the root of the texture elements
    for(tinyxml2::XMLElement* e=pStateRoot->FirstChildElement(); e != nullptr; e=e->NextSiblingElement())
    {
        if(e->Value() == std::string("TEXTURES")) { pTexRoot = e; }
    }

    // Now parse the textures
    parseTextures(pTexRoot, pTexIDs);

    // Pre declare the object root
    tinyxml2::XMLElement* pObjectRoot = nullptr;

    // Get the root node and assign it to pObjectRoot
    for(tinyxml2::XMLElement* e=pStateRoot->FirstChildElement(); e != nullptr; e=e->NextSiblingElement())
    {
        if(e->Value() == std::string("OBJECTS")) { pObjectRoot = e; }
    }

    // Now parse the objects
    parseObjects(pObjectRoot, pObjects);

    return true;
}

void StateParser::parseTextures(tinyxml2::XMLElement* pStateRoot,
std::vector<std::string> *pTexIDs)
{
    for(tinyxml2::XMLElement* e=pStateRoot->FirstChildElement(); e != nullptr; e=e->NextSiblingElement())
    {
        std::string filenameAttr = e->Attribute("filename");
        std::string idAttr = e->Attribute("ID");
        pTexIDs->push_back(idAttr); // Push into list

        TextureManager::Instance()->load(filenameAttr, idAttr, Game::Instance()->getRenderer());
    }
}

void StateParser::parseObjects(tinyxml2::XMLElement* pStateRoot,
std::vector<GameObject*> *pObjects)
{
    for(tinyxml2::XMLElement* e=pStateRoot->FirstChildElement(); e != nullptr; e=e->NextSiblingElement())
    {
        int x,y, w,h, numFrames, callbackID, animSpeed;
        std::string texID;
        
        x = e->IntAttribute("x");
        y = e->IntAttribute("y");
        w = e->IntAttribute("w");
        h = e->IntAttribute("h");
        numFrames = e->IntAttribute("numFrames");
        callbackID = e->IntAttribute("callbackID");
        animSpeed = e->IntAttribute("animSpeed");
        
        texID = e->Attribute("texID");

        GameObject* pObject = GameObjectFactory::Instance()->create(e->Attribute("type"));
        pObject->load(new LoaderParams(x,y, w,h, numFrames, texID, animSpeed, callbackID));
        pObjects->push_back(pObject);
    }
}