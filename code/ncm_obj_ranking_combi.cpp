#include "ncm_obj_ranking_combi.h"

NCM_OBJ_Ranking_Combi::NCM_OBJ_Ranking_Combi()
{

}

void NCM_OBJ_Ranking_Combi::update()
{
    //load and calc
    load_competitors();
    load_runs();
    calc_competitors_allowed();

    //update rankings
    RankingStageThis.update();
    RankingStagePrevious.update();

    //clear competitor categories
    Competitors_Qualified_Stage_Previous.clear();
    Competitors_Qualified_Challenges.clear();

    //quali from previous stage
    if(StagePreviousRelevant)
    {
        //loop runs
        size_t n_runs_prev = RankingStagePrevious.count_runs();
        for(size_t r = 0; r < n_runs_prev; r++)
        {
            NCM_OBJ_Competitor competitor = RankingStagePrevious.run(r).competitor();

            if(RankingStagePrevious.pos_current_class(competitor) <= RankingStageThis.stage().quali_count_previous(competitor.female()))
                Competitors_Qualified_Stage_Previous.add_competitor(competitor);
        }
    }

    //sizes
    size_t n_competitors = RankingStageThis.count_competitors_all();

    //quali states and combi ranking competitor list
    Competitors_All.clear();
    vQualiStates.clear();
    vQualiStates.resize(n_competitors, QUALI_STATE_UNKNOWN);

    //loop competitors
    for(size_t c = 0; c < n_competitors; c++)
    {
        NCM_OBJ_Competitor competitor = RankingStageThis.competitor(c);
        Competitors_All.add_competitor(competitor);

        size_t quali_spots_this = RankingStageThis.stage().quali_count_this(competitor.female());
        size_t quali_spots_prev = RankingStageThis.stage().quali_count_previous(competitor.female());

        bool got_quali_state = false;

        //stage previous
        if(!got_quali_state && Competitors_Qualified_Stage_Previous.contains_duplicate(competitor))
        {
            vQualiStates[c] = QUALI_STATE_QUALI_STAGE_PREVIOUS_SAFE;
            got_quali_state = true;
        }

        //stage this qualified
        if(!got_quali_state && RankingStageThis.runs().competitors_list().contains_duplicate(competitor))
        {
            //safe?
            if(!got_quali_state && RankingStageThis.pos_worst_class(competitor) <= quali_spots_this + quali_spots_prev)
            {
                Competitors_Qualified_Stage_This.add_competitor(competitor);
                vQualiStates[c] = QUALI_STATE_QUALI_STAGE_THIS_SAFE;
                got_quali_state = true;
            }

            //current?
            if(!got_quali_state && RankingStageThis.pos_current_class(competitor) <= quali_spots_this + quali_spots_prev)
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
        if(!got_quali_state)
        {
            vQualiStates[c] = QUALI_STATE_UNKNOWN;
        }
    }
}

NCM_OBJ_Competitor_List NCM_OBJ_Ranking_Combi::competitors_qualified()
{
    NCM_OBJ_Competitor_List qualified_competitors;
    for(size_t c = 0; c < Competitors_All.size(); c++)
        if(vQualiStates[c] == QUALI_STATE_QUALI_STAGE_PREVIOUS_SAFE || vQualiStates[c] == QUALI_STATE_QUALI_STAGE_THIS_SAFE || vQualiStates[c] == QUALI_STATE_QUALI_CHALLENGE)
            qualified_competitors.add_competitor(Competitors_All.get_competitor(c));

    return qualified_competitors;
}

size_t NCM_OBJ_Ranking_Combi::quali_state(NCM_OBJ_Competitor competitor)
{
    for(size_t c = 0; c < Competitors_All.size(); c++)
        if(competitor.is_duplicate(Competitors_All.get_competitor(c)))
            return vQualiStates[c];

    return QUALI_STATE_UNKNOWN;
}


