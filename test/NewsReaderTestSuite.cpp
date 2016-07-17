
#include "gmock/gmock.h"

#include <memory>
#include "NewsReader.h"
#include "ExclusionListMock.h"
#include "ExclusionListFromFile.h"
#include "News.h"
#include "NewspaperNews.h"
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
   std::set<std::string> obtainedMostMentionedEntities;
   for (auto& news : recoveredNews)
      obtainedMostMentionedEntities.insert(news->getMostMentionedEntity());
   EXPECT_THAT(obtainedMostMentionedEntities, ::testing::Eq(expectedMostMentionedEntities));

   std::vector<std::vector<std::string>> expectedParagraphs{
      {
         u8"Buen Titular para captar tu atención .",
         u8"Tras el Titular no hay nada más .",
         u8"La Noticia no dice nada ."
      },
      {
         u8"La canción de este Verano es la Cigüeña come un Entremés"
      }
   };
   std::size_t i = 0;
   for (auto& news : recoveredNews)
   {
      EXPECT_THAT(static_cast<NewspaperNews*>(news.get())->getParagraphs(),
         ::testing::Eq(expectedParagraphs[i++]));
   }
}

TEST_F(NewsReaderTestSuite, directoryWithPhonyJsonNews)
{
   NewsReader newsReader("dummyData/dummyJsonNews", exclusionList);

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
   std::set<std::string> obtainedMostMentionedEntities;
   for (auto& news : recoveredNews)
      obtainedMostMentionedEntities.insert(news->getMostMentionedEntity());
   EXPECT_THAT(obtainedMostMentionedEntities, ::testing::Eq(expectedMostMentionedEntities));

   std::vector<std::vector<std::string>> expectedParagraphs{
      {
         u8"Buen Titular para captar tu atención .",
         u8"Tras el Titular no hay nada más .",
         u8"La Noticia no dice nada ."
      },
      {
         u8"La canción de este Verano es la Cigüeña come un Entremés"
      }
   };
   std::size_t i = 0;
   for (auto& news : recoveredNews)
   {
      EXPECT_THAT(static_cast<NewspaperNews*>(news.get())->getParagraphs(),
         ::testing::Eq(expectedParagraphs[i++]));
   }
}

TEST_F(NewsReaderTestSuite, directoryWithRealNews)
{
   ExclusionListFromFile realExclusionList("../data/ES_stopList.txt");
   NewsReader newsReader("../data/news", realExclusionList);
   EXPECT_THAT(newsReader.getNews().size(), ::testing::Eq(48));
}

TEST_F(NewsReaderTestSuite, directoryWithRealJsonNews)
{
   ExclusionListFromFile realExclusionList("../data/ES_stopList.txt");
   NewsReader newsReader("../data/news_json", realExclusionList);
   EXPECT_THAT(newsReader.getNews().size(), ::testing::Eq(3));
}
