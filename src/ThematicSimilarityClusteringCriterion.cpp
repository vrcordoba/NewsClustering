
#include "ThematicSimilarityClusteringCriterion.h"
#include "NewsCluster.h"
#include "TwitterNews.h"

ThematicSimilarityClusteringCriterion::ThematicSimilarityClusteringCriterion() :
   newsDiscriminator()
{
}

ThematicSimilarityClusteringCriterion::~ThematicSimilarityClusteringCriterion()
{
}

bool ThematicSimilarityClusteringCriterion::areBothInTheSameCluster(NewsCluster& clusterA, NewsCluster& clusterB)
{
   if (clusterA.empty() or clusterB.empty())
      return false;

   if (doTheyHaveTheSameMostMentionedEntity(clusterA, clusterB))
      return true;

   bool result = false;
   for (auto& newsA : clusterA)
   {
      for (auto& newsB : clusterB)
      {
         NewsDiscriminator::DiscriminatorResult discriminatorResult =
            newsDiscriminator.discriminateType(newsA, newsB);
         if (NewsDiscriminator::bothFromNewspaper == discriminatorResult)
            result = areBothInTheSameClusterBothNewspaper(newsA, newsB);
         else if (NewsDiscriminator::bothFromTwitter == discriminatorResult)
            result = areBothInTheSameClusterBothTwitter(newsA, newsB);
         else if (NewsDiscriminator::firstFromNewspaperSecondFromTwitter == discriminatorResult)
            result = areBothInTheSameClusterNewspaperTwitter(newsA, newsB);
         else
            result = areBothInTheSameClusterNewspaperTwitter(newsB, newsA);

         if (result)
            return true;
      }
   }
   return result;
}

bool ThematicSimilarityClusteringCriterion::areBothInTheSameClusterBothNewspaper(
   const std::shared_ptr<News>& newsA, const std::shared_ptr<News>& newsB) const
{
   if (newsA->isContainedInHeadline(newsB->getMostMentionedEntity()) or
      newsB->isContainedInHeadline(newsA->getMostMentionedEntity()))
      return true;

   if (enoughRatioOfRelevantEntities(newsA, newsB) or
      enoughRatioOfRelevantEntities(newsB, newsA))
      return true;
   return false;
}

bool ThematicSimilarityClusteringCriterion::areBothInTheSameClusterBothTwitter(
   const std::shared_ptr<News>& newsA, const std::shared_ptr<News>& newsB) const
{
   return static_cast<TwitterNews*>(newsA.get())->shareMentionedEntities(
      static_cast<TwitterNews*>(newsB.get()));
}

bool ThematicSimilarityClusteringCriterion::areBothInTheSameClusterNewspaperTwitter(
   const std::shared_ptr<News>& newsA, const std::shared_ptr<News>& newsB) const
{
   return false;
}

bool ThematicSimilarityClusteringCriterion::doTheyHaveTheSameMostMentionedEntity(
   NewsCluster& clusterA, NewsCluster& clusterB) const
{
   for (auto& newsA : clusterA)
   {
      for (auto& newsB : clusterB)
      {
         if (newsA->getMostMentionedEntity() == newsB->getMostMentionedEntity())
            return true;
      }
   }
   return false;
}

bool ThematicSimilarityClusteringCriterion::enoughRatioOfRelevantEntities(
   const std::shared_ptr<News>& newsA, const std::shared_ptr<News>& newsB) const
{
   std::set<std::string> relevantEntities = newsA->getRelevantEntities();
   if (relevantEntities.empty())
      return false;

   float ratio = 0.0f;
   for (auto& relevantEntity : relevantEntities)
   {
      if (newsB->isContainedInRelevantEntities(relevantEntity))
         ratio += 1.0f;
   }
   return (ratio / static_cast<float>(relevantEntities.size())) > ratioToCluster;
}

