QT += qml quick multimedia

QMAKE_CXXFLAGS += -Werror
CONFIG += c++11

HEADERS +=  $$PWD/attack.h \
            $$PWD/attackpillow.h \
            $$PWD/attackpillowmodel.h \
            $$PWD/board.h \
            $$PWD/gameengine.h \
            $$PWD/level.h \
            $$PWD/player.h \
            $$PWD/monster.h \
            $$PWD/aibrain.h \
            $$PWD/monstermodel.h \
            $$PWD/levelmodel.h \
            $$PWD/playersettings.h \

SOURCES +=  $$PWD/attack.cpp \
            $$PWD/attackpillow.cpp \
            $$PWD/attackpillowmodel.cpp \
            $$PWD/board.cpp \
            $$PWD/gameengine.cpp \
            $$PWD/level.cpp \
            $$PWD/player.cpp \
            $$PWD/monster.cpp \
            $$PWD/aibrain.cpp \
            $$PWD/monstermodel.cpp \
            $$PWD/levelmodel.cpp \
            $$PWD/playersettings.cpp \

