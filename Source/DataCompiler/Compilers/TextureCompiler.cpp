#include "TextureCompiler.h"
#include "DC_Utils.h"
#include <stb_image/stb_image.h>
#include "stdafx.h"

TextureCompiler::TextureCompiler()
:m_format(DDS_FORMAT)
{

}

bool TextureCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    m_input = JSON_GetString(root.GetValue("input"));
    m_format = JSON_GetString(root.GetValue("format"));
    m_processed = processImage(m_input, m_output);
    return m_processed;
}

bool TextureCompiler::processImage( const std::string& input, const std::string& output )
{
    if(!isFileExist(input))
    {
        LOGE("file not exist, return.");
        return false;
    }

    bool fileExist = isFileExist(output);
    bool fileChanged = g_database.isFileChanged(input, m_modifyTime);
    if(fileExist && !fileChanged)
    {
        m_skipped = true;
        return true;
    }

    extern DC_Config    g_config;
    if(g_config.m_ignoreTextures)
    {
        m_skipped = true;
        return true;
    }

    //1. first convert the source texture to dds file.
    std::string fileName = getFileName(input);
    std::string ddsFile = getFilePath(output) + fileName + ".dds";
    std::string fileNameExt = getFileNameAndExtension(input);
    toLower(fileNameExt);
    texconv_compress(input, getFilePath(output), m_format);
    addDependency("texture", input);
    
    //2. read the dds file back
    FileReader texutreReader(ddsFile);
    if(!texutreReader.m_size) return false;

    //3. back the whole file to one blob.
    uint32_t memSize = texutreReader.m_size + sizeof(Texture);
    MemoryBuffer mem(memSize);
    Texture* tex = (Texture*)mem.m_buf;
    tex->m_handle.idx = bgfx::invalidHandle;
    tex->m_size = texutreReader.m_size;
    memcpy(mem.m_buf + sizeof(Texture), texutreReader.m_buf, texutreReader.m_size);
    write_file(output, mem.m_buf, memSize);

    //4. delete the temp dds file.
    delete_file(ddsFile);
    return true;
}

void TextureCompiler::postProcess()
{
    checkDependency();
    if(!m_processed) return;
    g_database.insertResourceFile(m_input, m_modifyTime);
}


bool DDSCompiler::process( const std::string& input, const std::string& output )
{
    FileReader ddsReader(input);
    if(!ddsReader.m_size) return false;

    uint32_t memSize = ddsReader.m_size + sizeof(Texture);
    MemoryBuffer mem(memSize);
    Texture* tex = (Texture*)mem.m_buf;
    tex->m_handle.idx = bgfx::invalidHandle;
    tex->m_size = ddsReader.m_size;
    memcpy(mem.m_buf + sizeof(Texture), ddsReader.m_buf, ddsReader.m_size);
    return write_file(output, mem.m_buf, memSize);
}

bool Texture3DCompiler::readJSON(const JsonValue& root)
{
    char inputName[256];
    JSON_GetString(root.GetValue("input"), inputName, sizeof(inputName));
    int w, h, comps;
    stbi_uc* image = stbi_load(inputName, &w, &h, &comps, 4);
    if(!image) {
        addError(__FUNCTION__" stbi_load failed");
        return false;
    }
    if(w != 256 || h != 16)
    {
        addError(__FUNCTION__"lut input error (%d, %d)", w, h);
        return false;
    }

    uint32_t memSize = sizeof(Raw3DTexture) + COLOR_LUT_SIZE*COLOR_LUT_SIZE*COLOR_LUT_SIZE*4;
   MemoryBuffer mem(memSize);
    Raw3DTexture* tex3d = (Raw3DTexture*)mem.m_buf;
    tex3d->m_blob = mem.m_buf + sizeof(Raw3DTexture);
    tex3d->m_width = 16;
    tex3d->m_height = 16;
    tex3d->m_depth = 16;
    tex3d->m_format = bgfx::TextureFormat::BGRA8;
    tex3d->m_size = memSize - sizeof(Raw3DTexture);
    tex3d->m_handle.idx = bgfx::invalidHandle;
    lut2d_to_3d(image, (uint8_t*)tex3d->m_blob);
    std::string outputLut = m_output;
    std::string outputPath = getFilePath(m_output);
    std::string fileName = getFileName(outputLut);
    outputLut = outputPath + "/" + fileName + "." +Raw3DTexture::get_name();
    stbi_image_free(image);
    return write_file(outputLut, mem.m_buf, memSize);
}

bool Texture2DCompiler::readJSON( const JsonValue& root )
{
    return false;
}
