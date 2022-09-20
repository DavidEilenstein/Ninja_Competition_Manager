#ifndef NCM_WIN_CHECKIN_H
#define NCM_WIN_CHECKIN_H

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
#include <ncm_obj_competitor.h>

//namespaces
using namespace std;

namespace Ui {
class NCM_WIN_CheckIn;
}

class NCM_WIN_CheckIn : public QMainWindow
{
    Q_OBJECT

public:
    explicit NCM_WIN_CheckIn(QWidget *parent = nullptr);
    ~NCM_WIN_CheckIn();

private:
    Ui::NCM_WIN_CheckIn *ui;
};

#endif // NCM_WIN_CHECKIN_H
