
#include <vector>
#include <string>
#include "gmock/gmock.h"
#include "News.h"
#include "ExclusionList.h"
#include "ExclusionListMock.h"

class NewsTestSuite : public ::testing::Test
{
protected:
   ExclusionListMock exclusionList;
};

TEST_F(NewsTestSuite, getMostMentionedEntityNoMentionedEntities)
{
   News news(exclusionList);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq(""));
}

TEST_F(NewsTestSuite, computeMostMentionedEntityWordsNotInExclusionList)
{
   std::vector<std::string> newsText{"Hello", "Hello", "Goodbye", "Sayonara"};
   News news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(4).WillRepeatedly(::testing::Return(false));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq("Hello"));
}

TEST_F(NewsTestSuite, computeMostMentionedEntityWordsInExclusionList)
{
   std::vector<std::string> newsText{"Hello", "Hello", "Hello", "Sayonara", "Sayonara"};
   News news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(5)
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(true))
      .WillRepeatedly(::testing::Return(false));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq("Sayonara"));
}

TEST_F(NewsTestSuite, computeMostMentionedEntityWordsNotStartedByCapitalLetter)
{
   std::vector<std::string> newsText{"hello", "hello", "hello", "Sayonara", "Sayonara"};
   News news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(2)
      .WillRepeatedly(::testing::Return(false));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq("Sayonara"));
}

TEST_F(NewsTestSuite, computeMostMentionedEntityNonAsciiWordsNotInExclusionList)
{
   std::vector<std::string> newsText{u8"Ñoñería", u8"Ñoñería", u8"Ungüento", u8"Comparación"};
   News news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(4).WillRepeatedly(::testing::Return(false));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq(u8"Ñoñería"));
}

TEST_F(NewsTestSuite, computeMostMentionedEntityNonAsciiWordsInExclusionList)
{
   std::vector<std::string> newsText{u8"Ñoñería", u8"Ñoñería", u8"Ungüento", u8"Ungüento", u8"Ñoñería"};
   News news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(5)
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq(u8"Ungüento"));
}

TEST_F(NewsTestSuite, computeMostMentionedEntityNonAsciiWordsNotStartedByCapitalLetter)
{
   std::vector<std::string> newsText{u8"ñoñería", u8"ñoñería", u8"ungüento", u8"Ungüento", u8"ñoñería"};
   News news(exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(1)
      .WillRepeatedly(::testing::Return(false));

   news.setMentionedEntities(newsText);
   EXPECT_THAT(news.getMostMentionedEntity(), ::testing::Eq(u8"Ungüento"));
}
