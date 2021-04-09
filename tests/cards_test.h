#ifndef CARDS_TEST_H
#define CARDS_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "cards.h"

#include <QObject>
#include <QMap>
#include <QList>
#include <QString>
#include <QPair>

TEST(addTest, simpleStrings)
{
    EXPECT_EQ(1, 1);
    Cards cards;
    EXPECT_EQ(cards.getCardsNumber(), 0);
    cards.addCard("qwe", "asd");
    cards.addCard("qwerty", "12345");
    EXPECT_EQ(cards.getCardsNumber(), 2);
}
TEST(addTest, russianStrings)
{
    EXPECT_EQ(1, 1);
    Cards cards;
    EXPECT_EQ(cards.getCardsNumber(), 0);
    cards.addCard("йцуке", "фыва");
    cards.addCard("олдж", "уцмуцруфцйр");
    EXPECT_EQ(cards.getCardsNumber(), 2);
}

TEST(addAndGetTest, one)
{
    EXPECT_EQ(1, 1);
    Cards cards;
    EXPECT_EQ(cards.getCardsNumber(), 0);

    QList<QPair<QString, QString>> toAdd = {QPair<QString, QString>("qwe", "asd")};

    for(QPair<QString, QString> pair : toAdd) {
        cards.addCard(pair.first, pair.second);
    }

    EXPECT_EQ(cards.getCardsNumber(), toAdd.length());

    QList<QPair<QString, QString>> res = cards.getCards();

    ASSERT_EQ(toAdd.length(), res.length());

    for(int i = 0; i < res.length(); i++) {
        EXPECT_STREQ(toAdd[i].first.toStdString().c_str(), res[i].first.toStdString().c_str());
        EXPECT_STREQ(toAdd[i].second.toStdString().c_str(), res[i].second.toStdString().c_str());
    }
}

TEST(addAndGetTest, multiple)
{
    EXPECT_EQ(1, 1);
    Cards cards;
    EXPECT_EQ(cards.getCardsNumber(), 0);

    QList<QPair<QString, QString>> toAdd = {
        QPair<QString, QString>("qwe", "asd"),
        QPair<QString, QString>("gfegwerg", "3gf4h34h"),
        QPair<QString, QString>("34g324g34g", "23f2f23df12h45j645")
    };

    for(QPair<QString, QString> pair : toAdd) {
        cards.addCard(pair.first, pair.second);
    }

    ASSERT_EQ(cards.getCardsNumber(), toAdd.length());

    QList<QPair<QString, QString>> res = cards.getCards();

    ASSERT_EQ(toAdd.length(), res.length());

    for(int i = 0; i < res.length(); i++) {
        EXPECT_STREQ(toAdd[i].first.toStdString().c_str(), res[i].first.toStdString().c_str());
        EXPECT_STREQ(toAdd[i].second.toStdString().c_str(), res[i].second.toStdString().c_str());
    }
}

TEST(addAndGetTest, byIndex)
{
    EXPECT_EQ(1, 1);
    Cards cards;
    EXPECT_EQ(cards.getCardsNumber(), 0);

    QList<QPair<QString, QString>> toAdd = {
        QPair<QString, QString>("qwe", "asd"),
        QPair<QString, QString>("gfegwerg", "3gf4h34h"),
        QPair<QString, QString>("34g324g34g", "23f2f23df12h45j645")
    };

    for(QPair<QString, QString> pair : toAdd) {
        cards.addCard(pair.first, pair.second);
    }

    ASSERT_EQ(cards.getCardsNumber(), toAdd.length());

    for(int i = 0; i < toAdd.length(); i++) {
        QPair<QString, QString> res = cards.getByCardIndex(i);
        EXPECT_STREQ(toAdd[i].first.toStdString().c_str(), res.first.toStdString().c_str());
        EXPECT_STREQ(toAdd[i].second.toStdString().c_str(), res.second.toStdString().c_str());
    }
}

