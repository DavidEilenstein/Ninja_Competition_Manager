#ifndef NCM_OBJ_RANKING_CHALLENGE_LIST_H
#define NCM_OBJ_RANKING_CHALLENGE_LIST_H

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
#include <ncm_obj_ranking_challenge.h>

//namespaces
using namespace std;

class NCM_OBJ_Ranking_Challenge_List
{
public:
    NCM_OBJ_Ranking_Challenge_List();
    NCM_OBJ_Ranking_Challenge_List(QDir dir_challenges, QDir dir_tries, QDir dir_competitors, QStringList challenge_names);

    void set_dir_challenges(QDir dir_challenges)                                                        {DIR_Challenges = dir_challenges;}
    void set_dir_tries(QDir dir_tries)                                                                  {DIR_Tries = dir_tries;}
    void set_dir_competitors(QDir dir_competitors)                                                      {DIR_Competitors = dir_competitors;}
    void set_dirs(QDir dir_challenges, QDir dir_tries, QDir dir_competitors)                            {set_dir_challenges(dir_challenges); set_dir_tries(dir_tries); set_dir_competitors(dir_competitors);}
    void set_challenges(QStringList challenge_names)                                                    {QSL_ChallengeNames = challenge_names;}
    void load(QDir dir_challenges, QDir dir_tries, QDir dir_competitors, QStringList challenge_names)   {set_dirs(dir_challenges, dir_tries, dir_competitors); set_challenges(challenge_names); load();}
    void load();

    void update();

    NCM_OBJ_Ranking_Challenge ranking(size_t c)                                                         {return c < size() ? vRankings[c] : NCM_OBJ_Ranking_Challenge();}
    bool contains_tryer(NCM_OBJ_Competitor c)                                                           {for(size_t i = 0; i < size(); i++) if(ranking(i).challengetrys().competitors_list().contains_name(c.name())) return true; return false;}

    size_t size()                                                                                       {return vRankings.size();}

private:

    QDir DIR_Challenges;
    QDir DIR_Tries;
    QDir DIR_Competitors;
    QStringList QSL_ChallengeNames;
    vector<NCM_OBJ_Ranking_Challenge> vRankings;
};

#endif // NCM_OBJ_RANKING_CHALLENGE_LIST_H
