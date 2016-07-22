
#include "gmock/gmock.h"

#include "TuitReader.h"
#include "InvalidLocationException.h"
#include "ExclusionListMock.h"
#include "ExclusionListFromFile.h"
#include "TwitterNews.h"

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

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(15)
      .WillRepeatedly(::testing::Return(false));

   std::vector<std::shared_ptr<News>> recoveredNews = newsReader.getNews();
   EXPECT_THAT(recoveredNews.size(), ::testing::Eq(2));

   std::set<std::string> expectedMostMentionedEntities{u8"Repelús", u8"Verano"};
   std::set<std::string> obtainedMostMentionedEntities;
   for (auto& news : recoveredNews)
      obtainedMostMentionedEntities.insert(news->getMostMentionedEntity());
   EXPECT_THAT(obtainedMostMentionedEntities, ::testing::Eq(expectedMostMentionedEntities));

   std::set<unsigned int> expectedIds{123, 456};
   std::set<unsigned int> obtainedIds;
   for (auto& news : recoveredNews)
      obtainedIds.insert(static_cast<TwitterNews*>(news.get())->getId());
   EXPECT_THAT(obtainedIds, ::testing::Eq(expectedIds));

   std::set<std::string> expectedUsers{u8"@yo", u8"@tu"};
   std::set<std::string> obtainedUsers;
   for (auto& news : recoveredNews)
      obtainedUsers.insert(static_cast<TwitterNews*>(news.get())->getUser());
   EXPECT_THAT(obtainedUsers, ::testing::Eq(expectedUsers));
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
   std::set<std::string> obtainedSubjects;
   for (auto& news : recoveredNews)
      obtainedSubjects.insert(news->getSubject());
   EXPECT_THAT(expectedSubjects, ::testing::Eq(obtainedSubjects));

   std::set<unsigned int> expectedIds{0, 1, 2};
   std::set<unsigned int> obtainedIds;
   for (auto& news : recoveredNews)
      obtainedIds.insert(static_cast<TwitterNews*>(news.get())->getId());
   EXPECT_THAT(obtainedIds, ::testing::Eq(expectedIds));

   std::set<std::string> expectedUsers{u8"@pepe_perez", u8"@juan_toqui", u8"@pupulupu"};
   std::set<std::string> obtainedUsers;
   for (auto& news : recoveredNews)
      obtainedUsers.insert(static_cast<TwitterNews*>(news.get())->getUser());
   EXPECT_THAT(obtainedUsers, ::testing::Eq(expectedUsers));
}
