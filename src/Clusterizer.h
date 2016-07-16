#ifndef CLUSTERIZER_H_
#define CLUSTERIZER_H_

#include <vector>
#include <memory>
#include "NewsCluster.h"

class ClusteringCriterion;
class Reader;

class Clusterizer final
{
public:
   Clusterizer();
   ~Clusterizer();

   void setCriterion(ClusteringCriterion* clusteringCriterion);
   void setNewsReader(const Reader* newsReader);
   void setTuitsReader(const Reader* tuitsReader);

   void obtainClusters();
   std::vector<NewsCluster> getClusters() const;

private:
   void createClustersFromNews(const std::vector<std::shared_ptr<News>>& newsVector);
   void analyzeNews();

   ClusteringCriterion* clusteringCriterion;
   const Reader* newsReader;
   const Reader* tuitsReader;
   std::vector<NewsCluster> newsClusters;
};

#endif
