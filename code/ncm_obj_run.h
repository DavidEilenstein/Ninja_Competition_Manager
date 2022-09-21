#ifndef NCM_OBJ_RUN_H
#define NCM_OBJ_RUN_H

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
#include <ncm_obj_stage.h>
#include <ncm_obj_competitor.h>

//namespaces
using namespace std;

class NCM_OBJ_Run
{
public:
    explicit NCM_OBJ_Run();
    explicit NCM_OBJ_Run(NCM_OBJ_Stage stage, NCM_OBJ_Competitor competitor, int cp_index, int t_min, int t_s, int t_ms);

    void set_stage(NCM_OBJ_Stage stage)                     {Stage = stage;}
    void set_competitor(NCM_OBJ_Competitor competitor)      {Competitor = competitor;}
    void set_time(int t_min, int t_s, int t_ms)             {set_time(t_min * 60 + t_s, t_ms);}
    void set_time(int t_s, int t_ms)                        {set_time(t_s * 1000 + t_ms);}
    void set_time(int t_ms)                                 {Time_ms = t_ms;}
    void set_checkpoint_reached(int cp_index)               {CheckpointReached = cp_index;}

    NCM_OBJ_Stage       stage()                             {return Stage;}
    NCM_OBJ_Competitor  competitor()                        {return Competitor;}
    int                 time_ms()                           {return Time_ms;}
    int                 checkpoint_reached()                {return CheckpointReached;}

    bool save(QDir DIR_Runs);
    bool load(QString QS_path);

    bool operator < (NCM_OBJ_Run run_other);
    bool operator > (NCM_OBJ_Run run_other)                 {return !(*this < run_other);}

private:

    NCM_OBJ_Competitor Competitor;
    NCM_OBJ_Stage Stage;

    int Time_ms = 0;
    int CheckpointReached = 0;

    QDateTime QDT_Recorded;
};

#endif // NCM_OBJ_RUN_H
