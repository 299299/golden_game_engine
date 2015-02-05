#pragma once
#include "ActorConverter.h"

class hkxNode;
class hkxScene;
class LevelConverter : public ActorConverter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    LevelConverter();
    ~LevelConverter();
    virtual void process(void* pData);
    virtual jsonxx::Object serializeToJson() const;
    virtual jsonxx::Object serializeToJsonSplit() const;
private:
    void process(hkxScene* scene);
    virtual void postProcess();
    Actor_Config* createConfig(const std::string& nodeName);
private:
    hkxScene*                                   m_scene;
    std::vector<hkxNode*>                       m_sceneNodes;
    std::vector<hkxNode*>                       m_meshNodes;
    std::vector<hkxNode*>                       m_lightNodes;
    std::vector<ActorConverter*>                m_levelMeshes;
    std::vector<ActorConverter*>                m_levelLights;
    ActorConverter*                             m_collisionActor;
    std::vector<Actor_Config*>                  m_configs;
};
