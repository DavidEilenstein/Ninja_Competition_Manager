#include "ncm_obj_try_list.h"

NCM_OBJ_Try_List::NCM_OBJ_Try_List()
{

}

NCM_OBJ_Try_List::NCM_OBJ_Try_List(QDir dir_saved_in)
{
    load(dir_saved_in);
}

bool NCM_OBJ_Try_List::contains_tryer_name(QString name)
{
    for(size_t t = 0; t < size(); t++)
        if(name == vTries[t].competitor().name())
            return true;

    return false;
}

bool NCM_OBJ_Try_List::contains_tryer_number(int number)
{
    for(size_t t = 0; t < size(); t++)
        if(number == vTries[t].competitor().number())
            return true;

    return false;
}

bool NCM_OBJ_Try_List::add_try(NCM_OBJ_Try challangetry)
{
    if(contains_tryer_name(challangetry.competitor().name()))
        return false;

    vTries.push_back(challangetry);

    return true;
}

bool NCM_OBJ_Try_List::replace_try(NCM_OBJ_Try challangetry)
{
    for(size_t t = 0; t < size(); t++)
    {
        if(vTries[t].competitor().is_name(challangetry.competitor().name()))
        {
            vTries[t] = challangetry;
            return true;
        }
    }

    return false;
}

NCM_OBJ_Competitor_List NCM_OBJ_Try_List::competitors_list()
{
    NCM_OBJ_Competitor_List competitors;
    for(size_t t = 0; t < size(); t++)
        competitors.add_competitor(vTries[t].competitor());

    return competitors;
}

NCM_OBJ_Try NCM_OBJ_Try_List::try_earliest()
{
    if(size() == 0)
        return NCM_OBJ_Try();

    NCM_OBJ_Try try_earliest = vTries[0];
    for(size_t t = 1; t < size(); t++)
        if(vTries[t].earlier_then(try_earliest))
            try_earliest = vTries[t];

    return try_earliest;
}

NCM_OBJ_Try NCM_OBJ_Try_List::try_latest()
{
    if(size() == 0)
        return NCM_OBJ_Try();

    NCM_OBJ_Try try_latest = vTries[0];
    for(size_t t = 1; t < size(); t++)
        if(vTries[t].later_then(try_latest))
            try_latest = vTries[t];

    return try_latest;
}

int NCM_OBJ_Try_List::average_time_start_to_start_ms()
{
    if(size() < 2)
        return 0;

    int dt_ms = abs(try_earliest().time_to_ms(try_latest().recorded()));

    int t_mean = dt_ms / int(size() - 1);
    return t_mean;
}

void NCM_OBJ_Try_List::sort(bool more_is_better)
{
    std::sort(vTries.begin(), vTries.end());
    if(!more_is_better)
        std::reverse(vTries.begin(), vTries.end());
}

bool NCM_OBJ_Try_List::load()
{
    if(!DIR_SavedIn.exists())
        return false;

    DIR_SavedIn.setPath(DIR_SavedIn.path());
    vTries.clear();

    QFileInfoList FIL_Tries = DIR_SavedIn.entryInfoList();
    for(int i = 0; i < FIL_Tries.size(); i++)
    {
        QFileInfo FI_Try = FIL_Tries[i];

        if(FI_Try.exists())
        {
            if(FI_Try.suffix() == "txt" || FI_Try.suffix() == "TXT")
            {
                if(FI_Try.baseName().startsWith("Try_"))
                {
                    NCM_OBJ_Try challengetry;
                    if(challengetry.load(FI_Try.absoluteFilePath()))
                        vTries.push_back(challengetry);
                }
            }
        }
    }

    return true;
}

bool NCM_OBJ_Try_List::save()
{
    if(!DIR_SavedIn.exists())
        QDir().mkdir(DIR_SavedIn.path());
    if(!DIR_SavedIn.exists())
        return false;

    for(size_t c = 0; c < size(); c++)
        vTries[c].save(DIR_SavedIn);

    return false;
}

void NCM_OBJ_Try_List::info_debug()
{
    for(size_t t = 0; t < size(); t++)
        qDebug() << get_try(t).competitor().name() << "-" << get_try(t).score() << get_try(t).challenge().unit();
}
