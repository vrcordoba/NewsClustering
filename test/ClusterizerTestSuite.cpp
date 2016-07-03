
#include <memory>
#include "gmock/gmock.h"
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
   std::vector<NewsCluster> emptyVectorOfNews;

   EXPECT_CALL(newsReader, getNews()).Times(1).WillOnce(::testing::Return(emptyVectorOfNews));
   EXPECT_CALL(clusteringCriterion, areBothInTheSameCluster(::testing::_, ::testing::_)).Times(0);

   clusterizer.createClusters();

   EXPECT_THAT(clusterizer.getClusters().empty(), ::testing::Eq(true));
}

TEST_F(ClusterizerTestSuite, onlyOneNewsInCluster)
{
   NewsCluster newsCluster;
   std::shared_ptr<News> news = std::make_shared<NewsMock>();
   newsCluster.addNews(news);
   std::vector<NewsCluster> vectorOfNews;
   vectorOfNews.push_back(newsCluster);

   EXPECT_CALL(newsReader, getNews()).Times(1).WillOnce(::testing::Return(vectorOfNews));
   EXPECT_CALL(clusteringCriterion, areBothInTheSameCluster(::testing::_, ::testing::_)).Times(0);

   clusterizer.createClusters();

   EXPECT_THAT(clusterizer.getClusters().size(), ::testing::Eq(1));
}

TEST_F(ClusterizerTestSuite, twoNewsNotFulfillingCriterion)
{
   NewsCluster newsCluster1;
   std::shared_ptr<News> news1 = std::make_shared<NewsMock>();
   newsCluster1.addNews(news1);

   NewsCluster newsCluster2;
   std::shared_ptr<News> news2 = std::make_shared<NewsMock>();
   newsCluster2.addNews(news2);

   std::vector<NewsCluster> vectorOfNews{newsCluster1, newsCluster2};

   EXPECT_CALL(newsReader, getNews()).Times(1).WillOnce(::testing::Return(vectorOfNews));
   EXPECT_CALL(clusteringCriterion, areBothInTheSameCluster(::testing::_, ::testing::_))
      .Times(2).WillRepeatedly(::testing::Return(false));

   clusterizer.createClusters();

   std::vector<NewsCluster> obtainedResult = clusterizer.getClusters();
   EXPECT_THAT(obtainedResult.size(), ::testing::Eq(2));
   EXPECT_THAT(obtainedResult[0].size(), ::testing::Eq(1));
   EXPECT_THAT(obtainedResult[1].size(), ::testing::Eq(1));
}

TEST_F(ClusterizerTestSuite, twoNewsFulfillingCriterion)
{
   NewsCluster newsCluster1;
   std::shared_ptr<News> news1 = std::make_shared<NewsMock>();
   newsCluster1.addNews(news1);

   NewsCluster newsCluster2;
   std::shared_ptr<News> news2 = std::make_shared<NewsMock>();
   newsCluster2.addNews(news2);

   std::vector<NewsCluster> vectorOfNews{newsCluster1, newsCluster2};

   EXPECT_CALL(newsReader, getNews()).Times(1).WillOnce(::testing::Return(vectorOfNews));
   EXPECT_CALL(clusteringCriterion, areBothInTheSameCluster(::testing::_, ::testing::_)).Times(2)
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(false));

   clusterizer.createClusters();

   std::vector<NewsCluster> obtainedResult = clusterizer.getClusters();
   EXPECT_THAT(obtainedResult.size(), ::testing::Eq(1));
   EXPECT_THAT(obtainedResult[0].size(), ::testing::Eq(2));
}

