/**
 * Memory_Cards -- Приложения с карточками для запоминания
 *
 * Copyright (c) 2021, Nadezhda Rymanceva <nrumyanc@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    id: menu
    Rectangle {
        id: bg
        anchors.fill: parent
        color: "#818DA1"
        radius: 5
    }

    signal addCard()

    Button {
        id: btn
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.rightMargin: 5
        anchors.leftMargin: 5
        height: width

        background: Rectangle {
            radius: 10
            // цвет зависит от состояния
            color: btn.pressed ? "#D1BC9F" : "#F8DFBD"
            border.color: "#CD998B"
            border.width: 5

            Image {
                width: parent.width - 30
                height: parent.height - 30
                anchors.centerIn: parent

                // также как и в Card.qml, картинка на кнопке (в Resources)
                source: "images/plus-circular-button.svg"
                antialiasing: true
            }
        }

        onClicked: {
            menu.addCard()
        }
    }
}


