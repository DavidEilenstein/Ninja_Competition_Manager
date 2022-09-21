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
    void load_competitors();
    void load_runs();
    void calc_competitors_allowed();

private:
    Ui::NCM_WIN_StarterList *ui;

    QTimer timer_autoupdate;

};

#endif // NCM_WIN_STARTERLIST_H
