
#include "ExclusionListFromFile.h"

#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

ExclusionListFromFile::ExclusionListFromFile(const std::string& exclusionListFile)
   : currentLocale("es_ES.UTF-8"), excludedWords()
{
   readExclusionListFromFile(exclusionListFile);
}

ExclusionListFromFile::~ExclusionListFromFile()
{
}

bool ExclusionListFromFile::isWordInExclusionList(const std::string& word) const
{
   std::string toLowerWord = toLower(word);
   return (excludedWords.find(toLowerWord) != excludedWords.end());
}

std::string ExclusionListFromFile::toLower(const std::string& word) const
{
   std::string toLowerWord;
   std::size_t numBitesInWord = word.size();
   std::size_t byte = 0;
   while (byte < numBitesInWord)
   {
      // Following https://en.wikipedia.org/wiki/UTF-8#Description
      unsigned character = word[byte] & 0x000000FF;
      if ((character >> 7) == 0)
      {
         toLowerWord += std::tolower(word[byte]);
      }
      else if ((character >> 5) == 6)
      {
         toLowerWord += nonAsciiCharactersToLower(word.substr(byte, 2));
         byte++;
      }
      else if ((character >> 4) == 14)
      {
         toLowerWord += nonAsciiCharactersToLower(word.substr(byte, 3));
         byte += 2;
      }
      else if ((character >> 3) == 30)
      {
         toLowerWord += nonAsciiCharactersToLower(word.substr(byte, 4));
         byte += 3;
      }
      else
      {
         toLowerWord += character;
      }
      byte++;
   }
   return toLowerWord;
}

std::string ExclusionListFromFile::nonAsciiCharactersToLower(const std::string& character) const
{
   std::setlocale(LC_ALL, currentLocale.c_str());
   wchar_t wideRepresentation;
   std::mbtowc(&wideRepresentation, character.c_str(), character.size());
   wchar_t lowerWideRepresentation = std::tolower(wideRepresentation, std::locale(currentLocale.c_str()));
   std::string lowerMultiByteRepresentation(character.size(), '\0');
   std::wctomb(&lowerMultiByteRepresentation[0], lowerWideRepresentation);
   return lowerMultiByteRepresentation;
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
