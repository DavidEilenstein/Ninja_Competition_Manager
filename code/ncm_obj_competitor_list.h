#ifndef NCM_OBJ_COMPETITOR_LIST_H
#define NCM_OBJ_COMPETITOR_LIST_H

//Qt
#include <QObject>
#include <QDir>
#include <QStringList>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QIcon>
#include <QDateEdit>

//c++
#include <vector>
#include <fstream>

//own
#include <NCM_Enum.h>
#include <ncm_obj_competition.h>
#include <ncm_obj_competitor.h>
#include <ncm_obj_run_list.h>

//namespaces
using namespace std;

class NCM_OBJ_Competitor_List
{

public:
    explicit NCM_OBJ_Competitor_List();
    explicit NCM_OBJ_Competitor_List(QDir dir_saved_in);

    bool                contains_duplicate(NCM_OBJ_Competitor competitor)   {return contains_duplicate(competitor.name(), competitor.number());}
    bool                contains_duplicate(QString name, int number)        {return contains_name(name) || contains_number(number);}
    bool                contains_name(QString name);
    bool                contains_number(int number);

    bool                add_competitor(NCM_OBJ_Competitor competitor);
    NCM_OBJ_Competitor  get_competitor(size_t c)                            {return c < count() ? vCompetitors[c] : NCM_OBJ_Competitor();}

    size_t              count()                                             {return vCompetitors.size();}

    void                set_dir(QDir dir)                                   {DIR_SavedIn = dir;}
    bool                load(QDir dir)                                      {set_dir(dir); return load();}
    bool                load();
    bool                save(QDir dir)                                      {set_dir(dir); return save();}
    bool                save();

private:

    vector<NCM_OBJ_Competitor>  vCompetitors;
    QDir                        DIR_SavedIn;

};

#endif // NCM_OBJ_COMPETITOR_LIST_H
