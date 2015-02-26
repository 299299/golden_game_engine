#include "TextureCompiler.h"
#include "Texture.h"
#include <stb/stb_image.c>

TextureCompiler::TextureCompiler()
:m_format(DDS_FORMAT)
{

}

bool TextureCompiler::readJSON(const jsonxx::Object& root)
{
    BaseCompiler::readJSON(root);
    m_input = root.get<std::string>("input");
    m_format = root.get<std::string>("format");
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
    bool fileChanged = g_config->is_file_changed(input, m_modifyTime);
    if(fileExist && !fileChanged)
    {
        m_skipped = true;
        return true;
    }

    if(g_config->m_ignoreTextures)
    {
        m_skipped = true;
        return true;
    }

    //1. first convert the source texture to dds file.
    std::string fileName = getFileName(input);
    std::string ddsFile = getFilePath(output) + fileName + ".dds";
    std::string fileNameExt = getFileNameAndExtension(input);
    toLower(fileNameExt);
#ifdef WIN32
    texconv_compress(input, getFilePath(output), m_format);
#else
    //in linux we just copy it to dest
    copy_file(input, ddsFile);
#endif

    addDependency("texture", input);

    //2. read the dds file back
    {
        FileReader texutreReader(ddsFile);
        if(!texutreReader.m_size) return false;

        //3. back the whole file to one blob.
        uint32_t memSize = texutreReader.m_size + sizeof(Texture);
        MemoryBuffer mem(memSize);
        Texture* tex = (Texture*)mem.m_buf;
        tex->m_handle.idx = bgfx::invalidHandle;
        tex->m_data_size = texutreReader.m_size;
        memcpy(mem.m_buf + sizeof(Texture), texutreReader.m_buf, texutreReader.m_size);
        write_file(output, mem.m_buf, memSize);
    }

    //3. delete the temp dds file.
    delete_file(ddsFile);

    return true;
}

void TextureCompiler::postProcess()
{
    checkDependency();
    if(!m_processed) return;
    g_config->m_database.insertResourceFile(m_input, m_modifyTime);
}


bool DDSCompiler::process( const std::string& input, const std::string& output )
{
    FileReader ddsReader(input);
    if(!ddsReader.m_size) return false;

    uint32_t memSize = ddsReader.m_size + sizeof(Texture);
    MemoryBuffer mem(memSize);
    Texture* tex = (Texture*)mem.m_buf;
    tex->m_handle.idx = bgfx::invalidHandle;
    tex->m_data_size = ddsReader.m_size;
    tex->m_data_offset = sizeof(Texture);
    memcpy(mem.m_buf + sizeof(Texture), ddsReader.m_buf, ddsReader.m_size);
    return write_file(output, mem.m_buf, memSize);
}

bool Texture3DCompiler::readJSON(const jsonxx::Object& root)
{
    const std::string& inputName = root.get<std::string>("input");
    int w, h, comps;
    stbi_uc* image = stbi_load(inputName.c_str(), &w, &h, &comps, 4);
    if(!image) {
        g_config->m_error.add_error("%s stbi_load failed", BX_FUNCTION);
        return false;
    }
    if(w != 256 || h != 16)
    {
        g_config->m_error.add_error("%s lut input error (%d, %d)", BX_FUNCTION, w, h);
        return false;
    }

    uint32_t memSize = sizeof(Raw3DTexture) + COLOR_LUT_SIZE*COLOR_LUT_SIZE*COLOR_LUT_SIZE*4;
    MemoryBuffer mem(memSize);
    Raw3DTexture* tex3d = (Raw3DTexture*)mem.m_buf;
    char* data = mem.m_buf + sizeof(Raw3DTexture);
    tex3d->m_width = 16;
    tex3d->m_height = 16;
    tex3d->m_depth = 16;
    tex3d->m_format = bgfx::TextureFormat::BGRA8;
    tex3d->m_data_size = memSize - sizeof(Raw3DTexture);
    tex3d->m_handle.idx = bgfx::invalidHandle;
    tex3d->m_data_offset = sizeof(Raw3DTexture);
    lut2d_to_3d(image, (uint8_t*)data);
    std::string outputLut = m_output;
    std::string outputPath = getFilePath(m_output);
    std::string fileName = getFileName(outputLut);
    outputLut = outputPath + "/" + fileName + "." + std::string(EngineNames::TEXTURE_3D);
    stbi_image_free(image);
    return write_file(outputLut, mem.m_buf, memSize);
}