
#include "gmock/gmock.h"

#include <memory>
#include "ThematicSimilarityClusteringCriterion.h"
#include "NewsCluster.h"
#include "NewsMock.h"

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

   EXPECT_TRUE(criterion.areBothInTheSameCluster(firstCluster, secondCluster));
}

TEST(ThematicSimilarityClusteringCriterionTestSuite,
   notInThesameClustersLowRatioOfRelevantEntities)
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

   EXPECT_FALSE(criterion.areBothInTheSameCluster(firstCluster, secondCluster));
}

TEST(ThematicSimilarityClusteringCriterionTestSuite, notInThesameClusters)
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

   EXPECT_FALSE(criterion.areBothInTheSameCluster(firstCluster, secondCluster));
}
