#ifndef NCM_WIN_RESULTENTERING_CHALLENGE_H
#define NCM_WIN_RESULTENTERING_CHALLENGE_H

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
#include <ncm_obj_challenge.h>
#include <ncm_obj_competitor.h>
#include <ncm_obj_competitor_list.h>
#include <ncm_obj_try_list.h>

//namespaces
using namespace std;

namespace Ui {
class NCM_WIN_ResultEntering_Challenge;
}

class NCM_WIN_ResultEntering_Challenge : public QMainWindow
{
    Q_OBJECT

public:
    explicit NCM_WIN_ResultEntering_Challenge(NCM_OBJ_Competition comp, QWidget *parent = nullptr);
    ~NCM_WIN_ResultEntering_Challenge();

    void get_data();
    void load_competitors();
    void load_tries();
    void calc_competitors_allowed();

private slots:

    void on_pushButton_Save_clicked();
    void on_actionData_Dialog_triggered();
    void on_actionReload_Competitors_and_Tries_triggered();
    void on_checkBox_AllowReTries_clicked();

private:
    Ui::NCM_WIN_ResultEntering_Challenge *ui;

    NCM_OBJ_Competition     Competition;
    NCM_OBJ_Challenge       Challenge;
    NCM_OBJ_Competitor_List Competitors_All;
    NCM_OBJ_Competitor_List Competitors_Allowed;
    NCM_OBJ_Try_List        Tries;

    bool data_loaded = false;
};

#endif // NCM_WIN_RESULTENTERING_CHALLENGE_H
