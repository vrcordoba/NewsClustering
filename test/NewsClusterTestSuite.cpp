
#include "gmock/gmock.h"

#include <memory>
#include "NewsCluster.h"
#include "NewsMock.h"

TEST(NewsClusterTestSuite, emptyCluster)
{
   NewsCluster newsCluster;
   ASSERT_THAT(newsCluster.empty(), ::testing::Eq(true));
}

TEST(NewsClusterTestSuite, addNews)
{
   NewsCluster newsCluster;
   std::shared_ptr<News> news = std::make_shared<NewsMock>();

   newsCluster.addNews(news);

   ASSERT_THAT(newsCluster.empty(), ::testing::Eq(false));
   ASSERT_THAT(newsCluster.size(), ::testing::Eq(1));
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

   ASSERT_THAT(newsCluster1.size(), ::testing::Eq(4));
   ASSERT_THAT(newsCluster2.size(), ::testing::Eq(0));

}
