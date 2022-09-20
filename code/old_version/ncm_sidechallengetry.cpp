#include "ncm_sidechallengetry.h"

NCM_sideChallengeTry::NCM_sideChallengeTry(QDir competition_dir, QString sideChallenge_name, QObject *parent) :
    NCM_Competitor(
        QDir(competition_dir.path() + "/" + QSL_CompDirs[COMP_DIR_COMPETITORS]),
        parent)
{
    DIR_Competition = competition_dir;
    QS_sideChallenge_Name =sideChallenge_name;

    DIR_Tries.setPath(DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_SIDECHALLENGE_TRIES]);

    DIR_TriesThisStage.setPath(DIR_Tries.path() + "/" + QS_sideChallenge_Name);
    if(!DIR_TriesThisStage.exists())
        QDir().mkdir(DIR_TriesThisStage.path());

    QDT_Recorded = QDateTime::currentDateTime();
}

void NCM_sideChallengeTry::set_competitor(NCM_Competitor *competitor)
{
    set_data(
                competitor->competitor_dir(),
                competitor->name(),
                competitor->competitor_class(),
                competitor->number());
}

bool NCM_sideChallengeTry::save()
{
    QString QS_StartNumber_6digits;
    if(number() < 10)
        QS_StartNumber_6digits = "00000" + QString::number(number());
    else if(number() < 100)
        QS_StartNumber_6digits = "0000" + QString::number(number());
    else if(number() < 1000)
        QS_StartNumber_6digits = "000" + QString::number(number());
    else if(number() < 10000)
        QS_StartNumber_6digits = "00" + QString::number(number());
    else if(number() < 100000)
        QS_StartNumber_6digits = "0" + QString::number(number());
    else
        QS_StartNumber_6digits = QString::number(number());

    QString QS_FileName = DIR_TriesThisStage.path() + "/Try_" + QS_sideChallenge_Name + "_" + QS_StartNumber_6digits + "_" + name() + ".txt";

    ofstream OF_Try;
    OF_Try.open(QS_FileName.toStdString());
    if(!OF_Try.is_open())
        return false;

    OF_Try << number() << "\n";
    OF_Try << name().toStdString() << "\n";
    OF_Try << competitor_class().toStdString() << "\n";
    OF_Try << QS_sideChallenge_Name.toStdString() << "\n";
    OF_Try << score << "\n";
    OF_Try << QDT_Recorded.toString(QS_DateTimeFormat).toStdString();

    OF_Try.close();

    return true;
}

bool NCM_sideChallengeTry::load()
{
    QString QS_StartNumber_6digits;
    if(number() < 10)
        QS_StartNumber_6digits = "00000" + QString::number(number());
    else if(number() < 100)
        QS_StartNumber_6digits = "0000" + QString::number(number());
    else if(number() < 1000)
        QS_StartNumber_6digits = "000" + QString::number(number());
    else if(number() < 10000)
        QS_StartNumber_6digits = "00" + QString::number(number());
    else if(number() < 100000)
        QS_StartNumber_6digits = "0" + QString::number(number());
    else
        QS_StartNumber_6digits = QString::number(number());

    QString QS_FileName = DIR_TriesThisStage.path() + "/Run_" + QS_sideChallenge_Name + "_" + QS_StartNumber_6digits + "_" + name() + ".txt";

    return load(QS_FileName);
}

bool NCM_sideChallengeTry::load(QString QS_path)
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
                set_starter_number(number);
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
            set_name(QS_Line);
        }
            break;

        case 2:
        {
            set_competitor_class(QS_Line);
        }
            break;

        case 3:
        {
            QS_sideChallenge_Name = QS_Line;
        }
            break;

        case 4:
        {
            bool ok;
            int score_read = QS_Line.toInt(&ok);
            if(ok)
            {
                score = score_read;
            }
            else
            {
                return false;
                IS_Competitor.close();
            }
        }
            break;

        case 5:
        {
            QDT_Recorded = QDT_Recorded.fromString(QS_Line, QS_DateTimeFormat);
            qDebug() << QS_Line << QDT_Recorded;
        }
            break;

        default:
            break;
        }

        i++;
    }

    return true;
}


