
#include "common.sc"

#ifndef DIFFUSE_MODEL
#define DIFFUSE_MODEL 0
#endif

#ifndef SPECULAR_MODEL
#define SPECULAR_MODEL 0
#endif

//#define REFLECTION_MASK
//#define DIFFUSE_ALPHA
//#define TRANSLUCENCY
//#define DIFFUSE_MAPPING
//#define NORMAL_MAPPING
//#define SPECULAR_MAPPING 
//#define RELECTION_MAPPING
//#define LIGHTMAP_MAPING
//#define EMISSIVE_MAPPING
//#define BLEND_NORMAL
//#define THICKNESS
//#define RIM_COLOR
//#define IBL_DIFFUSE
//#define AN_DIR_MAP

#ifdef RELECTION_MAPPING
#ifndef RELECTION_TYPE  //Cube:2D Spherical:2D LatLong:Cube & 2D Spherical:Cube & 2D LatLong
#define RELECTION_TYPE 0 
#endif
#endif

#ifdef IBL_DIFFUSE
#ifndef IBL_DIFFUSE_TYPE //Cube:2D Spherical:2D LatLong:Cube & 2D Spherical:Cube & 2D LatLong
#define IBL_DIFFUSE_TYPE 0 
#endif
// x --> DiffuseIBLBlur      5.0
// y --> DiffuseIBLRotation  0.0
// z --> DiffuseIBLPinching  1.1
// w --> DiffuseIBLIntensity 0.5
uniform vec4 u_diffseIBLParams;
#endif

//*****************************************************
#define AnisotropicRoughness1 0.2
#define AnisotropicSpecularColor vec3(1.0f, 1.0f, 1.0f)
//*****************************************************

//uniforms

#ifdef RIM_COLOR
uniform vec3 u_rimColorInfo; // x -> fresnel min, y -> fresnel max, z -> brightness
#endif

#ifdef TRANSLUCENCY
//vec3 SkinRampOuterColor = vec3(1.0f, 0.64f, 0.25f);
//vec3 SkinRampMediumColor = vec3(1.0f, 0.21f, 0.14f);
//vec3 SkinRampInnerColor = vec3(0.25f, 0.05f, 0.02f);
//float translucentDistortion = 0.2;
//float translucentPower = 3.0;
//float translucentScale = 1.0;
//float translucentMin = 0.0;
uniform vec3 u_skinRampOuterColor;
uniform vec3 u_skinRampMediumColor;
uniform vec3 u_skinRampInnerColor;
uniform vec4 u_translucentInfo;
#endif

// x --> blend normal, y --> normal height, z --> EmissiveIntensity
uniform vec4 u_matParams1;

#ifdef OPACITY
// x --> Opacity, y --> OpacityFresnelMin, z --> OpacityFresnelMax
uniform vec4 u_opacityParams;
#endif

uniform vec3 u_ambientSkyColor;
uniform vec3 u_ambientGroundColor;
uniform vec4 u_diffuseColor;
uniform vec4 u_specularColor;

uniform vec3 u_lightColor[BGFX_CONFIG_MAX_LIGHTS];
uniform vec3 u_lightVec[BGFX_CONFIG_MAX_LIGHTS];
uniform vec4 u_lightInfo[BGFX_CONFIG_MAX_LIGHTS];
uniform int  u_lightType[BGFX_CONFIG_MAX_LIGHTS];

#ifdef DIFFUSE_MAPPING
SAMPLER2D(u_texColor, TEX_COLOR_SLOT);
#endif

#ifdef NORMAL_MAPPING
SAMPLER2D(u_texNormal, TEX_NORMAL_SLOT);
#endif

#ifdef SPECULAR_MAPPING
SAMPLER2D(u_texSpecular, TEX_SPECULAR_SLOT);
#endif

#ifdef RELECTION_MAPPING
#if (RELECTION_TYPE == 0)
SAMPLERCUBE(u_texRelfection, TEX_REFLECTION_SLOT);
#elif(RELECTION_TYPE == 1)
SAMPLER2D(u_texRelfection, TEX_REFLECTION_SLOT);
#else
SAMPLER2D(u_texRelfection, TEX_REFLECTION_SLOT);
#endif
//Reflection
// x --> float ReflectionFresnelMin = 0.0;
// y --> float ReflectionFresnelMax = 0.0;
// z --> float ReflectionBlur = 0.0;
// w --> float ReflectionIntensity = 0.2f;
uniform vec4 u_relectionParams1;
// ------------------------------------------------------
// x --> float ReflectionRotation = 0.0;
// y --> float ReflectionPinching = 1.1;
// z --> bool UseSpecAlphaForReflectionBlur = false; // only 0.0, 1.0
// w --> bool UseSpecColorToTintReflection = false;  // only 0.0, 1.0
uniform vec4 u_relectionParams2;
#endif

#ifdef EMISSIVE_MAPPING
SAMPLER2D(u_texEmissive, TEX_EMISSIVE_SLOT);
#endif

#ifdef LIGHTMAP_MAPING
SAMPLER2D(u_texLightmap, TEX_LIGHTMAP_SLOT);
#endif

