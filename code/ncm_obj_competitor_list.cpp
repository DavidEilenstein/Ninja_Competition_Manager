#include "ncm_obj_competitor_list.h"

NCM_OBJ_Competitor_List::NCM_OBJ_Competitor_List()
{

}

NCM_OBJ_Competitor_List::NCM_OBJ_Competitor_List(QDir dir_saved_in)
{
    load(dir_saved_in);
}

bool NCM_OBJ_Competitor_List::contains_name(QString name)
{
    for(size_t c = 0; c < count(); c++)
    {
        if(name == vCompetitors[c].name())
        {
            qDebug() << name << "equals" << vCompetitors[c].name();
            return true;
        }
    }

    return false;
}

bool NCM_OBJ_Competitor_List::contains_number(int number)
{
    for(size_t c = 0; c < count(); c++)
        if(number == vCompetitors[c].number())
            return true;

    return false;
}

bool NCM_OBJ_Competitor_List::add_competitor(NCM_OBJ_Competitor competitor)
{
    if(contains_duplicate(competitor))
        return false;

    vCompetitors.push_back(competitor);

    return true;
}

bool NCM_OBJ_Competitor_List::load()
{
    if(!DIR_SavedIn.exists())
        return false;

    vCompetitors.clear();

    QFileInfoList FIL_Competitors = DIR_SavedIn.entryInfoList();
    for(int i = 0; i < FIL_Competitors.size(); i++)
    {
        QFileInfo FI_Competitor = FIL_Competitors[i];

        //qDebug() << "try to load" << FIL_Competitors[i].absoluteFilePath();
        if(FI_Competitor.exists())
        {
            if(FI_Competitor.suffix() == "txt" || FI_Competitor.suffix() == "TXT")
            {
                if(FI_Competitor.baseName().startsWith("Competitor_"))
                {
                    NCM_OBJ_Competitor competitor;
                    if(competitor.load(FI_Competitor.absoluteFilePath()))
                        vCompetitors.push_back(competitor);
                }
            }
        }
    }

    return true;
}

bool NCM_OBJ_Competitor_List::save()
{
    if(!DIR_SavedIn.exists())
        QDir().mkdir(DIR_SavedIn.path());
    if(!DIR_SavedIn.exists())
        return false;

    for(size_t c = 0; c < count(); c++)
        vCompetitors[c].save(DIR_SavedIn);

    return false;
}


