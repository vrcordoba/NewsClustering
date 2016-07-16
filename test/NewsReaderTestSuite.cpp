
#include "gmock/gmock.h"

#include <memory>
#include "NewsReader.h"
#include "ExclusionListMock.h"
#include "ExclusionListFromFile.h"
#include "News.h"
#include "InvalidLocationException.h"

class NewsReaderTestSuite : public ::testing::Test
{
protected:
   ExclusionListMock exclusionList;
};

TEST_F(NewsReaderTestSuite, wrongDirectory)
{
   NewsReader newsReader("/wrong_directory", exclusionList);
   EXPECT_THROW(newsReader.getNews(), InvalidLocationException);
}

TEST_F(NewsReaderTestSuite, emptyDirectory)
{
   NewsReader newsReader("dummyData/emptyDir", exclusionList);
   EXPECT_THAT(newsReader.getNews().size(), ::testing::Eq(0));
}

TEST_F(NewsReaderTestSuite, directoryWithPhonyNews)
{
   NewsReader newsReader("dummyData/dummyNews", exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(16)
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(true));

   std::vector<std::shared_ptr<News>> recoveredNews = newsReader.getNews();
   EXPECT_THAT(recoveredNews.size(), ::testing::Eq(2));
   std::set<std::string> expectedMostMentionedEntities{u8"Titular", u8"Verano"};
   for (auto& news : recoveredNews)
   {
      std::set<std::string>::iterator it = expectedMostMentionedEntities.find(
         news->getMostMentionedEntity());
      EXPECT_TRUE(it != expectedMostMentionedEntities.end());
      expectedMostMentionedEntities.erase(it);
   }
}

TEST_F(NewsReaderTestSuite, directoryWithRealNews)
{
   ExclusionListFromFile realExclusionList("../data/ES_stopList.txt");
   NewsReader newsReader("../data/news", realExclusionList);
   EXPECT_THAT(newsReader.getNews().size(), ::testing::Eq(48));
}
