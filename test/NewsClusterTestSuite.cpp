
#include "gmock/gmock.h"

#include <memory>
#include "NewsCluster.h"
#include "NewsMock.h"

TEST(NewsClusterTestSuite, emptyCluster)
{
   NewsCluster newsCluster;
   EXPECT_THAT(newsCluster.empty(), ::testing::Eq(true));
}

TEST(NewsClusterTestSuite, addNews)
{
   NewsCluster newsCluster;
   std::shared_ptr<News> news = std::make_shared<NewsMock>();

   newsCluster.addNews(news);

   EXPECT_THAT(newsCluster.empty(), ::testing::Eq(false));
   EXPECT_THAT(newsCluster.size(), ::testing::Eq(1));
}

TEST(NewsClusterTestSuite, mergeCluster)
{
   NewsCluster newsCluster1, newsCluster2;
   std::shared_ptr<News> newsA = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsB = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsC = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsD = std::make_shared<NewsMock>();
   newsCluster1.addNews(newsA);
   newsCluster1.addNews(newsB);
   newsCluster2.addNews(newsC);
   newsCluster2.addNews(newsD);

   newsCluster1.mergeCluster(newsCluster2);

   EXPECT_THAT(newsCluster1.size(), ::testing::Eq(4));
   EXPECT_THAT(newsCluster2.size(), ::testing::Eq(0));

}
