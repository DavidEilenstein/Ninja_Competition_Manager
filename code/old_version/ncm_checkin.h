#ifndef NCM_CHECKIN_H
#define NCM_CHECKIN_H

#include <QMainWindow>
#include <QDir>
#include <QFileInfo>
#include <QInputDialog>
#include <QFileDialog>
#include <fstream>
#include <vector>
#include <NCM_enum.h>
#include <QStringList>
#include <QFileInfoList>
#include <ncm_competitor.h>
#include <QMessageBox>

using namespace std;

namespace Ui {
class NCM_CheckIn;
}

class NCM_CheckIn : public QMainWindow
{
    Q_OBJECT

public:
    explicit NCM_CheckIn(QDir CompetitionDir, QStringList competitor_classes, QWidget *parent = nullptr);
    ~NCM_CheckIn();

    void load();
    void save();

private slots:
    void on_pushButton_CheckIn_clicked();

private:
    Ui::NCM_CheckIn *ui;

    QDir DIR_Competitors;
    QDir DIR_Competitors_CheckedIn;

    QDir DIR_Competition;
    QStringList QSL_CompetitorClasses;

    vector<NCM_Competitor*> vCompetitors;
};

#endif // NCM_CHECKIN_H
