QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    character.cpp \
    decoration.cpp \
    createaccount.cpp \
    enemy.cpp \
    explosion.cpp \
    finalboss.cpp \
    gameworld.cpp \
    gunshot.cpp \
    main.cpp \
    idcatc.cpp \
    obstacle.cpp \
    popupwindow.cpp \
    profileuser.cpp \
    user.cpp \
    worldobject.cpp

HEADERS += \
    character.h \
    decoration.h \
    createaccount.h \
    enemy.h \
    explosion.h \
    finalboss.h \
    gameworld.h \
    gunshot.h \
    idcatc.h \
    obstacle.h \
    popupwindow.h \
    profileuser.h \
    user.h \
    worldobject.h

FORMS += \
    createaccount.ui \
    gameworld.ui \
    idcatc.ui \
    popupwindow.ui \
    profileuser.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    spritesPhase1.qrc \
    spritesPhase2.qrc \
    welcome.qrc

DISTFILES += \
    Sprites/welcome1.png
