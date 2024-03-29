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
    for(size_t c = 0; c < size(); c++)
        if(name == vCompetitors[c].name())
            return true;

    return false;
}

bool NCM_OBJ_Competitor_List::contains_number(int number)
{
    for(size_t c = 0; c < size(); c++)
        if(number == vCompetitors[c].number())
            return true;

    return false;
}

bool NCM_OBJ_Competitor_List::add_competitor(NCM_OBJ_Competitor competitor)
{
    if(contains_name(competitor.name()))
        return false;

    vCompetitors.push_back(competitor);

    return true;
}

size_t NCM_OBJ_Competitor_List::get_competitor_index(NCM_OBJ_Competitor competitor)
{
    for(size_t c = 0; c < size(); c++)
        if(vCompetitors[c].name() == competitor.name())
            return c;

    return 0;
}

bool NCM_OBJ_Competitor_List::change_starter_number(NCM_OBJ_Competitor competitor, int new_number)
{
    for(size_t c = 0; c < size(); c++)
        if(get_competitor(c).is_name(competitor.name()))
        {
            vCompetitors[c].set_starter_number(new_number);
            return true;
        }

    return false;
}

QStringList NCM_OBJ_Competitor_List::names()
{
    QStringList names;
    for(size_t c = 0; c < size(); c++)
        names.push_back(vCompetitors[c].name());

    return names;
}

size_t NCM_OBJ_Competitor_List::count_in_class(bool female)
{
    size_t n = 0;
    for(size_t c = 0; c < size(); c++)
        if(vCompetitors[c].female() == female)
            n++;

    return n;
}

NCM_OBJ_Competitor_List NCM_OBJ_Competitor_List::subtract(NCM_OBJ_Competitor_List list)
{
    NCM_OBJ_Competitor_List list_difference;

    for(size_t c = 0; c < size(); c++)
        if(!list.contains_name(get_competitor(c).name()))
            list_difference.add_competitor(get_competitor(c));

    return list_difference;
}

NCM_OBJ_Competitor_List NCM_OBJ_Competitor_List::competitors_by_class(bool female)
{
    NCM_OBJ_Competitor_List list_filtered;

    for(size_t c = 0; c < size(); c++)
        if(get_competitor(c).female() == female)
            list_filtered.add_competitor(get_competitor(c));

    return list_filtered;
}

bool NCM_OBJ_Competitor_List::load()
{
    if(!DIR_SavedIn.exists())
        return false;

    DIR_SavedIn.setPath(DIR_SavedIn.path());
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

    for(size_t c = 0; c < size(); c++)
        vCompetitors[c].save(DIR_SavedIn);

    return false;
}


