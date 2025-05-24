TEMPLATE = app
TARGET = TheGame

QT += core gui widgets

CONFIG += c++14

SOURCES += \
    main.cpp \
    mapwindow.cc \
    house.cpp \
    mine.cpp \
    berrybush.cpp \
    stone.cpp \
    objectmanager.cpp \
    gameeventhandler.cpp \
    gamescene.cpp \
    starting_screen.cpp \
    mapitem.cpp \
    worker.cpp\
    player.cpp \
    popup_dialog.cpp \
    watertile.cpp \
    dock.cpp \
    forest_s.cpp \
    grassland_s.cpp \
    tilebase_s.cpp \
    workerbase_s.cpp \
    miner.cpp \
    add_building_dialog.cpp



HEADERS += \
    mapwindow.hh \
    house.h \
    mine.h \
    berrybush.h \
    stone.h \
    student_resourcemaps.h \
    gameeventhandler.hh \
    objectmanager.hh \
    gamescene.hh \
    starting_screen.hh \
    mapitem.hh \
    worker.h\
    player.hh \
    popup_dialog.hh \
    watertile.h \
    dock.h \
    forest_s.h \
    grassland_s.h \
    tilebase_s.h \
    workerbase_s.h \
    miner.h \
    add_building_dialog.hh




win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

FORMS += \
    mapwindow.ui \
    starting_screen.ui \
    popup_dialog.ui \
    add_building_dialog.ui

DISTFILES += \
    castle.png

RESOURCES += \
    imageresources.qrc
