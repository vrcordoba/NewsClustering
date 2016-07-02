#ifndef NEWSREADERFROMPLAINTEXT_H_
#define NEWSREADERFROMPLAINTEXT_H_

#include <vector>
#include <exception>
#include <memory>
#include "NewsReader.h"
#include "NewspaperNews.h"
#include "ExclusionList.h"
#include "NewsCluster.h"

class NewsReaderFromPlainText final : public NewsReader
{
public:
   NewsReaderFromPlainText(const std::string& newsDirectory, const ExclusionList& exclusionList);
   ~NewsReaderFromPlainText();

   std::vector<NewsCluster> getNews();

private:
   std::vector<std::string> getFilesInDirectory();
   std::shared_ptr<News> getNewsFromFile(const std::string& filename);

   std::string newsDirectory;
   const ExclusionList& exclusionList;
};

#endif
