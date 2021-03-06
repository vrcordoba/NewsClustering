
#include "gmock/gmock.h"

#include <memory>
#include "NewsReader.h"
#include "ExclusionListMock.h"
#include "ExclusionListFromFile.h"
#include "News.h"
#include "NewspaperNews.h"
#include "InvalidLocationException.h"

class NewsReaderTestSuite : public ::testing::TestWithParam<std::string>
{
protected:
   ExclusionListMock exclusionList;
};

TEST_F(NewsReaderTestSuite, wrongDirectory)
{
   NewsReader newsReader("/wrong_directory", exclusionList);
   EXPECT_THROW(newsReader.getNews(), InvalidLocationException);
}

TEST_P(NewsReaderTestSuite, directoryWithPhonyNews)
{
   NewsReader newsReader(GetParam(), exclusionList);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(15)
      .WillRepeatedly(::testing::Return(false));

   std::vector<std::shared_ptr<News>> recoveredNews = newsReader.getNews();
   EXPECT_THAT(recoveredNews.size(), ::testing::Eq(2));

   std::set<std::string> expectedMostMentionedEntities{u8"Repelús", u8"Verano"};
   std::set<std::string> obtainedMostMentionedEntities;
   for (auto& news : recoveredNews)
      obtainedMostMentionedEntities.insert(news->getMostMentionedEntity());
   EXPECT_THAT(obtainedMostMentionedEntities, ::testing::Eq(expectedMostMentionedEntities));

   std::set<std::vector<std::string>> expectedParagraphs{
      {
         u8"Buen Titular para captar tu atención .",
         u8"Tras él no hay nada más .",
         u8"La Noticia no dice nada ."
      },
      {
         u8"La canción de este Verano es la Cigüeña come un Entremés"
      }
   };
   EXPECT_THAT(recoveredNews.size(), ::testing::Eq(expectedParagraphs.size()));
   for (auto& news : recoveredNews)
   {
      std::vector<std::string> recoveredParagraph = static_cast<NewspaperNews*>(news.get())->getParagraphs();
      std::set<std::vector<std::string>>::iterator it = expectedParagraphs.find(recoveredParagraph);
      if (it == std::end(expectedParagraphs))
         FAIL() << "Paragraph not expected";
      else
         expectedParagraphs.erase(it);
   }
   if (not expectedParagraphs.empty())
   {
      FAIL() << "Result contains more news than expected";
   }
}

INSTANTIATE_TEST_CASE_P(Default, NewsReaderTestSuite, ::testing::Values(
   std::string("dummyData/dummyNews"), std::string("dummyData/dummyJsonNews")));

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
