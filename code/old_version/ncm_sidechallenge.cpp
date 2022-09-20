#include "ncm_sidechallenge.h"
#include "ui_ncm_sidechallenge.h"

NCM_SideChallenge::NCM_SideChallenge(QDir CompetitionDir, QStringList competitor_classes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NCM_SideChallenge)
{
    ui->setupUi(this);

    DIR_Competition = CompetitionDir;
    QSL_CompetitorClasses = competitor_classes;

    sideChallenge_code_update();

    setWindowTitle("Stage editor - by David Eilenstein");
    setWindowIcon(QIcon(":/logo/Logo_Final.jpg"));
}

NCM_SideChallenge::~NCM_SideChallenge()
{
    delete ui;
}

void NCM_SideChallenge::sideChallenge_code_set_to_ui()
{
    sideChallenge_code_set_to_ui(QSL_sideChallenge_Code);
}

void NCM_SideChallenge::sideChallenge_code_set_to_ui(QStringList stage_code)
{
    QString QS_PlainText_StageCode;
    for(int i = 0; i < stage_code.size(); i++)
        QS_PlainText_StageCode.append(stage_code[i] + "\n");

    ui->plainTextEdit_sideChallengeCode->blockSignals(true);
    ui->plainTextEdit_sideChallengeCode->setPlainText(QS_PlainText_StageCode);
    ui->plainTextEdit_sideChallengeCode->blockSignals(false);

    sideChallenge_code_get_from_ui();
}

void NCM_SideChallenge::sideChallenge_code_get_from_ui()
{
    QStringList QSL_Lines = ui->plainTextEdit_sideChallengeCode->toPlainText().split(QS_NewLine);

    QSL_sideChallenge_Code.clear();
    for(int i = 0; i < QSL_Lines.size(); i++)
        if(!QSL_Lines[i].isEmpty())
            QSL_sideChallenge_Code.append(QSL_Lines[i]);
}

void NCM_SideChallenge::sideChallenge_code_parse()
{
    sideChallenge_code_get_from_ui();

    vQualiGuarantee_CompetitorClasses.clear();
    vQualiGuarantee_GuranteeCount.clear();
    QS_Name = "Side Challenge 1 - Lache Dismount";
    QS_MeasureUnit = "cm";
    Measure_MoreIsBetter = true;

    for(int i = 0; i < QSL_sideChallenge_Code.size(); i++)
    {
        QStringList QSL_Blocks = QSL_sideChallenge_Code[i].split(QS_Separator);
        if(QSL_Blocks.size() > 0)
        {
            QString QS_1stBlock = QSL_Blocks.first();
            if(QS_1stBlock != QS_LineSpace && QS_1stBlock != "")
            {
                int keyword_index = -1;
                for(int k = 0; k < QSL_sideChallenge_Keywords.size() && keyword_index < 0; k++)
                    if(QS_1stBlock == QSL_sideChallenge_Keywords[k])
                        keyword_index = k;

                if(keyword_index >= 0) //valid keyword found
                {
                    switch (keyword_index) {

                    case SIDECHALLENGE_KEYWORD_NAME:
                    {
                        if(QSL_Blocks.size() >= 2)
                            QS_Name = QSL_Blocks[1];
                    }
                        break;

                    case SIDECHALLENGE_KEYWORD_QUALI_CLASS:
                    {
                        if(QSL_Blocks.size() == 3)
                        {
                            int class_index = -1;
                            for(int c = 0; c < QSL_CompetitorClasses.size() && class_index < 0; c++)
                                if(QSL_Blocks[1] == QSL_CompetitorClasses[c])
                                    class_index = c;

                            bool duplicate_found = false;
                            for(size_t i = 0; i < vQualiGuarantee_CompetitorClasses.size(); i++)
                                if(vQualiGuarantee_CompetitorClasses[i] == class_index)
                                    duplicate_found = true;

                            if(!duplicate_found)
                            {
                                if(class_index >= 0 && class_index < QSL_CompetitorClasses.size())
                                {
                                    bool ok;
                                    int number = QSL_Blocks[2].toInt(&ok);

                                    if(ok && number >= 0)
                                    {
                                        vQualiGuarantee_CompetitorClasses.push_back(class_index);
                                        vQualiGuarantee_GuranteeCount.push_back(number);
                                    }
                                }
                            }
                        }
                    }
                        break;

                    case SIDECHALLENGE_KEYWORD_MEASURE:
                    {
                        if(QSL_Blocks.size() >= 3)
                        {
                            QS_MeasureUnit = QSL_Blocks[1];
                            Measure_MoreIsBetter = QSL_Blocks[2] == QS_MoreIsBetter;
                        }
                    }
                        break;

                    default:
                        break;
                    }
                }
            }
        }
    }

    sideChallenge_code_update();
}

