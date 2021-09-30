#ifndef NCM_MAINWINDOW_H
#define NCM_MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileInfo>
#include <QStringList>
#include <vector>
#include <fstream>
#include <ncm_stage.h>
#include <ncm_competitor.h>
#include <ncm_competition.h>
#include <ncm_checkin.h>
#include <ncm_resultentering.h>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class NCM_MainWindow; }
QT_END_NAMESPACE

class NCM_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    NCM_MainWindow(QWidget *parent = nullptr);
    ~NCM_MainWindow();

    void settings_load();
    void settings_save();

private slots:
    void on_pushButton_CompetitionCreate_clicked();

    void on_pushButton_CompetitionLoad_clicked();

    void on_pushButton_EditStages_clicked();

    void on_pushButton_Checkin_clicked();

    void on_pushButton_ResultsEntering_clicked();

    void on_pushButton_StarterList_clicked();

    void on_pushButton_Ranking_clicked();

private:
    Ui::NCM_MainWindow *ui;

    QDir DIR_Master;
    QDir DIR_Settings;
    QFileInfo FI_Settings;

    NCM_Competition *competition;

    NCM_CheckIn *pCheckIn;
    NCM_ResultEntering *pResultEntering;
};
#endif // NCM_MAINWINDOW_H