#ifdef BLEND_NORMAL
SAMPLER2D(u_texBlendNormalMask, TEX_BLENDNORMAL_SLOT);
#endif

#ifdef IBL_DIFFUSE
#if(IBL_DIFFUSE_TYPE == 0)
SAMPLERCUBE(u_texIBL, TEX_IBL_SLOT);
#elif(IBL_DIFFUSE_TYPE == 1)
SAMPLER2D(u_texIBL, TEX_IBL_SLOT);
#else
SAMPLER2D(u_texIBL, TEX_IBL_SLOT);
#endif
#endif

#ifdef SHADOW
SAMPLER2DSHADOW(u_shadowMap, TEX_SHADOWMAP_SLOT);
uniform vec3  u_shadowParams;
#endif

#ifdef REFLECTION_MASK
SAMPLER2D(u_texReflectionMask, TEX_REFLECTIONMASK_SLOT);
#endif
#ifdef AN_DIR_MAP
SAMPLER2D(u_texAndirMap, TEX_ANISOTROPICDIR_SLOT);
#endif
#ifdef THICKNESS
SAMPLER2D(u_texThickness, TEX_THICKNESS_SLOT);
#endif




//------------------------------------
// Functions
//------------------------------------

float3 RotateVectorYaw(float3 vec, float degreeOfRotation)
{
    float3 rotatedVec = vec;
    float angle = radians(degreeOfRotation);
    rotatedVec.x = ( cos(angle) * vec.x ) - ( sin(angle) * vec.z );
    rotatedVec.z = ( sin(angle) * vec.x ) + ( cos(angle) * vec.z ); 
    return rotatedVec;
}

float3 RotateVectorRoll(float3 vec, float degreeOfRotation)
{
    float3 rotatedVec = vec;
    float angle = radians(degreeOfRotation);
    rotatedVec.y = ( cos(angle) * vec.y ) - ( sin(angle) * vec.z );
    rotatedVec.z = ( sin(angle) * vec.y ) + ( cos(angle) * vec.z ); 
    return rotatedVec;
}

float3 RotateVectorPitch(float3 vec, float degreeOfRotation)
{
    float3 rotatedVec = vec;
    float angle = radians(degreeOfRotation);
    rotatedVec.x = ( cos(angle) * vec.x ) - ( sin(angle) * vec.y );
    rotatedVec.y = ( sin(angle) * vec.x ) + ( cos(angle) * vec.y ); 
    return rotatedVec;
}


// Spot light cone
float lightConeangle(float coneAngle, float coneFalloff, float3 lightVec, float3 lightDir) 
{ 
    // the cone falloff should be equal or bigger then the coneAngle or the light inverts
    // this is added to make manually tweaking the spot settings easier.
    if (coneFalloff < coneAngle)
        coneFalloff = coneAngle;

    float LdotDir = dot(normalize(lightVec), -lightDir); 

    // cheaper cone, no fall-off control would be:
    // float cone = pow(saturate(LdotDir), 1 / coneAngle); 

    // higher quality cone (more expensive):
    float cone = smoothstep( cos(coneFalloff), cos(coneAngle), LdotDir);
    return cone; 
} 


#ifdef TRANSLUCENCY
// This function is a modified version of Colin Barre-Brisebois GDC talk
float3 translucency(float3 thickness, float3 V, float3 L, float3 N, float lightAttenuation, float3 albedoColor)
{
    float3 LightVec = L + (N * u_translucentInfo.x);
    float fLTDot = pow(saturate(dot(V,-LightVec)), u_translucentInfo.y) * u_translucentInfo.z;
    float3 translucence = lightAttenuation * (fLTDot + u_translucentInfo.w) * thickness;

    float3 skinDepthColor = albedoColor * translucence;

    // if the outcolor is set to complete black, we assume user does not want to use ramp
    // We'll then use the above: albedo * translucence
    if (u_skinRampOuterColor.r > 0 && u_skinRampOuterColor.g > 0 && u_skinRampOuterColor.b > 0)
    {
        if (translucence.r > 0.9)
        {
            skinDepthColor = lerp( u_skinRampOuterColor, float3(1,1,1), (translucence.r-0.9)/0.1);
        }
        else if (translucence.r > 0.7)
        {
            skinDepthColor = lerp( u_skinRampMediumColor, u_skinRampOuterColor, (translucence.r-0.7)/0.2);
        }
        else if (translucence.r > 0.4)
        {
            skinDepthColor = lerp( u_skinRampInnerColor, u_skinRampMediumColor, (translucence.r-0.4)/0.3);
        }
        else
        {
            skinDepthColor = lerp( float3(0,0,0), u_skinRampInnerColor, translucence.r/0.4);
        }

#ifdef GAMMA_CORRECTION
        skinDepthColor = toLinear(skinDepthColor);
#endif
    }

    return skinDepthColor;
}
#endif

// This function is from Nvidia's Human Head demo
float fresnelReflectance( float3 H, float3 V, float F0 )  
{
    float base = 1.0 - dot( V, H );
    float exponential = pow( base, 5.0 );  
    return exponential + F0 * ( 1.0 - exponential );
}

