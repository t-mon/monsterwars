TEMPLATE = app
TARGET = MonsterWars

load(ubuntu-click)

QT += qml quick

HEADERS +=  attack.h \
            backend.h \
            board.h \
            gameengine.h \
            level.h \
            node.h \
            particlecloud.h \
            pathfinder.h \
            player.h \
            monster.h \

SOURCES +=  main.cpp \
            attack.cpp \
            backend.cpp \
            board.cpp \
            gameengine.cpp \
            level.cpp \
            node.cpp \
            particlecloud.cpp \
            pathfinder.cpp \
            player.cpp \
            monster.cpp \


RESOURCES += MonsterWars.qrc \
             monsters.qrc

OTHER_FILES += MonsterWars.apparmor \
               MonsterWars.desktop \
               MonsterWars.png


# specify where the config files are installed to
config_files.path = /MonsterWars
config_files.files += $${OTHER_FILES}

# install Bacon2D files
bacon2d.path = $${UBUNTU_CLICK_BINARY_PATH}
bacon2d.files = /usr/lib/arm-linux-gnueabihf/qt5/qml/Bacon2D.1.0/

# install level files
levels.path = /
levels.files = levels/

INSTALLS += config_files bacon2d levels

# Default rules for deployment.
target.path = $${UBUNTU_CLICK_BINARY_PATH}
INSTALLS += target

