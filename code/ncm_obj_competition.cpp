#include "ncm_obj_competition.h"

NCM_OBJ_Competition::NCM_OBJ_Competition()
{
    vDIR_CompetitionSubdirs.resize(COMP_DIR_NUMBER_OF, QDir());
}

void NCM_OBJ_Competition::create()
{
    if(!DIR_Competition.exists())
        QDir().mkdir(DIR_Competition.path());

    for(int d = 0; d < COMP_DIR_NUMBER_OF; d++)
    {
        vDIR_CompetitionSubdirs[d].setPath(DIR_Competition.path() + "/" + QSL_CompDirs[d]);
        if(!vDIR_CompetitionSubdirs[d].exists())
            QDir().mkdir(vDIR_CompetitionSubdirs[d].path());
    }
}

void NCM_OBJ_Competition::load()
{
    for(int d = 0; d < COMP_DIR_NUMBER_OF; d++)
        vDIR_CompetitionSubdirs[d].setPath(DIR_Competition.path() + "/" + QSL_CompDirs[d]);
}

bool NCM_OBJ_Competition::is_valid()
{
    if(!DIR_Competition.exists())
        return false;

    for(int d = 0; d < COMP_DIR_NUMBER_OF; d++)
    {
        if(!vDIR_CompetitionSubdirs[d].exists())
        {
            return false;
        }
    }

    return true;
}

