/**
 * Memory_Cards -- Приложения с карточками для запоминания
 *
 * Copyright (c) 2021, Nadezhda Rymanceva <nrumyanc@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0

Window {
    id: window

    minimumWidth: 640
    minimumHeight: 480

    visible: true
    title: qsTr("Карточки для запоминания")
    color: "#8F9DB2"

    // простая модель для хранения карточек
    ListModel {
        id: cardsModel

        // когда объект готов, обновляем список карточек
        Component.onCompleted: {
            cardsFunctions.checkCards()
        }
    }

    RowLayout {
        id: row
        anchors.fill: parent

        ScrollView {
            id: scroll
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            padding: 10

            // список карточек
            ListView {
                id: cards
                clip: true
                spacing: 10
                model: cardsModel
                boundsBehavior: Flickable.StopAtBounds
                delegate: Card {
                    mainStr: mainText
                    backStr: backText
                    index: ind
                }
            }
        }

        SideMenu {
            id: menu
            width: 80
            Layout.rightMargin: 5
            Layout.leftMargin: 5
            Layout.bottomMargin: 5
            Layout.topMargin: 5
            Layout.fillHeight: true
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            onAddCard: {
                // открываем диалог
                dialog.open()
            }
        }

        // сигналы из C++ (emit)
        Connections {
            target: cardsFunctions

            onClearCardsQml: {
                cardsModel.clear();
            }

            // по сигналу из C++ добавляем карточку в модель
            onAddCardQml: {
                console.log(i)
                cardsModel.append({mainText: mainText, backText: backText, ind: i})
            }
        }
    }

    // диалог добавления новой карточки
    Dialog {
        id: dialog
        title: "Новая карточка"
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: {
            cardsFunctions.addCard(mainTextInput.text, backTextInput.text);
            mainTextInput.text = ""
            backTextInput.text = ""
        }

        onRejected: {
            console.log("Отмена")
        }

        anchors.centerIn: parent

        ColumnLayout {
            anchors.fill: parent
            TextField {
                id: mainTextInput
                placeholderText: "Основной текст"
            }

            TextField {
                id: backTextInput
                placeholderText: "Задний текст"
            }
        }
    }
}

