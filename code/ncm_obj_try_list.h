#ifndef NCM_OBJ_TRY_LIST_H
#define NCM_OBJ_TRY_LIST_H

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
#include <ncm_obj_competitor_list.h>
#include <ncm_obj_try.h>

//namespaces
using namespace std;

class NCM_OBJ_Try_List
{

public:
    explicit                NCM_OBJ_Try_List();
    explicit                NCM_OBJ_Try_List(QDir dir_saved_in);

    bool                    contains_tryer_name(QString name);
    bool                    contains_tryer_number(int number);

    bool                    add_try(NCM_OBJ_Try challangetry);
    bool                    replace_try(NCM_OBJ_Try challangetry);
    NCM_OBJ_Try             get_try(size_t t)                                           {return t < size() ? vTries[t] : NCM_OBJ_Try();}

    size_t                  size()                                                      {return vTries.size();}

    NCM_OBJ_Competitor_List competitors_list();

    NCM_OBJ_Try             try_earliest();
    NCM_OBJ_Try             try_latest();
    int                     average_time_start_to_start_ms();

    void                    sort()                                                      {std::sort(vTries.begin(), vTries.end());}

    void                    set_dir(QDir dir)                                           {DIR_SavedIn = dir;}
    bool                    load(QDir dir)                                              {set_dir(dir); return load();}
    bool                    load();
    bool                    save(QDir dir)                                              {set_dir(dir); return save();}
    bool                    save();


private:

    vector<NCM_OBJ_Try>     vTries;
    QDir                    DIR_SavedIn;

    void                    info_debug();

};

#endif // NCM_OBJ_TRY_LIST_H