// This function is from Nvidia's Human Head demo
float beckmannBRDF(float ndoth, float m)
{
  float alpha = acos( ndoth );  
  float ta = tan( alpha );  
  float val = 1.0/(m*m*pow(ndoth,4.0)) * exp(-(ta*ta)/(m*m));
  return val;  
}

// This function is from Nvidia's Human Head demo
float3 KelemenSzirmaykalosSpecular(float3 N, float3 L, float3 V, float roughness, float3 specularColorIn)
{
    float3 result = float3(0.0, 0.0, 0.0);
    float ndotl = dot(N, L);
    if (ndotl > 0.0)
    {
        float3 h = L + V;
        float3 H = normalize( h );
        float ndoth = dot(N, H);
        float PH = beckmannBRDF(ndoth, roughness);
        float F = fresnelReflectance( H, V, 0.028 );
        float frSpec = max( PH * F / dot( h, h ), 0 ); 
        result = ndotl * specularColorIn * frSpec;
    }
    return result;
}

// This function is from John Hable's Siggraph talk
float3 blendedNormalDiffuse(float3 L, float3 Ng, float3 Nm, float softenMask, float shadow, float blendNorm)
{
    float redBlend = lerp(0, 0.9, softenMask);
    float redSoften = redBlend * blendNorm;
    float blueBlend = lerp(0, 0.35, softenMask);
    float blueSoften = blueBlend * blendNorm;
    
    float DNr = (saturate(dot(Ng, L) * (1 - redSoften) + redSoften) * shadow);//diffuse using geometry normal
    float DNb = (saturate(dot(Nm, L) * (1 - blueSoften) + blueSoften) * shadow);//diffuse using normal map
    float R = lerp(DNb, DNr, redBlend);//final diffuse for red channel using more geometry normal
    float B = lerp(DNb, DNr, blueBlend);//final diffuse for blue using more normal map
    float3 finalDiffuse = float3(R, B, B);
    float cyanReduction = 0.03 + R;
    finalDiffuse.gb = min(cyanReduction, finalDiffuse.gb);
    return finalDiffuse;
}

//Ward anisotropic specular lighting, modified to support anisotropic direction map (aka Comb or Flow map)
float3 WardAniso(float3 N, float3 H, float NdotL, float NdotV, float NdotH, float Roughness1, float Roughness2, float3 anisotropicDir)
{
    float FirstTerm = saturate( 1.0f / sqrt(NdotL * NdotV) );
    float SecondTerm = saturate( 1.0f / (12.56 * Roughness1 * Roughness2) );
    
    float3 Direction = anisotropicDir; // {0.0f, 1.0f, 0.0};
    float3 X = normalize(cross(N, Direction));
    float3 Y = normalize(cross(N, X));
    float XdotH = dot(X, H);
    float YdotH = dot(X, Y);
    float A = -2.0f * (pow((XdotH / Roughness1) , 2)) + pow((YdotH / Roughness2) , 2);
    float B = 1.0f + NdotH;
    float ThirdTerm = saturate( exp(A/B) );
    
    return float3(FirstTerm, SecondTerm, ThirdTerm);
}

#ifdef SHADOW
float hardShadow(sampler2DShadow _sampler, vec4 _shadowCoord, float _bias)
{
    vec3 texCoord = _shadowCoord.xyz/_shadowCoord.w;
    return shadow2D(_sampler, vec3(texCoord.xy, texCoord.z - _bias) );
}

float PCF(sampler2DShadow _sampler, vec4 _shadowCoord, float _bias, vec2 _texelSize)
{
    vec2 texCoord = _shadowCoord.xy/_shadowCoord.w;

    bool outside = any(greaterThan(texCoord, vec2_splat(1.0)))
                || any(lessThan   (texCoord, vec2_splat(0.0)))
                 ;

    if (outside)
    {
        return 1.0;
    }

    float result = 0.0;
    vec2 offset = _texelSize * _shadowCoord.w;

    result += hardShadow(_sampler, _shadowCoord + vec4(vec2(-1.5, -1.5) * offset, 0.0, 0.0), _bias);
    result += hardShadow(_sampler, _shadowCoord + vec4(vec2(-1.5, -0.5) * offset, 0.0, 0.0), _bias);
    result += hardShadow(_sampler, _shadowCoord + vec4(vec2(-1.5,  0.5) * offset, 0.0, 0.0), _bias);
    result += hardShadow(_sampler, _shadowCoord + vec4(vec2(-1.5,  1.5) * offset, 0.0, 0.0), _bias);

    result += hardShadow(_sampler, _shadowCoord + vec4(vec2(-0.5, -1.5) * offset, 0.0, 0.0), _bias);
    result += hardShadow(_sampler, _shadowCoord + vec4(vec2(-0.5, -0.5) * offset, 0.0, 0.0), _bias);
    result += hardShadow(_sampler, _shadowCoord + vec4(vec2(-0.5,  0.5) * offset, 0.0, 0.0), _bias);
    result += hardShadow(_sampler, _shadowCoord + vec4(vec2(-0.5,  1.5) * offset, 0.0, 0.0), _bias);

    result += hardShadow(_sampler, _shadowCoord + vec4(vec2(0.5, -1.5) * offset, 0.0, 0.0), _bias);
    result += hardShadow(_sampler, _shadowCoord + vec4(vec2(0.5, -0.5) * offset, 0.0, 0.0), _bias);
    result += hardShadow(_sampler, _shadowCoord + vec4(vec2(0.5,  0.5) * offset, 0.0, 0.0), _bias);
    result += hardShadow(_sampler, _shadowCoord + vec4(vec2(0.5,  1.5) * offset, 0.0, 0.0), _bias);

    result += hardShadow(_sampler, _shadowCoord + vec4(vec2(1.5, -1.5) * offset, 0.0, 0.0), _bias);
    result += hardShadow(_sampler, _shadowCoord + vec4(vec2(1.5, -0.5) * offset, 0.0, 0.0), _bias);
    result += hardShadow(_sampler, _shadowCoord + vec4(vec2(1.5,  0.5) * offset, 0.0, 0.0), _bias);
    result += hardShadow(_sampler, _shadowCoord + vec4(vec2(1.5,  1.5) * offset, 0.0, 0.0), _bias);

    return result / 16.0;
}
#endif

