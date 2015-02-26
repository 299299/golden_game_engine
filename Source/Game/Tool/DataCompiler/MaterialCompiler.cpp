#include "MaterialCompiler.h"
#include "TextureCompiler.h"
#include "Shader.h"
#include "Material.h"

//material
MaterialCompiler::MaterialCompiler()
{

}

MaterialCompiler::~MaterialCompiler()
{
}

bool MaterialCompiler::readJSON( const jsonxx::Object& root )
{
    BaseCompiler::readJSON(root);
    //Texture samplers
    uint32_t samplerNum = 0;
    jsonxx::Array samplersValue;
    if(root.has<jsonxx::Array>("samplers"))
    {
        samplersValue = root.get<jsonxx::Array>("samplers");
        samplerNum = samplersValue.size();
    }

    uint32_t memSize = sizeof(Material) + sizeof(MatSampler) * samplerNum;
    uint32_t ac_size = memSize;
    memSize = NATIVE_ALGIN_SIZE(memSize);

    MemoryBuffer mem(memSize);
    Material* m = (Material*)mem.m_buf;

    vec3_make(m->m_diffuse, 255, 255, 255);
    vec3_make(m->m_specular, 255, 255, 255);

    char programName[256];
    std::string programFile = root.get<std::string>("shader");
    if(!programFile.empty())
    {
        bx::snprintf(programName, sizeof(programName), PROGRAM_PATH"%s", programFile.c_str());
        m->m_shader_name = stringid_caculate(programName);
        addDependency("shader", name_to_file_path(programName, EngineNames::PROGRAM));
    }

    programFile = root.get<std::string>("shadow_shader", "");
    if(!programFile.empty())
    {
        bx::snprintf(programName, sizeof(programName), PROGRAM_PATH"%s", programFile.c_str());
        m->m_shadow_shader_name = stringid_caculate(programName);
        addDependency("shadow shader", name_to_file_path(programName, EngineNames::PROGRAM));
    }

    uint64_t renderState = BGFX_STATE_RGB_WRITE
                            | BGFX_STATE_ALPHA_WRITE \
                            | BGFX_STATE_DEPTH_TEST_LESS \
                            | BGFX_STATE_DEPTH_WRITE \
                            | BGFX_STATE_CULL_CCW \
                            | BGFX_STATE_MSAA;


    json_to_floats(root, "diffuse", m->m_diffuse, 3);
    m->m_diffuse[3] = json_to_float(root, "diffuse_alpha", 1.0f);
    json_to_floats(root, "specular", m->m_specular, 3);
    m->m_specular[3] = json_to_float(root, "specular_power", 20.0f);

    //convert all color 255 to 1 range.
    for(uint32_t i=0; i<3; ++i)
    {
        m->m_diffuse[i] /= 255;
    }
    for(uint32_t i=0; i<3; ++i)
    {
        m->m_specular[i] /= 255;
    }

    m->m_offset_repeat[0] = 0;
    m->m_offset_repeat[1] = 0;
    m->m_offset_repeat[2] = 1;
    m->m_offset_repeat[3] = 1;

    json_to_floats(root, "uv_offset", m->m_offset_repeat, 2);
    json_to_floats(root, "uv_repeat", m->m_offset_repeat + 2, 2);

    extern const char*  g_textureNames[];
    extern const char* g_textureFlagNames[];
    extern uint32_t g_textureFlags[];
    extern uint32_t g_textureFlagNum;

    m->m_sampler_offset = sizeof(Material);
    m->m_num_samplers = samplerNum;

    if(samplerNum)
    {
        MatSampler * samplers = (MatSampler*)(mem.m_buf + m->m_sampler_offset);
        for(unsigned i=0; i<samplerNum; ++i)
        {
            const jsonxx::Object& o = samplersValue.get<jsonxx::Object>(i);
            MatSampler& sampler = samplers[i];
            sampler.m_type = json_to_enum(o, "name", g_textureNames);
            sampler.m_flags = 0;
            uint32_t flags = json_to_flags(o, "flags", g_textureFlagNames);
            if(flags > 0)
            {
                for(uint32_t i=0; i<g_textureFlagNum; ++i)
                {
                    uint32_t flag = (1 << i);
                    if(flags & flag)
                        sampler.m_flags |= g_textureFlags[i];
                }
            }

            std::string textureFile;
            if(o.has<jsonxx::Object>("texture"))
            {
                //if it is a object, this is special case come from
                //when group the texture resources to on json file.
                TextureCompiler* compiler = new TextureCompiler;
                compiler->m_mode = 1;
                compiler->m_outputFolder = getFilePath(m_output);
                if(!compiler->readJSON(o.get<jsonxx::Object>("texture")))
                    m_subCompilerError = true;
                textureFile = compiler->m_name;
                g_config->add_compiler(compiler);
            }
            else if(o.has<std::string>("texture"))
            {
                textureFile = o.get<std::string>("texture");
            }
            sampler.m_texture_name = stringid_caculate(textureFile.c_str());
            addDependency("texture", name_to_file_path(textureFile, EngineNames::TEXTURE));
        }
    }

    if(root.has<jsonxx::Object>("render_state"))
    {
        const jsonxx::Object& rsValue = root.get<jsonxx::Object>("render_state");
        //@TODO only cull mode now.
        if(rsValue.get<bool>("cull_none"))
        {
            renderState &= ~BGFX_STATE_CULL_CW;
            renderState &= ~BGFX_STATE_CULL_CCW;
        }
        if(rsValue.get<bool>("alpha_blending"))
        {
            renderState |= BGFX_STATE_BLEND_ADD;
            renderState |= BGFX_STATE_BLEND_ALPHA;
        }
    }

    extern const char* g_matFlagNames[];
    uint8_t flags = 0;
    if(root.has<jsonxx::Array>("flags"))
    {
        const jsonxx::Array& flagsValue = root.get<jsonxx::Array>("flags");
        for (uint32_t i=0; i<flagsValue.size(); ++i)
        {
            const jsonxx::Object& o = flagsValue.get<jsonxx::Object>(i);
            int type = json_to_enum(o, "name", g_matFlagNames);
            if(type < 0)
                continue;
            flags |= (1 << type);
        }
    }

    m->m_state = renderState;
    m->m_flags = flags;
    return write_file(m_output, mem.m_buf, memSize);
}