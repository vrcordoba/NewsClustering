
#include "NewsCluster.h"

NewsCluster::NewsCluster() : newsVector()
{
}

NewsCluster::~NewsCluster()
{
}

void NewsCluster::addNews(const std::shared_ptr<News>& news)
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

bool NewsCluster::empty() const
{
   return newsVector.empty();
}

std::size_t NewsCluster::size() const
{
   return newsVector.cend() - newsVector.cbegin();
}

std::set<std::string> NewsCluster::getMentionedEntities() const
{
   std::set<std::string> mentionedEntities;
   for (auto& news : newsVector)
   {
      std::set<std::string> newsMentionedEntities = news->getMentionedEntities();
      mentionedEntities.insert(std::begin(newsMentionedEntities), std::end(newsMentionedEntities));
   }
   return mentionedEntities;
}
