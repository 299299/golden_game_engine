#include "HC_Utils.h"
#include "Profiler.h"
#include "CommonUtils.h"
#include "Level.h"
#include "Actor.h"

void dumpNodeRec(hkxNode* theNode)
{
    hkVariant va = theNode->m_object;
    const char* className = "$No Class";
    if(va.m_class)
    {
        className = va.m_class->getName();
    }

    LOGD("node name=%s, object class=%s, properties=%s", theNode->m_name.cString(), className, theNode->m_userProperties.cString());
    LOGD("keyFrameSize=%d, childrenSize=%d, annotationSize=%d, linearKeyFrameSize=%d, selected=%s",
                        theNode->m_keyFrames.getSize(),
                        theNode->m_children.getSize(),
                        theNode->m_annotations.getSize(),
                        theNode->m_linearKeyFrameHints.getSize(),
                        theNode->m_selected ? "true" : "false");

    for (int i=0; i<theNode->m_annotations.getSize(); ++i)
    {
        const hkxNode::AnnotationData& annotation = theNode->m_annotations[i];
        LOGD("annotation[%d], time=%f, text=%s", i, annotation.m_time, annotation.m_description.cString());
    }

    for(int i=0; i<theNode->m_attributeGroups.getSize(); ++i)
    {
        const hkxAttributeGroup& attrGrp = theNode->m_attributeGroups[i];
        LOGD("attribute group name = %s, attributes = %d", 
                            attrGrp.m_name.cString(),
                            attrGrp.m_attributes.getSize());
        for(int j=0; j<attrGrp.m_attributes.getSize(); ++j)
        {
            const hkxAttribute& attr = attrGrp.m_attributes[j];
            const hkClass* pClass = attr.m_value.getClass();
            LOGD("attribute = %s, class = %s",
                                attr.m_name.cString(),
                                pClass->getName());
        }
    }

    for(int i=0; i<theNode->m_children.getSize(); ++i)
    {
        dumpNodeRec(theNode->m_children[i]);
    }
}

void findNodesRec(  hkxNode* theNode, 
                    const hkClass* theClass, 
                    std::vector<hkxNode*>& outNodes)
{
    hkVariant va = theNode->m_object;
    if (va.m_class == theClass) outNodes.push_back(theNode);
    for(int i=0; i<theNode->m_children.getSize(); ++i)
    {
        findNodesRec(theNode->m_children[i], theClass, outNodes);
    }
}

void findNodesRec(  hkxNode* theNode, 
                    const std::string& preFix, 
                    std::vector<hkxNode*>& outNodes)
{
    if (theNode->m_name.startsWith(preFix.c_str()))
        outNodes.push_back(theNode);

    for(int i=0; i<theNode->m_children.getSize(); ++i)
    {
        findNodesRec(theNode->m_children[i], preFix, outNodes);
    }
}

Actor_Config* createConfig( const std::string& input, const std::string& outFolder )
{
    extern ResourceFileDataBase g_havokDB;
    std::string hkxFileName = input;
    string_replace(hkxFileName, "\\", "/");
    std::string entityName = getFileName(hkxFileName);
    std::string outputFolder = outFolder;//std::string("intermediate/") + package + "/";
    bool bLevel = str_begin_with(entityName, "Level");
	static const std::string actor_prefix("actor/");
    if(!bLevel) outputFolder += actor_prefix;
    std::string outputFile;
    if(bLevel) outputFile = outputFolder + entityName + "." + Level::get_name();
    else outputFile = outputFolder + entityName + "."+ ActorResource::get_name();
    uint64_t fileTime = 0;
    bool bFileChanged = g_havokDB.isFileChanged(hkxFileName, fileTime);
    bool bFileExist = isFileExist(outputFile);
    if(!bFileChanged && bFileExist)
    {
        LOGI("ignore hkx file %s.", hkxFileName.c_str());
        return 0;
    }
    Actor_Config* config = new Actor_Config;
    config->m_time = fileTime;
    config->m_input = hkxFileName;
    config->m_exportName = entityName;
    config->m_exportFolder = outputFolder;
    config->m_output = outputFile;
    std::string path = config->m_exportFolder;
    string_replace(path, INTERMEDIATE_PATH, "");
    config->m_rootPath = path;
    return config;
}


void fill_object_attributes(jsonxx::Object& object, const hkxAttributeGroup* group)
{
    if(!group) return;
    //TODO Animated Attributes
    for (int i=0; i<group->m_attributes.getSize(); ++i)
    {
        const hkxAttribute& attrib = group->m_attributes[i];
        std::string attrName(attrib.m_name.cString());
        hkVariant variant(attrib.m_value);
        if(variant.m_class == &hkxSparselyAnimatedStringClass)
        {
            hkxSparselyAnimatedString* hString = (hkxSparselyAnimatedString*)variant.m_object;
            object << attrName << std::string(hString->m_strings[0].cString());
        }
        else if(variant.m_class == &hkxAnimatedFloatClass)
        {
            hkxAnimatedFloat* hFloat = (hkxAnimatedFloat*)variant.m_object;
            object << attrName << hFloat->m_floats[0];
        }
        else if(variant.m_class == &hkxAnimatedVectorClass)
        {
            hkxAnimatedVector* hVector = (hkxAnimatedVector*)variant.m_object;
            jsonxx::Array vectorArray;
            for(int i=0; i<hVector->m_vectors.getSize(); ++i)
            {
                vectorArray << hVector->m_vectors[i];
            }
            object << attrName << vectorArray;
        }
        else if(variant.m_class == &hkxSparselyAnimatedBoolClass)
        {
            hkxSparselyAnimatedBool* hBool = (hkxSparselyAnimatedBool*)variant.m_object;
            object << attrName << (bool)hBool->m_bools[0];
        }
        else if(variant.m_class == &hkxSparselyAnimatedIntClass)
        {
            hkxSparselyAnimatedInt* hInt = (hkxSparselyAnimatedInt*)variant.m_object;
            object << attrName << (int)hInt->m_ints[0];
        }
        else if(variant.m_class == &hkxAnimatedQuaternionClass)
        {
            hkxAnimatedQuaternion* hQuat = (hkxAnimatedQuaternion*)variant.m_object;
            jsonxx::Array vectorArray;
            for(int i=0; i<hQuat->m_quaternions.getSize(); ++i)
            {
                vectorArray << hQuat->m_quaternions[i];
            }
            object << attrName << vectorArray;
        }
        else if(variant.m_class == &hkxAnimatedMatrixClass)
        {
            hkxAnimatedMatrix* hMatrix = (hkxAnimatedMatrix*)variant.m_object;
            jsonxx::Array vectorArray;
            for(int i=0; i<hMatrix->m_matrices.getSize(); ++i)
            {
                vectorArray << hMatrix->m_matrices[i];
            }
            object << attrName << vectorArray;
        }
    }
}