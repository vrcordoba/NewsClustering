
#include "gmock/gmock.h"

#include <memory>
#include "ThematicSimilarityClusteringCriterion.h"
#include "NewsCluster.h"
#include "NewsMock.h"
#include "TwitterNews.h"
#include "NewspaperNews.h"
#include "ExclusionListMock.h"

TEST(ThematicSimilarityClusteringCriterionTestSuite, firstClusterIsEmpty)
{
   ThematicSimilarityClusteringCriterion criterion;
   NewsCluster firstCluster;
   std::shared_ptr<News> news = std::make_shared<NewsMock>();
   NewsCluster secondCluster;
   secondCluster.addNews(news);

   EXPECT_FALSE(criterion.areBothInTheSameCluster(firstCluster, secondCluster));
}

TEST(ThematicSimilarityClusteringCriterionTestSuite, secondClusterIsEmpty)
{
   ThematicSimilarityClusteringCriterion criterion;
   NewsCluster firstCluster;
   std::shared_ptr<News> news = std::make_shared<NewsMock>();
   firstCluster.addNews(news);
   NewsCluster secondCluster;

   EXPECT_FALSE(criterion.areBothInTheSameCluster(firstCluster, secondCluster));
}

TEST(ThematicSimilarityClusteringCriterionTestSuite,
   sameClustersBySameMostMentionedEntity)
{
   ThematicSimilarityClusteringCriterion criterion;

   NewsCluster firstCluster;
   NewsMock* news1 = new NewsMock();
   std::shared_ptr<News> ptrNews1(news1);
   firstCluster.addNews(ptrNews1);

   NewsCluster secondCluster;
   NewsMock* news2 = new NewsMock();
   std::shared_ptr<News> ptrNews2(news2);
   secondCluster.addNews(ptrNews2);

   EXPECT_CALL(*news1, getMostMentionedEntity()).Times(1).WillRepeatedly(::testing::Return("SameNews"));
   EXPECT_CALL(*news2, getMostMentionedEntity()).Times(1).WillRepeatedly(::testing::Return("SameNews"));

   EXPECT_TRUE(criterion.areBothInTheSameCluster(firstCluster, secondCluster));
}

