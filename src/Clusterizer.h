#ifndef CLUSTERIZER_H_
#define CLUSTERIZER_H_

#include <vector>
#include <memory>
#include "NewsCluster.h"

class ClusteringCriterion;
class NewsReader;

class Clusterizer final
{
public:
   Clusterizer();
   ~Clusterizer();

   void setCriterion(const ClusteringCriterion* clusteringCriterion);
   void setNewsReader(const NewsReader* newsReader);

   void obtainClusters();
   std::vector<NewsCluster> getClusters() const;

private:
   void createClustersFromNews(const std::vector<std::shared_ptr<News>>& newsVector);
   void analyzeNews();

   const ClusteringCriterion* clusteringCriterion;
   const NewsReader* newsReader;
   std::vector<NewsCluster> newsClusters;
};

#endif
