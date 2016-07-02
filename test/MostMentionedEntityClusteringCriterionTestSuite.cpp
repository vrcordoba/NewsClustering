
#include "gmock/gmock.h"

#include "MostMentionedEntityClusteringCriterion.h"
#include "NewsCluster.h"
#include "ExclusionListMock.h"

TEST(MostMentionedEntityClusteringCriterionTestSuite, firstClusterIsEmpty)
{
   MostMentionedEntityClusteringCriterion criterion;
   NewsCluster firstCluster;
   ExclusionListMock exclusionList;
   News news(exclusionList);
   NewsCluster secondCluster;
   secondCluster.addNews(news);

   ASSERT_THAT(criterion.areBothInTheSameCluster(firstCluster, secondCluster), ::testing::Eq(false));
}

TEST(MostMentionedEntityClusteringCriterionTestSuite, secondClusterIsEmpty)
{
   MostMentionedEntityClusteringCriterion criterion;
   ExclusionListMock exclusionList;
   News news(exclusionList);
   NewsCluster firstCluster;
   firstCluster.addNews(news);
   NewsCluster secondCluster;

   ASSERT_THAT(criterion.areBothInTheSameCluster(firstCluster, secondCluster), ::testing::Eq(false));
}

TEST(MostMentionedEntityClusteringCriterionTestSuite, differentClustersByCriterion)
{
   MostMentionedEntityClusteringCriterion criterion;
   ExclusionListMock exclusionList;
   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(8).WillRepeatedly(::testing::Return(false));

   NewsCluster firstCluster;
   News news1(exclusionList);
   std::vector<std::string> newsText1{"Hello", "Hello", "Goodbye", "Sayonara"};
   news1.setMentionedEntities(newsText1);
   firstCluster.addNews(news1);

   NewsCluster secondCluster;
   News news2(exclusionList);
   std::vector<std::string> newsText2{"Hello", "Sayonara", "Goodbye", "Sayonara"};
   news2.setMentionedEntities(newsText2);
   secondCluster.addNews(news2);

   ASSERT_THAT(criterion.areBothInTheSameCluster(firstCluster, secondCluster), ::testing::Eq(false));
}

TEST(MostMentionedEntityClusteringCriterionTestSuite, sameClustersByCriterion)
{
   MostMentionedEntityClusteringCriterion criterion;
   ExclusionListMock exclusionList;
   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(8).WillRepeatedly(::testing::Return(false));

   NewsCluster firstCluster;
   News news1(exclusionList);
   std::vector<std::string> newsText1{"Hello", "Sayonara", "Goodbye", "Sayonara"};
   news1.setMentionedEntities(newsText1);
   firstCluster.addNews(news1);

   NewsCluster secondCluster;
   News news2(exclusionList);
   std::vector<std::string> newsText2{"Hello", "Goodbye", "Sayonara", "Sayonara"};
   news2.setMentionedEntities(newsText2);
   secondCluster.addNews(news2);

   ASSERT_THAT(criterion.areBothInTheSameCluster(firstCluster, secondCluster), ::testing::Eq(true));
}
