
#include "MostMentionedEntityClusteringCriterion.h"

#include "NewsCluster.h"

MostMentionedEntityClusteringCriterion::MostMentionedEntityClusteringCriterion()
{
}

MostMentionedEntityClusteringCriterion::~MostMentionedEntityClusteringCriterion()
{
}

bool MostMentionedEntityClusteringCriterion::areBothInTheSameCluster(
   NewsCluster& clusterA, NewsCluster& clusterB) const
{
   if (clusterA.empty() or clusterB.empty())
      return false;
   std::string mostMentionedEntityA = (*clusterA.begin())->getMostMentionedEntity();
   std::string mostMentionedEntityB = (*clusterB.begin())->getMostMentionedEntity();
   return (0 == mostMentionedEntityA.compare(mostMentionedEntityB));
}

