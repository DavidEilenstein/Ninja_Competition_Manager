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

private:
    Ui::NCM_WIN_Main *ui;
};
#endif // NCM_WIN_MAIN_H
