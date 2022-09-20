#include "ncm_obj_stage.h"

NCM_OBJ_Stage::NCM_OBJ_Stage()
{

}

NCM_OBJ_Stage::NCM_OBJ_Stage(QFileInfo stage_file)
{
    set_file(stage_file);
    load();
}

QString NCM_OBJ_Stage::checkpoints_as_string_line_by_line()
{
    QString checkpoints;
    for(int l = 0; l < QSL_Checkpoints.size(); l++)
    {
        QString checkpoint = QSL_Checkpoints[l];
        if(!checkpoint.isEmpty())
        {
            if(!checkpoints.isEmpty())
                checkpoints.append("\n");

            checkpoints.append(checkpoint);
        }
    }

    return checkpoints;
}

QString NCM_OBJ_Stage::challenge_names_as_string_line_by_line()
{
    QString challenges;
    for(int l = 0; l < QSL_ChallengeNames.size(); l++)
    {
        QString challenge = QSL_ChallengeNames[l];
        if(!challenge.isEmpty())
        {
            if(!challenges.isEmpty())
                challenges.append("\n");

            challenges.append(challenge);
        }
    }

    return challenges;
}

bool NCM_OBJ_Stage::load()
{
    if(FI_StageFile.suffix() != "txt" && FI_StageFile.suffix() != "TXT")
        return false;

    if(!FI_StageFile.exists())
        return false;

    ifstream IS_StageCode;
    IS_StageCode.open(FI_StageFile.absoluteFilePath().toStdString());

    if(!IS_StageCode.is_open())
        return false;

    QSL_Stage_Code.clear();

    string ST_line;
    while(getline(IS_StageCode, ST_line))
    {
        QString QS_Line = QString::fromStdString(ST_line);
        QSL_Stage_Code.push_back(QS_Line);
    }

    IS_StageCode.close();

    code_parse();

    return true;
}

bool NCM_OBJ_Stage::save()
{
    if(FI_StageFile.suffix() != "txt" && FI_StageFile.suffix() != "TXT")
        return false;

    if(!FI_StageFile.dir().exists())
        QDir().mkdir(FI_StageFile.dir().path());
    if(!FI_StageFile.dir().exists())
        return false;

    code_update();

    ofstream OF_StageCode;
    OF_StageCode.open(FI_StageFile.absoluteFilePath().toStdString());
    if(!OF_StageCode.is_open())
        return false;

    for(int i = 0; i < QSL_Stage_Code.size(); i++)
        OF_StageCode << QSL_Stage_Code[i].toStdString() << QS_NewLine.toStdString();

    OF_StageCode.close();

    return true;
}

void NCM_OBJ_Stage::code_update()
{
    //clear
    QSL_Stage_Code.clear();

    //name
    QSL_Stage_Code.append(
                QSL_Stage_Keywords[STAGE_KEYWORD_NAME] +
                QS_Separator +
                QS_Name);

    QSL_Stage_Code.append(QS_LineSpace);//------------------------------

    //final
    QSL_Stage_Code.append(
                QSL_Stage_Keywords[STAGE_KEYWORD_FINAL] +
                QS_Separator +
                (IsFinal ? QS_IsFinal : QS_IsNotFinal));

    QSL_Stage_Code.append(QS_LineSpace);//------------------------------;

    //quali
    QSL_Stage_Code.append(
                QSL_Stage_Keywords[STAGE_KEYWORD_QUALI_THIS_STAGE_F] +
                QS_Separator +
                QString::number(QualiThisF));
    QSL_Stage_Code.append(
                QSL_Stage_Keywords[STAGE_KEYWORD_QUALI_THIS_STAGE_M] +
                QS_Separator +
                QString::number(QualiThisM));
    QSL_Stage_Code.append(
                QSL_Stage_Keywords[STAGE_KEYWORD_QUALI_PREVIOUS_STAGE_F] +
                QS_Separator +
                QString::number(QualiPreviousF));
    QSL_Stage_Code.append(
                QSL_Stage_Keywords[STAGE_KEYWORD_QUALI_PREVIOUS_STAGE_M] +
                QS_Separator +
                QString::number(QualiPreviousF));

    QSL_Stage_Code.append(QS_LineSpace);//------------------------------;

    //checkpoints
    QSL_Stage_Code.append(
                QSL_Stage_Keywords[STAGE_KEYWORD_CHALLENGE_LIST]);

    QSL_Stage_Code.append(QS_LineSpace);//------------------------------;

    for(int i = 0; i < QSL_ChallengeNames.size(); i++)
            QSL_Stage_Code.append(QSL_ChallengeNames[i]);

    QSL_Stage_Code.append(QS_LineSpace);//------------------------------;

    //checkpoints
    QSL_Stage_Code.append(
                QSL_Stage_Keywords[STAGE_KEYWORD_CHECKPOINTS]);

    QSL_Stage_Code.append(QS_LineSpace);//------------------------------;

    for(int i = 0; i < QSL_Checkpoints.size(); i++)
            QSL_Stage_Code.append(QSL_Checkpoints[i]);
}

void NCM_OBJ_Stage::code_parse()
{
    bool challenge_section_started = false;
    bool chekpoint_section_started = false;

    for(int i = 0; i < QSL_Stage_Code.size(); i++)
    {
        QStringList QSL_Blocks = QSL_Stage_Code[i].split(QS_Separator);
        if(QSL_Blocks.size() > 0)
        {
            QString QS_1stBlock = QSL_Blocks.first();
            if(QS_1stBlock != QS_LineSpace && QS_1stBlock != "")
            {
                if(!challenge_section_started && !chekpoint_section_started)//----------------------------------------
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

                        case STAGE_KEYWORD_FINAL:
                        {
                            if(QSL_Blocks.size() >= 2)
                                IsFinal = QSL_Blocks[1] == QS_IsFinal;
                        }
                            break;

                        case STAGE_KEYWORD_QUALI_THIS_STAGE_F:
                        {
                            if(QSL_Blocks.size() >= 2)
                                QS_Name = QSL_Blocks[1];
                        }
                            break;

                        case STAGE_KEYWORD_CHALLENGE_LIST:
                        {
                            QSL_ChallengeNames.clear();
                            challenge_section_started = true;
                        }
                            break;

                        default:
                            break;
                        }
                    }
                }
                else if(challenge_section_started && !chekpoint_section_started)//----------------------------------------
                {
                    if(QS_1stBlock != QSL_Stage_Keywords[STAGE_KEYWORD_CHECKPOINTS])
                    {
                        QSL_ChallengeNames.push_back(QS_1stBlock);
                        qDebug() << "Challenge:" << QS_1stBlock;
                    }
                    else
                    {
                        QSL_Checkpoints.clear();
                        chekpoint_section_started = true;
                    }
                }
                else if(chekpoint_section_started)//-----------------------------------------------------
                {
                    QSL_Checkpoints.push_back(QS_1stBlock);
                    qDebug() << "Checkpoint:" << QS_1stBlock;
                }
            }
        }
    }

    code_update();
}
