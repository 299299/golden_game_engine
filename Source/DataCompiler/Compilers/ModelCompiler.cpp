#include "ModelCompiler.h"
#include "MaterialCompiler.h"
#include "Mesh.h"
#include "DC_Utils.h"

ModelCompiler::ModelCompiler()
{

}

ModelCompiler::~ModelCompiler()
{
    
}

bool ModelCompiler::readJSON( const JsonValue& root )
{
    __super::readJSON(root);
    ModelResource model;
    memset(&model, 0x00, sizeof(model));

    std::string meshFile = JSON_GetString(root.GetValue("mesh"));
    model.m_meshName = StringId(meshFile.c_str());
    addDependency("mesh", name_to_file_path(meshFile, Mesh::getName()));
    extern const char* g_viewGroupNames[];
    model.m_viewId = JSON_GetEnum(root.GetValue("view_group"), g_viewGroupNames, kSceneViewId);

    extern const char* g_modelFlagNames[];
    model.m_flag = JSON_GetFlags(root.GetValue("flags"), g_modelFlagNames, kNodeFlagNone);

    JsonValue materialsValue = root.GetValue("materials");
    if(materialsValue.IsValid())
    {
        model.m_numMaterials = materialsValue.GetElementsCount();
        for(uint32_t i=0; i<model.m_numMaterials; ++i)
        {
            JsonValue matValue = materialsValue[i];
            std::string materialFile;
            if(matValue.GetType() == JSMN_OBJECT)
            {
                MaterialCompiler* compiler = new MaterialCompiler();
                compiler->m_mode = 1;
                compiler->m_outputFolder = getFilePath(m_output);
                if(!compiler->readJSON(matValue)) m_subCompilerError = true;
                materialFile = compiler->m_name;
                addChildCompiler(compiler); 
            }
            else materialFile = JSON_GetString(materialsValue[i]);
            model.m_materialNames[i] = StringId(materialFile.c_str());
            addDependency("material", name_to_file_path(materialFile, Material::getName()));
        }
    }
    
    if(!write_file(m_output, &model, sizeof(model)))
    {
        return false;
    }

#ifdef COMPILER_LOAD_TEST
    char* buf = 0;
    size_t fileLen = read_file(m_output, &buf);  
    HK_ASSERT(0, fileLen == sizeof(model));
    ModelResource* model2 = (ModelResource*)load_resource_model(buf, fileLen);
    HK_ASSERT(0, model2->m_numMaterials == model.m_numMaterials);
    HK_ASSERT(0, model2->m_meshName == model.m_meshName);
    for (uint32_t i=0; i<model2->m_numMaterials; ++i)
    {
        HK_ASSERT(0, model2->m_materialNames[i] == model.m_materialNames[i]);
    }
    free(buf);
#endif
    return true;
}