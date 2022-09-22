#include "ncm_obj_ranking_combi.h"

NCM_OBJ_Ranking_Combi::NCM_OBJ_Ranking_Combi()
{

}

void NCM_OBJ_Ranking_Combi::update()
{
    //update rankings
    RankingStageThis.update();
    RankingStagePrevious.update();

    //clear competitor categories
    Competitors_Qualified_Stage_Previous.clear();
    Competitors_Qualified_Challenges.clear();

    //sizes
    size_t n_competitors    = RankingStageThis.count_competitors_all();
    size_t n_runs_prev      = RankingStagePrevious.count_runs();

    //quali states and combi ranking competitor list
    Competitors_All.clear();
    vQualiStates.clear();
    vQualiStates.resize(n_competitors, QUALI_STATE_UNKNOWN);

    //quali from previous stage
    if(StagePreviousRelevant)
    {
        size_t safe_f       = 0;
        size_t safe_m       = 0;
        size_t safe_max_f   = RankingStageThis.stage().quali_count_previous_f();
        size_t safe_max_m   = RankingStageThis.stage().quali_count_previous_m();

        //loop runs
        for(size_t r = 0; r < n_runs_prev && (safe_f < safe_max_f || safe_m < safe_max_m); r++)
        {
            NCM_OBJ_Competitor competitor = RankingStagePrevious.competitor(r);

            if(competitor.female() && safe_f < safe_max_f)
            {
                Competitors_Qualified_Stage_Previous.add_competitor(competitor);
                safe_f++;
            }

            if(!competitor.female() && safe_m < safe_max_m)
            {
                Competitors_Qualified_Stage_Previous.add_competitor(competitor);
                safe_m++;
            }
        }
    }

    //loop competitors
    for(size_t c = 0; c < n_competitors; c++)
    {
        NCM_OBJ_Competitor competitor = RankingStageThis.competitor(c);
        Competitors_All.add_competitor(competitor);

        bool got_quali_state = false;

        //stage previous
        if(Competitors_Qualified_Stage_Previous.contains_duplicate(competitor))
        {
            vQualiStates[c] = QUALI_STATE_QUALI_STAGE_PREVIOUS_SAFE;
            got_quali_state = true;
        }

        //stage this qualified
        if(!got_quali_state && RankingStageThis.runs().competitors_list().contains_duplicate(competitor))
        {
            //safe?
            if(!got_quali_state && RankingStageThis.pos_worst_class(competitor) <= RankingStageThis.stage().quali_count_this(competitor.female()))
            {
                Competitors_Qualified_Stage_This.add_competitor(competitor);
                vQualiStates[c] = QUALI_STATE_QUALI_STAGE_THIS_SAFE;
                got_quali_state = true;
            }

            //current?
            if(!got_quali_state && RankingStageThis.pos_current_class(competitor) <= RankingStageThis.stage().quali_count_this(competitor.female()))
            {
                Competitors_Qualified_Stage_This.add_competitor(competitor);
                vQualiStates[c] = QUALI_STATE_QUALI_STAGE_THIS_CURRENT;
                got_quali_state = true;
            }
        }

        //challenges

        //stage this not qualified
        if(!got_quali_state && RankingStageThis.runs().competitors_list().contains_duplicate(competitor))
        {
            vQualiStates[c] = QUALI_STATE_OUT;
            got_quali_state = true;
        }

        //did nothing so far
        vQualiStates[c] = QUALI_STATE_UNKNOWN;
    }
}

size_t NCM_OBJ_Ranking_Combi::quali_state(NCM_OBJ_Competitor competitor)
{
    for(size_t c = 0; c < Competitors_All.size(); c++)
        if(competitor.is_duplicate(Competitors_All.get_competitor(c)))
            return vQualiStates[c];

    return QUALI_STATE_UNKNOWN;
}


