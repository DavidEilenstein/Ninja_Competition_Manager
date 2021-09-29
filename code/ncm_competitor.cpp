#include "ncm_competitor.h"

NCM_Competitor::NCM_Competitor(QDir competitors_dir, QObject *parent)
    : QObject(parent)
{
    DIR_Competitors = competitors_dir;
}

NCM_Competitor::NCM_Competitor(QDir competitors_dir, QString name, QString competitor_class, int number)
{
    set_data(competitors_dir, name, competitor_class, number);
}

bool NCM_Competitor::save()
{
    QString QS_StartNumber_6digits;
    if(starter_number < 10)
        QS_StartNumber_6digits = "00000" + QString::number(starter_number);
    else if(starter_number < 100)
        QS_StartNumber_6digits = "0000" + QString::number(starter_number);
    else if(starter_number < 1000)
        QS_StartNumber_6digits = "000" + QString::number(starter_number);
    else if(starter_number < 10000)
        QS_StartNumber_6digits = "00" + QString::number(starter_number);
    else if(starter_number < 100000)
        QS_StartNumber_6digits = "0" + QString::number(starter_number);
    else
        QS_StartNumber_6digits = QString::number(starter_number);

    QString QS_FileName = DIR_Competitors.path() + "/Competitor_" + QS_StartNumber_6digits + "_" + QS_Name + ".txt";

    ofstream OF_Competitor;
    OF_Competitor.open(QS_FileName.toStdString());
    if(!OF_Competitor.is_open())
        return false;

    OF_Competitor << starter_number << "\n";
    OF_Competitor << QS_Name.toStdString() << "\n";
    OF_Competitor << QS_CompClass.toStdString();

    OF_Competitor.close();

    return true;
}

bool NCM_Competitor::load()
{
    QString QS_StartNumber_6digits;
    if(starter_number < 10)
        QS_StartNumber_6digits = "00000" + QString::number(starter_number);
    else if(starter_number < 100)
        QS_StartNumber_6digits = "0000" + QString::number(starter_number);
    if(starter_number < 1000)
        QS_StartNumber_6digits = "000" + QString::number(starter_number);
    if(starter_number < 10000)
        QS_StartNumber_6digits = "00" + QString::number(starter_number);
    if(starter_number < 100000)
        QS_StartNumber_6digits = "0" + QString::number(starter_number);
    else
        QS_StartNumber_6digits = QString::number(starter_number);

    QString QS_FileName = DIR_Competitors.path() + "/Competitor_" + QS_StartNumber_6digits + ".txt";

    return load(QS_FileName);
}

bool NCM_Competitor::load(QString QS_path)
{
    if(QS_path.isEmpty())
        return false;

    QFileInfo FI(QS_path);
    if(!FI.exists())
        return false;

    if(!(FI.suffix() == "txt") && !(FI.suffix() == "TXT"))
        return false;

    ifstream IS_Competitor;
    IS_Competitor.open(FI.absoluteFilePath().toStdString());

    if(!IS_Competitor.is_open())
        return false;

    IS_Competitor.clear();

    string ST_line;
    int i = 0;
    while(getline(IS_Competitor, ST_line))
    {
        QString QS_Line = QString::fromStdString(ST_line);

        switch (i) {

        case 0:
        {
            bool ok;
            int number = QS_Line.toInt(&ok);
            if(ok)
            {
                starter_number = number;
            }
            else
            {
                return false;
                IS_Competitor.close();
            }
        }
            break;

        case 1:
        {
            QS_Name = QS_Line;
        }
            break;

        case 2:
        {
            QS_CompClass = QS_Line;
        }
            break;

        default:
            break;
        }

        i++;
    }

    return true;
}

void NCM_Competitor::set_data(QDir competitors_dir, QString name, QString competitor_class, int number)
{
    DIR_Competitors = competitors_dir;
    QS_Name = name;
    QS_CompClass = competitor_class;
    starter_number = number;
}
