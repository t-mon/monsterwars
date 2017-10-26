include(../../game/game.pri)
INCLUDEPATH += ../../game/

QML_IMPORT_PATH =
DEFINES += QT_DEPRECATED_WARNINGS

COMMON_DATA.path = /assets
COMMON_DATA.files = $$files(../../data/*)
INSTALLS += COMMON_DATA

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += ../generic/ui/ui.qrc
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

