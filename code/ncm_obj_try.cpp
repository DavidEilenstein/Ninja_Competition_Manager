#include "ncm_obj_try.h"

NCM_OBJ_Try::NCM_OBJ_Try()
{
    QDT_Recorded = QDateTime::currentDateTime();
}

NCM_OBJ_Try::NCM_OBJ_Try(NCM_OBJ_Challenge challenge, NCM_OBJ_Competitor competitor, double score)
{
    QDT_Recorded = QDateTime::currentDateTime();
    set_challenge(challenge);
    set_competitor(competitor);
    set_score(score);
}

bool NCM_OBJ_Try::save(QDir DIR_Tries)
{
    QString QS_StartNumber_6digits;
    if(Competitor.number() < 10)
        QS_StartNumber_6digits = "00000" + QString::number(Competitor.number());
    else if(Competitor.number() < 100)
        QS_StartNumber_6digits = "0000" + QString::number(Competitor.number());
    else if(Competitor.number() < 1000)
        QS_StartNumber_6digits = "000" + QString::number(Competitor.number());
    else if(Competitor.number() < 10000)
        QS_StartNumber_6digits = "00" + QString::number(Competitor.number());
    else if(Competitor.number() < 100000)
        QS_StartNumber_6digits = "0" + QString::number(Competitor.number());
    else
        QS_StartNumber_6digits = QString::number(Competitor.number());

    QString QS_FileName = DIR_Tries.path() + "/Try_" + Challenge.name() + "_" + QS_StartNumber_6digits + "_" + Competitor.name() + ".txt";

    ofstream OF_Try;
    OF_Try.open(QS_FileName.toStdString());
    if(!OF_Try.is_open())
        return false;

    OF_Try << Competitor.number() << "\n";
    OF_Try << Competitor.name().toStdString() << "\n";
    OF_Try << (Competitor.female() ? QS_Female : QS_Male).toStdString() << "\n";
    OF_Try << Challenge.name().toStdString() << "\n";
    OF_Try << QString::number(Score).replace(",", ".").toStdString() << "\n";
    OF_Try << QDT_Recorded.toString(QS_DateTimeFormat).toStdString();

    OF_Try.close();

    return true;
}

bool NCM_OBJ_Try::load(QString QS_path)
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
                Competitor.set_starter_number(number);
            }
            else
            {
                IS_Competitor.close();
                return false;
            }
        }
            break;

        case 1:
        {
            Competitor.set_name(QS_Line);
        }
            break;

        case 2:
        {
            Competitor.set_competitor_class(QS_Line == QS_Female);
        }
            break;

        case 3:
        {
            Challenge.set_name(QS_Line);
        }
            break;

        case 4:
        {
            bool ok;
            double score = QS_Line.toDouble(&ok);
            if(ok)
            {
                Score = score;
            }
            else
            {
                IS_Competitor.close();
                return false;
            }
        }
            break;

        case 5:
        {
            QDT_Recorded = QDT_Recorded.fromString(QS_Line, QS_DateTimeFormat);
        }
            break;

        default:
            break;
        }

        i++;
    }

    return true;
}
