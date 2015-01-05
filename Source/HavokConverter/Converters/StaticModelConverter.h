#pragma once
#include "ActorConverter.h"

class StaticModelConverter : public ActorConverter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    StaticModelConverter();
    ~StaticModelConverter();
    virtual void process(void* pData);
    void processNode(hkxNode* node);
    void processPhysics(hkpPhysicsData* physics);

    void setType(int modelType) { m_type = modelType; };

private:
    void process(hkxScene* scene);
private:
    hkxScene*           m_scene;
    int                 m_type;
};
