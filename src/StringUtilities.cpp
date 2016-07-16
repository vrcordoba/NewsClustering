
#include "StringUtilities.h"

#include <locale>
#include <sstream>
#include <iterator>
#include <algorithm>
#include "Utf8Constants.h"

namespace StringUtilities
{

std::string toLower(const std::string& word)
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

std::string nonAsciiCharacterToLower(const std::string& multiByteRepresentation)
{
   std::setlocale(LC_ALL, Utf8Constants::currentLocale);
   wchar_t wideRepresentation;
   std::mbtowc(&wideRepresentation, multiByteRepresentation.c_str(), multiByteRepresentation.size());
   wchar_t lowerWideRepresentation = std::tolower(wideRepresentation, std::locale(Utf8Constants::currentLocale));
   std::string lowerMultiByteRepresentation(multiByteRepresentation.size(), '\0');
   std::wctomb(&lowerMultiByteRepresentation[0], lowerWideRepresentation);
   return lowerMultiByteRepresentation;
}

bool isFirstCharacterCapitalLetter(const std::string& word)
{
   bool isCapitalLetter = false;
   unsigned firstCharacter = word[0] & 0x000000FF;
   // Following https://en.wikipedia.org/wiki/UTF-8#Description
   if ((firstCharacter >> Utf8Constants::oneByteMaskShift) == Utf8Constants::oneByteCharacterMask)
   {
      isCapitalLetter = std::isupper(word[0]);
   }
   else if ((firstCharacter >> Utf8Constants::twoBytesMaskShift) == Utf8Constants::twoBytesCharacterMask)
   {
      isCapitalLetter = isNonAsciiCharacterUpper(word.substr(0, 2));
   }
   else if ((firstCharacter >> Utf8Constants::threeBytesMaskShift) == Utf8Constants::threeBytesCharacterMask)
   {
      isCapitalLetter = isNonAsciiCharacterUpper(word.substr(0, 3));
   }
   else if ((firstCharacter >> Utf8Constants::fourBytesMaskShift) == Utf8Constants::fourBytesCharacterMask)
   {
      isCapitalLetter = isNonAsciiCharacterUpper(word.substr(0, 4));
   }
   return isCapitalLetter;
}

bool isNonAsciiCharacterUpper(const std::string& multiByteRepresentation)
{
   std::setlocale(LC_ALL, Utf8Constants::currentLocale);
   wchar_t wideRepresentation;
   std::mbtowc(&wideRepresentation, multiByteRepresentation.c_str(), multiByteRepresentation.size());
   return std::isupper(wideRepresentation, std::locale(Utf8Constants::currentLocale));
}

void breakTextIntoWords(const std::string& text, std::vector<std::string>& words)
{
   std::istringstream iss(text);
   std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
      std::back_inserter(words));
}

}

