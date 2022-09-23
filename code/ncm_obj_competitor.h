#ifndef NCM_OBJ_COMPETITOR_H
#define NCM_OBJ_COMPETITOR_H

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
#include <ncm_obj_competition.h>

//namespaces
using namespace std;

class NCM_OBJ_Competitor
{
public:

    explicit NCM_OBJ_Competitor();
    explicit NCM_OBJ_Competitor(QString name, int comp_class, int number);

    void    set_data(QString name, bool lady, int number)           {QS_Name = name; Female = lady; starter_number = number;}
    void    set_name(QString name)                                  {QS_Name = name;}
    void    set_competitor_class(bool lady)                         {Female = lady;}
    void    set_starter_number(int number)                          {starter_number = number;}

    int     number()                                                {return starter_number;}
    QString name()                                                  {return QS_Name;}
    bool    female()                                                {return Female;}
    bool    male()                                                  {return !Female;}
    QString competitor_class_text()                                 {return Female ? QS_Female : QS_Male;}
    QString competitor_class_symbol()                               {return Female ? QS_FemaleSymbol : QS_MaleSymbol;}

    bool    is_name(QString name_other)                             {return name_other == name();}
    bool    is_number(int number_other)                             {return number_other == number();}
    bool    is_duplicate(NCM_OBJ_Competitor competitor_other)       {return is_name(competitor_other.name()) || is_number(competitor_other.number());}

    bool    save(QDir DIR_competitors);
    bool    load(QString QS_path);


private:

    int starter_number = 0;
    QString QS_Name = "NameExample";
    bool Female = false;

};

#endif // NCM_OBJ_COMPETITOR_H
