#include "ncm_obj_ranking_challenge_list.h"

NCM_OBJ_Ranking_Challenge_List::NCM_OBJ_Ranking_Challenge_List()
{

}

NCM_OBJ_Ranking_Challenge_List::NCM_OBJ_Ranking_Challenge_List(QDir dir_challenges, QDir dir_tries, QDir dir_competitors, QStringList challenge_names)
{
    load(dir_challenges, dir_tries, dir_competitors, challenge_names);
}

void NCM_OBJ_Ranking_Challenge_List::load()
{
    vRankings.clear();

    for(int c = 0; c < QSL_ChallengeNames.size(); c++)
    {
        QString QS_ChallengeName = QSL_ChallengeNames[c];
        NCM_OBJ_Ranking_Challenge ranking;

        if(ranking.set_challenge(QFileInfo(DIR_Challenges.path() + "/" + QS_ChallengeName + ".txt")))
        {
            if(ranking.set_tries(QDir(DIR_Tries.path() + "/" + QS_ChallengeName)))
            {
                if(ranking.set_competitors(DIR_Competitors))
                {
                    vRankings.push_back(ranking);
                }
            }
        }
    }
}

void NCM_OBJ_Ranking_Challenge_List::update()
{
    for(size_t c = 0; c < size(); c++)
        vRankings[c].update();
}
