#ifndef NCM_WIN_RANKING_CHALLENGE_H
#define NCM_WIN_RANKING_CHALLENGE_H

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
#include <ncm_obj_ranking_combi.h>
#include <ncm_wid_table_multi.h>

//namespaces
using namespace std;

namespace Ui {
class NCM_WIN_Ranking_Challenge;
}

class NCM_WIN_Ranking_Challenge : public QMainWindow
{
    Q_OBJECT

public:
    explicit NCM_WIN_Ranking_Challenge(NCM_OBJ_Competition comp, QWidget *parent = nullptr);
    ~NCM_WIN_Ranking_Challenge();

    void get_data();

    void table_dims_dialog();

private slots:

    void update();
    void update_auto(bool activate);

    void on_actionget_data_triggered();

    void on_actionChange_table_settings_triggered();

    void on_actionUpdate_triggered();


    void on_actionAutoupdate_triggered(bool checked);

private:
    Ui::NCM_WIN_Ranking_Challenge *ui;

    NCM_OBJ_Competition     Competition;

    NCM_OBJ_Ranking_Combi   Ranking;

    NCM_WID_Table_Multi     Table;

    QTimer                  TimerAutoupdate;
    bool                    update_running = false;
    bool                    data_loaded = false;

    size_t challenge_index = 0;

    //col names
    const QStringList QSL_NamesColumns = {
        "name",
        "pos",
        "status",
        "run",
        "score"};
    enum COL_NAMES {
        COL_NAME,
        COL_POS,
        COL_QUALI,
        COL_RUN,
        COL_SCORE,
        COL_NUMBER_OF
    };
};

#endif // NCM_WIN_RANKING_CHALLENGE_H
