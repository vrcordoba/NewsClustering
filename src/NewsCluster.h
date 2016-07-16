#ifndef NEWSCLUSTER_H_
#define NEWSCLUSTER_H_

#include <vector>
#include <memory>
#include "News.h"

class NewsCluster final
{
public:
   NewsCluster();
   ~NewsCluster();

   void addNews(const std::shared_ptr<News>& news);
   void mergeCluster(NewsCluster& otherNewsCluster);

   typedef std::vector<std::shared_ptr<News>>::iterator iterator;
   typedef std::vector<std::shared_ptr<News>>::const_iterator const_iterator;
   iterator begin();
   const_iterator begin() const;
   iterator end();
   const_iterator end() const;
   bool empty() const;
   std::size_t size() const;

   std::set<std::string> getMentionedEntities() const;

private:
   std::vector<std::shared_ptr<News>> newsVector;
};

#endif
