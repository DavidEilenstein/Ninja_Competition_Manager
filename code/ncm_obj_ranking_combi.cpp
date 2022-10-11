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
    load_challenges();

    //update rankings
    RankingStageThis.update();
    RankingStagePrevious.update();
    RankingsChallenges.update();

    //clear competitor categories
    Competitors_Qualified_Stage_Previous.clear();
    Competitors_Qualified_Stage_This.clear();
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

    //--------------------------------------------------------------------------- quali stage

    //loop competitors
    for(size_t c = 0; c < n_competitors; c++)
    {
        NCM_OBJ_Competitor competitor = RankingStageThis.competitor(c);
        NCM_OBJ_Run run_this = RankingStageThis.run(competitor);
        Competitors_All.add_competitor(competitor);

        if(RankingStageThis.stage().is_final())
        {
            vQualiStates[c] = QUALI_STATE_END;

            if(RankingStageThis.pos_current_class(competitor) == 1)
                vQualiStates[c] = QUALI_STATE_1ST;
            else if(RankingStageThis.pos_current_class(competitor) == 2)
                vQualiStates[c] = QUALI_STATE_2ND;
            else if(RankingStageThis.pos_current_class(competitor) == 3)
                vQualiStates[c] = QUALI_STATE_3RD;
        }
        else
        {
            //quali spots
            size_t quali_spots_this = RankingStageThis.stage().quali_count_this(competitor.female());

            //count of safe from previous, that are better that this competitors run
            size_t safe_prev_better = 0;
            for(size_t c = 0; c < Competitors_Qualified_Stage_Previous.size(); c++)
            {
                NCM_OBJ_Competitor competitor_safe_prev = Competitors_Qualified_Stage_Previous.get_competitor(c);
                if(RankingStageThis.runs().competitors_list().contains_name(competitor_safe_prev.name()))
                    if(competitor_safe_prev.female() == competitor.female())
                        if(RankingStageThis.run(competitor_safe_prev).better_then(run_this))
                            safe_prev_better++;
            }

            bool got_quali_state = false;

            //stage previous
            if(!got_quali_state && Competitors_Qualified_Stage_Previous.contains_name(competitor.name()))
            {
                vQualiStates[c] = QUALI_STATE_QUALI_STAGE_PREVIOUS_SAFE;
                got_quali_state = true;
            }

            //stage this qualified
            if(!got_quali_state && RankingStageThis.runs().competitors_list().contains_name(competitor.name()))
            {
                //safe?
                if(!got_quali_state && RankingStageThis.pos_worst_class(competitor) <= quali_spots_this + safe_prev_better)
                {
                    qDebug() << competitor.name();
                    Competitors_Qualified_Stage_This.add_competitor(competitor);
                    vQualiStates[c] = QUALI_STATE_QUALI_STAGE_THIS_SAFE;
                    got_quali_state = true;
                }

                //current?
                if(!got_quali_state && RankingStageThis.pos_current_class(competitor) <= quali_spots_this + safe_prev_better)
                {
                    Competitors_Qualified_Stage_This.add_competitor(competitor);
                    vQualiStates[c] = QUALI_STATE_QUALI_STAGE_THIS_CURRENT;
                    got_quali_state = true;
                }
            }

            //stage this not qualified
            if(!got_quali_state && RankingStageThis.runs().competitors_list().contains_name(competitor.name()))
            {
                vQualiStates[c] = QUALI_STATE_OUT;
                got_quali_state = true;
            }
        }
    }

    //--------------------------------------------------------------------------- quali challenge

    //loop challenges
    for(size_t cha = 0; cha < RankingsChallenges.size(); cha++)
    {
        //challenge ranking
        NCM_OBJ_Ranking_Challenge challenge_ranking = RankingsChallenges.ranking(cha);

        //competitors possible quali with this challenge (sorted by score)
        NCM_OBJ_Competitor_List competitors_possible = challenge_ranking.challengetrys().competitors_list().subtract(Competitors_Qualified_Stage_This).subtract(Competitors_Qualified_Stage_Previous).subtract(Competitors_Qualified_Challenges);

        //female/male
        for(int cla = 0; cla < 2; cla++)
        {
            bool female = cla == 0;

            //quali candidates
            NCM_OBJ_Competitor_List competitors_possible_class = competitors_possible.competitors_by_class(female);

            //loop pos
            NCM_OBJ_Competitor competitor_last_added;
            bool added_competitor = false;
            double score_last_added = 0;
            size_t quali_spots = challenge_ranking.challenge().quali_count(female);
            for(size_t pos = 0; pos < quali_spots && pos < competitors_possible_class.size(); pos++)
            {
                //best competitors are at the beginning of the list, bacuase it is taken from sorted tries
                NCM_OBJ_Competitor competitor_qualified = competitors_possible_class.get_competitor(pos);

                Competitors_Qualified_Challenges.add_competitor(competitor_qualified);
                added_competitor = true;
                score_last_added = challenge_ranking.challengetry(competitor_qualified).score();
            }

            //add all competitors with equal score to the last competitor added
            if(added_competitor)
            {
                for(size_t com = 0; com < competitors_possible_class.size(); com++)
                {
                    NCM_OBJ_Competitor competitor_candidate = competitors_possible_class.get_competitor(com);
                    if(challenge_ranking.challengetry(competitor_candidate).score() == score_last_added)
                    {
                        Competitors_Qualified_Challenges.add_competitor(competitor_candidate);
                    }
                }
            }
        }
    }

    //set quali state for challenge qualis
    for(size_t com = 0; com < Competitors_All.size(); com++)
    {
        if(Competitors_Qualified_Challenges.contains_name(Competitors_All.get_competitor(com).name()))
        {
            vQualiStates[com] = QUALI_STATE_QUALI_CHALLENGE;
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
        if(competitor.is_name(Competitors_All.get_competitor(c).name()))
            return vQualiStates[c];

    return QUALI_STATE_UNKNOWN;
}


