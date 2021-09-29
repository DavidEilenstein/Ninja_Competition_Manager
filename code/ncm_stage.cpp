#include "ncm_stage.h"
#include "ui_ncm_stage.h"

NCM_Stage::NCM_Stage(QDir CompetitionDir, QStringList competitor_classes, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NCM_Stage)
{
    ui->setupUi(this);

    DIR_Competition = CompetitionDir;
    QSL_CompetitorClasses = competitor_classes;

    stage_code_update();
}

NCM_Stage::~NCM_Stage()
{
    delete ui;
}

void NCM_Stage::stage_code_set_to_ui()
{
    stage_code_set_to_ui(QSL_Stage_Code);
}

void NCM_Stage::stage_code_set_to_ui(QStringList stage_code)
{
    QString QS_PlainText_StageCode;
    for(int i = 0; i < stage_code.size(); i++)
        QS_PlainText_StageCode.append(stage_code[i] + "\n");

    ui->plainTextEdit_StageCode->blockSignals(true);
    ui->plainTextEdit_StageCode->setPlainText(QS_PlainText_StageCode);
    ui->plainTextEdit_StageCode->blockSignals(false);

    stage_code_get_from_ui();
}

void NCM_Stage::stage_code_get_from_ui()
{
    QStringList QSL_Lines = ui->plainTextEdit_StageCode->toPlainText().split(QS_NewLine);

    QSL_Stage_Code.clear();
    for(int i = 0; i < QSL_Lines.size(); i++)
        if(!QSL_Lines[i].isEmpty())
            QSL_Stage_Code.append(QSL_Lines[i]);
}

