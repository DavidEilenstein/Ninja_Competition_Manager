#ifndef NCM_ENUM_H
#define NCM_ENUM_H

#include <QStringList>

using namespace std;


enum COMP_DIR {
    COMP_DIR_GENERAL,
    COMP_DIR_STAGES,
    COMP_DIR_COMPETITORS,
    COMP_DIR_RUNS,
    COMP_DIR_NUMBER_OF
};
const QStringList QSL_CompDirs = {
    "General",
    "Stages",
    "Competitors",
    "Runs"
};

const QString QS_FileName_CompetitorClasses = "Competitor_Classes.txt";
const QString QS_FileName_StagesCount = "Stages_Count.txt";

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
