#ifndef NCM_RANKING_H
#define NCM_RANKING_H

#include <QMainWindow>
#include <ncm_table.h>
#include <ncm_competitor.h>
#include <ncm_run.h>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QTableWidget>
#include <QTableView>

namespace Ui {
class NCM_Ranking;
}

class NCM_Ranking : public QMainWindow
{
    Q_OBJECT

public:
    explicit NCM_Ranking(QDir competition_dir, QStringList competitor_classes, QWidget *parent = nullptr);
    ~NCM_Ranking();

    void table_dims_dialog();
    void init_tables();

    void get_data_dialog();
    bool load_competitors();
    bool load_runs();
    bool load_stage();
    bool load_special_prices();
    bool stage_code_parse();
    bool calc_competitors_not_run_yet();
    bool calc_ranking();

private slots:

    bool update_ranking();

    void on_actionSelect_Data_triggered();

    void on_actionUpdate_now_triggered();

    void on_actionUpdate_automatically_triggered(bool checked);

    void on_actionChange_table_layout_triggered();

private:
    Ui::NCM_Ranking *ui;

    vector<QTableWidget*> vTableWidget;
    vector<NCM_Table*> vTables;
    int count_tables = 2;
    int count_rows_per_table = 30;

    QTimer timer_autoupdate;

    QDir DIR_Competition;
    QDir DIR_Competitors;
    QDir DIR_CompetitorsThisStage;
    QDir DIR_Runs;

    QDir DIR_SpecialPrices;
    QFileInfo FI_FailOfTheDay;
    QFileInfo FI_SickestMove;

    QStringList QSL_CompetitorClasses;

    QFileInfo FI_StageFile;
    QStringList QSL_Stage_Code;
    QString QS_StageName;
    int quali_mode = QUALI_NUMBER;
    int quali_number = 20;
    vector<int> vQualiGuarantee_CompetitorClasses = {0};
    vector<int> vQualiGuarantee_GuranteeCount = {0};
    vector<int> vQualiGuarantee_GuaranteeMode = {QUALI_GUARANTEE_EXCLUSIVE};
    int QualiGuarantee_SpeedPreviousStage_Count = 0;
    int QualiGuarantee_SpeedPreviousStage_Mode = QUALI_GUARANTEE_INCLUSIVE;
    QStringList QSL_Checkpoints;

    vector<NCM_Competitor*> vCompetitorsAll;
    vector<NCM_Run*> vRunsCompleted;
    vector<int> vRankingOfRuns_All;
    vector<int> vRankingOfRuns_InClass;
    vector<int> vRankingOfRuns_WorstPossible_All;
    vector<int> vRankingOfRuns_WorstPossible_InClass;
    vector<int> vQualiStates;
    vector<int> vBuzzer;
    QStringList QSL_CompetitorsNotRunYet;

    bool state_data_loaded = false;

    enum COLUMNS {
        COLUMN_NAME,
        COLUMN_CHECKPOINT,
        COLUMN_TIME,
        COLUMN_QUALI,
        COLUMN_CLASS,
        //COLUMN_SAFE_ALL,
        //COLUMN_SAFE_CLASS
    };
    QStringList QSL_Names_Columns = {
        "Name",
        "Checkpoint",
        "Time",
        "Quali",
        "Class",
        //"Safe (all)",
        //"Safe (class)"
    };
};

#endif // NCM_RANKING_H
