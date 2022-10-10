#ifndef NCM_OBJ_TRY_H
#define NCM_OBJ_TRY_H

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
#include <ncm_obj_competitor.h>
#include <ncm_obj_challenge.h>

//namespaces
using namespace std;

class NCM_OBJ_Try
{
public:
    explicit NCM_OBJ_Try();
    explicit NCM_OBJ_Try(NCM_OBJ_Challenge challenge, NCM_OBJ_Competitor competitor, double score);

    void set_challenge(NCM_OBJ_Challenge challenge)         {Challenge = challenge;}
    void set_competitor(NCM_OBJ_Competitor competitor)      {Competitor = competitor;}
    void set_score(double score)                            {Score = score;}

    NCM_OBJ_Challenge   challenge()                         {return Challenge;}
    NCM_OBJ_Competitor  competitor()                        {return Competitor;}
    size_t              score()                             {return Score;}
    QDateTime           recorded()                          {return QDT_Recorded;}

    int                 time_to_ms(QDateTime QDT_other)     {return -QDT_Recorded.msecsTo(QDT_other);}
    int                 time_since_ms(QDateTime QDT_other)  {return QDT_Recorded.msecsTo(QDT_other);}

    bool                better_then(NCM_OBJ_Try try_other)  {return Challenge.order_more_is_better() ? Score > try_other.score() : Score < try_other.score();}
    bool                worse_then(NCM_OBJ_Try try_other)   {return Challenge.order_more_is_better() ? Score < try_other.score() : Score > try_other.score();}
    bool                equal(NCM_OBJ_Try try_other)        {return Score == try_other.score();}
    bool                operator>(NCM_OBJ_Try try_other)    {return worse_then(try_other);}
    bool                operator<(NCM_OBJ_Try try_other)    {return better_then(try_other);}

    bool                earlier_then(NCM_OBJ_Try try_other) {return time_to_ms(try_other.recorded()) < 0;}
    bool                later_then(NCM_OBJ_Try try_other)   {return time_to_ms(try_other.recorded()) > 0;}

    bool                save(QDir DIR_Tries);
    bool                load(QString QS_path);

private:

    NCM_OBJ_Competitor  Competitor;
    NCM_OBJ_Challenge   Challenge;

    double              Score;

    QDateTime           QDT_Recorded;
};

#endif // NCM_OBJ_TRY_H
