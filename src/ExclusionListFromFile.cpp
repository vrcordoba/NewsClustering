
#include "ExclusionListFromFile.h"

#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

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
         toLowerWord += spanishNonAsciiCharactersToLower(word.substr(byte, 2));
         byte++;
      }
      else if ((character >> 4) == 14)
      {
         toLowerWord += spanishNonAsciiCharactersToLower(word.substr(byte, 3));
         byte += 2;
      }
      else if ((character >> 3) == 30)
      {
         toLowerWord += spanishNonAsciiCharactersToLower(word.substr(byte, 4));
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

std::string ExclusionListFromFile::spanishNonAsciiCharactersToLower(const std::string& character) const
{
   if (character == u8"\u00d1") //ñ
      return u8"\u00f1";
   else if(character == u8"\u00dc") //ü
      return u8"\u00fc";
   else if(character == u8"\u00c1") //á
      return u8"\u00e1";
   else if(character == u8"\u00c9") //é
      return u8"\u00e9";
   else if(character == u8"\u00cd") //í­
      return u8"\u00ed";
   else if(character == u8"\u00d3") //ó
      return u8"\u00f3";
   else if(character == u8"\u00da") //ú
      return u8"\u00fa";
   else
      return character;
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
