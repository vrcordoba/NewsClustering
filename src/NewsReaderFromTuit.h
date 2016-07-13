#ifndef NEWSREADERFROMTUIT_H_
#define NEWSREADERFROMTUIT_H_

#include <vector>
#include <memory>
#include <string>
#include "NewsReader.h"

class ExclusionList;

namespace Json
{
class Value;
}

class NewsReaderFromTuit final : public NewsReader
{
public:
   NewsReaderFromTuit(const std::string& tuitsFile, const ExclusionList& exclusionList);
   ~NewsReaderFromTuit();

   std::vector<std::shared_ptr<News>> getNews() const;

private:
   void getTuitsFromFile(const Json::Value& rootElement,
      std::vector<std::shared_ptr<News>>& tuitsVector) const;

   std::string tuitsFile;
   const ExclusionList& exclusionList;
};

#endif
