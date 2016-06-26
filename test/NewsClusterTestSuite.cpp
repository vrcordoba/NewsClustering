
#include "gmock/gmock.h"

#include <cstdint>
#include "News.h"
#include "NewsCluster.h"
#include "ExclusionListMock.h"

TEST(NewsClusterTestSuite, emptyCluster)
{
   NewsCluster newsCluster;
   std::uint32_t clusterSize = 0;
   for (auto& news : newsCluster)
   {
      news.getMostMentionedEntity();
      clusterSize++;
   }
   ASSERT_THAT(clusterSize, ::testing::Eq(0));
}

TEST(NewsClusterTestSuite, addNews)
{
   NewsCluster newsCluster;
   ExclusionListMock exclusionList;
   News news(exclusionList);

   newsCluster.addNews(news);

   std::uint32_t clusterSize = 0;
   for (auto& news : newsCluster)
   {
      news.getMostMentionedEntity();
      clusterSize++;
   }
   ASSERT_THAT(clusterSize, ::testing::Eq(1));
}

TEST(NewsClusterTestSuite, mergeCluster)
{
   NewsCluster newsCluster1, newsCluster2;
   ExclusionListMock exclusionList;
   News newsA(exclusionList), newsB(exclusionList), newsC(exclusionList), newsD(exclusionList);
   newsCluster1.addNews(newsA);
   newsCluster1.addNews(newsB);
   newsCluster2.addNews(newsC);
   newsCluster2.addNews(newsD);

   newsCluster1.mergeCluster(newsCluster2);

   std::uint32_t clusterSize = 0;
   for (auto& news : newsCluster1)
   {
      news.getMostMentionedEntity();
      clusterSize++;
   }
   ASSERT_THAT(clusterSize, ::testing::Eq(4));

   clusterSize = 0;
   for (auto& news : newsCluster2)
   {
      news.getMostMentionedEntity();
      clusterSize++;
   }
   ASSERT_THAT(clusterSize, ::testing::Eq(0));
}
