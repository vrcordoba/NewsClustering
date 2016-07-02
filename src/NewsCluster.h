#ifndef NEWSCLUSTER_H_
#define NEWSCLUSTER_H_

#include <vector>
#include "News.h"

class NewsCluster final
{
public:
   NewsCluster();
   ~NewsCluster();

   void addNews(News& news);
   void mergeCluster(NewsCluster& otherNewsCluster);

   typedef std::vector<News>::iterator iterator;
   typedef std::vector<News>::const_iterator const_iterator;
   iterator begin();
   const_iterator begin() const;
   iterator end();
   const_iterator end() const;
   bool empty() const;
   std::size_t size() const;

private:
   std::vector<News> newsVector;
};

#endif
