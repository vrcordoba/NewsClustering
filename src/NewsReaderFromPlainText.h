#ifndef NEWSREADERFROMPLAINTEXT_H_
#define NEWSREADERFROMPLAINTEXT_H_

#include <vector>
#include <memory>
#include "NewsReader.h"
#include "News.h"

class ExclusionList;

class NewsReaderFromPlainText final : public NewsReader
{
public:
   NewsReaderFromPlainText(const std::string& newsDirectory, const ExclusionList& exclusionList);
   ~NewsReaderFromPlainText();

   std::vector<std::shared_ptr<News>> getNews() const;

private:
   std::vector<std::string> getFilesInDirectory() const;
   std::shared_ptr<News> getNewsFromFile(const std::string& filename) const;

   std::string newsDirectory;
   const ExclusionList& exclusionList;
};

#endif
