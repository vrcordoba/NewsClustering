#ifndef CLUSTERINGCRITERION_H_
#define CLUSTERINGCRITERION_H_

class NewsCluster;

class ClusteringCriterion
{
public:
   virtual ~ClusteringCriterion() {};

   virtual bool areBothInTheSameCluster(NewsCluster& clusterA, NewsCluster& clusterB) = 0;
};

#endif
