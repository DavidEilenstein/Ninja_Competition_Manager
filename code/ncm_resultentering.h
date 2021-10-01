#ifndef NCM_RESULTENTERING_H
#define NCM_RESULTENTERING_H

#include <QMainWindow>
#include <QDir>
#include <QInputDialog>
#include <QFileDialog>
#include <fstream>
#include <vector>
#include <ncm_run.h>
#include <QMessageBox>
#include <QDebug>

using namespace std;

namespace Ui {
class NCM_ResultEntering;
}

class NCM_ResultEntering : public QMainWindow
{
    Q_OBJECT

public:
    explicit NCM_ResultEntering(QDir competition_dir, QWidget *parent = nullptr);
    ~NCM_ResultEntering();

    void get_data_dialog();
    bool load_competitors();
    bool load_runs();
    bool load_checkpoints();
    bool calc_competitors_not_run_yet();

private slots:
    void on_actionStage_and_competitor_selection_triggered();
    void on_pushButton_SaveRun_clicked();

private:
    Ui::NCM_ResultEntering *ui;

    QDir DIR_Competition;
    QDir DIR_Competitors;
    QDir DIR_CompetitorsThisStage;
    QDir DIR_Runs_Out;

    QDir DIR_SpecialPrices;
    QFileInfo FI_FailOfTheDay;
    QFileInfo FI_SickestMove;

    QFileInfo FI_StageFile;

    QString QS_StageName;

    QStringList QSL_Checkpoints;

    vector<NCM_Competitor*> vCompetitorsAll;
    vector<NCM_Run*> vRunsCompleted;
    QStringList QSL_CompetitorsNotRunYet;

    bool state_data_loaded = false;
};

#endif // NCM_RESULTENTERING_H
