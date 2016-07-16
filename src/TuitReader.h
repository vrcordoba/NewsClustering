#ifndef TUITREADER_H_
#define TUITREADER_H_

#include <vector>
#include <memory>
#include <string>
#include "Reader.h"

class ExclusionList;

namespace Json
{
class Value;
}

class TuitReader final : public Reader
{
public:
   TuitReader(const std::string& tuitsFile, const ExclusionList& exclusionList);
   ~TuitReader();

   std::vector<std::shared_ptr<News>> getNews() const;

private:
   void getTuitsFromFile(const Json::Value& rootElement,
      std::vector<std::shared_ptr<News>>& tuitsVector) const;

   std::string tuitsFile;
   const ExclusionList& exclusionList;
};

#endif
