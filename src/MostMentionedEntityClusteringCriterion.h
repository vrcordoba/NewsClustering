#ifndef MOSTMENTIONEDENTITYCLUSTERINGCRITERION_H_
#define MOSTMENTIONEDENTITYCLUSTERINGCRITERION_H_

#include "ClusteringCriterion.h"

class NewsCluster;

class MostMentionedEntityClusteringCriterion: public ClusteringCriterion
{
public:
   MostMentionedEntityClusteringCriterion();
   ~MostMentionedEntityClusteringCriterion();

   bool areBothInTheSameCluster(NewsCluster& clusterA, NewsCluster& clusterB);
};

#endif
