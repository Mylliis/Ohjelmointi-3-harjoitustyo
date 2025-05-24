QT += testlib
QT -= gui
QT += core gui widgets
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testgeh.cpp \
    ../../Game/add_building_dialog.cpp \
    ../../Game/berrybush.cpp \
    ../../Game/dock.cpp \
    ../../Game/forest_s.cpp \
    ../../Game/gameeventhandler.cpp \
    ../../Game/gamescene.cpp \
    ../../Game/grassland_s.cpp \
    ../../Game/house.cpp \
    ../../Game/mapitem.cpp \
    ../../Game/mapwindow.cc \
    ../../Game/mine.cpp \
    ../../Game/miner.cpp \
    ../../Game/objectmanager.cpp \
    ../../Game/player.cpp \
    ../../Game/popup_dialog.cpp \
    ../../Game/starting_screen.cpp \
    ../../Game/stone.cpp \
    ../../Game/tilebase_s.cpp \
    ../../Game/watertile.cpp \
    ../../Game/worker.cpp \
    ../../Game/workerbase_s.cpp

INCLUDEPATH += $$PWD/../../Game\
$$PWD/../../Course/CourseLib
DEPENDPATH += $$PWD/../../Game\
$$PWD/../../Course/CourseLib

SUBDIRS += \
    ../../Game/Game.pro

RESOURCES += \
    ../../Game/imageresources.qrc

FORMS += \
    ../../Game/add_building_dialog.ui \
    ../../Game/mapwindow.ui \
    ../../Game/popup_dialog.ui \
    ../../Game/starting_screen.ui

DISTFILES += \
    ../../Game/blue_castle.png \
    ../../Game/blue_dock.png \
    ../../Game/blue_house.png \
    ../../Game/blue_mine.png \
    ../../Game/Bush.png \
    ../../Game/bush_2.png \
    ../../Game/castle.png \
    ../../Game/castle_2.png \
    ../../Game/dock.png \
    ../../Game/gametitle.png \
    ../../Game/housing.png \
    ../../Game/play_button.png \
    ../../Game/player_1_title.png \
    ../../Game/player_2_title.png \
    ../../Game/red_dock.png \
    ../../Game/red_house.png \
    ../../Game/red_mine.png \
    ../../Game/stonecave.png \
    ../../Game/water.png \
    ../../Game/woods.png

HEADERS += \
    ../../Game/add_building_dialog.hh \
    ../../Game/berrybush.h \
    ../../Game/dock.h \
    ../../Game/forest_s.h \
    ../../Game/gameeventhandler.hh \
    ../../Game/gamescene.hh \
    ../../Game/grassland_s.h \
    ../../Game/house.h \
    ../../Game/mapitem.hh \
    ../../Game/mapwindow.hh \
    ../../Game/mine.h \
    ../../Game/miner.h \
    ../../Game/objectmanager.hh \
    ../../Game/player.hh \
    ../../Game/popup_dialog.hh \
    ../../Game/starting_screen.hh \
    ../../Game/stone.h \
    ../../Game/student_resourcemaps.h \
    ../../Game/tilebase_s.h \
    ../../Game/watertile.h \
    ../../Game/worker.h \
    ../../Game/workerbase_s.h


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += -L$$OUT_PWD/../../Course/CourseLib/ -lCourseLib

INCLUDEPATH += $$PWD/../../Course/CourseLib
DEPENDPATH += $$PWD/../../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../Course/CourseLib/libCourseLib.a
