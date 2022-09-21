#ifndef NCM_OBJ_RUN_LIST_H
#define NCM_OBJ_RUN_LIST_H

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
#include <ncm_obj_run.h>
#include <ncm_obj_competitor_list.h>

//namespaces
using namespace std;

class NCM_OBJ_Run_List
{

public:
    explicit                NCM_OBJ_Run_List();
    explicit                NCM_OBJ_Run_List(QDir dir_saved_in);

    bool                    contains_runner_duplicate(NCM_OBJ_Competitor competitor)   {return contains_runner_duplicate(competitor.name(), competitor.number());}
    bool                    contains_runner_duplicate(QString name, int number)        {return contains_runner_name(name) || contains_runner_number(number);}
    bool                    contains_runner_name(QString name);
    bool                    contains_runner_number(int number);

    bool                    add_run(NCM_OBJ_Run run);
    NCM_OBJ_Run             get_run(size_t r)                                           {return r < size() ? vRuns[r] : NCM_OBJ_Run();}

    size_t                  size()                                                      {return vRuns.size();}

    NCM_OBJ_Competitor_List competitors_list();

    void                    set_dir(QDir dir)                                           {DIR_SavedIn = dir;}
    bool                    load(QDir dir)                                              {set_dir(dir); return load();}
    bool                    load();
    bool                    save(QDir dir)                                              {set_dir(dir); return save();}
    bool                    save();

private:

    vector<NCM_OBJ_Run> vRuns;
    QDir                DIR_SavedIn;

};

#endif // NCM_OBJ_RUN_LIST_H
