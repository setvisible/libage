/* - AGE Editor - Copyright (C) 2018 Sebastien Vavassori
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.0

Rectangle {
    id: button

    property bool active: buttonGroup.activeButton == button
    property bool fullDiscovery: false
    property alias text: label.text

    signal clicked()
    height: label.height*1.1

    color: active ? "#1c56f3" : "white"

    radius: 5
    border.width: 2

    Text {
        id: label
        text: "Full Discovery"
        font.bold: true
        font.pointSize: 17
        width: parent.width
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            button.clicked()
            //Reset the model
            btModel.running = false
            btModel.running = true
            buttonGroup.activeButton = button
        }
    }
}
