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
    ncm_checkin.cpp \
    ncm_competition.cpp \
    ncm_competitor.cpp \
    ncm_mainwindow.cpp \
    ncm_resultentering.cpp \
    ncm_run.cpp \
    ncm_stage.cpp \
    ncm_stage.cpp \
    ncm_starterlist.cpp \
    ncm_table.cpp

HEADERS += \
    NCM_enum.h \
    ncm_checkin.h \
    ncm_competition.h \
    ncm_competitor.h \
    ncm_mainwindow.h \
    ncm_resultentering.h \
    ncm_run.h \
    ncm_stage.h \
    ncm_stage.h \
    ncm_starterlist.h \
    ncm_table.h

FORMS += \
    ncm_checkin.ui \
    ncm_competition.ui \
    ncm_mainwindow.ui \
    ncm_resultentering.ui \
    ncm_stage.ui \
    ncm_starterlist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
