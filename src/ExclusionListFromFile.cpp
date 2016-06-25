
#include "ExclusionListFromFile.h"

#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include "StringUtilities.h"

ExclusionListFromFile::ExclusionListFromFile(const std::string& exclusionListFile)
   : excludedWords()
{
   readExclusionListFromFile(exclusionListFile);
}

ExclusionListFromFile::~ExclusionListFromFile()
{
}

bool ExclusionListFromFile::isWordInExclusionList(const std::string& word) const
{
   std::string toLowerWord = StringUtilities::toLower(word);
   return (excludedWords.find(toLowerWord) != excludedWords.end());
}

void ExclusionListFromFile::readExclusionListFromFile(const std::string& exclusionListFile)
{
   std::ifstream file(exclusionListFile);
   std::string line;
   std::getline(file, line);
   std::istringstream iss(line);
   std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
      std::inserter(excludedWords, excludedWords.end()));
}
