#ifndef NCM_SIDECHALLENGETRY_H
#define NCM_SIDECHALLENGETRY_H

#include <QObject>
#include <QDir>
#include <fstream>
#include <ncm_competitor.h>
#include <NCM_enum.h>
#include <QDateTime>
#include <QDebug>

class NCM_sideChallengeTry : public NCM_Competitor
{
    Q_OBJECT
public:
    NCM_sideChallengeTry(QDir competition_dir, QString sideChallenge_name, QObject *parent = nullptr);

    double get_score    ()                              {return score;}

    void set_competitor (NCM_Competitor *competitor);
    void set_score      (double s)                      {score = s;}

    bool save();
    bool load();
    bool load(QString QS_path);

    QDateTime   TimeOfMeasurement()                                     {return QDT_Recorded;}
    int         Time_since_other_try_seconds(QDateTime QDT_compare)     {return abs(QDT_compare.secsTo(QDT_Recorded));}

private:
    QDir DIR_Competition;
    QDir DIR_Tries;
    QDir DIR_TriesThisStage;

    int time_ms = 0;
    double score;
    QString QS_sideChallenge_Name = "";

    QDateTime QDT_Recorded;
};

#endif // NCM_SIDECHALLENGETRY_H
