#ifndef NCM_OBJ_RANKING_CHALLENGE_H
#define NCM_OBJ_RANKING_CHALLENGE_H

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
#include <ncm_obj_challenge.h>
#include <ncm_obj_try_list.h>

//namespaces
using namespace std;

class NCM_OBJ_Ranking_Challenge
{

public:
    explicit NCM_OBJ_Ranking_Challenge();

    bool                    set_competitors(QDir dir_competitors)       {return Competitors_All.load(dir_competitors);}
    bool                    set_tries(QDir dir_tries)                   {return Tries.load(dir_tries);}
    bool                    set_challenge(QFileInfo fi_challenge)       {return Challenge.load(fi_challenge);}

    void                    load_competitors()                          {Competitors_All.load();}
    void                    load_tries()                                {Tries.load();}
    void                    calc_competitors_allowed()                  {Competitors_Allowed = Competitors_All.subtract(Tries.competitors_list());}

    void                    update()                                    {Challenge.load(); load_competitors(); load_tries(); calc_competitors_allowed(); Tries.sort(Challenge.order_more_is_better());}

    size_t                  count_tries()                               {return Tries.size();}
    size_t                  count_competitors_all()                     {return Competitors_All.size();}
    size_t                  count_competitors_allowed()                 {return Competitors_Allowed.size();}

    size_t                  pos_current_overall(NCM_OBJ_Competitor c);
    size_t                  pos_current_class(NCM_OBJ_Competitor c);
    size_t                  pos_worst_overall(NCM_OBJ_Competitor c);
    size_t                  pos_worst_class(NCM_OBJ_Competitor c);

    NCM_OBJ_Try             challengetry(NCM_OBJ_Competitor c);
    NCM_OBJ_Competitor      competitor(size_t i)                        {return Competitors_All.get_competitor(i);}
    NCM_OBJ_Competitor_List competitor_list_all()                       {return Competitors_All;}
    NCM_OBJ_Competitor_List competitor_list_allowed()                   {return Competitors_Allowed;}
    NCM_OBJ_Try             challengetry(size_t i)                      {return Tries.get_try(i);}
    NCM_OBJ_Try_List        challengetrys()                             {return Tries;}

    NCM_OBJ_Challenge       challenge()                                 {return Challenge;}


private:

    NCM_OBJ_Challenge       Challenge;
    NCM_OBJ_Competitor_List Competitors_All;
    NCM_OBJ_Competitor_List Competitors_Allowed;
    NCM_OBJ_Try_List        Tries;
};

#endif // NCM_OBJ_RANKING_CHALLENGE_H
