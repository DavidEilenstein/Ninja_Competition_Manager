#ifndef NCM_OBJ_RANKING_COMBI_H
#define NCM_OBJ_RANKING_COMBI_H

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
#include <ncm_obj_ranking_challenge.h>
#include <ncm_obj_ranking_stage.h>

//namespaces
using namespace std;

class NCM_OBJ_Ranking_Combi
{

public:

    NCM_OBJ_Ranking_Combi();

    void                set_stage_this(QFileInfo fi_stage)                      {RankingStageThis.set_stage(fi_stage);}
    void                set_stage_this_competitors(QDir dir_competitors)        {RankingStageThis.set_competitors(dir_competitors);}
    void                set_stage_this_runs(QDir dir_runs)                      {RankingStageThis.set_runs(dir_runs);}

    void                set_stage_previous(QFileInfo fi_stage)                  {RankingStagePrevious.set_stage(fi_stage); StagePreviousRelevant = true;}
    void                set_stage_previous_competitors(QDir dir_competitors)    {RankingStagePrevious.set_competitors(dir_competitors);}
    void                set_stage_previous_runs(QDir dir_runs)                  {RankingStagePrevious.set_runs(dir_runs);}

    void                load_competitors()                                      {RankingStageThis.load_competitors();           RankingStagePrevious.load_competitors();}
    void                load_runs()                                             {RankingStageThis.load_runs();                  RankingStagePrevious.load_runs();}
    void                calc_competitors_allowed()                              {RankingStageThis.calc_competitors_allowed();   RankingStagePrevious.calc_competitors_allowed();}

    void                update();

    size_t              runs_count_stage_this()                                 {return RankingStageThis.count_runs();}
    size_t              pos_stage_current_overall(size_t i)                     {return RankingStageThis.pos_current_overall(i);}
    size_t              pos_stage_current_class(size_t i)                       {return RankingStageThis.pos_current_class(i);}
    size_t              pos_stage_worst_overall(size_t i)                       {return RankingStageThis.pos_worst_overall(i);}
    size_t              pos_stage_worst_class(size_t i)                         {return RankingStageThis.pos_worst_class(i);}

    /*
    size_t              quali_state(size_t i);
    bool                is_quali_state_stage_previous_safe(size_t i);
    bool                is_quali_state_stage_this_safe(size_t i);
    bool                is_quali_state_stage_this_current(size_t i);
    bool                is_quali_state_stage_challenge(size_t i);
    */


private:

    //Sub Rankings
    bool                                StagePreviousRelevant = false;
    NCM_OBJ_Ranking_Stage               RankingStageThis;
    NCM_OBJ_Ranking_Stage               RankingStagePrevious;
    vector<NCM_OBJ_Ranking_Challenge>   vRankingsChallenges;

    //Lists of Competitors by special quali state
    NCM_OBJ_Competitor_List             Competitors_Qualified_Stage_Previous_Safe;
    NCM_OBJ_Competitor_List             Competitors_Qualified_Challenges;

    //Resulting Combi Ranking
    NCM_OBJ_Competitor_List             Competitors_All;
    vector<size_t>                      vQualiStates;
};

#endif // NCM_OBJ_RANKING_COMBI_H
