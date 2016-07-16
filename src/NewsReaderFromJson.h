#ifndef NEWSREADERFROMJSON_H_
#define NEWSREADERFROMJSON_H_

#include <memory>
#include "News.h"

class ExclusionList;

class NewsReaderFromJson final
{
public:
   NewsReaderFromJson();
   ~NewsReaderFromJson();

   std::shared_ptr<News> readNews(const std::string& filename,
      const ExclusionList& exclusionList) const;
};

#endif
