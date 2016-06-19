#ifndef EXCLUSIONLISTFROMFILE_H_
#define EXCLUSIONLISTFROMFILE_H_

#include "ExclusionList.h"
#include <string>
#include <set>

class ExclusionListFromFile final : public ExclusionList
{
public:
   explicit ExclusionListFromFile(const std::string& exclusionListFile);
   ~ExclusionListFromFile();

   bool isWordInExclusionList(const std::string& word) const;

private:
   void readExclusionListFromFile(const std::string& exclusionListFile);

   const std::string currentLocale;
   std::string toLower(const std::string& word) const;
   std::string nonAsciiCharactersToLower(const std::string& character) const;
   std::set<std::string> excludedWords;
};

#endif
