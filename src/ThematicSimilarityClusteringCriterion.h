#ifndef THEMATICSIMILARITYCLUSTERINGCRITERION_H_
#define THEMATICSIMILARITYCLUSTERINGCRITERION_H_

#include "ClusteringCriterion.h"

#include <memory>
#include "News.h"

class NewsCluster;

class ThematicSimilarityClusteringCriterion final : public ClusteringCriterion
{
public:
   ThematicSimilarityClusteringCriterion();
   ~ThematicSimilarityClusteringCriterion();

   bool areBothInTheSameCluster(NewsCluster& clusterA, NewsCluster& clusterB) const;

private:
   bool doTheyHaveTheSameMostMentionedEntity(NewsCluster& clusterA, NewsCluster& clusterB) const;
   bool enoughRatioOfRelevantEntities(const std::shared_ptr<News>& newsA,
      const std::shared_ptr<News>& newsB) const;

   const float ratioToCluster = 0.3f;
};

#endif