vec4 CalculateLight_Direction(float3 lightDir, float3 lightColor, float4 lightInfo, 
                              float3 vertWorldPos, float3 vertexNormal, float3 normal, float3 diffuseColorIn, 
                              float3 eyeVec, float roughness, float3 specularColorIn, float3 thickness, float softenMask, 
                              float rim, float glossiness, float opacity, float4 anisotropicDir, vec4 _shadowCoord )
{
    vec4 OUT = vec4(0, 0, 0, 0);

    float lightFallOff = lightInfo.x;
    float lightIntensity = lightInfo.y;
    float lightConeAngle = lightInfo.z;
    float lightAtten = lightInfo.w;

    float3 lightVec = -lightDir;
    float3 L = normalize(lightVec); 

    // Diffuse:
    float3 diffuseColor = float3(0,0,0);
#if(DIFFUSE_MODEL == 0) // Lambert:
    diffuseColor = saturate(dot(normal, L)) * diffuseColorIn;
#elif(DIFFUSE_MODEL == 1) // Soften Diffuse, aka Blended Normal (skin):
    diffuseColor = blendedNormalDiffuse(L, vertexNormal, normal, softenMask, 1.0, u_matParams1.x) * diffuseColorIn;
#elif(DIFFUSE_MODEL == 2)
    /// lerp to shift the shadow boundary for a softer look:
    diffuseColor = saturate( lerp(0.25, 1.0, dot(normal, L) ) ) * diffuseColorIn;
#endif

    float3 rimColor = rim * saturate(dot(normal, -L));
    float3 specularColor = float3(0,0,0);

#if(SPECULAR_MODEL == 0) // BLINN
    float3 H = normalize(L + eyeVec); // half angle
    float NdotH = saturate( dot(normal, H) );
    specularColor = specularColorIn * pow(NdotH, glossiness);
    specularColor *= saturate( dot(normal, L) );    // prevent spec leak on back side of model
#elif(SPECULAR_MODEL == 1) // Kelemen-Szirmay-Kalos (skin):
    specularColor = KelemenSzirmaykalosSpecular(normal, L, eyeVec, roughness, specularColorIn);
#elif(SPECULAR_MODEL == 2) // Ward Anisotropic (brushed metal/hair):
    float3 H = normalize(L + eyeVec);
    float NdotL = saturate( dot(normal, L) );
    float NdotH = dot(normal, H);
    float NdotV = dot(normal, eyeVec);

    float3 anisoSpecularColor = specularColorIn;
    float anisotropicRoughness2 = 0.3;
    float3 aniso = WardAniso(normal, H, NdotL, NdotV, NdotH, AnisotropicRoughness1, anisotropicRoughness2, anisotropicDir.xyz);
    anisoSpecularColor = (AnisotropicSpecularColor * aniso.x + specularColorIn * aniso.y) * aniso.z;    // give the user the option for 2 colors
    anisoSpecularColor *= NdotL;    // prevent spec leak on back side of model
    specularColor = anisoSpecularColor;
#endif
    // compensate diffuse and specular color with various light settings:
    specularColor *= (lightColor * lightIntensity);
    diffuseColor *= (lightColor * lightIntensity);

#ifdef SHADOW
    vec2 texelSize = vec2_splat(1.0/SHADOWMAP_SIZE);
    float visibility = PCF(u_shadowMap, _shadowCoord, u_shadowParams.y, texelSize);
    specularColor *= visibility;
    diffuseColor *= visibility;
#endif

    // Translucency should be added on top after shadow and cone:
#ifdef TRANSLUCENCY
    float3 transColor = translucency(thickness, eyeVec, L, vertexNormal, 1.0f, diffuseColorIn);
    diffuseColor += transColor;
#endif
    // Add specular and rim light on top of final output color
    // multiply OUT.Color with opacity since we are using a pre-multiplied alpha render state
    // if we don't do this, the rim may have halo's around it when the object is fully transparent
    OUT.rgb += diffuseColor;
    OUT.rgb *= opacity;
    OUT.rgb += specularColor + rimColor;
    // Output specular and rim for opacity:
    OUT.a = dot(saturate(specularColor), float3(0.3f, 0.6f, 0.1f)) + rimColor.r; 
    return OUT;
}


