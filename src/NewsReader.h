#ifndef NEWSREADER_H_
#define NEWSREADER_H_

#include <vector>
#include "NewsCluster.h"

class NewsReader
{
public:
   virtual ~NewsReader() {};

   virtual std::vector<NewsCluster> getNews() = 0;
};

#endif
