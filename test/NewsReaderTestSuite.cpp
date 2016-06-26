
#include "gmock/gmock.h"

#include "ExclusionListFromFile.h"
#include "NewsReaderFromPlainText.h"
#include "InvalidDirectoryException.h"
#include "News.h"
#include "NewsCluster.h"

TEST(NewsReaderTestSuite, wrongDirectory)
{
   ExclusionListFromFile exclusionList("dummyData/emptyStopList.txt");
   NewsReaderFromPlainText newsReader("/wrong_directory", exclusionList);
   ASSERT_THROW(newsReader.getNews(), InvalidDirectoryException);
}

TEST(NewsReaderTestSuite, emptyDirectory)
{
   ExclusionListFromFile exclusionList("dummyData/emptyStopList.txt");
   NewsReaderFromPlainText newsReader("dummyData/emptyDir", exclusionList);
   EXPECT_THAT(newsReader.getNews().size(), ::testing::Eq(0));
}

TEST(NewsReaderTestSuite, directoryWithPhonyNews)
{
   ExclusionListFromFile exclusionList("dummyData/litteSpanishStopList.txt");
   NewsReaderFromPlainText newsReader("dummyData/dummyNews", exclusionList);
   std::vector<NewsCluster> recoveredNews = newsReader.getNews();
   EXPECT_THAT(recoveredNews.size(), ::testing::Eq(2));
   std::set<std::string> expectedMostMentionedEntities{u8"Titular", u8"Verano"};
   for (auto& news : recoveredNews)
   {
      std::set<std::string>::iterator it = expectedMostMentionedEntities.find(news.begin()->getMostMentionedEntity());
      EXPECT_TRUE(it != expectedMostMentionedEntities.end());
      expectedMostMentionedEntities.erase(it);
   }
}

TEST(NewsReaderTestSuite, directoryWithRealNews)
{
   ExclusionListFromFile exclusionList("../data/ES_stopList.txt");
   NewsReaderFromPlainText newsReader("../data/news", exclusionList);
   EXPECT_THAT(newsReader.getNews().size(), ::testing::Eq(48));
}
