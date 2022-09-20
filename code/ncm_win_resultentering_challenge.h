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

private:
    Ui::NCM_WIN_ResultEntering_Challenge *ui;
};

#endif // NCM_WIN_RESULTENTERING_CHALLENGE_H