void NCM_SideChallenge::sideChallenge_code_update()
{
    QSL_sideChallenge_Code.clear();

    //name
    QSL_sideChallenge_Code.append(
                QSL_sideChallenge_Keywords[SIDECHALLENGE_KEYWORD_NAME] +
                QS_Separator +
                QS_Name);

    QSL_sideChallenge_Code.append(QS_LineSpace);

    //guaranteed quali (class)
    for(size_t i = 0; i < vQualiGuarantee_CompetitorClasses.size(); i++)
        if(i < vQualiGuarantee_GuranteeCount.size())
            if(vQualiGuarantee_CompetitorClasses[i] < QSL_CompetitorClasses.size())
                QSL_sideChallenge_Code.append(
                            QSL_sideChallenge_Keywords[SIDECHALLENGE_KEYWORD_QUALI_CLASS] +
                            QS_Separator +
                            QSL_CompetitorClasses[vQualiGuarantee_CompetitorClasses[i]] +
                            QS_Separator +
                            QString::number(vQualiGuarantee_GuranteeCount[i]));

    QSL_sideChallenge_Code.append(QS_LineSpace);

    //measure
    QSL_sideChallenge_Code.append(
                QSL_sideChallenge_Keywords[SIDECHALLENGE_KEYWORD_MEASURE] +
                QS_Separator +
                QS_MeasureUnit +
                QS_Separator +
                (Measure_MoreIsBetter ? QS_MoreIsBetter : QS_LessIsBetter));

    sideChallenge_code_set_to_ui();
}

void NCM_SideChallenge::sideChallenge_code_load()
{
    QString QS_LoadPath = QFileDialog::getOpenFileName(
                this,
                "Load Side Challenge",
                DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_SIDECHALLENGES],
                tr("*txt *TXT"));

    if(QS_LoadPath.isEmpty())
        return;

    QFileInfo FI(QS_LoadPath);
    if(!FI.exists())
        return;

    if(!(FI.suffix() == "txt") && !(FI.suffix() == "TXT"))
        return;

    ifstream IS_sideChallengeCode;
    IS_sideChallengeCode.open(FI.absoluteFilePath().toStdString());

    if(!IS_sideChallengeCode.is_open())
        return;

    QSL_sideChallenge_Code.clear();

    string ST_line;
    while(getline(IS_sideChallengeCode, ST_line))
    {
        QString QS_Line = QString::fromStdString(ST_line);
        QSL_sideChallenge_Code.push_back(QS_Line);
    }

    IS_sideChallengeCode.close();

    sideChallenge_code_set_to_ui();
    sideChallenge_code_parse();
}

void NCM_SideChallenge::sideChallenge_code_save()
{
    sideChallenge_code_parse();

    QString QS_SavePath = QFileDialog::getSaveFileName(
                this,
                "Save Side Challenge",
                DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_SIDECHALLENGES] + "/" + QS_Name + ".txt",
                tr("*txt *TXT"));

    QFileInfo FI(QS_SavePath);
    if(!(FI.suffix() == "txt") && !(FI.suffix() == "TXT"))
        return;

    ofstream OF_sideChallengeCode;
    OF_sideChallengeCode.open(FI.absoluteFilePath().toStdString());
    if(!OF_sideChallengeCode.is_open())
        return;

    for(int i = 0; i < QSL_sideChallenge_Code.size(); i++)
        OF_sideChallengeCode << QSL_sideChallenge_Code[i].toStdString() << QS_NewLine.toStdString();

    OF_sideChallengeCode.close();
    saved = true;
}

