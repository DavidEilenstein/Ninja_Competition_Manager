#ifndef NCM_COMPETITION_H
#define NCM_COMPETITION_H

#include <QDebug>
#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <fstream>
#include <vector>
#include <NCM_enum.h>

using namespace std;

namespace Ui {
class NCM_Competition;
}

class NCM_Competition : public QDialog
{
    Q_OBJECT

public:
    explicit NCM_Competition(QDir *pMasterDir, QWidget *parent = nullptr);
    NCM_Competition();
    ~NCM_Competition();

    void create_dialogue();
    bool load_dialogue();

    void set_dir_master(QDir *master_dir)       {pDIR_Master = master_dir;}

    bool is_valid()                             {return valid;}
    QDir dir_competition()                      {return DIR_Competition;}
    QDir *pdir_master()                         {return pDIR_Master;}
    vector<QDir> vdir_competition_subdirs()     {return vDIR_CompetitionSubdirs;}
    int number_of_stages()                      {return stages_count;}
    QStringList competitor_classes()            {return QSL_CompetitorClasses;}
    QString name()                              {return QS_CompetitionName;}


private slots:
    void on_pushButton_Create_clicked();

    void on_pushButton_Cancel_clicked();

    void on_lineEdit_CompetitionName_textChanged(const QString &arg1);

    void on_spinBox_StageCount_valueChanged(int arg1);

    void on_plainTextEdit_CompetitorCalsses_textChanged();

private:

    bool save();

    Ui::NCM_Competition *ui;

    QString QS_CompetitionName = "Competition_Name";

    QDir *pDIR_Master = nullptr;
    QDir DIR_Competition = QDir();
    vector<QDir> vDIR_CompetitionSubdirs;

    int stages_count = 1;
    QStringList QSL_CompetitorClasses = {"female", "male"};

    bool valid = false;
};

#endif // NCM_COMPETITION_H
