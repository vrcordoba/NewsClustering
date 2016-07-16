#ifndef READER_H_
#define READER_H_

#include <vector>
#include <memory>
#include "News.h"

class Reader
{
public:
   virtual ~Reader() {};

   virtual std::vector<std::shared_ptr<News>> getNews() const = 0;
};

#endif
