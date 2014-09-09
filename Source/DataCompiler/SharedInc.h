#pragma once
//engine header
#include "Log.h"
#include "Memory.h"
#include "MemoryPool.h"
#include "MathDefs.h"
#include "Resource.h"
#include <stdio.h>

//std header
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <fstream>
#include <io.h>
#include <algorithm>
#include <bgfx.h>
#include <bx/fpumath.h>
#include <bx/bx.h>
#include <bx/commandline.h>

//components
#include "AnimRig.h"
#include "PhysicsInstance.h"
#include "ProxyInstance.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "Light.h"
#include "JsonParser.h"
#include "Animation.h"
#include "Ragdoll.h"
#include "IK.h"
#include "Graphics.h"
#include "Entity.h"
#include "Shader.h"
#include "Texture.h"
#include "ShadingEnviroment.h"
#include "AnimFSM.h"
#include "Level.h"

#include "DataDef.h"
#include "ShaderInc.h"
#include "Utils.h"
