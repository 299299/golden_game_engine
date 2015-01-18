#include "ModelCompiler.h"
#include "MaterialCompiler.h"
#include "Mesh.h"

ModelCompiler::ModelCompiler()
{

}

ModelCompiler::~ModelCompiler()
{
    
}

bool ModelCompiler::readJSON( const jsonxx::Object& root )
{
    __super::readJSON(root);
    ModelResource model;
    memset(&model, 0x00, sizeof(model));

    const std::string& meshFile = root.get<std::string>("mesh");
    model.m_meshName = StringId(meshFile.c_str());
    addDependency("mesh", name_to_file_path(meshFile, Mesh::get_name()));
    extern const char* g_viewGroupNames[];
    if(root.has<std::string>("view_group"))
        model.m_viewId = find_enum_index(root.get<std::string>("view_group").c_str(), g_viewGroupNames);
    else
        model.m_viewId = kSceneViewId;

    extern const char* g_modelFlagNames[];
    if(root.has<jsonxx::Array>("flags"))
        model.m_flag = json_to_flags(root.get<jsonxx::Array>("flags"), g_modelFlagNames);
    else
        model.m_flag = kNodeFlagNone;

    if(root.has<jsonxx::Array>("materials"))
    {
        const jsonxx::Array& materialsValue = root.get<jsonxx::Array>("materials");
        model.m_numMaterials = materialsValue.size();
        for(uint32_t i=0; i<model.m_numMaterials; ++i)
        {
            std::string materialFile;
            if(materialsValue.has<jsonxx::Object>(i))
            {
                const jsonxx::Object& matValue = materialsValue.get<jsonxx::Object>(i);
                MaterialCompiler* compiler = new MaterialCompiler();
                compiler->m_mode = 1;
                compiler->m_outputFolder = getFilePath(m_output);
                if(!compiler->readJSON(matValue)) m_subCompilerError = true;
                materialFile = compiler->m_name;
                g_config->add_child_compile(compiler); 
            }
            else 
            {
                materialFile = materialsValue.get<std::string>(i);
            }
            model.m_materialNames[i] = StringId(materialFile.c_str());
            addDependency("material", name_to_file_path(materialFile, Material::get_name()));
        }
    }
    
    return write_file(m_output, &model, sizeof(model));
}