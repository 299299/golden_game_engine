#include "ShaderCompiler.h"
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>

static std::vector<std::string> g_shaderProcessed;

bool isShaderProcessed(const std::string& fileName)
{
    for(size_t i=0; i<g_shaderProcessed.size(); ++i)
    {
        if(g_shaderProcessed[i] == fileName)
            return true;
    }
    return false;
}

void ShaderCompiler::preProcess()
{
    g_shaderProcessed.push_back(getFileName(m_input));
}

ShaderCompiler::ShaderCompiler()
{

}

ShaderCompiler::~ShaderCompiler()
{
    
}

bool ShaderCompiler::process(const std::string& input, const std::string& output)
{
    std::string fileName = getFileName(input);
    char firstChar = fileName[0];
    if(firstChar != 'v' && firstChar != 'f')
    {
        LOGE("[%s] shader name must with vs_... or fs_... !", input.c_str());
        return false;
    }

    char* blob = 0;
    uint32_t blobSize = read_file(input, &blob);
    if (!blobSize)
    {
        return false;
    }

    //find first line with def.
    const char* defMark = "[def=";
    char* defHead = blob;
    int index1 = find_char(defHead, blobSize, '[');
    defHead += index1;
    defHead += strlen(defMark);
    int index2 = find_char(defHead, blobSize, ']');
    std::string def(defHead, index2);
    free(blob);

    bool vs = (firstChar == 'v');
    compile_shader(input, output, def, vs);

    blobSize = read_file(output, &blob);
    if(!blobSize)
    {
        LOGE("[%s] shader compile error!", input.c_str());
        return false;
    }
    //delete the temp file of shaderc compiled.
    delete_file(output);

    uint32_t memSize = blobSize + sizeof(Shader);
    char* p = (char*)malloc(memSize);
    memset(p, 0x00, memSize);
    Shader* shader = (Shader*)p;
    shader->m_size = blobSize;
    shader->m_blob = p + sizeof(Shader);
    shader->m_handle.idx = bgfx::invalidHandle;
    shader->m_name = StringId(getFileName(m_input).c_str());
    memcpy(shader->m_blob, blob, blobSize);
    free(blob);

    if(!write_file(output, shader, memSize))
    {
        free(p);
        return false;
    }
    free(p);
    m_processed = true;
    return true;
}

ProgramCompiler::ProgramCompiler()
{

}

ProgramCompiler::~ProgramCompiler()
{

}

bool ProgramCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    std::string vsName = JSON_GetString(root.GetValue("vs"));
    std::string psName = JSON_GetString(root.GetValue("ps"));
    
    char vs[256];
    char ps[256];
    sprintf_s(vs, SHADER_PATH"%s", vsName.c_str());
    sprintf_s(ps, SHADER_PATH"%s", psName.c_str());
    LOGI("vs = %s, ps = %s, program=%s", vs, ps, m_output.c_str());

    ShaderProgram program;
    memset(&program, 0x00, sizeof(program));

    program.m_vsName = StringId(vs);
    program.m_psName = StringId(ps);
    program.m_handle.idx = bgfx::invalidHandle;

    addDependency("vertex-shader", name_to_file_path(vs, Shader::getName()));
    addDependency("pixel-shader", name_to_file_path(ps, Shader::getName()));

    return write_file(m_output, &program, sizeof(program));
}


ShaderIncludeCompiler::ShaderIncludeCompiler()
{

}

ShaderIncludeCompiler::~ShaderIncludeCompiler()
{
    
}

bool ShaderIncludeCompiler::process(const std::string& input, const std::string& output)
{
    std::vector<std::string> shaderFiles;
    findFiles(SHADER_SOURCE_PATH, "shader", false, shaderFiles);

    for(size_t i=0; i<shaderFiles.size(); ++i)
    {
        const std::string& shaderFile = shaderFiles[i];
        if(isShaderProcessed(getFileName(shaderFile))) continue;

        ShaderCompiler* shader = new ShaderCompiler;
        shader->m_input = shaderFile;
        shader->m_output = input_to_output(shaderFile);
        shader->checkModifyTime();
        shader->preProcess();
        shader->go();
        addChildCompiler(shader);
    }

    m_processed = true;
    return true;
}

bool ShaderIncludeCompiler::checkProcessing()
{
    if(!g_database.isFileChanged(m_input, m_modifyTime))
    {
        LOGI("file [%s] not change, ignore.", m_input.c_str())
        return false;
    }
    if(m_mode != 0) return true;
    if(m_packageName == "core" || m_packageName == "preview") return true;
    return true;
}
