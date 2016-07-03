
#include "gmock/gmock.h"

#include <memory>
#include "Clusterizer.h"
#include "ClusteringCriterionMock.h"
#include "NewsReaderMock.h"
#include "News.h"
#include "NewsMock.h"

class ClusterizerTestSuite : public ::testing::Test
{
protected:
   virtual void SetUp()
   {
      clusterizer.setCriterion(&clusteringCriterion);
      clusterizer.setNewsReader(&newsReader);
   }

   ClusteringCriterionMock clusteringCriterion;
   NewsReaderMock newsReader;
   Clusterizer clusterizer;
};

TEST_F(ClusterizerTestSuite, emptyVectorOfNews)
{
   std::vector<std::shared_ptr<News>> emptyVectorOfNews;

   EXPECT_CALL(newsReader, getNews()).Times(1).WillOnce(::testing::Return(emptyVectorOfNews));
   EXPECT_CALL(clusteringCriterion, areBothInTheSameCluster(::testing::_, ::testing::_)).Times(0);

   clusterizer.obtainClusters();

   EXPECT_THAT(clusterizer.getClusters().empty(), ::testing::Eq(true));
}

TEST_F(ClusterizerTestSuite, onlyOneNews)
{
   std::shared_ptr<News> news = std::make_shared<NewsMock>();
   std::vector<std::shared_ptr<News>> vectorOfNews{news};

   EXPECT_CALL(newsReader, getNews()).Times(1).WillOnce(::testing::Return(vectorOfNews));
   EXPECT_CALL(clusteringCriterion, areBothInTheSameCluster(::testing::_, ::testing::_)).Times(0);

   clusterizer.obtainClusters();

   std::vector<NewsCluster> obtainedResult = clusterizer.getClusters();
   EXPECT_THAT(obtainedResult.size(), ::testing::Eq(1));
   EXPECT_THAT(obtainedResult[0].size(), ::testing::Eq(1));
}

TEST_F(ClusterizerTestSuite, twoNewsNotFulfillingCriterion)
{
   std::shared_ptr<News> news1 = std::make_shared<NewsMock>();
   std::shared_ptr<News> news2 = std::make_shared<NewsMock>();
   std::vector<std::shared_ptr<News>> vectorOfNews{news1, news2};

   EXPECT_CALL(newsReader, getNews()).Times(1).WillOnce(::testing::Return(vectorOfNews));
   EXPECT_CALL(clusteringCriterion, areBothInTheSameCluster(::testing::_, ::testing::_))
      .Times(2).WillRepeatedly(::testing::Return(false));

   clusterizer.obtainClusters();

   std::vector<NewsCluster> obtainedResult = clusterizer.getClusters();
   EXPECT_THAT(obtainedResult.size(), ::testing::Eq(2));
   EXPECT_THAT(obtainedResult[0].size(), ::testing::Eq(1));
   EXPECT_THAT(obtainedResult[1].size(), ::testing::Eq(1));
}

TEST_F(ClusterizerTestSuite, twoNewsFulfillingCriterion)
{
   std::shared_ptr<News> news1 = std::make_shared<NewsMock>();
   std::shared_ptr<News> news2 = std::make_shared<NewsMock>();
   std::vector<std::shared_ptr<News>> vectorOfNews{news1, news2};

   EXPECT_CALL(newsReader, getNews()).Times(1).WillOnce(::testing::Return(vectorOfNews));
   EXPECT_CALL(clusteringCriterion, areBothInTheSameCluster(::testing::_, ::testing::_)).Times(2)
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(false));

   clusterizer.obtainClusters();

   std::vector<NewsCluster> obtainedResult = clusterizer.getClusters();
   EXPECT_THAT(obtainedResult.size(), ::testing::Eq(1));
   EXPECT_THAT(obtainedResult[0].size(), ::testing::Eq(2));
}

TEST_F(ClusterizerTestSuite, twoClustersSeveralNewsInEachCluster)
{
   std::shared_ptr<News> newsA = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsB = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsC = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsD = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsE = std::make_shared<NewsMock>();
   std::vector<std::shared_ptr<News>> vectorOfNews{newsA, newsB, newsC, newsD, newsE};

   EXPECT_CALL(newsReader, getNews()).Times(1).WillOnce(::testing::Return(vectorOfNews));
   EXPECT_CALL(clusteringCriterion, areBothInTheSameCluster(::testing::_, ::testing::_)).Times(20)
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(true))
      .WillRepeatedly(::testing::Return(false));

   clusterizer.obtainClusters();

   std::vector<NewsCluster> obtainedResult = clusterizer.getClusters();
   EXPECT_THAT(obtainedResult.size(), ::testing::Eq(2));
   EXPECT_THAT(obtainedResult[0].size(), ::testing::Eq(2));
   EXPECT_THAT(obtainedResult[1].size(), ::testing::Eq(3));
}
