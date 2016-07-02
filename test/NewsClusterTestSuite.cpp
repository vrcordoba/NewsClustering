
#include "gmock/gmock.h"

#include <cstdint>
#include "News.h"
#include "NewsCluster.h"
#include "ExclusionListMock.h"

TEST(NewsClusterTestSuite, emptyCluster)
{
   NewsCluster newsCluster;
   ASSERT_THAT(newsCluster.empty(), ::testing::Eq(true));
}

TEST(NewsClusterTestSuite, addNews)
{
   NewsCluster newsCluster;
   ExclusionListMock exclusionList;
   News news(exclusionList);

   newsCluster.addNews(news);

   ASSERT_THAT(newsCluster.empty(), ::testing::Eq(false));
   ASSERT_THAT(newsCluster.size(), ::testing::Eq(1));
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

   ASSERT_THAT(newsCluster1.size(), ::testing::Eq(4));
   ASSERT_THAT(newsCluster2.size(), ::testing::Eq(0));

}
