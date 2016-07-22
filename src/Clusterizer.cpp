
#include "Clusterizer.h"

#include <cassert>
#include <algorithm>
#include "ClusteringCriterion.h"
#include "Reader.h"

Clusterizer::Clusterizer() : clusteringCriterion(nullptr), newsReader(nullptr),
   tuitsReader(nullptr), newsClusters()
{
}

Clusterizer::~Clusterizer()
{
}

void Clusterizer::setCriterion(ClusteringCriterion* clusteringCriterion)
{
   this->clusteringCriterion = clusteringCriterion;
}

void Clusterizer::setNewsReader(const Reader* newsReader)
{
   this->newsReader = newsReader;
}

void Clusterizer::setTuitsReader(const Reader* tuitsReader)
{
   this->tuitsReader = tuitsReader;
}

void Clusterizer::obtainClusters()
{
   assert(newsReader != nullptr or tuitsReader != nullptr);
   if (newsReader != nullptr)
      createClustersFromNews(newsReader->getNews());
   if (tuitsReader != nullptr)
      createClustersFromNews(tuitsReader->getNews());
   analyzeNews();
}

void Clusterizer::createClustersFromNews(const std::vector<std::shared_ptr<News>>& newsVector)
{
   for (auto& news : newsVector)
   {
      NewsCluster newsCluster;
      newsCluster.addNews(news);
      newsClusters.push_back(newsCluster);
   }
}

void Clusterizer::analyzeNews()
{
   assert(clusteringCriterion != nullptr);
   std::size_t numberOfNewsToAnalyze = newsClusters.size();
   for (std::size_t i = 0; i < numberOfNewsToAnalyze; ++i)
   {
      for (std::size_t j = 0; j < numberOfNewsToAnalyze; ++j)
      {
         if (i != j and clusteringCriterion->areBothInTheSameCluster(newsClusters[i], newsClusters[j]))
         {
            newsClusters[i].mergeCluster(newsClusters[j]);
         }
      }
   }
   newsClusters.erase(std::remove_if(newsClusters.begin(), newsClusters.end(),
      [] (NewsCluster& cluster) {return cluster.empty();}), newsClusters.end());
}

std::vector<NewsCluster> Clusterizer::getClusters() const
{
   return newsClusters;
}

