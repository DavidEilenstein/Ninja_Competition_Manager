#include "ncm_obj_challenge.h"

NCM_OBJ_Challenge::NCM_OBJ_Challenge(NCM_OBJ_Competition comp)
{
    Competition = comp;
}

bool NCM_OBJ_Challenge::load()
{
    return true;
}

bool NCM_OBJ_Challenge::save()
{
    return true;
}

bool NCM_OBJ_Challenge::code_load()
{
    return true;
}

bool NCM_OBJ_Challenge::code_parse()
{
    return true;
}

bool NCM_OBJ_Challenge::code_update()
{
    return true;
}
