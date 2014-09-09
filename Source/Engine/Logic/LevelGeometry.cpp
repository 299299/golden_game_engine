#include "LevelGeometry.h"
#include "Component.h"
#include "MathDefs.h"
#include "Model.h"

void LevelGeometry::start(const hkQsTransform& t)
{
    m_transform = t;
    int modelIndex = getFirstCompIndexTypeOf(ModelResource::getType());
    ModelInstance* model = (ModelInstance*)getComponent(modelIndex);
    if(model) transform_matrix(model->m_transform, t);
}

void LevelGeometry::stop()
{

}