void NCM_Stage::stage_code_parse()
{
    stage_code_get_from_ui();

    QSL_CheckpointNames.clear();
    vQualiGuarantee_CompetitorClasses.clear();
    vQualiGuarantee_GuranteeCount.clear();
    vQualiGuarantee_GuaranteeMode.clear();
    QualiGuarantee_SpeedPreviousStage_Mode = QUALI_GUARANTEE_INCLUSIVE;
    QualiGuarantee_SpeedPreviousStage_Count = 0;
    QS_Name = "Example Name";
    quali_mode = QUALI_ALL;
    quali_number = 0;

    bool obstacle_section_started = false;
    for(int i = 0; i < QSL_Stage_Code.size(); i++)
    {
        QStringList QSL_Blocks = QSL_Stage_Code[i].split(QS_Separator);
        if(QSL_Blocks.size() > 0)
        {
            QString QS_1stBlock = QSL_Blocks.first();
            if(QS_1stBlock != QS_LineSpace && QS_1stBlock != "")
            {
                if(!obstacle_section_started)
                {
                    int keyword_index = -1;
                    for(int k = 0; k < QSL_Stage_Keywords.size() && keyword_index < 0; k++)
                        if(QS_1stBlock == QSL_Stage_Keywords[k])
                            keyword_index = k;

                    if(keyword_index >= 0) //valid keyword found
                    {
                        switch (keyword_index) {

                        case STAGE_KEYWORD_NAME:
                        {
                            if(QSL_Blocks.size() >= 2)
                                QS_Name = QSL_Blocks[1];
                        }
                            break;

                        case STAGE_KEYWORD_QUALI:
                        {
                            if(QSL_Blocks.size() >= 2)
                            {
                                int quali_mode_index = -1;
                                for(int q = 0; q < QSL_Quali.size() && quali_mode_index < 0; q++)
                                    if(QSL_Blocks[1] == QSL_Quali[q])
                                        quali_mode_index = q;

                                if(quali_mode_index >= 0 && quali_mode_index < QUALI_NUMBER_OF)
                                {
                                    if(quali_mode_index == QUALI_NUMBER)
                                    {
                                        if(QSL_Blocks.size() >= 3)
                                        {
                                            bool ok;
                                            int number = QSL_Blocks[2].toInt(&ok);
                                            if(ok && number >= 0)
                                            {
                                                quali_mode = quali_mode_index;
                                                quali_number = number;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        quali_mode = quali_mode_index;
                                        quali_number = 0;
                                    }
                                }
                            }
                        }
                            break;

                        case STAGE_KEYWORD_QUALI_GUARANTEE_CLASS:
                        {
                            if(QSL_Blocks.size() == 4)
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
                                            int inclusion_index = -1;
                                            for(int j = 0; j < QSL_QualiGuaranteeMode.size() && inclusion_index < 0; j++)
                                                if(QSL_Blocks[3] == QSL_QualiGuaranteeMode[j])
                                                    inclusion_index = j;

                                            if(inclusion_index >= 0 && inclusion_index < QUALI_GUARANTEE_NUMBER_OF)
                                            {
                                                vQualiGuarantee_CompetitorClasses.push_back(class_index);
                                                vQualiGuarantee_GuranteeCount.push_back(number);
                                                vQualiGuarantee_GuaranteeMode.push_back(inclusion_index);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                            break;

                        case STAGE_KEYWORD_QUALI_GUARANTEE_SPEED:
                        {
                            if(QSL_Blocks.size() == 3)
                            {
                                bool ok;
                                int number = QSL_Blocks[1].toInt(&ok);

                                if(ok && number >= 0)
                                {
                                    int inclusion_index = -1;
                                    for(int j = 0; j < QSL_QualiGuaranteeMode.size() && inclusion_index < 0; j++)
                                        if(QSL_Blocks[2] == QSL_QualiGuaranteeMode[j])
                                            inclusion_index = j;

                                    if(inclusion_index >= 0 && inclusion_index < QUALI_GUARANTEE_NUMBER_OF)
                                    {
                                        QualiGuarantee_SpeedPreviousStage_Mode = inclusion_index;
                                        QualiGuarantee_SpeedPreviousStage_Count = number;
                                    }
                                }
                            }
                        }
                            break;

                        case STAGE_KEYWORD_OBSTACLES:
                        {
                            QSL_CheckpointNames.clear();
                            obstacle_section_started = true;
                        }
                            break;

                        default:
                            break;
                        }
                    }
                }
                else
                {
                    QSL_CheckpointNames.push_back(QS_1stBlock);
                }
            }
        }
    }

    stage_code_update();
}

void NCM_Stage::stage_code_update()
{
    QSL_Stage_Code.clear();

    //name
    QSL_Stage_Code.append(
                QSL_Stage_Keywords[STAGE_KEYWORD_NAME] +
                QS_Separator +
                QS_Name);

    QSL_Stage_Code.append(QS_LineSpace);

    //quali
    if(quali_mode == QUALI_NUMBER)
        QSL_Stage_Code.append(
                    QSL_Stage_Keywords[STAGE_KEYWORD_QUALI] +
                    QS_Separator +
                    QSL_Quali[quali_mode] +
                    QS_Separator +
                    QString::number(quali_number));
    else
        QSL_Stage_Code.append(
                    QSL_Stage_Keywords[STAGE_KEYWORD_QUALI] +
                    QS_Separator +
                    QSL_Quali[quali_mode]);

    //guaranteed quali (class)
    for(size_t i = 0; i < vQualiGuarantee_CompetitorClasses.size(); i++)
        if(i < vQualiGuarantee_GuranteeCount.size())
            if(i < vQualiGuarantee_GuaranteeMode.size())
                if(vQualiGuarantee_CompetitorClasses[i] < QSL_CompetitorClasses.size())
                    if(vQualiGuarantee_GuaranteeMode[i] < QSL_QualiGuaranteeMode.size())
                        QSL_Stage_Code.append(
                                    QSL_Stage_Keywords[STAGE_KEYWORD_QUALI_GUARANTEE_CLASS] +
                                    QS_Separator +
                                    QSL_CompetitorClasses[vQualiGuarantee_CompetitorClasses[i]] +
                                    QS_Separator +
                                    QString::number(vQualiGuarantee_GuranteeCount[i]) +
                                    QS_Separator +
                                    QSL_QualiGuaranteeMode[vQualiGuarantee_GuaranteeMode[i]]);

    //guaranteed quali (speed)
    if(QualiGuarantee_SpeedPreviousStage_Count > 0)
        QSL_Stage_Code.append(
                    QSL_Stage_Keywords[STAGE_KEYWORD_QUALI_GUARANTEE_SPEED] +
                    QS_Separator +
                    QString::number(QualiGuarantee_SpeedPreviousStage_Count) +
                    QS_Separator +
                    QSL_QualiGuaranteeMode[QualiGuarantee_SpeedPreviousStage_Mode]);

    QSL_Stage_Code.append(QS_LineSpace);

    //obstacles
    QSL_Stage_Code.append(
                QSL_Stage_Keywords[STAGE_KEYWORD_OBSTACLES]);

    QSL_Stage_Code.append(QS_LineSpace);

    for(int i = 0; i < QSL_CheckpointNames.size(); i++)
        QSL_Stage_Code.append(QSL_CheckpointNames[i]);

    stage_code_set_to_ui();
}

void NCM_Stage::stage_code_load()
{
    QString QS_LoadPath = QFileDialog::getOpenFileName(
                this,
                "Load Stage",
                DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_STAGES],
                tr("*txt *TXT"));

    if(QS_LoadPath.isEmpty())
        return;

    QFileInfo FI(QS_LoadPath);
    if(!FI.exists())
        return;

    if(!(FI.suffix() == "txt") && !(FI.suffix() == "TXT"))
        return;

    ifstream IS_StageCode;
    IS_StageCode.open(FI.absoluteFilePath().toStdString());

    if(!IS_StageCode.is_open())
        return;

    QSL_Stage_Code.clear();

    string ST_line;
    while(getline(IS_StageCode, ST_line))
    {
        QString QS_Line = QString::fromStdString(ST_line);
        QSL_Stage_Code.push_back(QS_Line);
    }

    IS_StageCode.close();

    stage_code_set_to_ui();
    stage_code_parse();
}

void NCM_Stage::stage_code_save()
{
    stage_code_parse();

    QString QS_SavePath = QFileDialog::getSaveFileName(
                this,
                "Save Stage",
                DIR_Competition.path() + "/" + QSL_CompDirs[COMP_DIR_STAGES],
                tr("*txt *TXT"));

    QFileInfo FI(QS_SavePath);
    if(!(FI.suffix() == "txt") && !(FI.suffix() == "TXT"))
        return;

    ofstream OF_StageCode;
    OF_StageCode.open(FI.absoluteFilePath().toStdString());
    if(!OF_StageCode.is_open())
        return;

    for(int i = 0; i < QSL_Stage_Code.size(); i++)
        OF_StageCode << QSL_Stage_Code[i].toStdString() << QS_NewLine.toStdString();

    OF_StageCode.close();
    saved = true;
}

void NCM_Stage::on_plainTextEdit_StageCode_textChanged()
{
    saved = false;
}

void NCM_Stage::on_pushButton_EditStageName_clicked()
{
    stage_code_parse();

    bool ok;
    QString QS_NewName = QInputDialog::getText(
                this,
                "Stage Name",
                "Enter Stage Name",
                QLineEdit::Normal,
                QS_Name,
                &ok);

    if(!ok || QS_NewName.isEmpty())
        return;

    QS_Name = QS_NewName;

    stage_code_update();
}

void NCM_Stage::on_pushButton_ChangeQualiMode_clicked()
{
    stage_code_parse();

    bool ok;
    QString QS_SelectedMode = QInputDialog::getItem(
                this,
                "Select quali mode",
                "Please select the mode how competitors move to next stage.",
                QSL_QualiDetailed,
                quali_mode,
                false,
                &ok);

    if(!ok || QS_SelectedMode.isEmpty())
        return;

    for(int i = 0; i < QSL_QualiDetailed.size(); i++)
        if(QS_SelectedMode == QSL_QualiDetailed[i])
            quali_mode = i;

    if(quali_mode == QUALI_NUMBER)
    {
        int competitors_qualified = QInputDialog::getInt(
                    this,
                    "Select number of competitors to qualifiy",
                    "Please select number of competitors that qualify for the next stage:",
                    quali_number,
                    0,
                    999999,
                    1,
                    &ok);
        if(!ok)
            return;

        quali_number = competitors_qualified;
    }

    stage_code_update();
}

void NCM_Stage::on_pushButton_AddGuaranteeRule_clicked()
{
    stage_code_parse();

    switch (QMessageBox::question(
                this,
                "Add qualification guarantee rule",
                "Do you want to add a rule for a competitor class or for speed?",
                "Competitor class", "Speed", "Cancel",
                0,
                2))
    {

    case 0://competitor class
    {
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
                            "If you want to remove an existing one, please edit the stage code text (just remove the line with the rule you want to remove).");
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

        int include_mode = QMessageBox::question(
                    this,
                    "Inclusion mode",
                    "Do you want the " + QString::number(count_guaranteed) + " guaranteed competitors of competitor class '" + QS_CompClass + "'"
                    "to be included or excluded in the total number of competitors that move to next stage?\n"
                    "\n"
                    "Included means that these competitors will be included in the regular number of qualifications - so no extra spots.\n"
                    "\n"
                    "Excluded means that these competitors will be added up to the regular number of qualifications - extra spots",
                    "Included", //QUALI_GUARANTEE_INCLUSIVE=0
                    "Excldued", //QUALI_GUARANTEE_EXCLUSIVE=1
                    "Cancel",
                    1,
                    2);
        if(include_mode != QUALI_GUARANTEE_INCLUSIVE && include_mode != QUALI_GUARANTEE_EXCLUSIVE)
            return;

        vQualiGuarantee_CompetitorClasses.push_back(index_comp_class);
        vQualiGuarantee_GuranteeCount.push_back(count_guaranteed);
        vQualiGuarantee_GuaranteeMode.push_back(include_mode);
    }
        break;

    case 1://speed
    {
        bool ok;
        int count_guaranteed = QInputDialog::getInt(
                    this,
                    "Speed pass",
                    "How many competitors from a previous stage will be guaranteed\n"
                    "to move to next stage for beeing fastest in that previous stage?",
                    0,
                    0,
                    999999,
                    1,
                    &ok);
        if(count_guaranteed < 1 || !ok)
            return;

        int include_mode = QMessageBox::question(
                    this,
                    "Inclusion mode",
                    "Do you want the " + QString::number(count_guaranteed) + " guaranteed competitors that were the fastest in a previous stage"
                    "to be included or excluded in the total number of competitors that move to next stage?\n"
                    "\n"
                    "Included means that these competitors will be included in the regular number of qualifications - so no extra spots.\n"
                    "\n"
                    "Excluded means that these competitors will be added up to the regular number of qualifications - extra spots",
                    "Included", //QUALI_GUARANTEE_INCLUSIVE=0
                    "Excldued", //QUALI_GUARANTEE_EXCLUSIVE=1
                    "Cancel",
                    1,
                    2);
        if(include_mode != QUALI_GUARANTEE_INCLUSIVE && include_mode != QUALI_GUARANTEE_EXCLUSIVE)
            return;

        QualiGuarantee_SpeedPreviousStage_Count = count_guaranteed;
        QualiGuarantee_SpeedPreviousStage_Mode = include_mode;
    }
        break;

    default:
        return;

    }

    stage_code_update();
}

void NCM_Stage::on_pushButton_Load_clicked()
{
    stage_code_load();
}

void NCM_Stage::on_pushButton_Save_clicked()
{
    stage_code_save();
}

void NCM_Stage::on_pushButton_Close_clicked()
{
    if(!saved)
    {
        int answer = QMessageBox::question(
                    this,
                    "Save?",
                    "There are unsaved changes. Do you want to save the stage now?");

        if(answer == QMessageBox::StandardButton::Yes)
            stage_code_save();
        else if (answer == QMessageBox::StandardButton::No)
            this->close();
    }
    else
    {
        this->close();
    }
}
