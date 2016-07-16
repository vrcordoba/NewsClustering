#ifndef NEWSREADERFROMPLAINTEXT_H_
#define NEWSREADERFROMPLAINTEXT_H_

#include <memory>
#include "News.h"

class ExclusionList;

class NewsReaderFromPlainText final
{
public:
   NewsReaderFromPlainText();
   ~NewsReaderFromPlainText();

   std::shared_ptr<News> readNews(const std::string& filename,
      const ExclusionList& exclusionList) const;
};

#endif
