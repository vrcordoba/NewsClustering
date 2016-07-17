#ifndef NEWSREADER_H_
#define NEWSREADER_H_

#include <vector>
#include <memory>
#include "Reader.h"
#include "News.h"
#include "NewsReaderFromPlainText.h"
#include "NewsReaderFromJson.h"

class ExclusionList;

class NewsReader final : public Reader
{
public:
   NewsReader(const std::string& newsDirectory, const ExclusionList& exclusionList);
   ~NewsReader();

   std::vector<std::shared_ptr<News>> getNews() const;

private:
   std::vector<std::string> getFilesInDirectory(const char* extension) const;
   void getNewsFromPlainText(const std::vector<std::string>& plainTextFiles,
      std::vector<std::shared_ptr<News>>& newsVector) const;
   void getNewsFromJson(const std::vector<std::string>& jsonFiles,
      std::vector<std::shared_ptr<News>>& newsVector) const;

   std::string newsDirectory;
   const ExclusionList& exclusionList;
   const NewsReaderFromPlainText newsReaderFromPlainText;
   const NewsReaderFromJson newsReaderFromJson;
};

#endif
