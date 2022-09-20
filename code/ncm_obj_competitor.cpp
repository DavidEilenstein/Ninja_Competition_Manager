#include "ncm_obj_competitor.h"

NCM_OBJ_Competitor::NCM_OBJ_Competitor()
{

}

NCM_OBJ_Competitor::NCM_OBJ_Competitor(QString name, int comp_class, int number)
{
    set_data(name, comp_class, number);
}

bool NCM_OBJ_Competitor::save(QDir DIR_competitors)
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

    QString QS_FileName = DIR_competitors.path() + "/Competitor_" + QS_StartNumber_6digits + "_" + QS_Name + ".txt";

    ofstream OF_Competitor;
    OF_Competitor.open(QS_FileName.toStdString());
    if(!OF_Competitor.is_open())
        return false;

    OF_Competitor << starter_number << "\n";            //number
    OF_Competitor << QS_Name.toStdString() << "\n";     //name
    OF_Competitor << CompClass;                         //class

    OF_Competitor.close();

    return true;
}

bool NCM_OBJ_Competitor::load(QString QS_path)
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
    int line_index = 0;
    while(getline(IS_Competitor, ST_line))
    {
        QString QS_Line = QString::fromStdString(ST_line);

        switch (line_index) {

        case 0://number
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

        case 1://name
        {
            QS_Name = QS_Line;
        }
            break;

        case 2://class
        {
            bool ok;
            int class_index = QS_Line.toInt(&ok);
            if(ok)
            {
                CompClass = class_index;
            }
            else
            {
                return false;
                IS_Competitor.close();
            }
        }
            break;

        default:
            break;
        }

        line_index++;
    }

    return true;
}
