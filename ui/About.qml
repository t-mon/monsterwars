/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2015 Simon Stuerz <stuerz.simon@gmail.com>               *
 *                                                                         *
 *  This file is part of Monster Wars.                                     *
 *                                                                         *
 *  Monster Wars is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 3 of the License.                *
 *                                                                         *
 *  Monster Wars is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with Monster Wars. If not, see <http://www.gnu.org/licenses/>.   *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

import QtQuick 2.7
import MonsterWars 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0

Page {
    id: root

    property int titleSize: app.unitSize * 4
    property int textSize: app.unitSize * 3

    Rectangle {
        id: screenRectangle
        anchors.fill: parent
        color: "black"

        Image {
            id: backgroundImage
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
            sourceSize: Qt.size(parent.width, 0)
            source: Qt.resolvedUrl(dataDirectory + "/backgrounds/menu-background.jpg")
        }


        Flickable {
            anchors.margins: app.unitSize * 2
            anchors.top: menuBar.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            contentHeight: columnLayout.height

            BackgroundMonsters {
                anchors.fill: parent
            }

            ColumnLayout {
                id: columnLayout
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top

                spacing: app.unitSize * 2

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Monster Wars"
                    font.weight: Font.DemiBold
                    font.bold: true
                    style: Text.Outline
                    styleColor: "steelblue"
                    font.pixelSize: app.unitSize * 6
                }

                Item {
                    id: iconImage
                    width: app.unitSize * 10
                    height: app.unitSize * 10
                    Layout.alignment: Qt.AlignHCenter
                    Image {
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectCrop
                        source: Qt.resolvedUrl(dataDirectory + "/icons/monsterwars-512x512.png")
                    }
                }


                Text {
                    Layout.alignment: Qt.AlignHCenter
                    // TRANSLATORS: The "version" of the application
                    text: qsTr("Version:") + " " + version
                    font.weight: Font.DemiBold
                    font.pixelSize: textSize
                }

                Text {
                    // TRANSLATORS: Source code section in the "About" view
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Enjoying the game?")
                    font.weight: Font.DemiBold
                    style: Text.Outline
                    styleColor: "white"
                    font.pixelSize: textSize
                }

                Rectangle {
                    id: donateButton
                    height: app.unitSize * 12
                    width: app.unitSize * 30
                    Layout.alignment: Qt.AlignHCenter

                    color: "transparent"
                    Image {
                        id: donateButtonMonster
                        anchors.fill: parent
                        source: dataDirectory + "/images/donate-button.png"
                    }

                    Text {
                        anchors.centerIn: parent
                        // TRANSLATORS: The "Donate" button in the main menu
                        text: qsTr("Donate")
                        font.bold: true
                        font.pixelSize: textSize
                        color: donateButtonMouseArea.pressed ? "steelblue" : "white"
                    }

                    MouseArea {
                        id: donateButtonMouseArea
                        anchors.fill: parent
                        onClicked: Qt.openUrlExternally("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=ZLY4J8HCNEDE2")
                    }

                    SequentialAnimation {
                        id: donateButtonAnimation
                        ScaleAnimator {
                            target: donateButton
                            from: 0.99
                            to: 1.03
                            easing.type: Easing.Linear;
                            duration: 1000
                        }
                        ScaleAnimator {
                            target: donateButton
                            from: 1.03
                            to: 0.99
                            easing.type: Easing.Linear;
                            duration: 800
                        }
                        running: true
                        loops: Animation.Infinite
                    }
                }


                Row {
                    spacing: app.unitSize * 2
                    Layout.alignment: Qt.AlignHCenter
                    Text {
                        // TRANSLATORS: "Author" section in the "About" view
                        text: qsTr("Author")
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: textSize
                    }

                    Text {
                        text: "Simon Stürz"
                        font.weight: Font.DemiBold
                        font.pixelSize: textSize
                    }
                }

                Row {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: app.unitSize * 2
                    Text {
                        // TRANSLATORS: Design section in the "About" view
                        text: qsTr("Design")
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: textSize
                    }

                    Text {
                        text: "Simon Stürz"
                        font.weight: Font.DemiBold
                        font.pixelSize: textSize
                    }
                }

                Column {
                    spacing: app.unitSize * 2
                    Text {
                        // TRANSLATORS: Source code section in the "About" view
                        text: qsTr("Source code")
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: textSize
                    }

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: textSize
                        text: "https://github.com/t-mon/monsterwars"
                        font.weight: Font.DemiBold
                        font.underline: true
                        font.pixelSize: textSize
                        MouseArea {
                            anchors.fill: parent
                            onClicked: Qt.openUrlExternally("https://github.com/t-mon/monsterwars")
                        }
                    }
                }


                Column {
                    spacing: app.unitSize * 2
                    Text {
                        // TRANSLATORS: License section in the "About" view
                        text: qsTr("License")
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: textSize
                    }

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: textSize
                        text: "GPL v3"
                        font.weight: Font.DemiBold
                        font.underline: true
                        font.pixelSize: textSize
                        MouseArea {
                            anchors.fill: parent
                            onClicked: Qt.openUrlExternally("https://www.gnu.org/licenses/gpl-3.0.html")
                        }
                    }
                }

                Column {
                    spacing: app.unitSize * 2
                    Text {
                        // TRANSLATORS: Reference to the background image in the "About" view
                        text: qsTr("Backgrounds")
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: textSize
                    }

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: 2
                        text: "http://shadowhousecreations.blogspot.de"
                        font.weight: Font.DemiBold
                        font.underline: true
                        font.pixelSize: textSize
                        MouseArea {
                            anchors.fill: parent
                            onClicked: Qt.openUrlExternally("http://shadowhousecreations.blogspot.de")
                        }
                    }

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: textSize
                        // TRANSLATORS: Terms of use for the background image in the "About" view
                        text: qsTr("Terms of use")
                        font.weight: Font.DemiBold
                        font.underline: true
                        font.pixelSize: textSize
                        MouseArea {
                            anchors.fill: parent
                            onClicked: Qt.openUrlExternally("http://shadowhousecreations.blogspot.de/p/terms-of-use.html")
                        }
                    }
                }

                Column {
                    spacing: app.unitSize * 2
                    Text {
                        // TRANSLATORS: Reference to the music in the "About" view
                        text: qsTr("Music")
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: textSize
                    }
                    Column {
                        spacing: app.unitSize * 4
                        Row {
                            anchors.left: parent.left
                            anchors.right: parent.right
                            spacing: textSize
                            Image {
                                id: ccBySaImage
                                source: dataDirectory + "/images/cc-by-sa.png"
                                height: 2 * textSize
                                fillMode: Image.PreserveAspectFit
                                MouseArea {
                                    id: ccBySaMouseArea
                                    anchors.fill: parent
                                    onClicked: Qt.openUrlExternally("http://creativecommons.org/licenses/by-sa/3.0/")
                                }
                            }

                            Text {
                                anchors.verticalCenter: ccBySaImage.verticalCenter
                                text: "Kaetemi"
                                font.weight: Font.DemiBold
                                font.pixelSize: textSize
                            }
                        }

                        Text {
                            anchors.left: parent.left
                            anchors.leftMargin: textSize
                            text: "opengameart.org/content/polyverse-title-\nalternative"
                            font.weight: Font.DemiBold
                            font.underline: true
                            font.pixelSize: textSize
                            MouseArea {
                                anchors.fill: parent
                                onClicked: Qt.openUrlExternally("http://opengameart.org/content/polyverse-title-alternative")
                            }
                        }
                    }
                    Column {
                        spacing: app.unitSize * 4
                        Row {
                            anchors.left: parent.left
                            anchors.right: parent.right
                            spacing: textSize
                            Image {
                                id: ccImage
                                source: dataDirectory + "/images/cc0.png"
                                height: textSize * 2
                                fillMode: Image.PreserveAspectFit
                                MouseArea {
                                    id: ccMouseArea
                                    anchors.fill: parent
                                    onClicked: Qt.openUrlExternally("http://creativecommons.org/publicdomain/zero/1.0/")
                                }
                            }

                            Text {
                                anchors.verticalCenter: ccImage.verticalCenter
                                text: "Homingstar"
                                font.weight: Font.DemiBold
                                font.pixelSize: textSize
                            }
                        }

                        Text {
                            anchors.left: parent.left
                            anchors.leftMargin: textSize
                            text: "opengameart.org/content/fairy-spring"
                            font.weight: Font.DemiBold
                            font.underline: true
                            font.pixelSize: textSize
                            MouseArea {
                                anchors.fill: parent
                                onClicked: Qt.openUrlExternally("http://opengameart.org/content/fairy-spring")
                            }
                        }
                    }
                }

                Column {
                    spacing: app.unitSize * 4
                    Text {
                        // TRANSLATORS: Reference to the translations in the "About" view
                        text: qsTr("Translations")
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: textSize
                    }

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: textSize
                        // TRANSLATORS: Thank you very much for helping with the translations!! ;)  (in the "About" view)
                        text: qsTr("Thanks to all translators!")
                        font.weight: Font.DemiBold
                        font.underline: true
                        font.pixelSize: textSize
                        MouseArea {
                            anchors.fill: parent
                            onClicked: Qt.openUrlExternally("https://translations.launchpad.net/monsterwars")
                        }
                    }
                }
            }
        }

        MenuBar {
            id: menuBar
            height: app.unitSize * 5
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }
            menuTitle: qsTr("About")
        }
    }
}
