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
    MemoryBuffer mem(memSize);
    Material* m = (Material*)mem.m_buf;

    m->m_numSamplers = samplerNum;

    vec3_make(m->m_diffuse, 255, 255, 255);
    vec3_make(m->m_specular, 255, 255, 255);

    char programName[256];
    std::string programFile = root.get<std::string>("shader");
    if(!programFile.empty())
    {
        bx::snprintf(programName, sizeof(programName), PROGRAM_PATH"%s", programFile.c_str());
        m->m_shaderName = stringid_caculate(programName);
        addDependency("shader", name_to_file_path(programName, EngineNames::PROGRAM));
    }

    programFile = root.get<std::string>("shadow_shader", "");
    if(!programFile.empty())
    {
        bx::snprintf(programName, sizeof(programName), PROGRAM_PATH"%s", programFile.c_str());
        m->m_shadowShaderName = stringid_caculate(programName);
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

    m->m_offsetAndRepeat[0] = 0;
    m->m_offsetAndRepeat[1] = 0;
    m->m_offsetAndRepeat[2] = 1;
    m->m_offsetAndRepeat[3] = 1;

    json_to_floats(root, "uv_offset", m->m_offsetAndRepeat, 2);
    json_to_floats(root, "uv_repeat", m->m_offsetAndRepeat + 2, 2);

    m->m_params1[0] = json_to_float(root, "blend_normal", 0.4f);
    m->m_params1[1] = json_to_float(root, "normal_height", 1.0f);
    m->m_params1[2] = json_to_float(root, "emissive_intensity", 1.0f);

    extern const char*  g_textureNames[];
    extern const char* g_textureFlagNames[];
    extern uint32_t g_textureFlags[];
    extern uint32_t g_textureFlagNum;

    if(samplerNum)
    {
        m->m_samplers = (MatSampler*)(mem.m_buf + sizeof(Material));
        for(unsigned i=0; i<m->m_numSamplers; ++i)
        {
            const jsonxx::Object& o = samplersValue.get<jsonxx::Object>(i);
            MatSampler& sampler = m->m_samplers[i];
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
                g_config->add_child_compile(compiler);
            }
            else if(o.has<std::string>("texture"))
            {
                textureFile = o.get<std::string>("texture");
            }
            sampler.m_textureName = stringid_caculate(textureFile.c_str());
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
            if(type < 0) continue;
            flags |= (1 << type);

            switch(type)
            {
            case kFlagRimLighting:
                {
                    m->m_rimColor.m_rimFresnelMin = json_to_float(o, "rimFresnelMin", 0.8f);
                    m->m_rimColor.m_rimFresnelMax = json_to_float(o, "rimFresnelMax", 1.0f);
                    m->m_rimColor.m_rimBrightness = json_to_float(o, "rimBrightness", 0.0f);
                }
                break;
            case kFlagTranslucency:
                {
                    TranslucencyInfo& translucency = m->m_translucency;
                    vec3_make(translucency.m_rampOuterColor, 1.0f, 0.64f, 0.25f);
                    vec3_make(translucency.m_rampMediumColor, 1.0f, 0.21f, 0.14f);
                    vec3_make(translucency.m_rampInnerColor, 0.25f, 0.05f, 0.02f);
                    json_to_floats(o, "ramp_outer_color",translucency.m_rampOuterColor, 3);
                    json_to_floats(o, "ramp_medium_color",translucency.m_rampMediumColor, 3);
                    json_to_floats(o, "ramp_inner_color",translucency.m_rampInnerColor, 3);
                    translucency.m_info[0] = json_to_float(o, "distortion", 0.2f);
                    translucency.m_info[1] = json_to_float(o, "power", 3.0f);
                    translucency.m_info[2] = json_to_float(o, "scale", 1.0f);
                    translucency.m_info[3] = json_to_float(o, "min", 0.0f);
                }
                break;
            case kFlagOpacity:
                {
                    m->m_opacityParams[0] = json_to_float(o, "opacity", 1.0f);
                    m->m_opacityParams[1] = json_to_float(o, "fresnel_min", 0.0f);
                    m->m_opacityParams[2] = json_to_float(o, "fresnel_max", 0.0f);

                    //if opacity is on
                    //default to alpha blending render state.
                    renderState |= BGFX_STATE_BLEND_ADD;
                    renderState |= BGFX_STATE_BLEND_ALPHA;
                }
            default:
                break;
            }
        }
    }

    m->m_state = renderState;
    m->m_flags = flags;
    return write_file(m_output, mem.m_buf, memSize);
}