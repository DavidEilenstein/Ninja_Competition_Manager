#include "ncm_obj_run_list.h"

NCM_OBJ_Run_List::NCM_OBJ_Run_List()
{

}

NCM_OBJ_Run_List::NCM_OBJ_Run_List(QDir dir_saved_in)
{
    load(dir_saved_in);
}

bool NCM_OBJ_Run_List::contains_runner_name(QString name)
{
    for(size_t r = 0; r < size(); r++)
        if(name == vRuns[r].competitor().name())
            return true;

    return false;
}

bool NCM_OBJ_Run_List::contains_runner_number(int number)
{
    for(size_t r = 0; r < size(); r++)
        if(number == vRuns[r].competitor().number())
            return true;

    return false;
}

bool NCM_OBJ_Run_List::add_run(NCM_OBJ_Run run)
{
    if(contains_runner_duplicate(run.competitor()))
        return false;

    vRuns.push_back(run);

    return true;
}

NCM_OBJ_Competitor_List NCM_OBJ_Run_List::competitors_list()
{
    NCM_OBJ_Competitor_List competitors;
    for(size_t r = 0; r < size(); r++)
        competitors.add_competitor(vRuns[r].competitor());

    return competitors;
}

bool NCM_OBJ_Run_List::load()
{
    if(!DIR_SavedIn.exists())
        return false;

    vRuns.clear();

    QFileInfoList FIL_Runs = DIR_SavedIn.entryInfoList();
    for(int i = 0; i < FIL_Runs.size(); i++)
    {
        QFileInfo FI_Run = FIL_Runs[i];

        if(FI_Run.exists())
        {
            if(FI_Run.suffix() == "txt" || FI_Run.suffix() == "TXT")
            {
                if(FI_Run.baseName().startsWith("Run_"))
                {
                    NCM_OBJ_Run run;
                    if(run.load(FI_Run.absoluteFilePath()))
                        vRuns.push_back(run);
                }
            }
        }
    }

    return true;
}

bool NCM_OBJ_Run_List::save()
{
    if(!DIR_SavedIn.exists())
        QDir().mkdir(DIR_SavedIn.path());
    if(!DIR_SavedIn.exists())
        return false;

    for(size_t c = 0; c < size(); c++)
        vRuns[c].save(DIR_SavedIn);

    return false;
}
