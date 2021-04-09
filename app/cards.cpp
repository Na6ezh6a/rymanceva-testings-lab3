/**
 * Memory_Cards -- Приложения с карточками для запоминания
 *
 * Copyright (c) 2021, Nadezhda Rymanceva <nrumyanc@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include "cards.h"

Cards::Cards(QObject *parent) : QObject(parent)
{

}

// обновляет список карточек в QML
void Cards::updateCards() {
    emit clearCardsQml(); // удаляеми всё

    // добавляем заново
    for(qint64 i = 0; i < this->cards.length(); i++) {
        // emit создаёт сигнал для QML
        // параметры: основной текст, текст на задней стороне карточки, индекс
        emit addCardQml(this->cards[i].first, this->cards[i].second, i);
    }
}

// добавление карточки в список
void Cards::addCard(QString mainText, QString backText) {
    this->cards.push_back(QPair<QString, QString>(mainText, backText));

    // после добавления в C++ список надо обновить QML
    updateCards();
}

// удаление карточки по номеру
void Cards::removeCard(qint64 index) {
    if(index < 0 || index > this->cards.length() - 1) {
        // неправильный индекс
        // throw "кидает" ошибку, которую можно обработать при помощи catch
        throw std::range_error("Inavlid index!");
    }

    this->cards.removeAt(index);

    // после удаления из C++ списка надо обновить QML
    updateCards();
}

// передаём всё из C++ в QML
void Cards::checkCards() {
    updateCards();
}

// получаем список карточек
QList<QPair<QString, QString>> Cards::getCards() {
    return this->cards;
}

// получаем карточку по номеру
QPair<QString, QString> Cards::getByCardIndex(qint64 index) {
    if(index < 0 || index > this->cards.length() - 1) {
        // неправильный индекс
        // throw "кидает" ошибку, которую можно обработать при помощи catch
        throw std::range_error("Inavlid index!");
    }

    return this->cards[index];
}

// получаем кол-во карточек
qint64 Cards::getCardsNumber() {
    return this->cards.length();
}
