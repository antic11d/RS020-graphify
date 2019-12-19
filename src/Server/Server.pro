QT -= gui
QT += network

CONFIG += c++17 console
CONFIG -= app_bundle

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
        edge.cpp \
        entity.cpp \
        genre.cpp \
        gentrypoint.cpp \
        knowledgegraph.cpp \
        main.cpp \
        metadata.cpp \
        pentrypoint.cpp \
        performer.cpp \
        sentrypoint.cpp \
        server.cpp \
        song.cpp \
        worker.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    edge.h \
    entity.h \
    genre.h \
    gentrypoint.h \
    knowledgegraph.h \
    metadata.h \
    pentrypoint.h \
    performer.h \
    sentrypoint.h \
    server.h \
    song.h \
    worker.h

RESOURCES += \
    server.qrc
