#include "ncm_run.h"

NCM_Run::NCM_Run(QDir competition_dir, QString stage_name, QObject *parent) :
    NCM_Competitor(
        QDir(competition_dir.path() + "/" + QSL_CompDirs[COMP_DIR_COMPETITORS]),
        parent)
{
    DIR_Competition = competition_dir;
    QS_StageName = stage_name;

    DIR_Runs.setPath(DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_RUNS]);

    DIR_RunsThisStage.setPath(DIR_Runs.path() + "/" + QS_StageName);
    if(!DIR_RunsThisStage.exists())
        QDir().mkdir(DIR_RunsThisStage.path());

    QDT_Recorded = QDateTime::currentDateTime();
}

void NCM_Run::set_competitor(NCM_Competitor *competitor)
{
    set_data(
                competitor->competitor_dir(),
                competitor->name(),
                competitor->competitor_class(),
                competitor->number());
}

void NCM_Run::set_time(int minutes, int seconds, int milli_seconds)
{
    return set_time(minutes * 60 + seconds, milli_seconds);
}

void NCM_Run::set_time(int seconds, int milli_seconds)
{
    return set_time(seconds * 1000 + milli_seconds);
}

void NCM_Run::set_time(int milli_seconds)
{
    time_ms = milli_seconds;
}

bool NCM_Run::save()
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

    QString QS_FileName = DIR_RunsThisStage.path() + "/Run_" + QS_StageName + "_" + QS_StartNumber_6digits + "_" + name() + ".txt";

    ofstream OF_Run;
    OF_Run.open(QS_FileName.toStdString());
    if(!OF_Run.is_open())
        return false;

    OF_Run << number() << "\n";
    OF_Run << name().toStdString() << "\n";
    OF_Run << competitor_class().toStdString() << "\n";
    OF_Run << QS_StageName.toStdString() << "\n";
    OF_Run << QS_CheckpointReached.toStdString() << "\n";
    OF_Run << time_in_ms() << "\n";
    OF_Run << QDT_Recorded.toString(QS_DateTimeFormat).toStdString();

    OF_Run.close();

    return true;
}

bool NCM_Run::load()
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

    QString QS_FileName = DIR_RunsThisStage.path() + "/Run_" + QS_StageName + "_" + QS_StartNumber_6digits + "_" + name() + ".txt";

    return load(QS_FileName);
}

bool NCM_Run::load(QString QS_path)
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
            QS_StageName = QS_Line;
        }
            break;

        case 4:
        {
            QS_CheckpointReached = QS_Line;
        }
            break;

        case 5:
        {
            bool ok;
            int number = QS_Line.toInt(&ok);
            if(ok)
            {
                time_ms = number;
            }
            else
            {
                return false;
                IS_Competitor.close();
            }
        }
            break;

        case 6:
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



