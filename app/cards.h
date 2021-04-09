/**
 * Memory_Cards -- Приложения с карточками для запоминания
 *
 * Copyright (c) 2021, Nadezhda Rymanceva <nrumyanc@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#ifndef CARDS_H
#define CARDS_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QString>
#include <QPair>

class Cards : public QObject
{
    Q_OBJECT
public:
    explicit Cards(QObject *parent = nullptr);

private:
    QList<QPair<QString, QString>> cards;
    void updateCards(); // приватная функция для обновления карточек

signals:
    void clearCardsQml(); // сигнал для удаления всех карточек в QML
    void addCardQml(QString mainText, QString backText, qint64 i); // добавить карточку в QML

public slots:
    void addCard(QString mainText, QString backText); // добавить карточку в список
    void removeCard(int index); // удалить карточку из списка
    void checkCards(); // обновить карточки (вызвается из QML)
    QList<QPair<QString, QString>> getCards() const; // получить список карточек
    QPair<QString, QString> getByCardIndex(int index); // получить карточку по номеру
    qint64 getCardsNumber() const; // получить количество карточек
};

#endif // CARDS_H
