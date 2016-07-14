
#include "gmock/gmock.h"

#include <memory>
#include "NewsDiscriminator.h"
#include "ExclusionListMock.h"
#include "News.h"
#include "NewspaperNews.h"
#include "TwitterNews.h"

class NewsDiscriminatorTestSuite : public ::testing::Test
{
protected:
   ExclusionListMock exclusionList;
};

TEST_F(NewsDiscriminatorTestSuite, bothNewspaper)
{
   NewsDiscriminator newsDiscriminator;
   News* news1 = new NewspaperNews(exclusionList);
   std::shared_ptr<News> firstNews(news1);
   News* news2 = new NewspaperNews(exclusionList);
   std::shared_ptr<News> secondNews(news2);

   EXPECT_THAT(newsDiscriminator.discriminateType(firstNews, secondNews),
      ::testing::Eq(NewsDiscriminator::bothFromNewspaper));
}

TEST_F(NewsDiscriminatorTestSuite, bothTwitter)
{
   NewsDiscriminator newsDiscriminator;
   News* news1 = new TwitterNews(exclusionList);
   std::shared_ptr<News> firstNews(news1);
   News* news2 = new TwitterNews(exclusionList);
   std::shared_ptr<News> secondNews(news2);

   EXPECT_THAT(newsDiscriminator.discriminateType(firstNews, secondNews),
      ::testing::Eq(NewsDiscriminator::bothFromTwitter));
}

TEST_F(NewsDiscriminatorTestSuite, newspaperTwitter)
{
   NewsDiscriminator newsDiscriminator;
   News* news1 = new NewspaperNews(exclusionList);
   std::shared_ptr<News> firstNews(news1);
   News* news2 = new TwitterNews(exclusionList);
   std::shared_ptr<News> secondNews(news2);

   EXPECT_THAT(newsDiscriminator.discriminateType(firstNews, secondNews),
      ::testing::Eq(NewsDiscriminator::firstFromNewspaperSecondFromTwitter));
}

TEST_F(NewsDiscriminatorTestSuite, twitterNewspaper)
{
   NewsDiscriminator newsDiscriminator;
   News* news1 = new TwitterNews(exclusionList);
   std::shared_ptr<News> firstNews(news1);
   News* news2 = new NewspaperNews(exclusionList);
   std::shared_ptr<News> secondNews(news2);

   EXPECT_THAT(newsDiscriminator.discriminateType(firstNews, secondNews),
      ::testing::Eq(NewsDiscriminator::firstFromTwitterSecondFromNewspaper));
}

TEST_F(NewsDiscriminatorTestSuite, severalCalls)
{
   NewsDiscriminator newsDiscriminator;
   News* news1 = new NewspaperNews(exclusionList);
   std::shared_ptr<News> firstNews(news1);
   News* news2 = new NewspaperNews(exclusionList);
   std::shared_ptr<News> secondNews(news2);
   News* news3 = new TwitterNews(exclusionList);
   std::shared_ptr<News> thirdNews(news3);
   News* news4 = new TwitterNews(exclusionList);
   std::shared_ptr<News> fourthNews(news4);

   EXPECT_THAT(newsDiscriminator.discriminateType(firstNews, secondNews),
      ::testing::Eq(NewsDiscriminator::bothFromNewspaper));
   EXPECT_THAT(newsDiscriminator.discriminateType(thirdNews, fourthNews),
      ::testing::Eq(NewsDiscriminator::bothFromTwitter));
}
