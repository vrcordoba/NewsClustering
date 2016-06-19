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

   std::string toLower(const std::string& word) const;
   std::string nonAsciiCharacterToLower(const std::string& multiByteRepresentation) const;
   std::set<std::string> excludedWords;
};

#endif