// 0 direction 1 spot 2 point
vec4 CalculateLight_Point(  float3 lightPos, float3 lightColor, float4 lightInfo,
                            float3 vertWorldPos, float3 vertexNormal, float3 normal, float3 diffuseColorIn, 
                            float3 eyeVec, float roughness, float3 specularColorIn, float3 thickness, float softenMask, 
                            float rim, float glossiness, float opacity, float4 anisotropicDir )
{
    vec4 OUT = vec4(0, 0, 0, 0);

    float lightFallOff = lightInfo.x;
    float lightIntensity = lightInfo.y;
    float lightConeAngle = lightInfo.z;
    float lightAtten = lightInfo.w;

    float3 lightVec = lightPos - vertWorldPos;
    float3 L = normalize(lightVec); 

    // Diffuse:
    float3 diffuseColor = float3(0,0,0);
#if(DIFFUSE_MODEL == 0) // Lambert:
    diffuseColor = saturate(dot(normal, L)) * diffuseColorIn;
#elif(DIFFUSE_MODEL == 1) // Soften Diffuse, aka Blended Normal (skin):
    diffuseColor = blendedNormalDiffuse(L, vertexNormal, normal, softenMask, 1.0, u_matParams1.x) * diffuseColorIn;
#elif(DIFFUSE_MODEL == 2) /// lerp to shift the shadow boundary for a softer look:
    diffuseColor = saturate( lerp(0.25, 1.0, dot(normal, L) ) ) * diffuseColorIn;
#endif

    float3 rimColor = rim * saturate(dot(normal, -L));
    float3 specularColor = float3(0,0,0);

#if(SPECULAR_MODEL == 0) // BLINN
    float3 H = normalize(L + eyeVec); // half angle
    float NdotH = saturate( dot(normal, H) );
    specularColor = specularColorIn * pow(NdotH, glossiness);
    specularColor *= saturate( dot(normal, L) );    // prevent spec leak on back side of model
#elif(SPECULAR_MODEL == 1) // Kelemen-Szirmay-Kalos (skin):
    specularColor = KelemenSzirmaykalosSpecular(normal, L, eyeVec, roughness, specularColorIn);
#elif(SPECULAR_MODEL == 2) // Ward Anisotropic (brushed metal/hair):
    float3 H = normalize(L + eyeVec);
    float NdotL = saturate( dot(normal, L) );
    float NdotH = dot(normal, H);
    float NdotV = dot(normal, eyeVec);

    float3 anisoSpecularColor = specularColorIn;
    float anisotropicRoughness2 = 0.3;
    float3 aniso = WardAniso(normal, H, NdotL, NdotV, NdotH, AnisotropicRoughness1, anisotropicRoughness2, anisotropicDir.xyz);
    anisoSpecularColor = (AnisotropicSpecularColor * aniso.x + specularColorIn * aniso.y) * aniso.z;    // give the user the option for 2 colors
    anisoSpecularColor *= NdotL;    // prevent spec leak on back side of model
    specularColor = anisoSpecularColor;
#endif

    // Light Attenuation:
    bool enableAttenuation = lightAtten > 0.0001f;
    float attenuation = lerp(1.0, 1 / pow(length(lightVec), lightAtten), enableAttenuation);

    // compensate diffuse and specular color with various light settings:
    specularColor *= (lightColor * lightIntensity * attenuation);
    diffuseColor *= (lightColor * lightIntensity * attenuation);

    // Translucency should be added on top after shadow and cone:
#ifdef TRANSLUCENCY
    float3 transColor = translucency(thickness, eyeVec, L, vertexNormal, attenuation, diffuseColorIn);
    diffuseColor += transColor;
#endif

    // Add specular and rim light on top of final output color
    // multiply OUT.Color with opacity since we are using a pre-multiplied alpha render state
    // if we don't do this, the rim may have halo's around it when the object is fully transparent
    OUT.rgb += diffuseColor;
    OUT.rgb *= opacity;
    OUT.rgb += specularColor + rimColor;
    // Output specular and rim for opacity:
    OUT.a = dot(saturate(specularColor), float3(0.3f, 0.6f, 0.1f)) + rimColor.r;
    return OUT;
}



