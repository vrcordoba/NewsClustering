
#include "gmock/gmock.h"

#include <fstream>
#include <memory>
#include <cstdio>
#include "PlainTextClusterWriter.h"
#include "InvalidDirectoryException.h"
#include "NewsMock.h"

class PlainTextClusterWriterTestSuite : public ::testing::Test
{
protected:
   PlainTextClusterWriterTestSuite() : destinationFile("/tmp/ClusterWriterTest.txt") {}

   virtual void TearDown()
   {
      std::remove(destinationFile.c_str());
   }

   void verifyResult(std::ifstream& file, const std::vector<std::string>&
      expectedResult)
   {
      std::string obtainedLine;
      for (std::size_t i = 0; i < expectedResult.size(); ++i)
      {
         std::getline(file, obtainedLine);
         EXPECT_THAT(obtainedLine, ::testing::Eq(expectedResult[i]));
      }
      std::getline(file, obtainedLine);
      EXPECT_TRUE(file.eof());
   }

   std::string destinationFile;
};

TEST_F(PlainTextClusterWriterTestSuite, nonValidDirectory)
{
   ASSERT_THROW(PlainTextClusterWriter clusterWriter("/wrong_directory/ClusterWriterTest.txt"), InvalidDirectoryException);
}

TEST_F(PlainTextClusterWriterTestSuite, noClustersToPrint)
{
   std::vector<NewsCluster> newsClusters;
   PlainTextClusterWriter clusterWriter(destinationFile);

   clusterWriter.write(newsClusters);

   std::ifstream file(destinationFile);
   std::string obtainedResult;
   std::getline(file, obtainedResult);
   EXPECT_TRUE(obtainedResult.empty());
}

TEST_F(PlainTextClusterWriterTestSuite, onlyOneClusterSeveralNews)
{
   NewsMock* newsA = new NewsMock();
   NewsMock* newsB = new NewsMock();
   NewsMock* newsC = new NewsMock();
   std::shared_ptr<News> ptrNewsA(newsA);
   std::shared_ptr<News> ptrNewsB(newsB);
   std::shared_ptr<News> ptrNewsC(newsC);
   NewsCluster newsCluster;
   newsCluster.addNews(ptrNewsA);
   newsCluster.addNews(ptrNewsB);
   newsCluster.addNews(ptrNewsC);
   std::vector<NewsCluster> newsClusters{newsCluster};
   PlainTextClusterWriter clusterWriter(destinationFile);

   EXPECT_CALL(*newsA, getHeadline()).Times(1).WillOnce(::testing::Return("This are the first news"));
   EXPECT_CALL(*newsB, getHeadline()).Times(1).WillOnce(::testing::Return("This are the second news"));
   EXPECT_CALL(*newsC, getHeadline()).Times(1).WillOnce(::testing::Return("This are the third news"));

   clusterWriter.write(newsClusters);

   std::ifstream file(destinationFile);
   std::vector<std::string> expectedResult{
      "=== Cluster 001 ===",
      "===================",
      "",
      "This are the first news",
      "This are the second news",
      "This are the third news",
      ""};
   verifyResult(file, expectedResult);
}

TEST_F(PlainTextClusterWriterTestSuite, severalClusterSeveralNewsInEachCluster)
{
   NewsMock* newsA = new NewsMock();
   NewsMock* newsB = new NewsMock();
   NewsMock* newsC = new NewsMock();
   NewsMock* newsD = new NewsMock();
   NewsMock* newsE = new NewsMock();
   NewsMock* newsF = new NewsMock();
   std::shared_ptr<News> ptrNewsA(newsA);
   std::shared_ptr<News> ptrNewsB(newsB);
   std::shared_ptr<News> ptrNewsC(newsC);
   std::shared_ptr<News> ptrNewsD(newsD);
   std::shared_ptr<News> ptrNewsE(newsE);
   std::shared_ptr<News> ptrNewsF(newsF);
   NewsCluster firstNewsCluster, secondNewsCluster, thirdNewsCluster;
   firstNewsCluster.addNews(ptrNewsA);
   firstNewsCluster.addNews(ptrNewsB);
   secondNewsCluster.addNews(ptrNewsC);
   thirdNewsCluster.addNews(ptrNewsD);
   thirdNewsCluster.addNews(ptrNewsE);
   thirdNewsCluster.addNews(ptrNewsF);
   std::vector<NewsCluster> newsClusters{firstNewsCluster, secondNewsCluster,
      thirdNewsCluster};
   PlainTextClusterWriter clusterWriter(destinationFile);

   EXPECT_CALL(*newsA, getHeadline()).Times(1).WillOnce(::testing::Return("This are the first news"));
   EXPECT_CALL(*newsB, getHeadline()).Times(1).WillOnce(::testing::Return("This are the second news"));
   EXPECT_CALL(*newsC, getHeadline()).Times(1).WillOnce(::testing::Return("This are the third news"));
   EXPECT_CALL(*newsD, getHeadline()).Times(1).WillOnce(::testing::Return("This are the fourth news"));
   EXPECT_CALL(*newsE, getHeadline()).Times(1).WillOnce(::testing::Return("This are the fifth news"));
   EXPECT_CALL(*newsF, getHeadline()).Times(1).WillOnce(::testing::Return("This are the sixth news"));

   clusterWriter.write(newsClusters);

   std::ifstream file(destinationFile);
   std::vector<std::string> expectedResult{
      "=== Cluster 001 ===",
      "===================",
      "",
      "This are the first news",
      "This are the second news",
      "",
      "=== Cluster 002 ===",
      "===================",
      "",
      "This are the third news",
      "",
      "=== Cluster 003 ===",
      "===================",
      "",
      "This are the fourth news",
      "This are the fifth news",
      "This are the sixth news",
      ""};
   verifyResult(file, expectedResult);
}
