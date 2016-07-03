#ifndef NEWSREADER_H_
#define NEWSREADER_H_

#include <vector>
#include <memory>
#include "News.h"

class NewsReader
{
public:
   virtual ~NewsReader() {};

   virtual std::vector<std::shared_ptr<News>> getNews() const = 0;
};

#endif
