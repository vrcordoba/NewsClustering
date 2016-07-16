#ifndef NEWSREADER_H_
#define NEWSREADER_H_

#include <vector>
#include <memory>
#include "Reader.h"
#include "News.h"

class ExclusionList;

class NewsReader final : public Reader
{
public:
   NewsReader(const std::string& newsDirectory, const ExclusionList& exclusionList);
   ~NewsReader();

   std::vector<std::shared_ptr<News>> getNews() const;

private:
   std::vector<std::string> getFilesInDirectory() const;
   std::shared_ptr<News> getNewsFromFile(const std::string& filename) const;

   std::string newsDirectory;
   const ExclusionList& exclusionList;
};

#endif
