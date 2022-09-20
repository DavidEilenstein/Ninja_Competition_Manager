#ifndef NCM_OBJ_CHALLENGE_H
#define NCM_OBJ_CHALLENGE_H

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

//namespaces
using namespace std;


class NCM_OBJ_Challenge
{
public:
    explicit NCM_OBJ_Challenge(NCM_OBJ_Competition comp);

    void set_name(QString name)             {QS_Name = name;}
    void set_quali_count(int f, int m)      {QualiCount_F = f; QualiCount_M = m;}
    void set_order(bool more_is_better)     {OrderMoreIsBetter = more_is_better;}
    void set_unit(QString unit)             {QS_Unit = unit;}
    void set_stage_parallel(QString name)   {QS_StageParallelName = name;}

    QString name()                          {return QS_Name;}
    int quali_count_m()                     {return QualiCount_M;}
    int quali_count_f()                     {return QualiCount_F;}
    bool order_more_is_better()             {return OrderMoreIsBetter;}
    QString stage_parallel_name()           {return QS_StageParallelName;}

    bool load();
    bool save();

private:

    bool code_save();
    bool code_load();
    bool code_parse();
    bool code_update();

    NCM_OBJ_Competition Competition;

    QString QS_Name = "ChallengeExample";
    int QualiCount_F = 1;
    int QualiCount_M = 1;
    bool OrderMoreIsBetter = true;
    QString QS_Unit = "cm";
    QString QS_StageParallelName = "StageExample";

    QStringList Code;
};

#endif // NCM_OBJ_CHALLENGE_H
