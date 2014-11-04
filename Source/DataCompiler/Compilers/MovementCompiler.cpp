#include "MovementCompiler.h"

MovementCompiler::MovementCompiler()
{

}

MovementCompiler::~MovementCompiler()
{

}

bool MovementCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);

    MovementResource move;
    memset(&move, 0x00, sizeof(move));

    move.m_moveState = JSON_GetEnum(root.GetValue("state"), movement_names);
    //------------------------------------------------------
    //
    //------------------------------------------------------
    return write_file(m_output, &move, sizeof(move));
}