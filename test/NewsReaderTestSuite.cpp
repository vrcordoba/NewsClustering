
#include "gmock/gmock.h"

#include "ExclusionListFromFile.h"
#include "NewsReaderFromPlainText.h"
#include "InvalidDirectoryException.h"
#include "News.h"

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
   std::vector<News> recoveredNews = newsReader.getNews();
   EXPECT_THAT(recoveredNews.size(), ::testing::Eq(2));
   EXPECT_THAT(recoveredNews[0].getMostMentionedEntity(), ::testing::Eq(std::string(u8"Titular")));
   EXPECT_THAT(recoveredNews[1].getMostMentionedEntity(), ::testing::Eq(std::string(u8"Verano")));
}

TEST(NewsReaderTestSuite, directoryWithRealNews)
{
   ExclusionListFromFile exclusionList("../data/ES_stopList.txt");
   NewsReaderFromPlainText newsReader("../data/news", exclusionList);
   EXPECT_THAT(newsReader.getNews().size(), ::testing::Eq(48));
}
