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
#include <ncm_obj_competition.h>
#include <ncm_obj_challenge.h>
#include <ncm_obj_try.h>

//namespaces
using namespace std;

class NCM_OBJ_Ranking_Challenge
{

public:
    explicit NCM_OBJ_Ranking_Challenge();

signals:

};

#endif // NCM_OBJ_RANKING_CHALLENGE_H
