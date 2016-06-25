#ifndef NEWSREADER_H_
#define NEWSREADER_H_

#include <vector>
#include "News.h"

class NewsReader
{
public:
   virtual ~NewsReader() {};

   virtual std::vector<News> getNews() = 0;
};

#endif