TEST_F(ClusterizerTestSuite, twoClustersSeveralNewsInEachClusterNotFulfillingCriterion)
{
   std::shared_ptr<News> newsA = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsB = std::make_shared<NewsMock>();
   NewsCluster newsCluster1;
   newsCluster1.addNews(newsA);
   newsCluster1.addNews(newsB);

   std::shared_ptr<News> newsC = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsD = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsE = std::make_shared<NewsMock>();
   NewsCluster newsCluster2;
   newsCluster2.addNews(newsC);
   newsCluster2.addNews(newsD);
   newsCluster2.addNews(newsE);

   std::vector<NewsCluster> vectorOfNews{newsCluster1, newsCluster2};

   EXPECT_CALL(newsReader, getNews()).Times(1).WillOnce(::testing::Return(vectorOfNews));
   EXPECT_CALL(clusteringCriterion, areBothInTheSameCluster(::testing::_, ::testing::_))
      .Times(2).WillRepeatedly(::testing::Return(false));

   clusterizer.createClusters();

   std::vector<NewsCluster> obtainedResult = clusterizer.getClusters();
   EXPECT_THAT(obtainedResult.size(), ::testing::Eq(2));
   EXPECT_THAT(obtainedResult[0].size(), ::testing::Eq(2));
   EXPECT_THAT(obtainedResult[1].size(), ::testing::Eq(3));
}

TEST_F(ClusterizerTestSuite, twoClustersSeveralNewsInEachClusterFulfillingCriterion)
{
   std::shared_ptr<News> newsA = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsB = std::make_shared<NewsMock>();
   NewsCluster newsCluster1;
   newsCluster1.addNews(newsA);
   newsCluster1.addNews(newsB);

   std::shared_ptr<News> newsC = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsD = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsE = std::make_shared<NewsMock>();
   NewsCluster newsCluster2;
   newsCluster2.addNews(newsC);
   newsCluster2.addNews(newsD);
   newsCluster2.addNews(newsE);

   std::vector<NewsCluster> vectorOfNews{newsCluster1, newsCluster2};

   EXPECT_CALL(newsReader, getNews()).Times(1).WillOnce(::testing::Return(vectorOfNews));
   EXPECT_CALL(clusteringCriterion, areBothInTheSameCluster(::testing::_, ::testing::_))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(false));

   clusterizer.createClusters();

   std::vector<NewsCluster> obtainedResult = clusterizer.getClusters();
   EXPECT_THAT(obtainedResult.size(), ::testing::Eq(1));
   EXPECT_THAT(obtainedResult[0].size(), ::testing::Eq(5));
}

TEST_F(ClusterizerTestSuite, severalClustersSeveralNewsInEachCluster)
{
   std::shared_ptr<News> newsA = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsB = std::make_shared<NewsMock>();
   NewsCluster newsCluster1;
   newsCluster1.addNews(newsA);
   newsCluster1.addNews(newsB);

   std::shared_ptr<News> newsC = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsD = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsE = std::make_shared<NewsMock>();
   NewsCluster newsCluster2;
   newsCluster2.addNews(newsC);
   newsCluster2.addNews(newsD);
   newsCluster2.addNews(newsE);

   std::shared_ptr<News> newsF = std::make_shared<NewsMock>();
   NewsCluster newsCluster3;
   newsCluster3.addNews(newsF);

   std::shared_ptr<News> newsG = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsH = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsI = std::make_shared<NewsMock>();
   std::shared_ptr<News> newsJ = std::make_shared<NewsMock>();
   NewsCluster newsCluster4;
   newsCluster4.addNews(newsG);
   newsCluster4.addNews(newsH);
   newsCluster4.addNews(newsI);
   newsCluster4.addNews(newsJ);

   std::vector<NewsCluster> vectorOfNews{newsCluster1, newsCluster2,
      newsCluster3, newsCluster4};

   EXPECT_CALL(newsReader, getNews()).Times(1).WillOnce(::testing::Return(vectorOfNews));
   EXPECT_CALL(clusteringCriterion, areBothInTheSameCluster(::testing::_, ::testing::_)).Times(12)
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false));

   clusterizer.createClusters();

   std::vector<NewsCluster> obtainedResult = clusterizer.getClusters();
   EXPECT_THAT(obtainedResult.size(), ::testing::Eq(2));
   EXPECT_THAT(obtainedResult[0].size(), ::testing::Eq(3));
   EXPECT_THAT(obtainedResult[1].size(), ::testing::Eq(7));
}
