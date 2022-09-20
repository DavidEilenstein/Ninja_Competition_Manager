#ifndef NCM_OBJ_CHALLENGE_H
#define NCM_OBJ_CHALLENGE_H

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

//namespaces
using namespace std;


class NCM_OBJ_Challenge : public QObject
{
    Q_OBJECT
public:
    explicit NCM_OBJ_Challenge(QObject *parent = nullptr);

signals:

};

#endif // NCM_OBJ_CHALLENGE_H
