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
    QStringList QSL_Lines = ui->plainTextEdit_StageCode->toPlainText().split("\"");

    QSL_Stage_Code.clear();
    for(int i = 0; i < QSL_Lines.size(); i++)
        if(!QSL_Lines[i].isEmpty())
            QSL_Stage_Code.append(QSL_Lines[i]);
}

void NCM_Stage::stage_code_parse()
{
    stage_code_get_from_ui();


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

}

void NCM_Stage::stage_code_save()
{

}

void NCM_Stage::on_plainTextEdit_StageCode_textChanged()
{
    stage_code_parse();
    saved = false;
}

void NCM_Stage::on_pushButton_EditStageName_clicked()
{
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

void NCM_Stage::on_pushButton_AddObstacle_clicked()
{

}

void NCM_Stage::on_pushButton_MoveObstacle_clicked()
{

}

void NCM_Stage::on_pushButton_RemoveObstacle_clicked()
{

}

void NCM_Stage::on_pushButton_ClearStage_clicked()
{

}

void NCM_Stage::on_pushButton_ChangeQualiMode_clicked()
{

}

void NCM_Stage::on_pushButton_EditCompetitorClasses_clicked()
{

}

void NCM_Stage::on_pushButton_AddGuaranteeRule_clicked()
{

}

void NCM_Stage::on_pushButton_Load_clicked()
{

}

void NCM_Stage::on_pushButton_Save_clicked()
{

}

void NCM_Stage::on_pushButton_Cancel_clicked()
{

}

void NCM_Stage::on_pushButton_Close_clicked()
{

}
