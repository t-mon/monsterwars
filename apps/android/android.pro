include(../../game/game.pri)

QT += qml quick

TEMPLATE = app
TARGET = monsterwars

INCLUDEPATH += ../../game/

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

DEFINES += QT_DEPRECATED_WARNINGS

COMMON_DATA.path = /assets
COMMON_DATA.files = $$files(../../data/*)
INSTALLS += COMMON_DATA

RESOURCES += ui/ui.qrc qml.qrc
SOURCES += main.cpp

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
