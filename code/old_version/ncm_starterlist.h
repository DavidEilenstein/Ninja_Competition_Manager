#ifndef NCM_STARTERLIST_H
#define NCM_STARTERLIST_H

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
#include <QHeaderView>
#include <QDesktopServices>
#include <QUrl>
#include <QDateTime>

using namespace std;

namespace Ui {
class NCM_StarterList;
}

class NCM_StarterList : public QMainWindow
{
    Q_OBJECT

public:
    explicit NCM_StarterList(QDir competition_dir, QWidget *parent = nullptr);
    ~NCM_StarterList();

    void table_dims_dialog();
    void init_tables();

    void get_data_dialog();
    bool load_competitors();
    bool load_runs();
    bool calc_competitors_not_run_yet();
    bool calc_mean_time_between_runs();

private slots:

    bool update_starter_list();

    void on_actionChose_competitors_and_stage_triggered();

    void on_actionUpdate_now_triggered();

    void auto_update(bool activate);
    void on_actionUpdate_automatically_triggered(bool checked);

    void on_actionChange_table_settings_triggered();

    void on_pushButton_DavidEilenstein_clicked();

    void on_actionSave_Screenshot_triggered();

private:
    Ui::NCM_StarterList *ui;

    vector<QTableWidget*> vTableWidget;
    vector<NCM_Table*> vTables;
    int count_tables = 1;
    int count_rows_per_table = 30;

    QTimer timer_autoupdate;

    QDir DIR_Competition;
    QDir DIR_Competitors;
    QDir DIR_CompetitorsThisStage;
    QDir DIR_Runs_Out;
    QDir DIR_Screenshots;

    QFileInfo FI_StageFile;

    QString QS_StageName;

    vector<NCM_Competitor*> vCompetitorsAll;
    vector<NCM_Run*> vRunsCompleted;
    QStringList QSL_CompetitorsNotRunYet;

    bool state_data_loaded = false;
    bool state_update_running = false;

    int mean_time_between_runs_seconds = 0;
    QDateTime QDT_LastRun;
    int valid_times_between_runs = 0;
};

#endif // NCM_STARTERLIST_H
