#ifndef NCM_STAGE_H
#define NCM_STAGE_H

#include <QDialog>
#include <QInputDialog>
#include <QFileDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QDir>
#include <ncm_rankingscheme.h>
#include <NCM_enum.h>
#include <fstream>

using namespace std;

namespace Ui {
class NCM_Stage;
}

class NCM_Stage : public QDialog
{
    Q_OBJECT

public:
    explicit NCM_Stage(QDir CompetitionDir, QStringList competitor_classes, QWidget *parent = nullptr);
    ~NCM_Stage();

    void stage_code_set_to_ui();
    void stage_code_set_to_ui(QStringList stage_code);
    void stage_code_get_from_ui();
    void stage_code_parse();
    void stage_code_update();
    void stage_code_load();
    void stage_code_save();

private slots:
    void on_plainTextEdit_StageCode_textChanged();
    void on_pushButton_EditStageName_clicked();
    void on_pushButton_ChangeQualiMode_clicked();
    void on_pushButton_AddGuaranteeRule_clicked();
    void on_pushButton_Load_clicked();
    void on_pushButton_Save_clicked();
    void on_pushButton_Close_clicked();

private:

    Ui::NCM_Stage *ui;

    QDir DIR_Competition;
    QStringList QSL_CompetitorClasses;

    QStringList QSL_Stage_Code;

    QString QS_Name = "Stage 2";

    int quali_mode = QUALI_NUMBER;
    int quali_number = 20;

    vector<int> vQualiGuarantee_CompetitorClasses = {0};
    vector<int> vQualiGuarantee_GuranteeCount = {3};
    vector<int> vQualiGuarantee_GuaranteeMode = {QUALI_GUARANTEE_EXCLUSIVE};

    int QualiGuarantee_SpeedPreviousStage_Count = 3;
    int QualiGuarantee_SpeedPreviousStage_Mode = QUALI_GUARANTEE_INCLUSIVE;

    QStringList QSL_CheckpointNames = {
        "Start",
        "5 Step (1)",
        "5 Step (2)",
        "5 Step (3)",
        "5 Step (4)",
        "5 Step (5)",
        "5 Step (Plattform)",
        "Double Salmon Ladder (1st trasfer)",
        "Double Salmon Ladder (4th ladder rung)",
        "Double Salmon Ladder (2nd transfer)",
        "Bar after Double Salmon Ladder",
        "Ringslider (holded safely)",
        "Ringslider (started sliding)",
        "Ringslider (Plattform)",
        "Wall (tired)",
        "Buzzer"};

    bool saved = false;
};

#endif // NCM_STAGE_H
