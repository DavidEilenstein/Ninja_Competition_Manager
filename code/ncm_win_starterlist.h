#ifndef NCM_WIN_STARTERLIST_H
#define NCM_WIN_STARTERLIST_H

//Qt
#include <QMainWindow>
#include <QDir>
#include <QStringList>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QIcon>
#include <QDateEdit>
#include <QTimer>

//c++
#include <vector>
#include <fstream>

//own
#include <NCM_Enum.h>
#include <ncm_obj_competition.h>
#include <ncm_obj_competitor_list.h>
#include <ncm_obj_run_list.h>
#include <ncm_wid_table_multi.h>

//namespaces
using namespace std;

namespace Ui {
class NCM_WIN_StarterList;
}

class NCM_WIN_StarterList : public QMainWindow
{
    Q_OBJECT

public:
    explicit NCM_WIN_StarterList(NCM_OBJ_Competition comp, QWidget *parent = nullptr);
    ~NCM_WIN_StarterList();

    void get_data();

    void table_dims_dialog();

    void load_competitors();
    void load_runs();
    void calc_competitors_allowed();

private slots:

    void update();
    void update_auto(bool activate);

    void on_actionget_data_triggered();
    void on_actionreload_competitors_and_runs_triggered();
    void on_actionUpdate_triggered();
    void on_actionAutoupdate_triggered(bool checked);
    void on_actionChange_Table_Settings_triggered();

private:
    Ui::NCM_WIN_StarterList *ui;

    NCM_OBJ_Competition     Competition;
    NCM_OBJ_Stage           Stage;
    NCM_OBJ_Competitor_List Competitors_All;
    NCM_OBJ_Competitor_List Competitors_Allowed;
    NCM_OBJ_Run_List        Runs;

    NCM_WID_Table_Multi     Table;

    QTimer                  TimerAutoupdate;
    bool                    update_running = false;
    bool                    data_loaded = false;

    //col names
    const QStringList QSL_NamesColumns = {
        "Number",
        "Name",
        "Class",
        "est. Start"};
    enum COL_NAMES {
        COL_NUMBER,
        COL_NAME,
        COL_CLASS,
        COL_EST_TIME,
        COL_NUMBER_OF
    };
};

#endif // NCM_WIN_STARTERLIST_H
