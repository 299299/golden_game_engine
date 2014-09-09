#pragma once
#include <stdint.h>


#define SAFE_DELETE(ptr)                            delete (ptr); (ptr) = 0;
#define SAFE_DELETE_ARRAY(ptr)                      delete[] (ptr); (ptr) = 0;
#define SAFE_REMOVEREF(ptr)                         if(ptr) { (ptr)->removeReference(); (ptr) = 0;}
//no template
#define SAFE_DESTRUCTOR(ptr, class_name)            if(ptr) { (ptr)->~class_name(); (ptr) = 0;}

#define INVALID_U8          (0xFF)
#define INVALID_U16         (0xFFFF)
#define INVALID_U32         (0xFFFFFFFF)

typedef uint32_t ID;
#define INVALID_ID          INVALID_U32

#define INDEX_MASK                  0xffff
#define NEW_OBJECT_ID_ADD           0x10000

struct Index 
{
    ID              m_id;
    uint16_t        m_index;
    uint16_t        m_next;
};

#define LOAD_OBJECT(container, objectClassName)\
                 (objectClassName*)container->findObjectByType( objectClassName##Class.getName() );


#define RGBA(r,g,b,a) (((unsigned)r) | ((unsigned)g << 8) | ((unsigned)b << 16) | ((unsigned)a << 24))
#define RGBCOLOR(r,g,b) RGBA(r,g,b,255)
#define RGBA_TO_FLOAT(rgba, color)\
    color[0] = (rgba & 0x000000FF) / 255.0f;\
    color[1] = ((rgba & 0x0000FF00) >> 8) / 255.0f;\
    color[2] = ((rgba & 0x00FF0000) >> 16) / 255.0f;\
    color[3] = ((rgba & 0xFF000000) >> 24) / 255.0f;

#define ADD_BITS(value, bit)                (value |= bit)
#define REMOVE_BITS(value, bit)             (value &= ~bit)
#define HAS_BITS(value, bit)                (value & bit)
#define NOT_HAS_BITS(value, bit)            (value & bit == 0)

#define ENGINE_ALIGN(_alignment)    __declspec(align(_alignment))
#define ENGINE_NATIVE_ALIGN         ENGINE_ALIGN(16)

#define DECLARE_RESOURCE(name)\
        static const char* getName() {return #name; } \
        static const StringId& getType() { static StringId type(getName()); return type; };


#ifdef _DEBUG
//#define DUMP_RESOURCE
#endif

#ifndef _RETAIL
#define RESOURCE_RELOAD
#endif



