
#include "ExclusionListFromFile.h"

#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include "Utf8Constants.h"

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
   std::string toLowerWord = toLower(word);
   return (excludedWords.find(toLowerWord) != excludedWords.end());
}

std::string ExclusionListFromFile::toLower(const std::string& word) const
{
   std::string toLowerWord;
   std::size_t numBytesInWord = word.size();
   std::size_t byte = 0;
   while (byte < numBytesInWord)
   {
      // Following https://en.wikipedia.org/wiki/UTF-8#Description
      unsigned character = word[byte] & 0x000000FF;
      if ((character >> Utf8Constants::oneByteMaskShift) == Utf8Constants::oneByteCharacterMask)
      {
         toLowerWord += std::tolower(word[byte]);
      }
      else if ((character >> Utf8Constants::twoBytesMaskShift) == Utf8Constants::twoBytesCharacterMask)
      {
         toLowerWord += nonAsciiCharacterToLower(word.substr(byte, 2));
         byte++;
      }
      else if ((character >> Utf8Constants::threeBytesMaskShift) == Utf8Constants::threeBytesCharacterMask)
      {
         toLowerWord += nonAsciiCharacterToLower(word.substr(byte, 3));
         byte += 2;
      }
      else if ((character >> Utf8Constants::fourBytesMaskShift) == Utf8Constants::fourBytesCharacterMask)
      {
         toLowerWord += nonAsciiCharacterToLower(word.substr(byte, 4));
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

std::string ExclusionListFromFile::nonAsciiCharacterToLower(const std::string& multiByteRepresentation) const
{
   std::setlocale(LC_ALL, Utf8Constants::currentLocale);
   wchar_t wideRepresentation;
   std::mbtowc(&wideRepresentation, multiByteRepresentation.c_str(), multiByteRepresentation.size());
   wchar_t lowerWideRepresentation = std::tolower(wideRepresentation, std::locale(Utf8Constants::currentLocale));
   std::string lowerMultiByteRepresentation(multiByteRepresentation.size(), '\0');
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
