
#include "gmock/gmock.h"

#include "TuitReader.h"
#include "InvalidLocationException.h"
#include "ExclusionListMock.h"
#include "ExclusionListFromFile.h"

class TuitReaderTestSuite : public ::testing::Test
{
protected:
   ExclusionListMock exclusionList;
};

TEST_F(TuitReaderTestSuite, wrongFile)
{
   TuitReader newsReader("/wrong_file.json", exclusionList);
   EXPECT_THROW(newsReader.getNews(), InvalidLocationException);
}

TEST_F(TuitReaderTestSuite, emptyFile)
{
   TuitReader newsReader("dummyData/dummyTwitterNews/empty.json", exclusionList);
   EXPECT_THAT(newsReader.getNews().size(), ::testing::Eq(0));
}

TEST_F(TuitReaderTestSuite, fileWithPhonyNews)
{
   TuitReader newsReader("dummyData/dummyTwitterNews/dummy.json", exclusionList);

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

TEST_F(TuitReaderTestSuite, fileWithRealNews)
{
   ExclusionListFromFile realExclusionList("../data/ES_stopList.txt");
   TuitReader newsReader("../data/tuits.txt", realExclusionList);

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
