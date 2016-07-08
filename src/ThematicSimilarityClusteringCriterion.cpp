
#include "ThematicSimilarityClusteringCriterion.h"
#include "NewsCluster.h"

ThematicSimilarityClusteringCriterion::ThematicSimilarityClusteringCriterion()
{

}

ThematicSimilarityClusteringCriterion::~ThematicSimilarityClusteringCriterion()
{
}

bool ThematicSimilarityClusteringCriterion::areBothInTheSameCluster(NewsCluster& clusterA, NewsCluster& clusterB) const
{
   if (clusterA.empty() or clusterB.empty())
      return false;

   if (doTheyHaveTheSameMostMentionedEntity(clusterA, clusterB))
      return true;

   for (auto& newsA : clusterA)
   {
      for (auto& newsB : clusterB)
      {
         if (newsA->isContainedInHeadline(newsB->getMostMentionedEntity()) or
            newsB->isContainedInHeadline(newsA->getMostMentionedEntity()))
            return true;

         if (enoughRatioOfRelevantEntities(newsA, newsB) or
            enoughRatioOfRelevantEntities(newsB, newsA))
            return true;
      }
   }
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

