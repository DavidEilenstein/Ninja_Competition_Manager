#ifndef NCM_RESULTENTERING_H
#define NCM_RESULTENTERING_H

#include <QMainWindow>
#include <QDir>
#include <QInputDialog>
#include <QFileDialog>
#include <fstream>
#include <vector>
#include <ncm_run.h>

using namespace std;

namespace Ui {
class NCM_ResultEntering;
}

class NCM_ResultEntering : public QMainWindow
{
    Q_OBJECT

public:
    explicit NCM_ResultEntering(QDir competition_dir, QWidget *parent = nullptr);
    ~NCM_ResultEntering();

private slots:
    void on_actionStage_and_competitor_selection_triggered();
    void on_pushButton_SaveRun_clicked();

private:
    Ui::NCM_ResultEntering *ui;

    QDir DIR_Competition;
};

#endif // NCM_RESULTENTERING_H
