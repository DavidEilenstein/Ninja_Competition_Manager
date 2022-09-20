#ifndef NCM_OBJ_COMPETITION_H
#define NCM_OBJ_COMPETITION_H

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

//namespaces
using namespace std;

class NCM_OBJ_Competition : public QObject
{
    Q_OBJECT
public:
    explicit NCM_OBJ_Competition(QObject *parent = nullptr);

signals:

};

#endif // NCM_OBJ_COMPETITION_H
