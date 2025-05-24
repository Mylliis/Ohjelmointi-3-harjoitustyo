TEMPLATE = subdirs

SUBDIRS += \
    CourseLib \
    UnitTests \
    Game \

CourseLib.subdir = Course/CourseLib
Game.depends = CourseLib
UnitTests.depends = CourseLib
