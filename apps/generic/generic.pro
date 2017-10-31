include(../../game/game.pri)

INCLUDEPATH += ../../game/

TARGET = monsterwars

QT += qml quick

QML_FILES = ../../ui/*.qml

# Install data
data.files = ../../data
data.path = /usr/share/monsterwars

RESOURCES += ../../ui/ui.qrc
SOURCES += main.cpp

target.path = /usr/bin/
INSTALLS += target
