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
#include <ncm_obj_competitor.h>

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

private:
    Ui::NCM_WIN_ResultEntering_Stage *ui;
};

#endif // NCM_WIN_RESULTENTERING_STAGE_H
