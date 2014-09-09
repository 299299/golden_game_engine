#include "MaterialCompiler.h"
#include "TextureCompiler.h"

//material
MaterialCompiler::MaterialCompiler()
{

}

MaterialCompiler::~MaterialCompiler()
{
}

bool MaterialCompiler::readJSON( const JsonValue& root )
{
    __super::readJSON(root);
    //Texture samplers
    uint32_t samplerNum = 0;    
    JsonValue samplersValue = root.GetValue("samplers");
    if(samplersValue.IsValid()) 
    {
        samplerNum = samplersValue.GetElementsCount();
    }
    
    uint32_t memSize = sizeof(Material) + sizeof(MatSampler) * samplerNum;
    char* p = (char*)malloc(memSize);
    memset(p, 0x00, memSize);
    Material* m = (Material*)p;
    
    m->m_numSamplers = samplerNum;
    
    vec3Make(m->m_diffuse, 255, 255, 255);
    vec3Make(m->m_specular, 255, 255, 255);

     char programName[256];
    std::string programFile = JSON_GetString(root.GetValue("shader"));
    if(!programFile.empty())
    {
        sprintf_s(programName, PROGRAM_PATH"%s", programFile.c_str());
        m->m_shaderName = StringId(programName);
        addDependency("shader", name_to_file_path(programName, ShaderProgram::getName()));
    }
    else
    {
        addError("material[%s] with a null shader name", m_input.c_str());
    }
   
    programFile = JSON_GetString(root.GetValue("shadow-shader"));
    if(!programFile.empty())
    {
        sprintf_s(programName, PROGRAM_PATH"%s", programFile.c_str());
        m->m_shadowShaderName = StringId(programName);
        addDependency("shadow-shader", name_to_file_path(programName, ShaderProgram::getName()));
    }

    uint64_t renderState = BGFX_STATE_RGB_WRITE 
                            | BGFX_STATE_ALPHA_WRITE \
                            | BGFX_STATE_DEPTH_TEST_LESS \
                            | BGFX_STATE_DEPTH_WRITE \
                            | BGFX_STATE_CULL_CCW \
                            | BGFX_STATE_MSAA;


    JSON_GetFloats(root.GetValue("diffuse"), m->m_diffuse, 3);
    m->m_diffuse[3] = JSON_GetFloat(root.GetValue("diffuse-alpha"), 1.0f);
    JSON_GetFloats(root.GetValue("specular"), m->m_specular, 3);
    m->m_specular[3] = JSON_GetFloat(root.GetValue("specular-power"), 20.0f);

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
    
    JSON_GetFloats(root.GetValue("uv-offset"), m->m_offsetAndRepeat, 2);
    JSON_GetFloats(root.GetValue("uv-repeat"), m->m_offsetAndRepeat + 2, 2);

    m->m_params1[0] = JSON_GetFloat(root.GetValue("blend-normal"), 0.4f);
    m->m_params1[1] = JSON_GetFloat(root.GetValue("normal-height"), 1.0f);
    m->m_params1[2] = JSON_GetFloat(root.GetValue("emissive-intensity"), 1.0f);

    extern const char*  g_textureNames[];
    extern const char* g_textureFlagNames[];
    extern uint32_t g_textureFlags[];
    extern uint32_t g_textureFlagNum;

    if(samplersValue.IsValid())
    {
        m->m_samplers = (MatSampler*)(p + sizeof(Material));
        for(unsigned i=0; i<m->m_numSamplers; ++i)
        {
            JsonValue samplerValue = samplersValue[i];
            MatSampler& sampler = m->m_samplers[i];
            sampler.m_type = JSON_GetEnum(samplerValue.GetValue("name"), g_textureNames);
            sampler.m_flags = 0;
            uint32_t flags = JSON_GetFlags(samplerValue.GetValue("flags"), g_textureFlagNames);
            if(flags > 0)
            {
                for(uint32_t i=0; i<g_textureFlagNum; ++i)
                {
                    uint32_t flag = (1 << i);
                    if(flags & flag)
                        sampler.m_flags |= g_textureFlags[i];
                }
            }

            JsonValue textureValue = samplerValue.GetValue("texture");
            std::string textureFile;
            if(textureValue.GetType() == JSMN_STRING)
            {
                textureFile = JSON_GetString(textureValue);
            }
            else
            {
                //if it is a object, this is special case come from 
                //when group the texture resources to on json file.
                TextureCompiler* compiler = new TextureCompiler;
                compiler->m_mode = 1;
                compiler->m_outputFolder = getFilePath(m_output);
                if(!compiler->readJSON(textureValue)) m_subCompilerError = true;
                textureFile = compiler->m_name;
                addChildCompiler(compiler);
            }
            sampler.m_textureName = StringId(textureFile.c_str());
            addDependency("texture", name_to_file_path(textureFile, Texture::getName()));
        }
    }

    JsonValue rsValue = root.GetValue("render-state");
    if(rsValue.IsValid())
    {
        //@TODO only cull mode now.
        if(JSON_GetBool(rsValue.GetValue("cull-none")))
        {
            renderState &= ~BGFX_STATE_CULL_CW;
            renderState &= ~BGFX_STATE_CULL_CCW;
        }
        if(JSON_GetBool(rsValue.GetValue("alpha-blending")))
        {
            renderState |= BGFX_STATE_BLEND_ADD;
            renderState |= BGFX_STATE_BLEND_ALPHA;
        }
    }

    extern const char* g_matFlagNames[];
    uint8_t flags = 0;
    JsonValue flagsValue = root.GetValue("flags");
    if(flagsValue.IsValid())
    {
        for (uint32_t i=0; i<flagsValue.GetElementsCount(); ++i)
        {
            JsonValue flagValue = flagsValue[i];
            int type = JSON_GetEnum(flagValue.GetValue("name"), g_matFlagNames, -1);
            if(type < 0) continue;
            flags |= (1 << type);

            switch(type)
            {
            case kFlagRimLighting:
                {
                    m->m_rimColor.m_rimFresnelMin = JSON_GetFloat(flagValue.GetValue("rimFresnelMin"), 0.8f);
                    m->m_rimColor.m_rimFresnelMax = JSON_GetFloat(flagValue.GetValue("rimFresnelMax"), 1.0f);
                    m->m_rimColor.m_rimBrightness = JSON_GetFloat(flagValue.GetValue("rimBrightness"), 0.0f);
                }
                break;
            case kFlagTranslucency:
                {
                    TranslucencyInfo& translucency = m->m_translucency;
                    vec3Make(translucency.m_rampOuterColor, 1.0f, 0.64f, 0.25f);
                    vec3Make(translucency.m_rampMediumColor, 1.0f, 0.21f, 0.14f);
                    vec3Make(translucency.m_rampInnerColor, 0.25f, 0.05f, 0.02f);
                    JSON_GetFloats(flagValue.GetValue("ramp-outer-color"),translucency.m_rampOuterColor, 3);
                    JSON_GetFloats(flagValue.GetValue("ramp-medium-color"),translucency.m_rampMediumColor, 3);
                    JSON_GetFloats(flagValue.GetValue("ramp-inner-color"),translucency.m_rampInnerColor, 3);
                    translucency.m_info[0] = JSON_GetFloat(flagValue.GetValue("distortion"), 0.2f);
                    translucency.m_info[1] = JSON_GetFloat(flagValue.GetValue("power"), 3.0f);
                    translucency.m_info[2] = JSON_GetFloat(flagValue.GetValue("scale"), 1.0f);
                    translucency.m_info[3] = JSON_GetFloat(flagValue.GetValue("min"), 0.0f);
                }
                break;
            case kFlagOpacity:
                {
                    m->m_opacityParams[0] = JSON_GetFloat(flagValue.GetValue("opacity"), 1.0f);
                    m->m_opacityParams[1] = JSON_GetFloat(flagValue.GetValue("fresnel-min"), 0.0f);
                    m->m_opacityParams[2] = JSON_GetFloat(flagValue.GetValue("fresnel-max"), 0.0f);

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
    
    if(!write_file(m_output, p, memSize))
    {
        free(p); 
        return false;
    }

#ifdef COMPILER_LOAD_TEST
    char* buf = 0;
    size_t fileLen = read_file(m_output, &buf);  
    HK_ASSERT(0, fileLen == memSize);
    LOGD("dummping material %s.", m_output.c_str());
    Material* m1  = (Material*)load_resource_material(buf, fileLen);
    HK_ASSERT(0, m1->m_numSamplers == m->m_numSamplers);
    HK_ASSERT(0, m1->m_state == m->m_state);
    HK_ASSERT(0, m1->m_flags == m->m_flags);
    free(buf);
#endif

    free(p);
    return true;
}