#ifndef NCM_ENUM_H
#define NCM_ENUM_H

#include <QStringList>

using namespace std;

const QString QS_VersionNumber = "v1.4 - 2022_09_14";

enum COMP_DIR {
    COMP_DIR_GENERAL,
    COMP_DIR_STAGES,
    COMP_DIR_COMPETITORS,
    COMP_DIR_RUNS,
    COMP_DIR_SPECIAL_PRICES,
    COMP_DIR_SCREENSHOTS,
    COMP_DIR_SIDECHALLENGES,
    COMP_DIR_SIDECHALLENGE_TRIES,
    COMP_DIR_NUMBER_OF
};
const QStringList QSL_CompDirs = {
    "General",
    "Stages",
    "Competitors",
    "Runs",
    "SpecialPrices",
    "Screenshots",
    "SideChallenges",
    "SideChallengeTries"
};

enum STAGE_KEYWORDS {
    STAGE_KEYWORD_NAME,
    STAGE_KEYWORD_COMPETITOR_CLASSES,
    STAGE_KEYWORD_QUALI,
    STAGE_KEYWORD_QUALI_GUARANTEE_CLASS,
    STAGE_KEYWORD_QUALI_GUARANTEE_SPEED,
    STAGE_KEYWORD_OBSTACLES,
    STAGE_KEYWORD_NUMBER_OF
};
const QStringList QSL_Stage_Keywords = {
    "NAME",
    "CLASSES",
    "QUALI",
    "QUALI_GUARANTEE_CLASS",
    "QUALI_GUARANTEE_SPEED",
    "CHECKPOINTS"
};

enum SIDECHALLENGE_KEYWORDS {
    SIDECHALLENGE_KEYWORD_NAME,
    SIDECHALLENGE_KEYWORD_COMPETITOR_CLASSES,
    SIDECHALLENGE_KEYWORD_QUALI_CLASS,
    SIDECHALLENGE_KEYWORD_MEASURE,
    SIDECHALLENGE_KEYWORD_NUMBER_OF
};
const QStringList QSL_sideChallenge_Keywords = {
    "NAME",
    "CLASSES",
    "QUALI_CLASS",
    "MEASURE"
};

const QString QS_MoreIsBetter = "moreIsBetter";
const QString QS_LessIsBetter = "lessIsBetter";

enum QUALI_MODE {
    QUALI_ALL,
    QUALI_BUZZER,
    QUALI_NUMBER,
    QUALI_FINAL,
    QUALI_NUMBER_OF
};
const QStringList QSL_Quali = {
    "ALL_TO_NEXT",
    "BUZZER_TO_NEXT",
    "NUMBER_TO_NEXT",
    "FINAL_ROUND"
};
const QStringList QSL_QualiDetailed = {
    "All competitors qualify",
    "Only buzzers qualify",
    "Choosen number of competitors qualify",
    "Final round, so no qualification"
};

/*
enum QUALI_GUARANTEE {
    QUALI_GUARANTEE_INCLUSIVE,
    QUALI_GUARANTEE_EXCLUSIVE,
    QUALI_GUARANTEE_NUMBER_OF
};
const QStringList QSL_QualiGuaranteeMode = {
    "inclusive",
    "exclusive"
};
*/

enum QUALI_STATE {
    QUALI_STATE_UNDEFINED,
    QUALI_STATE_SAFE_REGULAR,
    QUALI_STATE_SAFE_CLASS,
    QUALI_STATE_SAFE_SPEED,
    QUALI_STATE_CURRENT_REGULAR,
    QUALI_STATE_CURRENT_CLASS,
    QUALI_STATE_OUT,
    QUALI_STATE_END,
    QUALI_STATE_END_1ST,
    QUALI_STATE_END_2ND,
    QUALI_STATE_END_3RD,
    QUALI_STATE_NUMBER_OF
};
const QStringList QSL_QualiState = {
    "😅",
    "😎",
    "🤩",
    "👽",
    "🙂",
    "😏",
    "😭",
    "😴",
    "🥇",
    "🥈",
    "🥉"
};

const QString QS_FileName_CompetitorClasses = "Competitor_Classes.txt";
const QString QS_FileName_StagesCount = "Stages_Count.txt";
const QString QS_FileName_SpecialPrice_FailOfTheDay = "FailOfTheDay.txt";
const QString QS_FileName_SpecialPrice_SickestMove = "SickestMove.txt";

const QString QS_Separator = ";";
const QString QS_NewLine = "\n";
const QString QS_LineSpace = "----------------";

const QString QS_DateTimeFormat = "yyyy.MM.dd hh:mm:ss";

const QString QS_Buzzer = "🛎️";

const QStringList QSl_AlphabetSmall {
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
    "z"
};

const QStringList QSl_AlphabetBig {
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
    "Z"
};

#endif // NCM_ENUM_H
