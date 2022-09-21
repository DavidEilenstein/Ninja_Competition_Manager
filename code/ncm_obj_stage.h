#ifndef NCM_OBJ_STAGE_H
#define NCM_OBJ_STAGE_H

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
#include <ncm_obj_challenge_list.h>

//namespaces
using namespace std;

class NCM_OBJ_Stage
{
public:
    explicit NCM_OBJ_Stage();
    explicit NCM_OBJ_Stage(QFileInfo stage_file);

    void set_name(QString name)                                                     {QS_Name = name;}
    void set_final(bool final)                                                      {IsFinal = final;}
    void set_quali_counts(int this_f, int this_m, int previous_f, int previous_m)   {QualiThisF = this_f; QualiThisM = this_m; QualiPreviousF = previous_f; QualiPreviousM = previous_m;}
    void set_checkpoints(QStringList checkpoints)                                   {QSL_Checkpoints = checkpoints;}
    void set_challenges(QStringList challenge_names)                                {QSL_ChallengeNames = challenge_names;}
    void set_file(QFileInfo file)                                                   {FI_StageFile = file;}

    QString                 name()                                                  {return QS_Name;}
    bool                    is_final()                                              {return IsFinal;}
    int                     quali_count_this_f()                                    {return QualiThisF;}
    int                     quali_count_this_m()                                    {return QualiThisM;}
    int                     quali_count_previous_f()                                {return QualiPreviousF;}
    int                     quali_count_previous_m()                                {return QualiPreviousM;}
    QStringList             checkpoints()                                           {return QSL_Checkpoints;}
    QString                 checkpoints_as_string_line_by_line();
    QString                 challenge_names_as_string_line_by_line();

    bool                    load();
    bool                    save();

private:

    void                    code_update();
    void                    code_parse();

    QFileInfo FI_StageFile;

    QStringList QSL_Stage_Code;

    QString QS_Name = "StageExample";
    bool IsFinal = false;
    int QualiThisF = 1;
    int QualiThisM = 1;
    int QualiPreviousF = 0;
    int QualiPreviousM = 0;

    QStringList QSL_ChallengeNames = {
        "Challenge A",
        "Challenge B",
        "Challenge C"};

    QStringList QSL_Checkpoints = {
        "Checkpoint 0",
        "Checkpoint 1",
        "Checkpoint 2"};
};

#endif // NCM_OBJ_STAGE_H
