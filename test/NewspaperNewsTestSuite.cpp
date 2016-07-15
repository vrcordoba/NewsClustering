
#include "gmock/gmock.h"

#include <vector>
#include <string>
#include <set>
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

TEST_F(NewspaperNewsTestSuite, newsSubject)
{
   NewspaperNews news(exclusionList);
   std::string subject(u8"Dummy title");
   news.setSubject(subject);
   EXPECT_THAT(news.getSubject(), ::testing::Eq(subject));
}

TEST_F(NewspaperNewsTestSuite, wordIsNotContainedInSubject)
{
   NewspaperNews news(exclusionList);
   std::string subject(u8"La Policía intervino durante la manifestación");
   news.setSubject(subject);
   EXPECT_FALSE(news.isContainedInSubject("Policías"));
}

TEST_F(NewspaperNewsTestSuite, wordIsContainedInSubject)
{
   NewspaperNews news(exclusionList);
   std::string subject(u8"La Policía intervino durante la manifestación");
   news.setSubject(subject);
   EXPECT_TRUE(news.isContainedInSubject("Policía"));
}

TEST_F(NewspaperNewsTestSuite, getRelevantEntitiesNoMentionedEntities)
{
   NewspaperNews news(exclusionList);
   std::set<std::string> emptyRelevantEntities;
   EXPECT_THAT(news.getRelevantEntities(), ::testing::Eq(emptyRelevantEntities));
}

TEST_F(NewspaperNewsTestSuite, getRelevantEntitiesSomeEntitiesInExclusionList)
{
   std::vector<std::string> newsText{u8"One", u8"Two", u8"Three", u8"Four", u8"Five", u8"Six"};
   NewspaperNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(6)
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(false));

   news.setMentionedEntities(newsText);

   std::set<std::string> expectedResult{u8"Two"};
   EXPECT_THAT(news.getRelevantEntities(), ::testing::Eq(expectedResult));
}

TEST_F(NewspaperNewsTestSuite, getRelevantEntitiesSomeWordsNotMentionedEntities)
{
   std::vector<std::string> newsText{u8"One", u8"two", u8"Three", u8"four", u8"Five",
      u8"six", u8"Seven", u8"eight", u8"Nine", u8"ten", u8"Eleven", u8"twelve"};
   NewspaperNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(6)
      .WillRepeatedly(::testing::Return(false));

   news.setMentionedEntities(newsText);

   std::set<std::string> expectedResult{u8"One", u8"Three"};
   EXPECT_THAT(news.getRelevantEntities(), ::testing::Eq(expectedResult));
}

TEST_F(NewspaperNewsTestSuite, isNotContainedInRelevantEntities)
{
   std::vector<std::string> mentionedEntities{"One", "Two", "Three",
      "Four", "Five", "Six"};
   NewspaperNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(6)
      .WillRepeatedly(::testing::Return(false));
   news.setMentionedEntities(mentionedEntities);

   EXPECT_FALSE(news.isContainedInRelevantEntities("Three"));
}

TEST_F(NewspaperNewsTestSuite, isContainedInRelevantEntities)
{
   std::vector<std::string> mentionedEntities{"One", "Two", "Three",
      "Four", "Five", "Six"};
   NewspaperNews news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(6)
      .WillRepeatedly(::testing::Return(false));
   news.setMentionedEntities(mentionedEntities);

   EXPECT_TRUE(news.isContainedInRelevantEntities("Two"));
}
