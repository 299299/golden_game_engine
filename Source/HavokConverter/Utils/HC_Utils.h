#pragma once
#include "stdafx.h"
#include "CommonUtils.h"

void dumpNodeRec(hkxNode* theNode);
void findNodesRec(hkxNode* theNode, const hkClass* theClass, std::vector<hkxNode*>& outNodes);
void findNodesRec(hkxNode* theNode, const std::string& preFix, std::vector<hkxNode*>& outNodes);
Actor_Config* createConfig(const std::string& input, const std::string& outputFolder);
void fill_object_attributes(jsonxx::Object& object, const hkxAttributeGroup* group);