vec4 CalculateLight_Spot(   float3 lightDir, float3 lightPos, float3 lightColor, float4 lightInfo,
                            float3 vertWorldPos, float3 vertexNormal, float3 normal, float3 diffuseColorIn, 
                            float3 eyeVec, float roughness, float3 specularColorIn, float3 thickness, float softenMask, 
                            float rim, float glossiness, float opacity, float4 anisotropicDir )
{
    vec4 OUT = vec4(0, 0, 0, 0);

    float lightFallOff = lightInfo.x;
    float lightIntensity = lightInfo.y;
    float lightConeAngle = lightInfo.z;
    float lightAtten = lightInfo.w;

    float3 lightVec = lightPos - vertWorldPos;
    float3 L = normalize(lightVec); 

    // Diffuse:
    float3 diffuseColor = float3(0,0,0);
#if(DIFFUSE_MODEL == 0) // Lambert:
    diffuseColor = saturate(dot(normal, L)) * diffuseColorIn;
#elif(DIFFUSE_MODEL == 1) // Soften Diffuse, aka Blended Normal (skin):
    diffuseColor = blendedNormalDiffuse(L, vertexNormal, normal, softenMask, 1.0, u_matParams1.x) * diffuseColorIn;
#elif(DIFFUSE_MODEL == 2)
    /// lerp to shift the shadow boundary for a softer look:
    diffuseColor = saturate( lerp(0.25, 1.0, dot(normal, L) ) ) * diffuseColorIn;
#endif

    float3 rimColor = rim * saturate(dot(normal, -L));
    float3 specularColor = float3(0,0,0);

#if(SPECULAR_MODEL == 0) // BLINN
    float3 H = normalize(L + eyeVec); // half angle
    float NdotH = saturate( dot(normal, H) );
    specularColor = specularColorIn * pow(NdotH, glossiness);
    specularColor *= saturate( dot(normal, L) );    // prevent spec leak on back side of model
#elif(SPECULAR_MODEL == 1) // Kelemen-Szirmay-Kalos (skin):
    specularColor = KelemenSzirmaykalosSpecular(normal, L, eyeVec, roughness, specularColorIn);
#elif(SPECULAR_MODEL == 2) // Ward Anisotropic (brushed metal/hair):
    float3 H = normalize(L + eyeVec);
    float NdotL = saturate( dot(normal, L) );
    float NdotH = dot(normal, H);
    float NdotV = dot(normal, eyeVec);

    float3 anisoSpecularColor = specularColorIn;
    float anisotropicRoughness2 = 0.3;
    float3 aniso = WardAniso(normal, H, NdotL, NdotV, NdotH, AnisotropicRoughness1, anisotropicRoughness2, anisotropicDir.xyz);
    anisoSpecularColor = (AnisotropicSpecularColor * aniso.x + specularColorIn * aniso.y) * aniso.z;    // give the user the option for 2 colors
    anisoSpecularColor *= NdotL;    // prevent spec leak on back side of model
    specularColor = anisoSpecularColor;
#endif

    // Light Attenuation:
    bool enableAttenuation = lightAtten > 0.0001f;
    float attenuation = lerp(1.0, 1 / pow(length(lightVec), lightAtten), enableAttenuation);

    // compensate diffuse and specular color with various light settings:
    specularColor *= (lightColor * lightIntensity * attenuation);
    diffuseColor *= (lightColor * lightIntensity * attenuation);

    // Spot light Cone Angle:
    float angle = lightConeangle(lightConeAngle, lightFallOff, lightVec, lightDir);
    diffuseColor *= angle;
    specularColor *= angle;

    // Translucency should be added on top after shadow and cone:
#ifdef TRANSLUCENCY
    float3 transColor = translucency(thickness, eyeVec, L, vertexNormal, attenuation, diffuseColorIn);
    diffuseColor += transColor;
#endif

    // Add specular and rim light on top of final output color
    // multiply OUT.Color with opacity since we are using a pre-multiplied alpha render state
    // if we don't do this, the rim may have halo's around it when the object is fully transparent
    OUT.rgb += diffuseColor;
    OUT.rgb *= opacity;
    OUT.rgb += specularColor + rimColor;
    // Output specular and rim for opacity:
    OUT.a = dot(saturate(specularColor), float3(0.3f, 0.6f, 0.1f)) + rimColor.r;
    return OUT;
}

