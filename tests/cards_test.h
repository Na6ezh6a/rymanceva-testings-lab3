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

#endif // CARDS_TEST_H
