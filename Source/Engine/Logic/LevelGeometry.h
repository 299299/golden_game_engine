#pragma once
#include "Entity.h"

ENGINE_ALIGN(16) struct LevelGeometry : public EntityInstance
{
    void start(const hkQsTransform& t);
    void stop();
    void preStep(float dt) {};
    void postStep(float dt) {};
};



