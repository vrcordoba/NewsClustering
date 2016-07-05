
#include "gmock/gmock.h"

#include <vector>
#include <string>
#include "NewspaperNews.h"
#include "ExclusionListMock.h"

class NewspaperNewsTestSuite : public ::testing::Test
{
protected:
   ExclusionListMock exclusionList;
};

TEST_F(NewspaperNewsTestSuite, getMostMentionedEntityNoMentionedEntities)
{
   NewspaperNews news(exclusionList);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq(""));
}

TEST_F(NewspaperNewsTestSuite, computeMostMentionedEntityNonAlphabeticWords)
{
   std::vector<std::string> newsText{"3000", "3000", "3000", "400.000", ".", ".", ";", ","};
   NewspaperNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(0);

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq(""));
}

TEST_F(NewspaperNewsTestSuite, computeMostMentionedEntityWordsNotInExclusionList)
{
   std::vector<std::string> newsText{"Hello", "Hello", "Goodbye", "Sayonara"};
   NewspaperNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(4).WillRepeatedly(::testing::Return(false));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq("Hello"));
}

TEST_F(NewspaperNewsTestSuite, computeMostMentionedEntityWordsInExclusionList)
{
   std::vector<std::string> newsText{"Hello", "Hello", "Hello", "Sayonara", "Sayonara"};
   NewspaperNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(5)
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(true))
      .WillRepeatedly(::testing::Return(false));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq("Sayonara"));
}

TEST_F(NewspaperNewsTestSuite, computeMostMentionedEntityWordsNotStartedByCapitalLetter)
{
   std::vector<std::string> newsText{"hello", "hello", "hello", "Sayonara", "Sayonara"};
   NewspaperNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(2)
      .WillRepeatedly(::testing::Return(false));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq("Sayonara"));
}

TEST_F(NewspaperNewsTestSuite, computeMostMentionedEntityNonAsciiWordsNotInExclusionList)
{
   std::vector<std::string> newsText{u8"Ñoñería", u8"Ñoñería", u8"Ungüento", u8"Comparación"};
   NewspaperNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(4).WillRepeatedly(::testing::Return(false));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq(u8"Ñoñería"));
}

TEST_F(NewspaperNewsTestSuite, computeMostMentionedEntityNonAsciiWordsInExclusionList)
{
   std::vector<std::string> newsText{u8"Ñoñería", u8"Ñoñería", u8"Ungüento", u8"Ungüento", u8"Ñoñería"};
   NewspaperNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(5)
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq(u8"Ungüento"));
}

TEST_F(NewspaperNewsTestSuite, computeMostMentionedEntityNonAsciiWordsNotStartedByCapitalLetter)
{
   std::vector<std::string> newsText{u8"ñoñería", u8"ñoñería", u8"ungüento", u8"Ungüento", u8"óscar", u8"óscar", u8"ñoñería"};
   NewspaperNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(1)
      .WillRepeatedly(::testing::Return(false));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq(u8"Ungüento"));
}

TEST_F(NewspaperNewsTestSuite, newsHeadline)
{
   NewspaperNews news(exclusionList);
   std::string headline(u8"Dummy title");
   news.setHeadline(headline);
   EXPECT_THAT(news.getHeadline(), ::testing::Eq(headline));
}

TEST_F(NewspaperNewsTestSuite, wordIsNotContainedInHeadline)
{
   NewspaperNews news(exclusionList);
   std::string headline(u8"La Policía intervino durante la manifestación");
   news.setHeadline(headline);
   EXPECT_FALSE(news.isContainedInHeadline("Policías"));
}

TEST_F(NewspaperNewsTestSuite, wordIsContainedInHeadline)
{
   NewspaperNews news(exclusionList);
   std::string headline(u8"La Policía intervino durante la manifestación");
   news.setHeadline(headline);
   EXPECT_TRUE(news.isContainedInHeadline("Policía"));
}
