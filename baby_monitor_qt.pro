target.path = /home/pi/
INSTALLS += target

QT += widgets
QT += multimedia
QT += multimediawidgets
QT += core
QT += gui
QT += network

HEADERS += \
    mainwindow.h \
    manager.h \
    clienttcp.h \
    menuwindow.h \
    menumusicwindow.h \
    decoder.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    manager.cpp \
    clienttcp.cpp \
    menuwindow.cpp \
    menumusicwindow.cpp \
    decoder.cpp
