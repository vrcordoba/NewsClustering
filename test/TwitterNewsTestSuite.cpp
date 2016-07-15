
#include "gmock/gmock.h"

#include <vector>
#include <string>
#include <set>
#include "TwitterNews.h"
#include "ExclusionListMock.h"

class TwitterNewsTestSuite : public ::testing::Test
{
protected:
   ExclusionListMock exclusionList;
};

TEST_F(TwitterNewsTestSuite, getMostMentionedEntityNoMentionedEntities)
{
   TwitterNews news(exclusionList);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq(""));
}

TEST_F(TwitterNewsTestSuite, computeMostMentionedEntityNonAlphabeticWords)
{
   std::vector<std::string> newsText{"3000", "3000", "3000", "400.000", ".", ".", ";", ","};
   TwitterNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(0);

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq(""));
}

TEST_F(TwitterNewsTestSuite, computeMostMentionedEntityWordsNotInExclusionList)
{
   std::vector<std::string> newsText{"Hello", "Hello", "Goodbye", "Sayonara"};
   TwitterNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(4).WillRepeatedly(::testing::Return(false));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq("Hello"));
}

TEST_F(TwitterNewsTestSuite, computeMostMentionedEntityWordsInExclusionList)
{
   std::vector<std::string> newsText{"Hello", "Hello", "Hello", "Sayonara", "Sayonara"};
   TwitterNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(5)
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(true))
      .WillRepeatedly(::testing::Return(false));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq("Sayonara"));
}

TEST_F(TwitterNewsTestSuite, computeMostMentionedEntityWordsNotStartedByCapitalLetter)
{
   std::vector<std::string> newsText{"hello", "hello", "hello", "Sayonara", "Sayonara"};
   TwitterNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(2)
      .WillRepeatedly(::testing::Return(false));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq("Sayonara"));
}

TEST_F(TwitterNewsTestSuite, computeMostMentionedEntityNonAsciiWordsNotInExclusionList)
{
   std::vector<std::string> newsText{u8"Ñoñería", u8"Ñoñería", u8"Ungüento", u8"Comparación"};
   TwitterNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(4).WillRepeatedly(::testing::Return(false));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq(u8"Ñoñería"));
}

TEST_F(TwitterNewsTestSuite, computeMostMentionedEntityNonAsciiWordsInExclusionList)
{
   std::vector<std::string> newsText{u8"Ñoñería", u8"Ñoñería", u8"Ungüento", u8"Ungüento", u8"Ñoñería"};
   TwitterNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(5)
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq(u8"Ungüento"));
}

TEST_F(TwitterNewsTestSuite, computeMostMentionedEntityNonAsciiWordsNotStartedByCapitalLetter)
{
   std::vector<std::string> newsText{u8"ñoñería", u8"ñoñería", u8"ungüento", u8"Ungüento", u8"óscar", u8"óscar", u8"ñoñería"};
   TwitterNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(1)
      .WillRepeatedly(::testing::Return(false));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq(u8"Ungüento"));
}

TEST_F(TwitterNewsTestSuite, newsHeadline)
{
   TwitterNews news(exclusionList);
   std::string headline(u8"Dummy title");
   news.setHeadline(headline);
   EXPECT_THAT(news.getHeadline(), ::testing::Eq(headline));
}

TEST_F(TwitterNewsTestSuite, wordIsNotContainedInHeadline)
{
   TwitterNews news(exclusionList);
   std::string headline(u8"La Policía intervino durante la manifestación");
   news.setHeadline(headline);
   EXPECT_FALSE(news.isContainedInHeadline("Policías"));
}

TEST_F(TwitterNewsTestSuite, wordIsContainedInHeadline)
{
   TwitterNews news(exclusionList);
   std::string headline(u8"La Policía intervino durante la manifestación");
   news.setHeadline(headline);
   EXPECT_TRUE(news.isContainedInHeadline("Policía"));
}

TEST_F(TwitterNewsTestSuite, shareMentionedEntities)
{
   TwitterNews news1(exclusionList);
   std::vector<std::string> newsText1{"One", "Two", "Three", "Four", "Five"};
   TwitterNews news2(exclusionList);
   std::vector<std::string> newsText2{"Six", "Seven", "Eight", "Three", "Ten"};

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(10)
      .WillRepeatedly(::testing::Return(false));

   news1.setMentionedEntities(newsText1);
   news2.setMentionedEntities(newsText2);

   EXPECT_TRUE(news1.shareMentionedEntities(&news2));
   EXPECT_TRUE(news2.shareMentionedEntities(&news1));
}

TEST_F(TwitterNewsTestSuite, doNotShareMentionedEntities)
{
   TwitterNews news1(exclusionList);
   std::vector<std::string> newsText1{"One", "Two", "Three", "Four", "Five"};
   TwitterNews news2(exclusionList);
   std::vector<std::string> newsText2{"Six", "Seven", "Eight", "Nine", "Ten"};

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(10)
      .WillRepeatedly(::testing::Return(false));

   news1.setMentionedEntities(newsText1);
   news2.setMentionedEntities(newsText2);

   EXPECT_FALSE(news1.shareMentionedEntities(&news2));
   EXPECT_FALSE(news2.shareMentionedEntities(&news1));
}
