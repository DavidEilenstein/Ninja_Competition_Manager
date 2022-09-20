#ifndef NCM_SIDECHALLENGE_H
#define NCM_SIDECHALLENGE_H

#include <QDialog>
#include <QInputDialog>
#include <QFileDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QDir>
#include <NCM_enum.h>
#include <fstream>
#include <QIcon>

using namespace std;

namespace Ui {
class NCM_SideChallenge;
}

class NCM_SideChallenge : public QDialog
{
    Q_OBJECT

public:
    explicit NCM_SideChallenge(QDir CompetitionDir, QStringList competitor_classes, QWidget *parent = nullptr);
    ~NCM_SideChallenge();

    void sideChallenge_code_set_to_ui();
    void sideChallenge_code_set_to_ui(QStringList stage_code);
    void sideChallenge_code_get_from_ui();
    void sideChallenge_code_parse();
    void sideChallenge_code_update();
    void sideChallenge_code_load();
    void sideChallenge_code_save();

    private slots:

    void on_pushButton_ChangeName_clicked();

    void on_pushButton_SetMeasure_clicked();

    void on_pushButton_AddQuali_clicked();

    void on_pushButton_Load_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_Close_clicked();

    void on_plainTextEdit_sideChallenge_textChanged();

private:
    Ui::NCM_SideChallenge *ui;

    QDir DIR_Competition;
    QStringList QSL_CompetitorClasses;

    QStringList QSL_sideChallenge_Code;

    QString QS_Name = "Side Challenge 1 - Lache Dismount";
    QString QS_MeasureUnit = "cm";
    bool Measure_MoreIsBetter = true;

    vector<int> vQualiGuarantee_CompetitorClasses = {0, 1};
    vector<int> vQualiGuarantee_GuranteeCount = {1, 1};

    bool saved = false;
};

#endif // NCM_SIDECHALLENGE_H
