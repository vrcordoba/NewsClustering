#ifndef THEMATICSIMILARITYCLUSTERINGCRITERION_H_
#define THEMATICSIMILARITYCLUSTERINGCRITERION_H_

#include "ClusteringCriterion.h"

#include <memory>
#include "News.h"
#include "NewsDiscriminator.h"

class NewsCluster;

class ThematicSimilarityClusteringCriterion final : public ClusteringCriterion
{
public:
   ThematicSimilarityClusteringCriterion();
   ~ThematicSimilarityClusteringCriterion();

   bool areBothInTheSameCluster(NewsCluster& clusterA, NewsCluster& clusterB);

private:
   bool areBothInTheSameClusterBothNewspaper(const std::shared_ptr<News>& newsA,
      const std::shared_ptr<News>& newsB) const;
   bool areBothInTheSameClusterBothTwitter(const std::shared_ptr<News>& newsA,
      const std::shared_ptr<News>& newsB) const;
   bool areBothInTheSameClusterNewspaperTwitter(const std::shared_ptr<News>& newspaper,
      const std::shared_ptr<News>& twitter) const;
   bool doTheyHaveTheSameMostMentionedEntity(NewsCluster& clusterA, NewsCluster& clusterB) const;
   bool enoughRatioOfRelevantEntities(const std::shared_ptr<News>& newsA,
      const std::shared_ptr<News>& newsB) const;

   const float ratioToCluster = 0.3f;
   NewsDiscriminator newsDiscriminator;
};

#endif
