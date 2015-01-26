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
    BaseCompiler::readJSON(root);
    ModelResource model;
    memset(&model, 0x00, sizeof(model));

    std::string meshFile = m_pathPrefix + root.get<std::string>("mesh");
    model.m_meshName = StringId(meshFile.c_str());
    addDependency("mesh", name_to_file_path(meshFile, Mesh::get_name()));
    extern const char* g_viewGroupNames[];
    model.m_viewId = json_to_enum(root, "view_group", g_viewGroupNames, kSceneViewId);

    extern const char* g_modelFlagNames[];
    model.m_flag = json_to_flags(root, "flags", g_modelFlagNames);

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
            materialFile = m_pathPrefix + materialFile;
            model.m_materialNames[i] = StringId(materialFile.c_str());
            addDependency("material", name_to_file_path(materialFile, Material::get_name()));
        }
    }

    return write_file(m_output, &model, sizeof(model));
}