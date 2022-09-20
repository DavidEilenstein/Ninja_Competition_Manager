#ifndef NCM_WIN_EDIT_STAGE_H
#define NCM_WIN_EDIT_STAGE_H

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

//namespaces
using namespace std;

namespace Ui {
class NCM_WIN_Edit_Stage;
}

class NCM_WIN_Edit_Stage : public QMainWindow
{
    Q_OBJECT

public:
    explicit NCM_WIN_Edit_Stage(NCM_OBJ_Competition comp, QWidget *parent = nullptr);
    ~NCM_WIN_Edit_Stage();

private slots:

    void on_pushButton_Load_clicked();
    void on_pushButton_Save_clicked();

private:
    Ui::NCM_WIN_Edit_Stage *ui;

    NCM_OBJ_Competition Competition;
    NCM_OBJ_Stage       Stage;
};

#endif // NCM_WIN_EDIT_STAGE_H
