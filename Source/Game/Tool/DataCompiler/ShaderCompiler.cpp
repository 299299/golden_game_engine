#include "ShaderCompiler.h"

bool isShaderProcessed(const std::string& fileName)
{
    for(size_t i=0; i<g_config->m_processedShader.size(); ++i)
    {
        if(g_config->m_processedShader[i] == fileName)
            return true;
    }
    return false;
}

void ShaderCompiler::preProcess()
{
    g_config->m_processedShader.push_back(getFileName(m_input));
}

ShaderCompiler::ShaderCompiler()
{

}

ShaderCompiler::~ShaderCompiler()
{

}

bool ShaderCompiler::process(const std::string& input, const std::string& output)
{
#ifdef WIN32
    std::string fileName = getFileName(input);
    char firstChar = fileName[0];
    if(firstChar != 'v' && firstChar != 'f')
    {
        LOGE("[%s] shader name must with vs_... or fs_... !", input.c_str());
        return false;
    }

    FileReader shaderReader(input);
    if(!shaderReader.m_size) return false;

    //find first line with def.
    const char* defMark = "[def=";
    char* defHead = shaderReader.m_buf;
    int index1 = find_char(defHead, shaderReader.m_size, '[');
    defHead += index1;
    defHead += strlen(defMark);
    int index2 = find_char(defHead, shaderReader.m_size, ']');
    std::string def(defHead, index2);

    bool vs = (firstChar == 'v');
    std::string tmp_output = output + "_tmp";
    compile_shader(input, tmp_output, def, vs);

    {
        FileReader outputReader(tmp_output);
        if(!outputReader.m_size)
        {
            g_config->m_error.add_error("[%s] shader compile error!", input.c_str());
            return false;
        }

        uint32_t memSize = outputReader.m_size + sizeof(Shader);
        MemoryBuffer mem(memSize);
        Shader* shader = (Shader*)mem.m_buf;
        shader->m_size = outputReader.m_size;
        shader->m_blob = mem.m_buf + sizeof(Shader);
        shader->m_handle.idx = bgfx::invalidHandle;
        shader->m_name = stringid_caculate(getFileName(m_input).c_str());
        memcpy(shader->m_blob, outputReader.m_buf, outputReader.m_size);
        m_processed = write_file(output, shader, memSize);
    }

    //delete the temp file of shaderc compiled.
    delete_file(tmp_output);
    return m_processed;
#else
    m_processed = true;
    return m_processed;
#endif
}

ProgramCompiler::ProgramCompiler()
{

}

ProgramCompiler::~ProgramCompiler()
{

}

bool ProgramCompiler::readJSON(const jsonxx::Object& root)
{
    BaseCompiler::readJSON(root);
    const std::string& vsName = root.get<std::string>("vs");
    const std::string& psName = root.get<std::string>("ps");

    char vs[256];
    char ps[256];
    bx::snprintf(vs, sizeof(vs), SHADER_PATH"%s", vsName.c_str());
    bx::snprintf(ps, sizeof(ps), SHADER_PATH"%s", psName.c_str());
    LOGI("vs = %s, ps = %s, program=%s", vs, ps, m_output.c_str());

    ShaderProgram program;
    memset(&program, 0x00, sizeof(program));

    program.m_vsName = stringid_caculate(vs);
    program.m_psName = stringid_caculate(ps);
    program.m_handle.idx = bgfx::invalidHandle;

    addDependency("vertex shader", name_to_file_path(vs, Shader::get_name()));
    addDependency("pixel shader", name_to_file_path(ps, Shader::get_name()));

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
    StringArray shaderFiles;
    scan_dir(shaderFiles, SHADER_SOURCE_PATH, "shader", SCAN_FILES, false);

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
        g_config->add_child_compile(shader);
    }

    m_processed = true;
    return true;
}

bool ShaderIncludeCompiler::checkProcessing()
{
    if(!g_config->m_database.isFileChanged(m_input, m_modifyTime))
    {
        LOGI("file [%s] not change, ignore.", m_input.c_str())
        return false;
    }
    return true;
}
