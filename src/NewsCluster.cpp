#include "NewsCluster.h"

NewsCluster::NewsCluster() : newsVector()
{
}

NewsCluster::~NewsCluster()
{
}

void NewsCluster::addNews(News& news)
{
   newsVector.push_back(news);
}

void NewsCluster::mergeCluster(NewsCluster& otherNewsCluster)
{
   newsVector.reserve(newsVector.size() + otherNewsCluster.newsVector.size());
   newsVector.insert(newsVector.end(), otherNewsCluster.newsVector.begin(),
      otherNewsCluster.newsVector.end());
   otherNewsCluster.newsVector.clear();
}

NewsCluster::iterator NewsCluster::begin()
{
   return newsVector.begin();
}

NewsCluster::const_iterator NewsCluster::begin() const
{
   return newsVector.cbegin();
}

NewsCluster::iterator NewsCluster::end()
{
   return newsVector.end();
}

NewsCluster::const_iterator NewsCluster::end() const
{
   return newsVector.cend();
}