void NCM_SideChallenge::on_pushButton_ChangeName_clicked()
{
    sideChallenge_code_parse();

    bool ok;
    QString QS_NewName = QInputDialog::getText(
                this,
                "Side Challenge Name",
                "Enter Side Challange Name",
                QLineEdit::Normal,
                QS_Name,
                &ok);

    if(!ok || QS_NewName.isEmpty())
        return;

    QS_Name = QS_NewName;

    sideChallenge_code_update();
}

void NCM_SideChallenge::on_pushButton_SetMeasure_clicked()
{
    sideChallenge_code_parse();

    bool ok;
    QString QS_NewUnit = QInputDialog::getText(
                this,
                "Measure Unit",
                "Enter Measurement Unit",
                QLineEdit::Normal,
                QS_MeasureUnit,
                &ok);

    if(!ok || QS_NewUnit.isEmpty())
        return;

    QS_MeasureUnit = QS_NewUnit;

    int answer = QMessageBox::question(
                this,
                "Measure Order",
                "Which is the better score?",
                "More",
                "Less",
                "Close",
                Measure_MoreIsBetter ? 0 : 1,
                2);

    if(answer == 0) Measure_MoreIsBetter = true;
    if(answer == 1) Measure_MoreIsBetter = false;
    if(answer == 2) return;

    sideChallenge_code_update();
}

void NCM_SideChallenge::on_pushButton_AddQuali_clicked()
{
    sideChallenge_code_parse();

    bool ok;
    QString QS_CompClass = QInputDialog::getItem(
                this,
                "Select competitor class",
                "Please select the competitor class you want to add a rule for.",
                QSL_CompetitorClasses,
                0,
                false,
                &ok);

    if(!ok || QS_CompClass.isEmpty())
        return;

    int index_comp_class = -1;
    for(int i = 0; i < QSL_CompetitorClasses.size(); i++)
        if(QS_CompClass == QSL_CompetitorClasses[i])
            index_comp_class = i;

    if(index_comp_class < 0)
        return;

    for(size_t i = 0; i < vQualiGuarantee_CompetitorClasses.size(); i++)
        if(vQualiGuarantee_CompetitorClasses[i] == index_comp_class)
        {
            QMessageBox::warning(
                        this,
                        "Duplicate detected",
                        "For this competitor class a guranteed qualification role allready exists.\n"
                        "There can only be one per competitor class.\n"
                        "If you want to remove an existing one, please edit the side challenge code text (just remove the line with the rule you want to remove).");
            return;
        }

    int count_guaranteed = QInputDialog::getInt(
                this,
                "Guaranteed number",
                "How many persons from the competitor class '" + QS_CompClass + "' do you want to guarantee for the next stage?",
                0,
                0,
                999999,
                1,
                &ok);
    if(!ok)
        return;

    vQualiGuarantee_CompetitorClasses.push_back(index_comp_class);
    vQualiGuarantee_GuranteeCount.push_back(count_guaranteed);

    sideChallenge_code_update();
}

void NCM_SideChallenge::on_pushButton_Load_clicked()
{
    sideChallenge_code_load();
}

void NCM_SideChallenge::on_pushButton_Save_clicked()
{
    sideChallenge_code_save();
}

void NCM_SideChallenge::on_pushButton_Close_clicked()
{
    if(!saved)
    {
        int answer = QMessageBox::question(
                    this,
                    "Save?",
                    "There are unsaved changes. Do you want to save the side challenge now?");

        if(answer == QMessageBox::StandardButton::Yes)
            sideChallenge_code_save();
        else if (answer == QMessageBox::StandardButton::No)
            this->close();
    }
    else
    {
        this->close();
    }
}

void NCM_SideChallenge::on_plainTextEdit_sideChallenge_textChanged()
{
    saved = false;
}
