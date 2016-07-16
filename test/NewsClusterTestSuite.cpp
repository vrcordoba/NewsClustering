
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

TEST(NewsClusterTestSuite, getMentionedEntities)
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

   std::set<std::string> mentionedEntitiesA{"One", "Two", "Three"};
   std::set<std::string> mentionedEntitiesB{"Four", "Three", "Five", "Six"};
   std::set<std::string> mentionedEntitiesC{"Seven", "Eight", "One"};
   EXPECT_CALL(*newsA, getMentionedEntities()).Times(1).WillOnce(::testing::Return(mentionedEntitiesA));
   EXPECT_CALL(*newsB, getMentionedEntities()).Times(1).WillOnce(::testing::Return(mentionedEntitiesB));
   EXPECT_CALL(*newsC, getMentionedEntities()).Times(1).WillOnce(::testing::Return(mentionedEntitiesC));

   std::set<std::string> expectedResult{"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight"};
   EXPECT_THAT(newsCluster.getMentionedEntities(), ::testing::Eq(expectedResult));
}
