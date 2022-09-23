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
#include <algorithm>

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

    bool                    contains_runner_name(QString name);
    bool                    contains_runner_number(int number);

    bool                    add_run(NCM_OBJ_Run run);
    NCM_OBJ_Run             get_run(size_t r)                                           {return r < size() ? vRuns[r] : NCM_OBJ_Run();}

    size_t                  size()                                                      {return vRuns.size();}

    NCM_OBJ_Competitor_List competitors_list();

    NCM_OBJ_Run             run_earliest();
    NCM_OBJ_Run             run_latest();
    int                     average_time_start_to_start_ms();

    void                    sort()                                                      {std::sort(vRuns.begin(), vRuns.end());}

    void                    set_dir(QDir dir)                                           {DIR_SavedIn = dir;}
    bool                    load(QDir dir)                                              {set_dir(dir); return load();}
    bool                    load();
    bool                    save(QDir dir)                                              {set_dir(dir); return save();}
    bool                    save();


private:

    vector<NCM_OBJ_Run>     vRuns;
    QDir                    DIR_SavedIn;

    void                    info_debug();

};

#endif // NCM_OBJ_RUN_LIST_H