TEST(ThematicSimilarityClusteringCriterionTestSuite,
   sameClustersMostMentionedEntityOfFirstInHeadlineOfSecond)
{
   ThematicSimilarityClusteringCriterion criterion;

   NewsCluster firstCluster;
   NewsMock* newsA = new NewsMock();
   std::shared_ptr<News> ptrNewsA(newsA);
   NewsMock* newsB = new NewsMock();
   std::shared_ptr<News> ptrNewsB(newsB);
   firstCluster.addNews(ptrNewsA);
   firstCluster.addNews(ptrNewsB);

   NewsCluster secondCluster;
   NewsMock* newsC = new NewsMock();
   std::shared_ptr<News> ptrNewsC(newsC);
   NewsMock* newsD = new NewsMock();
   std::shared_ptr<News> ptrNewsD(newsD);
   secondCluster.addNews(ptrNewsC);
   secondCluster.addNews(ptrNewsD);

   EXPECT_CALL(*newsA, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsA"));
   EXPECT_CALL(*newsB, getMostMentionedEntity()).Times(3).WillRepeatedly(::testing::Return("NewsB"));
   EXPECT_CALL(*newsC, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsC"));
   EXPECT_CALL(*newsD, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsD"));

   std::set<std::string> emptyRelevantEntities;
   EXPECT_CALL(*newsA, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(emptyRelevantEntities));
   EXPECT_CALL(*newsB, getRelevantEntities()).Times(1).WillRepeatedly(::testing::Return(emptyRelevantEntities));
   EXPECT_CALL(*newsC, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(emptyRelevantEntities));
   EXPECT_CALL(*newsD, getRelevantEntities()).Times(1).WillRepeatedly(::testing::Return(emptyRelevantEntities));

   EXPECT_CALL(*newsA, isContainedInHeadline("NewsC")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsC, isContainedInHeadline("NewsA")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsA, isContainedInHeadline("NewsD")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsD, isContainedInHeadline("NewsA")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsB, isContainedInHeadline("NewsC")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsC, isContainedInHeadline("NewsB")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsB, isContainedInHeadline("NewsD")).Times(1).WillOnce(::testing::Return(true));
   EXPECT_CALL(*newsD, isContainedInHeadline("NewsB")).Times(0);

   EXPECT_CALL(*newsA, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsB, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsC, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsD, accept(::testing::_)).Times(2);

   EXPECT_TRUE(criterion.areBothInTheSameCluster(firstCluster, secondCluster));
}

TEST(ThematicSimilarityClusteringCriterionTestSuite,
   sameClustersMostMentionedEntityOfSecondInHeadlineOfFirst)
{
   ThematicSimilarityClusteringCriterion criterion;

   NewsCluster firstCluster;
   NewsMock* newsA = new NewsMock();
   std::shared_ptr<News> ptrNewsA(newsA);
   NewsMock* newsB = new NewsMock();
   std::shared_ptr<News> ptrNewsB(newsB);
   firstCluster.addNews(ptrNewsA);
   firstCluster.addNews(ptrNewsB);

   NewsCluster secondCluster;
   NewsMock* newsC = new NewsMock();
   std::shared_ptr<News> ptrNewsC(newsC);
   NewsMock* newsD = new NewsMock();
   std::shared_ptr<News> ptrNewsD(newsD);
   secondCluster.addNews(ptrNewsC);
   secondCluster.addNews(ptrNewsD);

   EXPECT_CALL(*newsA, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsA"));
   EXPECT_CALL(*newsB, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsB"));
   EXPECT_CALL(*newsC, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsC"));
   EXPECT_CALL(*newsD, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsD"));

   std::set<std::string> emptyRelevantEntities;
   EXPECT_CALL(*newsA, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(emptyRelevantEntities));
   EXPECT_CALL(*newsB, getRelevantEntities()).Times(1).WillRepeatedly(::testing::Return(emptyRelevantEntities));
   EXPECT_CALL(*newsC, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(emptyRelevantEntities));
   EXPECT_CALL(*newsD, getRelevantEntities()).Times(1).WillRepeatedly(::testing::Return(emptyRelevantEntities));

   EXPECT_CALL(*newsA, isContainedInHeadline("NewsC")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsC, isContainedInHeadline("NewsA")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsA, isContainedInHeadline("NewsD")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsD, isContainedInHeadline("NewsA")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsB, isContainedInHeadline("NewsC")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsC, isContainedInHeadline("NewsB")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsB, isContainedInHeadline("NewsD")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsD, isContainedInHeadline("NewsB")).Times(1).WillOnce(::testing::Return(true));

   EXPECT_CALL(*newsA, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsB, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsC, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsD, accept(::testing::_)).Times(2);

   EXPECT_TRUE(criterion.areBothInTheSameCluster(firstCluster, secondCluster));
}

TEST(ThematicSimilarityClusteringCriterionTestSuite,
   sameClustersHighRatioOfRelevantEntitiesOfFirstInSecond)
{
   ThematicSimilarityClusteringCriterion criterion;

   NewsCluster firstCluster;
   NewsMock* newsA = new NewsMock();
   std::shared_ptr<News> ptrNewsA(newsA);
   NewsMock* newsB = new NewsMock();
   std::shared_ptr<News> ptrNewsB(newsB);
   firstCluster.addNews(ptrNewsA);
   firstCluster.addNews(ptrNewsB);

   NewsCluster secondCluster;
   NewsMock* newsC = new NewsMock();
   std::shared_ptr<News> ptrNewsC(newsC);
   NewsMock* newsD = new NewsMock();
   std::shared_ptr<News> ptrNewsD(newsD);
   secondCluster.addNews(ptrNewsC);
   secondCluster.addNews(ptrNewsD);

   EXPECT_CALL(*newsA, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsA"));
   EXPECT_CALL(*newsB, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsB"));
   EXPECT_CALL(*newsC, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsC"));
   EXPECT_CALL(*newsD, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsD"));

   std::set<std::string> someRelevantEntities{u8"One", u8"Two", u8"Three"};
   EXPECT_CALL(*newsA, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(someRelevantEntities));
   EXPECT_CALL(*newsB, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(someRelevantEntities));
   EXPECT_CALL(*newsC, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(someRelevantEntities));
   EXPECT_CALL(*newsD, getRelevantEntities()).Times(1).WillRepeatedly(::testing::Return(someRelevantEntities));

   EXPECT_CALL(*newsA, isContainedInHeadline("NewsC")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsC, isContainedInHeadline("NewsA")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsA, isContainedInHeadline("NewsD")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsD, isContainedInHeadline("NewsA")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsB, isContainedInHeadline("NewsC")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsC, isContainedInHeadline("NewsB")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsB, isContainedInHeadline("NewsD")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsD, isContainedInHeadline("NewsB")).Times(1).WillOnce(::testing::Return(false));

   EXPECT_CALL(*newsC, isContainedInRelevantEntities(::testing::_)).Times(6).WillRepeatedly(::testing::Return(false));
   EXPECT_CALL(*newsA, isContainedInRelevantEntities(::testing::_)).Times(6).WillRepeatedly(::testing::Return(false));
   EXPECT_CALL(*newsB, isContainedInRelevantEntities(::testing::_)).Times(3).WillRepeatedly(::testing::Return(false));
   EXPECT_CALL(*newsD, isContainedInRelevantEntities(::testing::_)).Times(6)
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true))
      .WillRepeatedly(::testing::Return(false));

   EXPECT_CALL(*newsA, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsB, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsC, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsD, accept(::testing::_)).Times(2);

   EXPECT_TRUE(criterion.areBothInTheSameCluster(firstCluster, secondCluster));
}

TEST(ThematicSimilarityClusteringCriterionTestSuite,
   sameClustersHighRatioOfRelevantEntitiesOfSecondInFirst)
{
   ThematicSimilarityClusteringCriterion criterion;

   NewsCluster firstCluster;
   NewsMock* newsA = new NewsMock();
   std::shared_ptr<News> ptrNewsA(newsA);
   NewsMock* newsB = new NewsMock();
   std::shared_ptr<News> ptrNewsB(newsB);
   firstCluster.addNews(ptrNewsA);
   firstCluster.addNews(ptrNewsB);

   NewsCluster secondCluster;
   NewsMock* newsC = new NewsMock();
   std::shared_ptr<News> ptrNewsC(newsC);
   NewsMock* newsD = new NewsMock();
   std::shared_ptr<News> ptrNewsD(newsD);
   secondCluster.addNews(ptrNewsC);
   secondCluster.addNews(ptrNewsD);

   EXPECT_CALL(*newsA, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsA"));
   EXPECT_CALL(*newsB, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsB"));
   EXPECT_CALL(*newsC, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsC"));
   EXPECT_CALL(*newsD, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsD"));

   std::set<std::string> someRelevantEntities{u8"One", u8"Two", u8"Three"};
   EXPECT_CALL(*newsA, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(someRelevantEntities));
   EXPECT_CALL(*newsB, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(someRelevantEntities));
   EXPECT_CALL(*newsC, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(someRelevantEntities));
   EXPECT_CALL(*newsD, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(someRelevantEntities));

   EXPECT_CALL(*newsA, isContainedInHeadline("NewsC")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsC, isContainedInHeadline("NewsA")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsA, isContainedInHeadline("NewsD")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsD, isContainedInHeadline("NewsA")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsB, isContainedInHeadline("NewsC")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsC, isContainedInHeadline("NewsB")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsB, isContainedInHeadline("NewsD")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsD, isContainedInHeadline("NewsB")).Times(1).WillOnce(::testing::Return(false));

   EXPECT_CALL(*newsC, isContainedInRelevantEntities(::testing::_)).Times(6).WillRepeatedly(::testing::Return(false));
   EXPECT_CALL(*newsA, isContainedInRelevantEntities(::testing::_)).Times(6).WillRepeatedly(::testing::Return(false));
   EXPECT_CALL(*newsB, isContainedInRelevantEntities(::testing::_)).Times(6)
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true))
      .WillRepeatedly(::testing::Return(false));
   EXPECT_CALL(*newsD, isContainedInRelevantEntities(::testing::_)).Times(6).WillRepeatedly(::testing::Return(false));

   EXPECT_CALL(*newsA, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsB, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsC, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsD, accept(::testing::_)).Times(2);

   EXPECT_TRUE(criterion.areBothInTheSameCluster(firstCluster, secondCluster));
}

TEST(ThematicSimilarityClusteringCriterionTestSuite,
   notInTheSameClustersLowRatioOfRelevantEntities)
{
   ThematicSimilarityClusteringCriterion criterion;

   NewsCluster firstCluster;
   NewsMock* newsA = new NewsMock();
   std::shared_ptr<News> ptrNewsA(newsA);
   NewsMock* newsB = new NewsMock();
   std::shared_ptr<News> ptrNewsB(newsB);
   firstCluster.addNews(ptrNewsA);
   firstCluster.addNews(ptrNewsB);

   NewsCluster secondCluster;
   NewsMock* newsC = new NewsMock();
   std::shared_ptr<News> ptrNewsC(newsC);
   NewsMock* newsD = new NewsMock();
   std::shared_ptr<News> ptrNewsD(newsD);
   secondCluster.addNews(ptrNewsC);
   secondCluster.addNews(ptrNewsD);

   EXPECT_CALL(*newsA, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsA"));
   EXPECT_CALL(*newsB, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsB"));
   EXPECT_CALL(*newsC, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsC"));
   EXPECT_CALL(*newsD, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsD"));

   std::set<std::string> someRelevantEntities{u8"One", u8"Two", u8"Three", u8"Four"};
   EXPECT_CALL(*newsA, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(someRelevantEntities));
   EXPECT_CALL(*newsB, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(someRelevantEntities));
   EXPECT_CALL(*newsC, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(someRelevantEntities));
   EXPECT_CALL(*newsD, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(someRelevantEntities));

   EXPECT_CALL(*newsA, isContainedInHeadline("NewsC")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsC, isContainedInHeadline("NewsA")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsA, isContainedInHeadline("NewsD")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsD, isContainedInHeadline("NewsA")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsB, isContainedInHeadline("NewsC")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsC, isContainedInHeadline("NewsB")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsB, isContainedInHeadline("NewsD")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsD, isContainedInHeadline("NewsB")).Times(1).WillOnce(::testing::Return(false));

   EXPECT_CALL(*newsC, isContainedInRelevantEntities(::testing::_)).Times(8).WillRepeatedly(::testing::Return(false));
   EXPECT_CALL(*newsA, isContainedInRelevantEntities(::testing::_)).Times(8).WillRepeatedly(::testing::Return(false));
   EXPECT_CALL(*newsB, isContainedInRelevantEntities(::testing::_)).Times(8).WillRepeatedly(::testing::Return(false));
   EXPECT_CALL(*newsD, isContainedInRelevantEntities(::testing::_)).Times(8)
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(false))
      .WillOnce(::testing::Return(true))
      .WillRepeatedly(::testing::Return(false));

   EXPECT_CALL(*newsA, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsB, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsC, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsD, accept(::testing::_)).Times(2);

   EXPECT_FALSE(criterion.areBothInTheSameCluster(firstCluster, secondCluster));
}

TEST(ThematicSimilarityClusteringCriterionTestSuite, notInTheSameClusters)
{
   ThematicSimilarityClusteringCriterion criterion;

   NewsCluster firstCluster;
   NewsMock* newsA = new NewsMock();
   std::shared_ptr<News> ptrNewsA(newsA);
   NewsMock* newsB = new NewsMock();
   std::shared_ptr<News> ptrNewsB(newsB);
   firstCluster.addNews(ptrNewsA);
   firstCluster.addNews(ptrNewsB);

   NewsCluster secondCluster;
   NewsMock* newsC = new NewsMock();
   std::shared_ptr<News> ptrNewsC(newsC);
   NewsMock* newsD = new NewsMock();
   std::shared_ptr<News> ptrNewsD(newsD);
   secondCluster.addNews(ptrNewsC);
   secondCluster.addNews(ptrNewsD);

   EXPECT_CALL(*newsA, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsA"));
   EXPECT_CALL(*newsB, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsB"));
   EXPECT_CALL(*newsC, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsC"));
   EXPECT_CALL(*newsD, getMostMentionedEntity()).Times(4).WillRepeatedly(::testing::Return("NewsD"));

   std::set<std::string> someRelevantEntities{u8"One", u8"Two", u8"Three"};
   EXPECT_CALL(*newsA, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(someRelevantEntities));
   EXPECT_CALL(*newsB, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(someRelevantEntities));
   EXPECT_CALL(*newsC, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(someRelevantEntities));
   EXPECT_CALL(*newsD, getRelevantEntities()).Times(2).WillRepeatedly(::testing::Return(someRelevantEntities));

   EXPECT_CALL(*newsA, isContainedInHeadline("NewsC")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsC, isContainedInHeadline("NewsA")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsA, isContainedInHeadline("NewsD")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsD, isContainedInHeadline("NewsA")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsB, isContainedInHeadline("NewsC")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsC, isContainedInHeadline("NewsB")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsB, isContainedInHeadline("NewsD")).Times(1).WillOnce(::testing::Return(false));
   EXPECT_CALL(*newsD, isContainedInHeadline("NewsB")).Times(1).WillOnce(::testing::Return(false));

   EXPECT_CALL(*newsC, isContainedInRelevantEntities(::testing::_)).Times(6).WillRepeatedly(::testing::Return(false));
   EXPECT_CALL(*newsA, isContainedInRelevantEntities(::testing::_)).Times(6).WillRepeatedly(::testing::Return(false));
   EXPECT_CALL(*newsB, isContainedInRelevantEntities(::testing::_)).Times(6).WillRepeatedly(::testing::Return(false));
   EXPECT_CALL(*newsD, isContainedInRelevantEntities(::testing::_)).Times(6).WillRepeatedly(::testing::Return(false));

   EXPECT_CALL(*newsA, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsB, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsC, accept(::testing::_)).Times(2);
   EXPECT_CALL(*newsD, accept(::testing::_)).Times(2);

   EXPECT_FALSE(criterion.areBothInTheSameCluster(firstCluster, secondCluster));
}

TEST(ThematicSimilarityClusteringCriterionTestSuite, bothTwitterNewsNotInTheSameClusters)
{
   ExclusionListMock exclusionList;
   TwitterNews* news1 = new TwitterNews(exclusionList);
   std::vector<std::string> newsText1{"One", "Two", "Three", "Four", "Five"};
   std::shared_ptr<News> newsPtr1(news1);
   TwitterNews* news2 = new TwitterNews(exclusionList);
   std::vector<std::string> newsText2{"Six", "Seven", "Eight", "Nine", "Ten"};
   std::shared_ptr<News> newsPtr2(news2);
   NewsCluster firstCluster;
   firstCluster.addNews(newsPtr1);
   NewsCluster secondCluster;
   secondCluster.addNews(newsPtr2);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(10)
      .WillRepeatedly(::testing::Return(false));

   newsPtr1->setMentionedEntities(newsText1);
   newsPtr2->setMentionedEntities(newsText2);

   ThematicSimilarityClusteringCriterion criterion;
   EXPECT_FALSE(criterion.areBothInTheSameCluster(firstCluster, secondCluster));
}

TEST(ThematicSimilarityClusteringCriterionTestSuite, bothTwitterNewsInTheSameClusters)
{
   ExclusionListMock exclusionList;
   TwitterNews* news1 = new TwitterNews(exclusionList);
   std::vector<std::string> newsText1{"One", "Two", "Three", "Four", "Five"};
   std::shared_ptr<News> newsPtr1(news1);
   TwitterNews* news2 = new TwitterNews(exclusionList);
   std::vector<std::string> newsText2{"Six", "Seven", "Eight", "Two", "Ten"};
   std::shared_ptr<News> newsPtr2(news2);
   NewsCluster firstCluster;
   firstCluster.addNews(newsPtr1);
   NewsCluster secondCluster;
   secondCluster.addNews(newsPtr2);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(10)
      .WillRepeatedly(::testing::Return(false));

   newsPtr1->setMentionedEntities(newsText1);
   newsPtr2->setMentionedEntities(newsText2);

   ThematicSimilarityClusteringCriterion criterion;
   EXPECT_TRUE(criterion.areBothInTheSameCluster(firstCluster, secondCluster));
}

TEST(ThematicSimilarityClusteringCriterionTestSuite, newspaperTwitterNotInTheSameClusters)
{
   ExclusionListMock exclusionList;
   TwitterNews* news1 = new TwitterNews(exclusionList);
   std::string newsText1 = "One Two Three Four Five";
   std::shared_ptr<News> newsPtr1(news1);
   NewspaperNews* news2 = new NewspaperNews(exclusionList);
   std::vector<std::string> newsText2{"Six", "Seven", "Eight", "Nine", "Ten"};
   std::shared_ptr<News> newsPtr2(news2);
   NewsCluster firstCluster;
   firstCluster.addNews(newsPtr1);
   NewsCluster secondCluster;
   secondCluster.addNews(newsPtr2);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(5)
      .WillRepeatedly(::testing::Return(false));

   newsPtr1->setHeadline(newsText1);
   newsPtr2->setMentionedEntities(newsText2);

   ThematicSimilarityClusteringCriterion criterion;
   EXPECT_FALSE(criterion.areBothInTheSameCluster(firstCluster, secondCluster));
}

TEST(ThematicSimilarityClusteringCriterionTestSuite, newspaperTwitterInTheSameClusters)
{
   ExclusionListMock exclusionList;
   NewspaperNews* news1 = new NewspaperNews(exclusionList);
   std::vector<std::string> newsText1{"Six", "Seven", "Eight", "Nine", "Ten", "Ten"};
   TwitterNews* news2 = new TwitterNews(exclusionList);
   std::string newsText2 = "One Two Three Four Ten";
   std::shared_ptr<News> newsPtr1(news1);
   std::shared_ptr<News> newsPtr2(news2);
   NewsCluster firstCluster;
   firstCluster.addNews(newsPtr1);
   NewsCluster secondCluster;
   secondCluster.addNews(newsPtr2);

   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(6)
      .WillRepeatedly(::testing::Return(false));

   newsPtr1->setMentionedEntities(newsText1);
   newsPtr2->setHeadline(newsText2);

   ThematicSimilarityClusteringCriterion criterion;
   EXPECT_TRUE(criterion.areBothInTheSameCluster(firstCluster, secondCluster));
}
