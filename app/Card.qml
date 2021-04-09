/**
 * Memory_Cards -- Приложения с карточками для запоминания
 *
 * Copyright (c) 2021, Nadezhda Rymanceva <nrumyanc@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0

Item {
    id: item1
    anchors.right: parent.right
    anchors.left: parent.left
    height: textLbl.height < 70 ? 70 : textLbl.height

    property var mainStr
    property var backStr
    property int index
    property bool fliped: false

    Rectangle {
        id: rectangle
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.rightMargin: 5
        anchors.left: parent.left
        anchors.right: delBtn.left
        rotation: 0

        // цвет зависит от состояния
        color: fliped ? "#BDF8D7" : "#F8DFBD"
        border.color: "#CD998B"
        border.width: 5
        radius: 10

        MouseArea {
            anchors.fill: parent
            onClicked: {
                fliped = !fliped
                rectangleAnimation.start() // запуск анимации
            }
        }

        Text {
            id: textLbl
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            width: parent.width
            anchors.centerIn: parent
            text: fliped ? qsTr(backStr) : qsTr(mainStr)
            wrapMode: Text.Wrap
            textFormat: Text.AutoText
        }

        RotationAnimation {
            id: rectangleAnimation
            target: rectangle
            from: 0
            to: 360
            duration: 300
            running: false
        }
    }

    Button {
        id: delBtn
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        height: 70

        width: height

        background: Rectangle {
            radius: 10
            // тут цвет тоже зависит от состояния
            color: delBtn.pressed ? "#D1BC9F" : "#F8DFBD"
            border.color: "#CD998B"
            border.width: 5

            Image {
                width: parent.width - 30
                height: parent.height - 30
                anchors.centerIn: parent

                // картинка на кнопке (в Resources)
                source: "images/delete-button-svgrepo-com.svg"
                antialiasing: true
            }
        }

        onClicked: {
            console.log(index)
            cardsFunctions.removeCard(index)
        }
    }
}