void main()
{
    //**************************************************************
    float SpecPower = u_specularColor.a;
    vec3 diffuseColor = u_diffuseColor.rgb;
    float diffuseAlpha = u_diffuseColor.a;

    float EmissiveIntensity = u_matParams1.z;
    vec3 thickness = vec3(1,1,1);
    float softenMask = 1.0f;
    //**************************************************************

#ifdef DIFFUSE_MAPPING
    //**************************************************************
    //DIFFUSE　MAP
    vec4 diffuseMap = texture2D(u_texColor, v_texcoord0);
#ifdef GAMMA_CORRECTION
    diffuseColor *= toLinear(diffuseMap.rgb) * u_diffuseColor.rgb;
#else
    diffuseColor *= diffuseMap.rgb * u_diffuseColor.rgb;
#endif

#ifdef DIFFUSE_ALPHA
    diffuseAlpha = diffuseMap.a;
#endif

#ifdef ALPHA_MASK
    clip(diffuseMap.a < ALPHA_THRESHOLD ? -1:1);
#endif
    //**************************************************************
#endif

    vec3 N = v_normal;//normalize(v_normal);
    vec3 Nw = N;
    vec3 V = v_view;//normalize(v_view.xyz);

#ifdef NORMAL_MAPPING
    //**************************************************************
    //NORMAL MAP
    vec3 T = v_tangent;
    vec3 Bn = v_binormal;//cross(N, T);
    mat3 tbn = mat3(v_tangent, v_binormal, N);
    vec3 normalMap;
    normalMap = texture2D(u_texNormal, v_texcoord0).xyz;
    //normalMap.xy = normalMap.xy * 2.0 - 1.0;
    //normalMap.z = sqrt(1.0 - dot(normalMap.xy, normalMap.xy) );
    normalMap.xy *= u_matParams1.y; 
    normalMap = mul(normalMap.xyz, tbn);
    N = normalize(normalMap.rgb);
    //**************************************************************
#endif

    //**************************************************************
    //SPECULAR MAP
    float glossiness =  max(1.0, SpecPower);
    float specularAlpha = 1.0;
    vec3 specularColor = u_specularColor.rgb;
#ifdef SPECULAR_MAPPING
    {
        vec4 specularMap = texture2D(u_texSpecular, v_texcoord0);
        specularColor *= toLinear(specularMap.rgb);
        specularAlpha = specularMap.a;
        glossiness *= (specularMap.a + 1);
    }
#endif
    //**************************************************************

#ifdef NORMAL_MAPPING
    float4 anisotropicDir = float4(T, 1);   // alpha is the blinn-aniso mask
#else
    float4 anisotropicDir = float4(0, 0, 0, 1);
#endif

#ifdef AN_DIR_MAP
    {
        anisotropicDir = texture2D(u_texAndirMap, v_texcoord0);
        anisotropicDir.xyz = anisotropicDir.xyz * 2 - 1;    // unpack
    }
#endif

    //**************************************************************
    //RELECTION　MASK
    // divide by 100 so we get more user friendly values when switching from Phong based on slider range.
    float roughness = min( SpecPower/100.0f, 1) * specularAlpha;
    // flip so it is more user friendly when switching from Phong     
    roughness = 1.0f-roughness;
#ifdef RELECTION_MAPPING
    float reflectFresnel = saturate((saturate(1.0f - dot(N, V))-u_relectionParams1.x)/(u_relectionParams1.y - u_relectionParams1.x));
    float3 reflectionColor = lerp(float3(1,1,1), specularColor, u_relectionParams2.w) * u_relectionParams1.w * reflectFresnel;
#else
    float3 reflectionColor = float3(0, 0, 0);
#endif

#ifdef REFLECTION_MASK
    {
        float4 ReflectionMaskSample = texture2D(u_texReflectionMask, v_texcoord0);
        reflectionColor *=  ReflectionMaskSample.r;
    }
#endif
    //**************************************************************


    //**************************************************************
    //REFLECTION MAP
#ifdef OPACITY
    float opacityFresnel = saturate( (saturate(1.0f - dot(N, V)) - u_opacityParams.y)/(u_opacityParams.z - u_opacityParams.y) );
    float opacity = saturate(diffuseAlpha * u_opacityParams.x * opacityFresnel);
#else
    float opacity = 1.0f;
#endif

    float3 reflectColorTotal = reflectionColor;
#ifdef RELECTION_MAPPING
    {
        // below "8" should really be the number of mip maps levels in the cubemap, 
        // but since we don't know this (Maya is not passing this to us) we hard code it.
        float ReflectionMipLevel = (u_relectionParams1.z + (8.0 * (u_relectionParams2.z * (1 - specularAlpha))));

        float3 reflectMapColor = float3(0,0,0);
        vec4 reflectionMap;

    #if(RELECTION_TYPE == 0) //CUBE
        float3 reflectionVector = reflect(-V, N);
        reflectionVector = RotateVectorYaw(reflectionVector, u_relectionParams2.x);
        reflectionVector = normalize(reflectionVector);
        reflectionMap = textureCubeLod(u_texReflection, reflectionVector, ReflectionMipLevel);
        reflectMapColor += toLinear(reflectionMap.rgb);
    #elif(RELECTION_TYPE == 1) // 2D SPHERICAL
        float3 reflectionVector = reflect(V, N);
        reflectionVector = RotateVectorYaw(reflectionVector, u_relectionParams2.x);
        reflectionVector = normalize(reflectionVector);
        float2 sphericalUVs = SphericalReflectionUVFunction(reflectionVector, u_relectionParams2.y);
        reflectionMap = texture2D(u_texReflection, sphericalUVs, ReflectionMipLevel);
        reflectMapColor += toLinear(reflectionMap.rgb);
    #elif(RELECTION_TYPE == 2) // 2D LATLONG
        float3 reflectionVector = reflect(-V, N);
        reflectionVector = RotateVectorYaw(reflectionVector, u_relectionParams2.x);
        reflectionVector = normalize(reflectionVector);
        float2 latLongUVs = Latlong(reflectionVector);
        reflectionMap = texture2D(u_texReflection, latLongUVs, ReflectionMipLevel);
        reflectMapColor += toLinear(reflectionMap.rgb);
    #endif
        reflectColorTotal *= reflectMapColor;
    }
#endif
    //**************************************************************

    //**************************************************************
    // AMBIENT COLOR
    float ambientUpAxis = N.y;
    vec3 ambientColor = (lerp(u_ambientGroundColor, u_ambientSkyColor, ((ambientUpAxis * 0.5) + 0.5)) * diffuseColor);
    //**************************************************************


    //**************************************************************
    // EMISSIVE MAP
    // emissive after AO to make sure AO does not block glow
#ifdef EMISSIVE_MAPPING
    {
        vec4 EmissiveColor = texture2D(u_texEmissive, v_texcoord0);
        ambientColor += EmissiveColor.rgb * EmissiveIntensity;
    }
#endif
    //**************************************************************

    //**************************************************************
#ifdef LIGHTMAP_MAPING
    {
        // We assume this texture does not need to be converted to linear space
        vec3 lightmapColor = texture2D(u_texLightmap, v_texcoord1).rgb;
        diffuseColor *= lightmapColor;
    }
#endif
    //**************************************************************

    //**************************************************************
    // THICKNESS TEXTURE
#ifdef THICKNESS
    thickness = texture2D(u_texThickness, v_texcoord0).rgb;
#endif
    //**************************************************************

    //**************************************************************
    // BLENDNORMAL TEXTURE
#ifdef BLEND_NORMAL
    softenMask = texture2D(u_texBlendNormalMask, v_texcoord0).r;
#endif
    //**************************************************************

    // Rim light:
    // This will only work well for polygons that are facing the camera
    //**********************************************************
    // RIM COLOR
#ifdef RIM_COLOR
    float rim = saturate((saturate(1.0f - dot(N, V))-u_rimColorInfo.x)/(max(u_rimColorInfo.y, u_rimColorInfo.x)  - u_rimColorInfo.x));
    rim *= u_rimColorInfo.z * max(specularAlpha, 0.2);
#else
    float rim = 0;
#endif
    //**********************************************************

    vec4 _shadowCoord = vec4(0, 0, 0, 0);
#ifdef SHADOW
    _shadowCoord = v_shadowcoord;
#endif
    vec4 light0 = CalculateLight_Direction( u_lightVec[0], u_lightColor[0], u_lightInfo[0],
                                            v_wpos.xyz, Nw, N, diffuseColor, 
                                            V, roughness, specularColor,
                                            thickness, softenMask, rim, glossiness, opacity, anisotropicDir, _shadowCoord );
#if 0
    vec4 light1 = CalculateLight_Point(   u_lightVec[1], u_lightColor[1], u_lightInfo[1],
                                        v_wpos.xyz, Nw, N, diffuseColor, 
                                        V, roughness, specularColor,
                                        thickness, softenMask, rim, glossiness, opacity, anisotropicDir );

    vec4 light2 = CalculateLight_Point(   u_lightVec[2], u_lightColor[2], u_lightInfo[2],
                                        v_wpos.xyz, Nw, N, diffuseColor, 
                                        V, roughness, specularColor,
                                        thickness, softenMask, rim, glossiness, opacity, anisotropicDir );
#endif    
    vec3 lightTotal =  light0.rgb;// + light1.rgb + light2.rgb;


    // Diffuse IBL
#ifdef IBL_DIFFUSE
    float diffuseIBLMipLevel = u_diffseIBLParams.x;
    // We use the world normal to sample the lighting texture
    float3 diffuseIBLVec = RotateVectorYaw(N, u_diffseIBLParams.y);
    diffuseIBLVec = normalize(diffuseIBLVec);

    float3 diffuseIBLcolor = float3(0,0,0);

    #if(IBL_DIFFUSE_TYPE == 0) // CUBE
        diffuseIBLcolor = toLinear(textureCubeLod(u_texIBL, diffuseIBLVec, diffuseIBLMipLevel).rgb);
    #elif(IBL_DIFFUSE_TYPE == 1) // 2D SPHERICAL
        float2 sphericalUVs = SphericalReflectionUVFunction(-diffuseIBLVec, u_diffseIBLParams.z);
        diffuseIBLcolor = toLinear(texture2D(u_texIBL, sphericalUVs, diffuseIBLMipLevel).rgb);
    #elif(IBL_DIFFUSE_TYPE == 2) // 2D LATLONG
        float2 latLongUVs = Latlong(diffuseIBLVec);
        diffuseIBLcolor = toLinear(texture2D(u_texIBL, latLongUVs, diffuseIBLMipLevel).rgb);
    #endif

    // The Diffuse IBL gets added to what the dynamic lights have already illuminated
    // The Diffuse IBL texture should hold diffuse lighting information, so we multiply the diffuseColor (diffuseTexture) by the IBL
    // IBL intensity allows the user to specify how much the IBL contributes on top of the dynamic lights
    // Also compensate for pre-multiplied alpha
    lightTotal += diffuseColor * diffuseIBLcolor * u_diffseIBLParams.w * opacity;
#endif

    // ambient must also compensate for pre-multiplied alpha
    vec3 result = (ambientColor * opacity) + reflectColorTotal;
    result += lightTotal;

#ifndef HDR
#ifdef GAMMA_CORRECTION
    result = toGamma(result);
#endif
#endif

    // final alpha:
    float transparency = opacity;
    float cubeTransparency = dot(saturate(reflectColorTotal), vec3(0.3, 0.6, 0.1));
    float specTotal = light0.a;// + light1.a + light2.a;
    transparency += (cubeTransparency + specTotal);
    transparency = saturate(transparency);  // keep 0-1 range

    //dont use rgbe or loguv for hdr since it will ruin alpha.
    gl_FragData[0] = vec4(result, transparency);
}
