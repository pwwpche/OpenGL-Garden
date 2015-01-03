#-------------------------------------------------
#
# Project created by QtCreator 2014-11-09T10:03:06
#
#-------------------------------------------------

QT       += core gui opengl
LIBS = -lGLU -lGlAux -lglew32 -ladvapi32 \

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gltest.cpp \
    Camera.cpp \
    Ground.cpp \
    SkySphere.cpp \
    TextureManager.cpp \
    Fence.cpp \
    Flower.cpp \
    Tree.cpp \
    Calculator.cpp \
    fog.cpp \
    Flake.cpp \
    Snow.cpp \
    Wind.cpp

HEADERS  += mainwindow.h \
    gltest.h \
    Camera.h \
    Ground.h \
    SkySphere.h \
    TextureManager.h \
    Fence.h \
    Flower.h \
    Tree.h \
    Calculator.h \
    fog.h \
    Flake.h \
    Snow.h \
    Wind.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/D:/setup/Qt/Qt5.2.0/5.2.0/msvc2010_opengl/lib/ -lglut -lglew32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/D:/setup/Qt/Qt5.2.0/5.2.0/msvc2010_opengl/lib/ -lglut
else:unix: LIBS += -L$$PWD/D:/setup/Qt/Qt5.2.0/5.2.0/msvc2010_opengl/lib/ -lglut

INCLUDEPATH += $$PWD/D:/setup/Qt/Qt5.2.0/5.2.0/msvc2010_opengl/include
DEPENDPATH += $$PWD/D:/setup/Qt/Qt5.2.0/5.2.0/msvc2010_opengl/include
