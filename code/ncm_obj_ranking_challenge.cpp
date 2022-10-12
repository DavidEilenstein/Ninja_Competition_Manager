#include "ncm_obj_ranking_challenge.h"

NCM_OBJ_Ranking_Challenge::NCM_OBJ_Ranking_Challenge()
{

}

size_t NCM_OBJ_Ranking_Challenge::pos_current_overall(NCM_OBJ_Competitor c)
{
    Tries.set_challenge(Challenge);

    NCM_OBJ_Try c_challengetry = challengetry(c);
    size_t pos = 1;

    for(size_t r = 0; r < Tries.size(); r++)
    {
        if(challengetry(r).competitor().is_name(c.name()))
            return pos;

        if(challengetry(r).better_then(c_challengetry))
            pos++;
    }

    return pos;
}

size_t NCM_OBJ_Ranking_Challenge::pos_current_class(NCM_OBJ_Competitor c)
{
    Tries.set_challenge(Challenge);

    bool female = c.female();
    NCM_OBJ_Try c_challengetry = challengetry(c);
    size_t pos = 1;

    for(size_t r = 0; r < Tries.size(); r++)
    {
        if(challengetry(r).competitor().female() == female)
        {
            if(challengetry(r).competitor().is_name(c.name()))
                return pos;

            if(challengetry(r).better_then(c_challengetry))
                pos++;
        }
    }

    return pos;
}

size_t NCM_OBJ_Ranking_Challenge::pos_worst_overall(NCM_OBJ_Competitor c)
{
    return pos_current_overall(c) + Competitors_Allowed.size();
}

size_t NCM_OBJ_Ranking_Challenge::pos_worst_class(NCM_OBJ_Competitor c)
{
    return pos_current_class(c) + Competitors_Allowed.count_in_class(c.female());
}

NCM_OBJ_Try NCM_OBJ_Ranking_Challenge::challengetry(NCM_OBJ_Competitor c)
{
    for(size_t r = 0; r < Tries.size(); r++)
        if(Tries.get_try(r).competitor().is_name(c.name()))
            return challengetry(r);

    return NCM_OBJ_Try();
}


