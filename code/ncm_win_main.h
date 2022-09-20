#ifndef NCM_WIN_MAIN_H
#define NCM_WIN_MAIN_H

//Qt
#include <QMainWindow>
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
#include <ncm_win_checkin.h>
#include <ncm_win_starterlist.h>
#include <ncm_win_resultentering_stage.h>
#include <ncm_win_resultentering_challenge.h>
#include <ncm_win_ranking_stage.h>
#include <ncm_win_ranking_challenge.h>
#include <ncm_win_edit_stage.h>
#include <ncm_win_edit_challenge.h>

//namespaces
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class NCM_WIN_Main; }
QT_END_NAMESPACE

class NCM_WIN_Main : public QMainWindow
{
    Q_OBJECT

public:
    NCM_WIN_Main(QWidget *parent = nullptr);
    ~NCM_WIN_Main();

    void settings_load();
    void settings_save();

private:

    void enable_ui();

private slots:

    void on_pushButton_Comp_Create_clicked();
    void on_pushButton_Comp_Select_clicked();
    void on_pushButton_Comp_Load_clicked();

    void on_pushButton_Checkin_clicked();

    void on_pushButton_Stage_Edit_clicked();
    void on_pushButton_Stage_StarterList_clicked();
    void on_pushButton_Stage_ResultEntering_clicked();
    void on_pushButton_Stage_Ranking_clicked();

    void on_pushButton_Challenges_Edit_clicked();
    void on_pushButton_Challenges_ResultEntering_clicked();
    void on_pushButton_Challenges_Ranking_clicked();

private:
    Ui::NCM_WIN_Main *ui;

    QDir                                DIR_Settings;
    QFileInfo                           FI_Settings;


    NCM_OBJ_Competition                 Competition;


    NCM_WIN_CheckIn*                    win_checkin;

    NCM_WIN_Edit_Stage*                 win_edit_stage;
    NCM_WIN_StarterList*                win_starterlist;
    NCM_WIN_ResultEntering_Stage*       win_resultentering_stage;
    NCM_WIN_Ranking_Stage*              win_ranking_stage;

    NCM_WIN_Edit_Challenge*             win_edit_challenge;
    NCM_WIN_ResultEntering_Challenge*   win_resultentering_challenge;
    NCM_WIN_Ranking_Challenge*          win_ranking_challenge;
};
#endif // NCM_WIN_MAIN_H
