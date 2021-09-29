#ifndef NCM_RUN_H
#define NCM_RUN_H

#include <QObject>
#include <QDir>
#include <fstream>
#include <ncm_competitor.h>
#include <NCM_enum.h>

class NCM_Run : public NCM_Competitor
{
    Q_OBJECT
public:
    explicit NCM_Run(QDir competition_dir, QString stage_name, QObject *parent = nullptr);

    QString checkpoint_reached()    {return QS_CheckpointReached;}
    int time_in_ms()                {return time_ms;}

    void set_competitor(NCM_Competitor *competitor);
    void set_time(int minutes, int seconds, int milli_seconds);
    void set_time(int seconds, int milli_seconds);
    void set_time(int milli_seconds);

    void set_checkpoint_reached(QString checkpoint) {QS_CheckpointReached = checkpoint;}

    bool save();
    bool load();
    bool load(QString QS_path);

signals:

private:
    QDir DIR_Competition;
    QDir DIR_Runs;
    QDir DIR_RunsThisStage;

    int time_ms = 0;
    QString QS_CheckpointReached = "";
    QString QS_StageName = "";
};

#endif // NCM_RUN_H