TEST(removeTest, normal)
{
    EXPECT_EQ(1, 1);
    Cards cards;
    EXPECT_EQ(cards.getCardsNumber(), 0);

    QList<QPair<QString, QString>> toAdd = {
        QPair<QString, QString>("qwe", "asd"),
        QPair<QString, QString>("gfegwerg", "3gf4h34h"),
        QPair<QString, QString>("34g324g34g", "23f2f23df12h45j645")
    };

    for(QPair<QString, QString> pair : toAdd) {
        cards.addCard(pair.first, pair.second);
    }

    ASSERT_EQ(cards.getCardsNumber(), toAdd.length());

    cards.removeCard(2);
    cards.removeCard(0);
    EXPECT_EQ(cards.getCardsNumber(), 1);
}

TEST(removeTest, empty)
{
    EXPECT_EQ(1, 1);
    Cards cards;
    EXPECT_EQ(cards.getCardsNumber(), 0);

    cards.removeCard(0);
    EXPECT_EQ(cards.getCardsNumber(), 0);
}

TEST(removeTest, invalid)
{
    EXPECT_EQ(1, 1);
    Cards cards;
    EXPECT_EQ(cards.getCardsNumber(), 0);

    QList<QPair<QString, QString>> toAdd = {
        QPair<QString, QString>("qwe", "asd"),
        QPair<QString, QString>("gfegwerg", "3gf4h34h"),
        QPair<QString, QString>("34g324g34g", "23f2f23df12h45j645")
    };

    for(QPair<QString, QString> pair : toAdd) {
        cards.addCard(pair.first, pair.second);
    }

    ASSERT_EQ(cards.getCardsNumber(), toAdd.length());

    try {
        cards.removeCard(-1);
        FAIL() << "No error!"; // не было ошибки, а должна быть
    } catch (std::range_error const & e) {
        EXPECT_EQ(e.what(),std::string("Inavlid index!"));
    } catch(...) {
        FAIL() << "Invalid error!";
    }

    try {
        cards.removeCard(toAdd.length());
        FAIL() << "No error!"; // не было ошибки, а должна быть
    } catch (std::range_error const & e) {
        EXPECT_EQ(e.what(),std::string("Inavlid index!"));
    } catch(...) {
        FAIL() << "Invalid error!";
    }

    EXPECT_EQ(cards.getCardsNumber(), toAdd.length());
}

TEST(getTest, invalid)
{
    EXPECT_EQ(1, 1);
    Cards cards;
    EXPECT_EQ(cards.getCardsNumber(), 0);

    QList<QPair<QString, QString>> toAdd = {
        QPair<QString, QString>("qwe", "asd"),
        QPair<QString, QString>("gfegwerg", "3gf4h34h"),
        QPair<QString, QString>("34g324g34g", "23f2f23df12h45j645")
    };

    for(QPair<QString, QString> pair : toAdd) {
        cards.addCard(pair.first, pair.second);
    }

    ASSERT_EQ(cards.getCardsNumber(), toAdd.length());

    try {
        cards.getByCardIndex(-1);
        FAIL() << "No error!"; // не было ошибки, а должна быть
    } catch (std::range_error const & e) {
        EXPECT_EQ(e.what(),std::string("Inavlid index!"));
    } catch(...) {
        FAIL() << "Invalid error!";
    }

    try {
        cards.getByCardIndex(toAdd.length());
        FAIL() << "No error!"; // не было ошибки, а должна быть
    } catch (std::range_error const & e) {
        EXPECT_EQ(e.what(),std::string("Inavlid index!"));
    } catch(...) {
        FAIL() << "Invalid error!";
    }
}

TEST(checkTest, simple)
{
    EXPECT_EQ(1, 1);
    Cards cards;
    EXPECT_EQ(cards.getCardsNumber(), 0);

    QList<QPair<QString, QString>> toAdd = {
        QPair<QString, QString>("qwe", "asd"),
        QPair<QString, QString>("gfegwerg", "3gf4h34h"),
        QPair<QString, QString>("34g324g34g", "23f2f23df12h45j645")
    };

    for(QPair<QString, QString> pair : toAdd) {
        cards.addCard(pair.first, pair.second);
    }

    ASSERT_EQ(cards.getCardsNumber(), toAdd.length());

    cards.checkCards();
}

TEST(checkTest, empty)
{
    EXPECT_EQ(1, 1);
    Cards cards;
    EXPECT_EQ(cards.getCardsNumber(), 0);

    cards.checkCards();
}

#endif // CARDS_TEST_H
