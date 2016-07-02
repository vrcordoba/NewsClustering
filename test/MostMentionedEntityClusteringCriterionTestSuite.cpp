
#include "gmock/gmock.h"

#include "MostMentionedEntityClusteringCriterion.h"
#include "NewsCluster.h"
#include "NewsMock.h"

TEST(MostMentionedEntityClusteringCriterionTestSuite, firstClusterIsEmpty)
{
   MostMentionedEntityClusteringCriterion criterion;
   NewsCluster firstCluster;
   std::shared_ptr<News> news = std::make_shared<NewsMock>();
   NewsCluster secondCluster;
   secondCluster.addNews(news);

   ASSERT_THAT(criterion.areBothInTheSameCluster(firstCluster, secondCluster), ::testing::Eq(false));
}

TEST(MostMentionedEntityClusteringCriterionTestSuite, secondClusterIsEmpty)
{
   MostMentionedEntityClusteringCriterion criterion;
   NewsCluster firstCluster;
   std::shared_ptr<News> news = std::make_shared<NewsMock>();
   firstCluster.addNews(news);
   NewsCluster secondCluster;

   ASSERT_THAT(criterion.areBothInTheSameCluster(firstCluster, secondCluster), ::testing::Eq(false));
}

TEST(MostMentionedEntityClusteringCriterionTestSuite, differentClustersByCriterion)
{
   MostMentionedEntityClusteringCriterion criterion;

   NewsCluster firstCluster;
   NewsMock* news1 = new NewsMock();
   std::shared_ptr<News> firstNews(news1);
   firstCluster.addNews(firstNews);

   NewsCluster secondCluster;
   NewsMock* news2 = new NewsMock();
   std::shared_ptr<News> secondNews(news2);
   secondCluster.addNews(secondNews);

   EXPECT_CALL(*news1, getMostMentionedEntity()).Times(1).WillRepeatedly(::testing::Return("FirstNews"));
   EXPECT_CALL(*news2, getMostMentionedEntity()).Times(1).WillRepeatedly(::testing::Return("SecondNews"));

   ASSERT_THAT(criterion.areBothInTheSameCluster(firstCluster, secondCluster), ::testing::Eq(false));
}

TEST(MostMentionedEntityClusteringCriterionTestSuite, sameClustersByCriterion)
{
   MostMentionedEntityClusteringCriterion criterion;

   NewsCluster firstCluster;
   NewsMock* news1 = new NewsMock();
   std::shared_ptr<News> firstNews(news1);
   firstCluster.addNews(firstNews);

   NewsCluster secondCluster;
   NewsMock* news2 = new NewsMock();
   std::shared_ptr<News> secondNews(news2);
   secondCluster.addNews(secondNews);

   EXPECT_CALL(*news1, getMostMentionedEntity()).Times(1).WillRepeatedly(::testing::Return("SameNews"));
   EXPECT_CALL(*news2, getMostMentionedEntity()).Times(1).WillRepeatedly(::testing::Return("SameNews"));

   ASSERT_THAT(criterion.areBothInTheSameCluster(firstCluster, secondCluster), ::testing::Eq(true));
}
