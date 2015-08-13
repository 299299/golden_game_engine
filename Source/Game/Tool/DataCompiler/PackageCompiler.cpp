#include "PackageCompiler.h"
#include "Resource.h"

PackageCompiler::PackageCompiler()
{

}

PackageCompiler::~PackageCompiler()
{
    for(size_t i=0; i<m_groups.size(); ++i)
    {
        delete m_groups[i];
    }
}

int PackageCompiler::findGroup(const std::string& ext) const
{
    for(size_t i=0; i<m_groups.size(); ++i)
    {
        if(m_groups[i]->m_ext == ext)
            return i;
    }
    return -1;
}

static bool compare_less_group(PackageGroup* grpA, PackageGroup* grpB)
{
    return grpA->m_order < grpB->m_order;
}

bool PackageCompiler::process(const std::string& input, const std::string& output)
{
    StringArray filesInFolder;
    scan_dir(filesInFolder, input.c_str(), "*", SCAN_FILES, true);

    size_t numResources = filesInFolder.size();
    uint32_t memSize = sizeof(ResourcePackage);
    memSize += sizeof(ResourceInfo) * numResources;
    uint32_t totalFileSize = 0;
    bool bundled = g_config->m_bundled;

    for(size_t i=0; i<numResources; ++i)
    {
        const std::string& fileName = filesInFolder[i];
        std::string ext = getFileExt(fileName);
        int order = g_resourceMgr.get_resource_order(stringid_caculate(ext.c_str()));
        if(order < 0)
        {
            LOGW("not engine resource %s.", fileName.c_str());
            continue;
        }

        int index = findGroup(ext);
        PackageGroup* group = 0;

        if(index < 0)
        {
            group = new PackageGroup;
            group->m_ext = ext;
            group->m_type = stringid_caculate(ext.c_str());
            group->m_order = order;
            m_groups.push_back(group);
        }
        else
        {
            group = m_groups[index];
        }

        if(!bundled)
            memSize += fileName.length();

        group->m_files.push_back(&fileName);
        uint32_t fileSize = (uint32_t)get_file_size(fileName);
        fileSize = NATIVE_ALGIN_SIZE(fileSize) + NATIVE_ALIGN_VALUE;
        totalFileSize += fileSize;
    }

    std::sort(m_groups.begin(), m_groups.end(), compare_less_group);
    memSize += sizeof(ResourceGroup) * m_groups.size();
    uint32_t acSize = memSize;
    memSize = NATIVE_ALGIN_SIZE(memSize);

    LOGI("%s resource package group num = %d, total mem len = %d, total file size = %d",
        BX_FUNCTION, m_groups.size(), memSize, totalFileSize);

    MemoryBuffer mem(memSize);
    ResourcePackage* package = (ResourcePackage*)mem.m_buf;
    package->m_bundled = bundled;
    totalFileSize = NATIVE_ALGIN_SIZE(totalFileSize);
    if(!bundled)
        package->m_memBudget = totalFileSize;
    package->m_name = stringid_caculate(output.c_str());
    package->m_numGroups = m_groups.size();

    char* offset = mem.m_buf + sizeof(ResourcePackage);
    package->m_groups = (ResourceGroup*)offset;
    offset += sizeof(ResourceGroup) * m_groups.size();

    for(size_t i=0; i<m_groups.size(); ++i)
    {
        const PackageGroup* in_group = m_groups[i];
        LOGI("group[%d] name=%s, num-of-resource=%d, order=%d", i,
            in_group->m_ext.c_str(), in_group->m_files.size(), in_group->m_order);

        ResourceGroup& out_group = package->m_groups[i];
        out_group.m_numResources = in_group->m_files.size();
        out_group.m_type = in_group->m_type;
        out_group.m_resources = (ResourceInfo*)offset;
        out_group.m_resourceInfoOffset = (offset - mem.m_buf);
        offset += sizeof(ResourceInfo) * out_group.m_numResources;
        LOGI("group[%d] name = %s, num-resources = %d, type=%u, info-offset=%d", i,
            in_group->m_ext.c_str(),
            in_group->m_files.size(),
            out_group.m_type,
            out_group.m_resourceInfoOffset);
    }

    //===================================================
    //  TRAPS HERE
    //
    //  NOTICE resource name id is not a file path
    //  it`s in a relative name root on intermediate.
    //
    //  so a file in runtime data folder like this:
    //  data/core/common/test.texture
    //
    //  the resource name should be:
    //  core/common/test.texture
    //
    //===================================================
    int memOffset = memSize;
    for(size_t i=0; i<m_groups.size(); ++i)
    {
        const PackageGroup* in_group = m_groups[i];
        ResourceGroup& out_group = package->m_groups[i];
        LOGI("packing group %s", in_group->m_ext.c_str());

        for(size_t j=0; j<in_group->m_files.size(); ++j)
        {
            const std::string& fileName = *in_group->m_files[j];
            ResourceInfo& info = out_group.m_resources[j];

            std::string resourceName = remove_top_folder(fileName);
            removeExtension(resourceName);

            LOGI("resource file:%s, name:%s", fileName.c_str(), resourceName.c_str());

            info.m_name = stringid_caculate(resourceName.c_str());
            if(bundled)
            {
                info.m_size = get_file_size(fileName);
                info.m_size = NATIVE_ALGIN_SIZE(info.m_size);
                info.m_offset = memOffset;
                memOffset += info.m_size;
            }
            else
            {
                info.m_size = fileName.length();
                info.m_offset = offset - mem.m_buf;
                memcpy(offset, fileName.c_str(), info.m_size);
                offset += info.m_size;
            }
        }
    }

    FILE* fp = fopen(output.c_str(), "wb");
    fwrite(mem.m_buf, 1, memSize, fp);
    ENGINE_ASSERT(offset == mem.m_buf + acSize, "offset error.");

    if(bundled)
    {
        for(size_t i=0; i<m_groups.size(); ++i)
        {
            const PackageGroup* in_group = m_groups[i];
            ResourceGroup& out_group = package->m_groups[i];
            int memOffset = memSize;
            for(size_t j=0; j<in_group->m_files.size(); ++j)
            {
                const std::string& fileName = *in_group->m_files[j];
                FileReader reader(fileName);
                uint32_t memSize = NATIVE_ALGIN_SIZE(reader.m_size);
                ENGINE_ASSERT(reader.m_buf, "bundle file [%s] not found.", fileName.c_str());
                fwrite(reader.m_buf, 1, reader.m_size, fp);
                if(memSize > reader.m_size)
                {
                    uint32_t size = memSize - reader.m_size;
                    char buf[1024];
                    memset(buf, 0x00, sizeof(buf));
                    fwrite(buf, 1, size, fp);
                }
            }
        }
    }

    fclose(fp);

    // check code
    if(!bundled)
    {
        fp = fopen(output.c_str(), "rb");
        fread(mem.m_buf, memSize, 1, fp);
        ResourcePackage* check_pack = (ResourcePackage*)mem.m_buf;
        check_pack->m_groups = (ResourceGroup*)(mem.m_buf + sizeof(ResourcePackage));

        ENGINE_ASSERT(check_pack->m_name == package->m_name, "package check failed");
        ENGINE_ASSERT(check_pack->m_memBudget == package->m_memBudget, "package check failed");
        ENGINE_ASSERT(check_pack->m_numGroups == package->m_numGroups, "package check failed");
        for (size_t i=0; i<check_pack->m_numGroups; ++i)
        {
            ResourceGroup* check_grp = check_pack->m_groups + i;
            ResourceGroup* grp = package->m_groups + i;
            ENGINE_ASSERT(check_grp->m_memUsed == grp->m_memUsed, "package check failed");
            ENGINE_ASSERT(check_grp->m_numResources == grp->m_numResources, "package check failed");
            ENGINE_ASSERT(check_grp->m_resourceInfoOffset == grp->m_resourceInfoOffset, "package check failed");
            ENGINE_ASSERT(check_grp->m_type == grp->m_type, "package check failed");
        }

        fclose(fp);
    }


    m_processed = true;
    return true;
}

void PackageCompiler::postProcess()
{

}
