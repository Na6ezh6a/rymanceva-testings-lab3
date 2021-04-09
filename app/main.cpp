/**
 * Memory_Cards -- Приложения с карточками для запоминания
 *
 * Copyright (c) 2021, Nadezhda Rymanceva <nrumyanc@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "cards.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    Cards cards;
    // примеры карточек
    cards.addCard("To borrow", "Взять в долг");
    cards.addCard("Scholarship", "Стипендия");

    // добавляем в контекст (для вызова из QML)
    engine.rootContext()->setContextProperty("cardsFunctions", &cards);

    engine.load(url);

    return app.exec();
}
