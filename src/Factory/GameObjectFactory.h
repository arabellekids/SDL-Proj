#ifndef __GAMEOBJECTFACTORY__
#define __GAMEOBJECTFACTORY__

#include <string>
#include <map>
#include <iostream>

#include "../Objects/_Objects.h"

class GameObjectFactory
{
public:
    // Gets the singleton instance
    static GameObjectFactory* Instance()
    {
        if(s_pInstance == nullptr)
        {
            s_pInstance = new GameObjectFactory();
        }
        return s_pInstance;
    }

    bool registerType(std::string typeID, BaseCreator* pCreator)
    {
        std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);

        // If the type is already registered, do nothing
        if(it != m_creators.end())
        {
            delete pCreator;
            return false;
        }
        m_creators[typeID] = pCreator;
        return true;
    }
    GameObject* create(std::string typeID)
    {
        std::map<std::string, BaseCreator*>::iterator it = m_creators.find(typeID);
        if(it == m_creators.end())
        {
            std::cout << "Could not find type: " << typeID << "\n";
            return nullptr;
        }
        BaseCreator* pCreator = (*it).second;
        return pCreator->createGameObject();
    }
private:
    GameObjectFactory() {}
    static GameObjectFactory* s_pInstance;

    std::map<std::string, BaseCreator*> m_creators;
};

#endif