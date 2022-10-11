QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    ncm_obj_challenge.cpp \
    ncm_obj_challenge_list.cpp \
    ncm_obj_competition.cpp \
    ncm_obj_competitor.cpp \
    ncm_obj_competitor_list.cpp \
    ncm_obj_ranking_challenge.cpp \
    ncm_obj_ranking_challenge_list.cpp \
    ncm_obj_ranking_combi.cpp \
    ncm_obj_ranking_stage.cpp \
    ncm_obj_run.cpp \
    ncm_obj_run_list.cpp \
    ncm_obj_stage.cpp \
    ncm_obj_try.cpp \
    ncm_obj_try_list.cpp \
    ncm_wid_table.cpp \
    ncm_wid_table_multi.cpp \
    ncm_win_checkin.cpp \
    ncm_win_edit_challenge.cpp \
    ncm_win_edit_stage.cpp \
    ncm_win_main.cpp \
    ncm_win_ranking_challenge.cpp \
    ncm_win_ranking_stage.cpp \
    ncm_win_resultentering_challenge.cpp \
    ncm_win_resultentering_stage.cpp \
    ncm_win_starterlist.cpp

HEADERS += \
    NCM_Enum.h \
    ncm_obj_challenge.h \
    ncm_obj_challenge_list.h \
    ncm_obj_competition.h \
    ncm_obj_competitor.h \
    ncm_obj_competitor_list.h \
    ncm_obj_ranking_challenge.h \
    ncm_obj_ranking_challenge_list.h \
    ncm_obj_ranking_combi.h \
    ncm_obj_ranking_stage.h \
    ncm_obj_run.h \
    ncm_obj_run_list.h \
    ncm_obj_stage.h \
    ncm_obj_try.h \
    ncm_obj_try_list.h \
    ncm_wid_table.h \
    ncm_wid_table_multi.h \
    ncm_win_checkin.h \
    ncm_win_edit_challenge.h \
    ncm_win_edit_stage.h \
    ncm_win_main.h \
    ncm_win_ranking_challenge.h \
    ncm_win_ranking_stage.h \
    ncm_win_resultentering_challenge.h \
    ncm_win_resultentering_stage.h \
    ncm_win_starterlist.h

FORMS += \
    ncm_win_checkin.ui \
    ncm_win_edit_challenge.ui \
    ncm_win_edit_stage.ui \
    ncm_win_main.ui \
    ncm_win_ranking_challenge.ui \
    ncm_win_ranking_stage.ui \
    ncm_win_resultentering_challenge.ui \
    ncm_win_resultentering_stage.ui \
    ncm_win_starterlist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../img/img.qrc
