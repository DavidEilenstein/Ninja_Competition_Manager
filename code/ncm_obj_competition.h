#ifndef NCM_OBJ_COMPETITION_H
#define NCM_OBJ_COMPETITION_H

//Qt
#include <QObject>
#include <QDir>
#include <QStringList>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QIcon>
#include <QDateEdit>
#include <QDebug>

//c++
#include <vector>
#include <fstream>

//own
#include <NCM_Enum.h>

//namespaces
using namespace std;

class NCM_OBJ_Competition
{
public:
    explicit NCM_OBJ_Competition();

    void    create();
    void    load();

    void    set_path_competition(QString path)  {DIR_Competition.setPath(path);}

    QString name()                              {return DIR_Competition.path().split("/").last();}
    QDir    dir_competition()                   {return DIR_Competition;}
    QDir    dir(int index)                      {return vDIR_CompetitionSubdirs[index];}
    bool    is_valid();

private:

    QDir DIR_Competition;
    vector<QDir> vDIR_CompetitionSubdirs;
};

#endif // NCM_OBJ_COMPETITION_H
