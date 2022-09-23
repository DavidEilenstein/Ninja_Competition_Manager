#include "ncm_obj_ranking_stage.h"

NCM_OBJ_Ranking_Stage::NCM_OBJ_Ranking_Stage()
{

}

size_t NCM_OBJ_Ranking_Stage::pos_current_overall(NCM_OBJ_Competitor c)
{
    NCM_OBJ_Run c_run = run(c);
    size_t pos = 1;

    for(size_t r = 0; r < Runs.size(); r++)
    {
        if(run(r).competitor().is_duplicate(c))
            return pos;

        if(run(r).better_then(c_run))
            pos++;
    }

    return pos;
}

size_t NCM_OBJ_Ranking_Stage::pos_current_class(NCM_OBJ_Competitor c)
{
    bool female = c.female();
    NCM_OBJ_Run c_run = run(c);
    size_t pos = 1;

    for(size_t r = 0; r < Runs.size(); r++)
    {
        if(run(r).competitor().female() == female)
        {
            if(run(r).competitor().is_duplicate(c))
                return pos;

            if(run(r).better_then(c_run))
                pos++;
        }
    }

    return pos;
}

size_t NCM_OBJ_Ranking_Stage::pos_worst_overall(NCM_OBJ_Competitor c)
{
    return pos_current_overall(c) + Competitors_Allowed.size();
}

size_t NCM_OBJ_Ranking_Stage::pos_worst_class(NCM_OBJ_Competitor c)
{
    return pos_current_class(c) + Competitors_Allowed.count_in_class(c.female());
}

NCM_OBJ_Run NCM_OBJ_Ranking_Stage::run(NCM_OBJ_Competitor c)
{
    for(size_t r = 0; r < Runs.size(); r++)
        if(Runs.get_run(r).competitor().is_name(c.name()))
            return run(r);

    return NCM_OBJ_Run();
}


