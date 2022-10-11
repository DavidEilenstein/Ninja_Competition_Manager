#ifndef NCM_OBJ_CHALLENGE_H
#define NCM_OBJ_CHALLENGE_H

//Qt
#include <QObject>
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

//namespaces
using namespace std;


class NCM_OBJ_Challenge
{
public:
    explicit    NCM_OBJ_Challenge();

    void        set_name(QString name)             {QS_Name = name;}
    void        set_file(QFileInfo file)           {FI_ChallengeFile = file;}
    void        set_quali_count(int f, int m)      {QualiCount_F = f; QualiCount_M = m;}
    void        set_order(bool more_is_better)     {OrderMoreIsBetter = more_is_better;}
    void        set_unit(QString unit)             {QS_Unit = unit;}

    QString     name()                              {return QS_Name;}
    QString     unit()                              {return QS_Unit;}
    size_t      quali_count(bool female)            {return female ? QualiCount_F : QualiCount_M;}
    size_t      quali_count_m()                     {return QualiCount_M;}
    size_t      quali_count_f()                     {return QualiCount_F;}
    bool        order_more_is_better()              {return OrderMoreIsBetter;}

    bool        load(QFileInfo file)                {set_file(file); return load();}
    bool        load();
    bool        save();

private:

    bool        code_parse();
    bool        code_update();

    QFileInfo   FI_ChallengeFile;

    QStringList QSL_Challenge_Code;

    QString     QS_Name = "Challenge 1 - Max Dismount Lache";
    size_t      QualiCount_F = 1;
    size_t      QualiCount_M = 1;
    bool        OrderMoreIsBetter = true;
    QString     QS_Unit = "cm";
};

#endif // NCM_OBJ_CHALLENGE_H
