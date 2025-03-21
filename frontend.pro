QT       += core gui network multimedia websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/core/audioplayer.cpp \
    src/core/backendclient.cpp \
    src/core/mainwidget.cpp \
    src/core/mainwindow.cpp \
    src/core/settingswidget.cpp \
    src/main.cpp

HEADERS += \
    src/core/audioplayer.h \
    src/core/backendclient.h \
    src/core/mainwidget.h \
    src/core/mainwindow.h \
    src/core/settingswidget.h

FORMS += \
    src/gui/mainwidget.ui \
    src/gui/mainwidget.ui \
    src/gui/settingswidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
