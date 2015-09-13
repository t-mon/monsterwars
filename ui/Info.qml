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

import QtQuick 2.2
import MonsterWars 1.0
import QtQuick.Layouts 1.1

Item {
    id: root

    Rectangle {
        id: screenRectangle
        anchors.fill: parent
        color: "black"

        Image {
            id: backgroundImage
            anchors.fill: parent
            source: "qrc:///backgrounds/background1.jpg"
        }

        Flickable {
            anchors.fill: parent
            anchors.margins: units.gu(2)
            contentHeight: columnLayout.height

            ColumnLayout {
                id: columnLayout
                spacing: units.gu(4)

                Column {
                    spacing: units.gu(1)
                    Text {
                        text: "Monster Wars"
                        font.weight: Font.DemiBold
                        font.bold: true
                        style: Text.Outline
                        styleColor: "steelblue"
                        font.pixelSize: units.gu(9)
                    }

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: units.gu(2)
                        text: i18n.tr("Version:") + " " + app.version
                        font.weight: Font.DemiBold
                        font.pixelSize: units.gu(3)
                    }
                }

                Column {
                    spacing: units.gu(1)
                    Text {
                        text: i18n.tr("Author")
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: units.gu(4)
                    }

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: units.gu(2)
                        text: "Simon Stürz"
                        font.weight: Font.DemiBold
                        font.pixelSize: units.gu(3)
                    }
                }

                Column {
                    spacing: units.gu(1)
                    Text {
                        text: i18n.tr("Design")
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: units.gu(4)
                    }

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: units.gu(2)
                        text: "Simon Stürz"
                        font.weight: Font.DemiBold
                        font.pixelSize: units.gu(3)
                    }
                }

                Column {
                    spacing: units.gu(1)
                    Text {
                        text: i18n.tr("Source code")
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: units.gu(4)
                    }

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: units.gu(2)
                        text: "https://github.com/t-mon/monsterwars"
                        font.weight: Font.DemiBold
                        font.underline: true
                        font.pixelSize: units.gu(3)
                        MouseArea {
                            anchors.fill: parent
                            onClicked: Qt.openUrlExternally("https://github.com/t-mon/monsterwars")
                        }
                    }
                }


                Column {
                    spacing: units.gu(1)
                    Text {
                        text: i18n.tr("License")
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: units.gu(4)
                    }

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: units.gu(2)
                        text: "GPL v3"
                        font.weight: Font.DemiBold
                        font.underline: true
                        font.pixelSize: units.gu(3)
                        MouseArea {
                            anchors.fill: parent
                            onClicked: Qt.openUrlExternally("https://www.gnu.org/licenses/gpl-3.0.html")
                        }
                    }
                }


                Column {
                    spacing: units.gu(1)
                    Text {
                        text: i18n.tr("Backgrounds")
                        font.weight: Font.DemiBold
                        style: Text.Outline
                        styleColor: "white"
                        font.pixelSize: units.gu(4)
                    }

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: units.gu(2)
                        text: "http://shadowhousecreations.blogspot.de"
                        font.weight: Font.DemiBold
                        font.underline: true
                        font.pixelSize: units.gu(3)
                        MouseArea {
                            anchors.fill: parent
                            onClicked: Qt.openUrlExternally("http://shadowhousecreations.blogspot.de")
                        }
                    }

                    Text {
                        anchors.left: parent.left
                        anchors.leftMargin: units.gu(2)
                        text: "Terms of use"
                        font.weight: Font.DemiBold
                        font.underline: true
                        font.pixelSize: units.gu(3)
                        MouseArea {
                            anchors.fill: parent
                            onClicked: Qt.openUrlExternally("http://shadowhousecreations.blogspot.de/p/terms-of-use.html")
                        }
                    }
                }
            }
        }

        Rectangle {
            id: closeButton
            width: units.gu(8)
            height: width
            anchors.right: parent.right
            anchors.rightMargin: units.gu(1)
            anchors.top: parent.top
            anchors.topMargin: units.gu(1)
            color: "black"
            radius: width / 2

            Text {
                anchors.centerIn: parent
                text: "X"
                color: "white"
                font.bold: true
                font.pixelSize: units.gu(6)
            }

            MouseArea {
                anchors.fill: parent
                onClicked: pageStack.pop()
            }
        }
    }
}
