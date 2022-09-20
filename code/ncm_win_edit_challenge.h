#ifndef NCM_WIN_EDIT_CHALLENGE_H
#define NCM_WIN_EDIT_CHALLENGE_H

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

//namespaces
using namespace std;

namespace Ui {
class NCM_WIN_Edit_Challenge;
}

class NCM_WIN_Edit_Challenge : public QMainWindow
{
    Q_OBJECT

public:
    explicit NCM_WIN_Edit_Challenge(QWidget *parent = nullptr);
    ~NCM_WIN_Edit_Challenge();

private:
    Ui::NCM_WIN_Edit_Challenge *ui;
};

#endif // NCM_WIN_EDIT_CHALLENGE_H
