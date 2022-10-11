#ifndef NCM_ENUM_H
#define NCM_ENUM_H

#include <QStringList>
#include <vector>
#include <QColor>

using namespace std;

const QString QS_VersionNumber = "v2.1 - 2022_09_25";

enum COMP_DIR {
    COMP_DIR_GENERAL,
    COMP_DIR_STAGES,
    COMP_DIR_COMPETITORS,
    COMP_DIR_RUNS,
    COMP_DIR_SPECIAL_PRICES,
    COMP_DIR_SCREENSHOTS,
    COMP_DIR_CHALLENGES,
    COMP_DIR_CHALLENGE_TRIES,
    COMP_DIR_NUMBER_OF
};
const QStringList QSL_CompDirs = {
    "General",
    "Stages",
    "Competitors",
    "Runs",
    "SpecialPrices",
    "Competition_Status_Images",
    "Challenges",
    "ChallengeTries"
};

const QString QS_FemaleSymbol = "♀";
const QString QS_MaleSymbol = "♂";

const QString QS_Female = "female";
const QString QS_Male = "male";

enum STAGE_KEYWORDS {
    STAGE_KEYWORD_NAME,
    STAGE_KEYWORD_FINAL,
    STAGE_KEYWORD_QUALI_THIS_STAGE_F,
    STAGE_KEYWORD_QUALI_THIS_STAGE_M,
    STAGE_KEYWORD_QUALI_PREVIOUS_STAGE_F,
    STAGE_KEYWORD_QUALI_PREVIOUS_STAGE_M,
    STAGE_KEYWORD_CHALLENGE_LIST,
    STAGE_KEYWORD_CHECKPOINTS,
    STAGE_KEYWORD_NUMBER_OF
};
const QStringList QSL_Stage_Keywords = {
    "NAME",
    "FINAL",
    "QUALI_THIS_STAGE_FEMALE",
    "QUALI_THIS_STAGE_MALE",
    "QUALI_PREVIOUS_STAGE_FEMALE",
    "QUALI_PREVIOUS_STAGE_MALE",
    "CHALLENGE_LIST",
    "CHECKPOINTS"
};

const QString QS_IsFinal = "Final";
const QString QS_IsNotFinal = "IsNotFinal";

enum CHALLENGE_KEYWORDS {
    CHALLENGE_KEYWORD_NAME,
    CHALLENGE_KEYWORD_UNIT,
    CHALLENGE_KEYWORD_ORDER,
    CHALLENGE_KEYWORD_QUALI_FEMALE,
    CHALLENGE_KEYWORD_QUALI_MALE,
    CHALLENGE_KEYWORD_NUMBER_OF
};
const QStringList QSL_Challenge_Keywords = {
    "NAME",
    "UNIT",
    "ORDER",
    "QUALI_FEMALE",
    "QUALI_MALE"
};

const QString QS_OrderMoreIsBetter = "MoreIsBetter";
const QString QS_OrderLessIsBetter = "LessIsBetter";

enum QUALI_STATE {
    QUALI_STATE_QUALI_STAGE_PREVIOUS_SAFE,
    QUALI_STATE_QUALI_STAGE_THIS_CURRENT,
    QUALI_STATE_QUALI_STAGE_THIS_SAFE,
    QUALI_STATE_QUALI_CHALLENGE,
    QUALI_STATE_1ST,
    QUALI_STATE_2ND,
    QUALI_STATE_3RD,
    QUALI_STATE_END,
    QUALI_STATE_OUT,
    QUALI_STATE_UNKNOWN,
    QUALI_STATE_NUMBER_OF
};
const QStringList QSL_QualiState = {
    "👽",
    "🐻",
    "🐯",
    "💪",
    "🥇",
    "🥈",
    "🥉",
    "🐱‍👤",
    "💀",
    "❓"
};
const QString QS_QualiChallengeThis = "🦾";

const QString QS_FileName_SpecialPrice_BestTrick = "BestTrick.txt";
const QString QS_FileName_SpecialPrice_WorstFail = "WorstFail.txt";

const QString QS_Separator = ";";
const QString QS_NewLine = "\n";
const QString QS_LineSpace = "----------------";
const QString QS_DateTimeFormat = "yyyy.MM.dd hh:mm:ss";

const QString QS_Buzzer = "🛎️";

const QStringList QSl_AllowedChars {
    "a",
    "b",
    "c",
    "d",
    "e",
    "f",
    "g",
    "h",
    "i",
    "j",
    "k",
    "l",
    "m",
    "n",
    "o",
    "p",
    "q",
    "r",
    "s",
    "t",
    "u",
    "v",
    "w",
    "x",
    "y",
    "z",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    " ",
    "-",
    "_"
};

#endif // NCM_ENUM_H
