
#include "gmock/gmock.h"

#include <memory>
#include "ExclusionListMock.h"
#include "ExclusionListFromFile.h"
#include "NewsReaderFromPlainText.h"
#include "InvalidDirectoryException.h"
#include "News.h"

class NewsReaderTestSuite : public ::testing::Test
{
protected:
   ExclusionListMock exclusionList;
};

TEST_F(NewsReaderTestSuite, wrongDirectory)
{
   NewsReaderFromPlainText newsReader("/wrong_directory", exclusionList);
   EXPECT_THROW(newsReader.getNews(), InvalidDirectoryException);
}

TEST_F(NewsReaderTestSuite, emptyDirectory)
{
   NewsReaderFromPlainText newsReader("dummyData/emptyDir", exclusionList);
   EXPECT_THAT(newsReader.getNews().size(), ::testing::Eq(0));
}

TEST_F(NewsReaderTestSuite, directoryWithPhonyNews)
{
   NewsReaderFromPlainText newsReader("dummyData/dummyNews", exclusionList);

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
   NewsReaderFromPlainText newsReader("../data/news", realExclusionList);
   EXPECT_THAT(newsReader.getNews().size(), ::testing::Eq(48));
}
