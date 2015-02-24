#include "ModelCompiler.h"
#include "MaterialCompiler.h"
#include "Mesh.h"

ModelCompiler::ModelCompiler()
{
    memset(&m_model, 0x00, sizeof(m_model));
}

ModelCompiler::~ModelCompiler()
{

}

bool ModelCompiler::readJSON( const jsonxx::Object& root )
{
    BaseCompiler::readJSON(root);

    std::string meshFile = m_pathPrefix + root.get<std::string>("mesh");
    m_model.m_meshName = stringid_caculate(meshFile.c_str());
    addDependency("mesh", name_to_file_path(meshFile, EngineNames::MESH));
    extern const char* g_viewGroupNames[];
    m_model.m_viewId = json_to_enum(root, "view_group", g_viewGroupNames, kSceneViewId);

    extern const char* g_modelFlagNames[];
    m_model.m_flag = json_to_flags(root, "flags", g_modelFlagNames);

    if(root.has<jsonxx::Array>("materials"))
    {
        const jsonxx::Array& materialsValue = root.get<jsonxx::Array>("materials");
        m_model.m_numMaterials = materialsValue.size();
        for(uint32_t i=0; i<m_model.m_numMaterials; ++i)
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
                g_config->add_compiler(compiler);
            }
            else
            {
                materialFile = materialsValue.get<std::string>(i);
            }
            materialFile = m_pathPrefix + materialFile;
            m_model.m_materialNames[i] = stringid_caculate(materialFile.c_str());
            addDependency("material", name_to_file_path(materialFile, EngineNames::MATERIAL));
        }
    }

    return true;
}