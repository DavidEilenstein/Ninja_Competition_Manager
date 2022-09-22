#include "ncm_obj_ranking_stage.h"

NCM_OBJ_Ranking_Stage::NCM_OBJ_Ranking_Stage()
{

}

size_t NCM_OBJ_Ranking_Stage::index_of_competitor(NCM_OBJ_Competitor c)
{
    for(size_t r = 0; r < Runs.size(); r++)
        if(Runs.get_run(r).competitor().is_duplicate(c))
            return r;

    return Runs.size();
}

size_t NCM_OBJ_Ranking_Stage::pos_current_class(size_t i)
{
    bool female = Runs.get_run(i).competitor().female();
    size_t pos = 1;
    for(size_t r = 0; r < i && r < Runs.size(); r++)
        if(Runs.get_run(r).competitor().female() == female)
            pos++;

    return pos;
}

