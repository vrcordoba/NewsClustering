
#include "gmock/gmock.h"

#include "NewsReaderFromTuit.h"
#include "InvalidLocationException.h"
#include "ExclusionListMock.h"
#include "ExclusionListFromFile.h"

class NewsReaderFromTuitTestSuite : public ::testing::Test
{
protected:
   ExclusionListMock exclusionList;
};

TEST_F(NewsReaderFromTuitTestSuite, wrongFile)
{
   NewsReaderFromTuit newsReader("/wrong_file.json", exclusionList);
   EXPECT_THROW(newsReader.getNews(), InvalidLocationException);
}

TEST_F(NewsReaderFromTuitTestSuite, emptyFile)
{
   NewsReaderFromTuit newsReader("dummyData/dummyJsonNews/empty.json", exclusionList);
   EXPECT_THAT(newsReader.getNews().size(), ::testing::Eq(0));
}

TEST_F(NewsReaderFromTuitTestSuite, fileWithPhonyNews)
{
   NewsReaderFromTuit newsReader("dummyData/dummyJsonNews/dummy.json", exclusionList);

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

TEST_F(NewsReaderFromTuitTestSuite, fileWithRealNews)
{
   ExclusionListFromFile realExclusionList("../data/ES_stopList.txt");
   NewsReaderFromTuit newsReader("../data/tuits.txt", realExclusionList);

   std::vector<std::shared_ptr<News>> recoveredNews = newsReader.getNews();
   EXPECT_THAT(recoveredNews.size(), ::testing::Eq(3));
   std::set<std::string> expectedSubjects{
      u8"Liberan a los dos sospechosos detenidos por el asesinato de un niño de 11 años en Liverpool",
      u8"Detienen a seis jóvenes más en relación con el asesinato de el niño de Liverpool",
      u8"Siguen los interrogatorios a los detenidos por el asesinato de el niño de Liverpool"
   };
   for (auto& news : recoveredNews)
   {
      std::set<std::string>::iterator it = expectedSubjects.find(
         news->getSubject());
      EXPECT_TRUE(it != expectedSubjects.end());
      expectedSubjects.erase(it);
   }
}
