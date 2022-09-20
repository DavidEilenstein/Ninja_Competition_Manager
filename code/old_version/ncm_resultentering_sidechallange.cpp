#include "ncm_resultentering_sidechallange.h"
#include "ui_ncm_resultentering_sidechallange.h"

NCM_ResultEntering_SideChallange::NCM_ResultEntering_SideChallange(QDir competition_dir, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NCM_ResultEntering_SideChallange)
{
    ui->setupUi(this);

    DIR_Competition = competition_dir;

    DIR_Competitors.setPath(DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_COMPETITORS]);
    if(!DIR_Competitors.exists())
        QDir().mkdir(DIR_Competitors.path());

    get_data_dialog();

    setWindowTitle("Result entering (side challenge) - by David Eilenstein");
    setWindowIcon(QIcon(":/logo/Logo_Final.jpg"));
}

NCM_ResultEntering_SideChallange::~NCM_ResultEntering_SideChallange()
{
    delete ui;
}

void NCM_ResultEntering_SideChallange::get_data_dialog()
{
    if(state_data_loaded)
        return;

    //------------------------------- competitors

    QString QS_CompetitorsLoadPath = QFileDialog::getExistingDirectory(
                this,
                "Select competitors directory",
                DIR_Competitors.path());

    if(QS_CompetitorsLoadPath.isEmpty())
        return;

    DIR_CompetitorsThisChallenge.setPath(QS_CompetitorsLoadPath);
    if(!DIR_CompetitorsThisChallenge.exists())
        return;

    //------------------------------- stage

    QString QS_StageLoadPath = QFileDialog::getOpenFileName(
                this,
                "Select side challenge file",
                DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_SIDECHALLENGES],
                tr("*.txt *.TXT"));

    if(QS_StageLoadPath.isEmpty())
        return;

    FI_sideChallengeFile.setFile(QS_StageLoadPath);
    if(!FI_sideChallengeFile.exists())
        return;
    if(FI_sideChallengeFile.suffix() != "txt" && FI_sideChallengeFile.suffix() != "TXT")
        return;
    QS_Name = FI_sideChallengeFile.baseName();
    ui->label_Name->setText(QS_Name);

    //------------------------------- output

    DIR_Tries_Out.setPath(DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_SIDECHALLENGE_TRIES] + "/" + QS_Name);
    if(!DIR_Tries_Out.exists())
        QDir().mkdir(DIR_Tries_Out.path());

    //------------------------------- load if everything is correct

    if(!load_competitors())
        return;

    if(!load_tries())
        return;

    if(!calc_competitors_allowed_to_try())
        return;

    state_data_loaded = true;
    ui->centralwidget->setEnabled(true);
    ui->actionChallange_and_Competitor_selection->setEnabled(false);
}

bool NCM_ResultEntering_SideChallange::load_competitors()
{
    if(state_data_loaded)
        return false;

    vCompetitorsAll.clear();
    QFileInfoList FIL_Competitors = DIR_CompetitorsThisChallenge.entryInfoList();
    for(int i = 0; i < FIL_Competitors.size(); i++)
    {
        qDebug() << "try to load" << FIL_Competitors[i].absoluteFilePath();
        if(FIL_Competitors[i].exists())
            if(FIL_Competitors[i].suffix() == "txt" || FIL_Competitors[i].suffix() == "TXT")
                if(FIL_Competitors[i].baseName().startsWith("Competitor_"))
                {
                    NCM_Competitor *competitor = new NCM_Competitor(DIR_CompetitorsThisChallenge);
                    if(competitor->load(FIL_Competitors[i].absoluteFilePath()))
                        vCompetitorsAll.push_back(competitor);
                    else
                        delete competitor;
                }
    }

    qDebug() << vCompetitorsAll.size() << "competitors found";
    return true;
}

bool NCM_ResultEntering_SideChallange::load_tries()
{
    if(state_data_loaded)
        return false;

    vTriesDone.clear();
    QFileInfoList FIL_Tries = DIR_Tries_Out.entryInfoList();
    for(int i = 0; i < FIL_Tries.size(); i++)
        if(FIL_Tries[i].exists())
            if(FIL_Tries[i].suffix() == "txt" || FIL_Tries[i].suffix() == "TXT")
                if(FIL_Tries[i].baseName().startsWith("Try_"))
                {
                    NCM_sideChallengeTry *run = new NCM_sideChallengeTry(DIR_Competition, QS_Name);
                    if(run->load(FIL_Tries[i].absoluteFilePath()))
                        vTriesDone.push_back(run);
                    else
                        delete run;
                }

    qDebug() << vTriesDone.size() << "tries loaded";
    return true;
}

bool NCM_ResultEntering_SideChallange::calc_competitors_allowed_to_try()
{
    QSL_CompetitorsAllowedToTry.clear();
    for(size_t c = 0; c < vCompetitorsAll.size(); c++)
    {
        QString QS_NameOfCompetitor = vCompetitorsAll[c]->name();
        bool allowed = true;

        if(!ui->checkBox_AllowMultiTries->isChecked())
            for(size_t t = 0; t < vTriesDone.size() && allowed; t++)
                if(QS_NameOfCompetitor == vTriesDone[t]->name())
                    allowed = false;

        if(allowed)
            QSL_CompetitorsAllowedToTry.append(QS_NameOfCompetitor);
    }

    ui->comboBox_Competitors->clear();
    ui->comboBox_Competitors->addItems(QSL_CompetitorsAllowedToTry);

    qDebug() << QSL_CompetitorsAllowedToTry.size() << "competitors allowed to try";
    return true;
}

void NCM_ResultEntering_SideChallange::on_actionChallange_and_Competitor_selection_triggered()
{
    get_data_dialog();
}

void NCM_ResultEntering_SideChallange::on_pushButton_SaveTry_clicked()
{
    NCM_sideChallengeTry *Try = new NCM_sideChallengeTry(DIR_Competition, QS_Name);

    QString QS_NameOfCompetitor = ui->comboBox_Competitors->currentText();
    bool competitor_found = false;
    for(size_t i = 0; i < vCompetitorsAll.size() && !competitor_found; i++)
        if(vCompetitorsAll[i]->name() == QS_NameOfCompetitor)
        {
            competitor_found = true;
            Try->set_competitor(vCompetitorsAll[i]);
        }

    if(!competitor_found)
    {
        QMessageBox::warning(
                    this,
                    "Competitor unkown",
                    "The selected competitor '" + QS_NameOfCompetitor + "' was not found in the list of competitors!");
        delete Try;
        return;
    }

    Try->set_score(ui->doubleSpinBox_Score->value());

    Try->save();
    vTriesDone.push_back(Try);

    calc_competitors_allowed_to_try();

    ui->comboBox_Competitors->setCurrentIndex(0);
    ui->doubleSpinBox_Score->setValue(0);
}
