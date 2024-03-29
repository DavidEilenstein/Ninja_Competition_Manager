#ifndef NCM_OBJ_RANKING_STAGE_H
#define NCM_OBJ_RANKING_STAGE_H

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
#include <ncm_obj_stage.h>
#include <ncm_obj_run_list.h>
#include <ncm_obj_competitor_list.h>

//namespaces
using namespace std;

class NCM_OBJ_Ranking_Stage
{

public:

    explicit                NCM_OBJ_Ranking_Stage();

    bool                    set_competitors(QDir dir_competitors)       {return Competitors_All.load(dir_competitors);}
    bool                    set_runs(QDir dir_runs)                     {return Runs.load(dir_runs);}
    bool                    set_stage(QFileInfo fi_stage)               {return Stage.load(fi_stage);}

    void                    load_competitors()                          {Competitors_All.load();}
    void                    load_runs()                                 {Runs.load();}
    void                    calc_competitors_allowed()                  {Competitors_Allowed = Competitors_All.subtract(Runs.competitors_list());}

    void                    update()                                    {load_competitors(); load_runs(); calc_competitors_allowed(); Runs.sort();}

    size_t                  count_runs()                                {return Runs.size();}
    size_t                  count_competitors_all()                     {return Competitors_All.size();}
    size_t                  count_competitors_allowed()                 {return Competitors_Allowed.size();}

    size_t                  pos_current_overall(NCM_OBJ_Competitor c);
    size_t                  pos_current_class(NCM_OBJ_Competitor c);
    size_t                  pos_worst_overall(NCM_OBJ_Competitor c);
    size_t                  pos_worst_class(NCM_OBJ_Competitor c);

    NCM_OBJ_Run             run(NCM_OBJ_Competitor c);
    NCM_OBJ_Competitor      competitor(size_t i)                        {return Competitors_All.get_competitor(i);}
    NCM_OBJ_Competitor_List competitor_list_all()                       {return Competitors_All;}
    NCM_OBJ_Competitor_List competitor_list_allowed()                   {return Competitors_Allowed;}
    NCM_OBJ_Run             run(size_t i)                               {return Runs.get_run(i);}
    NCM_OBJ_Run_List        runs()                                      {return Runs;}

    NCM_OBJ_Stage           stage()                                     {return Stage;}

private:

    NCM_OBJ_Stage           Stage;
    NCM_OBJ_Competitor_List Competitors_All;
    NCM_OBJ_Competitor_List Competitors_Allowed;
    NCM_OBJ_Run_List        Runs;

};

#endif // NCM_OBJ_RANKING_STAGE_H
