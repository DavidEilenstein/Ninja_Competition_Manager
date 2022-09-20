#ifndef NCM_RESULTENTERING_SIDECHALLANGE_H
#define NCM_RESULTENTERING_SIDECHALLANGE_H

#include <QMainWindow>
#include <QDir>
#include <QInputDialog>
#include <QFileDialog>
#include <fstream>
#include <vector>
#include <ncm_sidechallengetry.h>
#include <QMessageBox>
#include <QDebug>

using namespace std;

namespace Ui {
class NCM_ResultEntering_SideChallange;
}

class NCM_ResultEntering_SideChallange : public QMainWindow
{
    Q_OBJECT

public:
    explicit NCM_ResultEntering_SideChallange(QDir competition_dir, QWidget *parent = nullptr);
    ~NCM_ResultEntering_SideChallange();

    void get_data_dialog();
    bool load_competitors();
    bool load_tries();
    bool calc_competitors_allowed_to_try();

private slots:
    void on_actionChallange_and_Competitor_selection_triggered();

    void on_pushButton_SaveTry_clicked();

private:
    Ui::NCM_ResultEntering_SideChallange *ui;

    QDir DIR_Competition;
    QDir DIR_Competitors;
    QDir DIR_CompetitorsThisChallenge;
    QDir DIR_Tries_Out;

    QFileInfo FI_sideChallengeFile;

    QString QS_Name = "Side Challenge 1 - Lache Dismount";
    QString QS_MeasureUnit = "cm";
    bool Measure_MoreIsBetter = true;

    vector<NCM_Competitor*> vCompetitorsAll;
    vector<NCM_sideChallengeTry*> vTriesDone;
    QStringList QSL_CompetitorsAllowedToTry;

    bool state_data_loaded = false;
};

#endif // NCM_RESULTENTERING_SIDECHALLANGE_H
