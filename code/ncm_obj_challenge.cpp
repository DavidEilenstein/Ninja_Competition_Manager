#include "ncm_obj_challenge.h"

NCM_OBJ_Challenge::NCM_OBJ_Challenge()
{

}

bool NCM_OBJ_Challenge::load()
{
    if(FI_ChallengeFile.suffix() != "txt" && FI_ChallengeFile.suffix() != "TXT")
        return false;

    if(!FI_ChallengeFile.exists())
        return false;

    ifstream IS_ChallengeCode;
    IS_ChallengeCode.open(FI_ChallengeFile.absoluteFilePath().toStdString());

    if(!IS_ChallengeCode.is_open())
        return false;

    QSL_Challenge_Code.clear();

    string ST_line;
    while(getline(IS_ChallengeCode, ST_line))
    {
        QString QS_Line = QString::fromStdString(ST_line);
        QSL_Challenge_Code.push_back(QS_Line);
    }

    IS_ChallengeCode.close();

    code_parse();

    return true;
}

bool NCM_OBJ_Challenge::save()
{
    if(FI_ChallengeFile.suffix() != "txt" && FI_ChallengeFile.suffix() != "TXT")
        return false;

    if(!FI_ChallengeFile.dir().exists())
        QDir().mkdir(FI_ChallengeFile.dir().path());
    if(!FI_ChallengeFile.dir().exists())
        return false;

    code_update();

    ofstream OF_ChallengeCode;
    OF_ChallengeCode.open(FI_ChallengeFile.absoluteFilePath().toStdString());
    if(!OF_ChallengeCode.is_open())
        return false;

    for(int i = 0; i < QSL_Challenge_Code.size(); i++)
        OF_ChallengeCode << QSL_Challenge_Code[i].toStdString() << QS_NewLine.toStdString();

    OF_ChallengeCode.close();

    return true;
}

bool NCM_OBJ_Challenge::code_update()
{
    //clear
    QSL_Challenge_Code.clear();

    //name
    QSL_Challenge_Code.append(
                QSL_Challenge_Keywords[CHALLENGE_KEYWORD_NAME] +
                QS_Separator +
                QS_Name);

    QSL_Challenge_Code.append(QS_LineSpace);//------------------------------;

    //Measure - unit
    QSL_Challenge_Code.append(
                QSL_Challenge_Keywords[CHALLENGE_KEYWORD_UNIT] +
                QS_Separator +
                QS_Unit);

    //Measure - order
    QSL_Challenge_Code.append(
                QSL_Challenge_Keywords[CHALLENGE_KEYWORD_ORDER] +
                QS_Separator +
                (OrderMoreIsBetter ? QS_OrderMoreIsBetter : QS_OrderLessIsBetter));

    QSL_Challenge_Code.append(QS_LineSpace);//------------------------------;

    //quali
    QSL_Challenge_Code.append(
                QSL_Challenge_Keywords[CHALLENGE_KEYWORD_QUALI_FEMALE] +
                QS_Separator +
                QString::number(QualiCount_F));
    QSL_Challenge_Code.append(
                QSL_Challenge_Keywords[CHALLENGE_KEYWORD_QUALI_MALE] +
                QS_Separator +
                QString::number(QualiCount_M));

    return true;
}


bool NCM_OBJ_Challenge::code_parse()
{
    for(int i = 0; i < QSL_Challenge_Code.size(); i++)
    {
        QStringList QSL_Blocks = QSL_Challenge_Code[i].split(QS_Separator);
        if(QSL_Blocks.size() > 0)
        {
            QString QS_1stBlock = QSL_Blocks.first();
            if(QS_1stBlock != QS_LineSpace && QS_1stBlock != "")
            {
                int keyword_index = -1;
                for(int k = 0; k < QSL_Challenge_Keywords.size() && keyword_index < 0; k++)
                    if(QS_1stBlock == QSL_Challenge_Keywords[k])
                        keyword_index = k;

                if(keyword_index >= 0) //valid keyword found
                {
                    switch (keyword_index) {

                    case CHALLENGE_KEYWORD_NAME:
                    {
                        if(QSL_Blocks.size() >= 2)
                            QS_Name = QSL_Blocks[1];
                    }
                        break;

                    case CHALLENGE_KEYWORD_UNIT:
                    {
                        if(QSL_Blocks.size() >= 2)
                            QS_Unit = QSL_Blocks[1];
                    }
                        break;

                    case CHALLENGE_KEYWORD_ORDER:
                    {
                        if(QSL_Blocks.size() >= 2)
                            OrderMoreIsBetter = QSL_Blocks[1] == QS_OrderMoreIsBetter;
                    }
                        break;

                    case CHALLENGE_KEYWORD_QUALI_FEMALE:
                    {
                        if(QSL_Blocks.size() >= 2)
                        {
                            bool ok;
                            int count = QSL_Blocks[1].toInt(&ok);
                            if(ok)
                                QualiCount_F = count;
                            else
                                return false;
                        }
                    }
                        break;

                    case CHALLENGE_KEYWORD_QUALI_MALE:
                    {
                        if(QSL_Blocks.size() >= 2)
                        {
                            bool ok;
                            int count = QSL_Blocks[1].toInt(&ok);
                            if(ok)
                                QualiCount_M = count;
                            else
                                return false;
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

    return code_update();
}

