#ifndef NCM_WIN_RESULTENTERING_STAGE_H
#define NCM_WIN_RESULTENTERING_STAGE_H

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
#include <ncm_obj_stage.h>
#include <ncm_obj_competitor_list.h>
#include <ncm_obj_run_list.h>

//namespaces
using namespace std;

namespace Ui {
class NCM_WIN_ResultEntering_Stage;
}

class NCM_WIN_ResultEntering_Stage : public QMainWindow
{
    Q_OBJECT

public:
    explicit NCM_WIN_ResultEntering_Stage(NCM_OBJ_Competition comp, QWidget *parent = nullptr);
    ~NCM_WIN_ResultEntering_Stage();

    void get_data();
    void load_competitors();
    void load_runs();
    void calc_competitors_allowed();

private slots:

    void on_pushButton_SaveRun_clicked();
    void on_actionData_Dialog_triggered();
    void on_checkBox_Rerun_clicked();
    void on_actionreload_competitors_and_runs_triggered();

private:
    Ui::NCM_WIN_ResultEntering_Stage *ui;

    NCM_OBJ_Competition     Competition;
    NCM_OBJ_Stage           Stage;
    NCM_OBJ_Competitor_List Competitors_All;
    NCM_OBJ_Competitor_List Competitors_Allowed;
    NCM_OBJ_Run_List        Runs;

    bool data_loaded = false;

};

#endif // NCM_WIN_RESULTENTERING_STAGE_H
