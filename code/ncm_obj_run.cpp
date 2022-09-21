#include "ncm_obj_run.h"

NCM_OBJ_Run::NCM_OBJ_Run()
{
    QDT_Recorded = QDateTime::currentDateTime();
}

NCM_OBJ_Run::NCM_OBJ_Run(NCM_OBJ_Stage stage, NCM_OBJ_Competitor competitor, QString cp, int t_min, int t_s, int t_ms)
{
    QDT_Recorded = QDateTime::currentDateTime();
    set_stage(stage);
    set_competitor(competitor);
    set_checkpoint_reached(cp);
    set_time(t_min, t_s, t_ms);
}

bool NCM_OBJ_Run::save(QDir DIR_Runs)
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

    QString QS_FileName = DIR_Runs.path() + "/Run_" + Stage.name() + "_" + QS_StartNumber_6digits + "_" + Competitor.name() + ".txt";

    ofstream OF_Run;
    OF_Run.open(QS_FileName.toStdString());
    if(!OF_Run.is_open())
        return false;

    OF_Run << Competitor.number() << "\n";
    OF_Run << Competitor.name().toStdString() << "\n";
    OF_Run << (Competitor.female() ? QS_Female : QS_Male).toStdString() << "\n";
    OF_Run << Stage.name().toStdString() << "\n";
    OF_Run << QS_CheckpointReached.toStdString() << "\n";
    OF_Run << Time_ms << "\n";
    OF_Run << QDT_Recorded.toString(QS_DateTimeFormat).toStdString();

    OF_Run.close();

    return true;
}

bool NCM_OBJ_Run::load(QString QS_path)
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
                return false;
                IS_Competitor.close();
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
            Stage.set_name(QS_Line);
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
                Time_ms = number;
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
            //qDebug() << QS_Line << QDT_Recorded;
        }
            break;

        default:
            break;
        }

        i++;
    }

    return true;
}
