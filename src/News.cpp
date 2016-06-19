
#include "News.h"

#include <locale>
#include "ExclusionList.h"
#include "Utf8Constants.h"

News::News(const ExclusionList& exclusionList) : exclusionList(exclusionList),
   mostMentionedEntity(), mentionedEntities()
{
}

News::~News()
{
}

std::string News::getMostMentionedEntity()
{
   if (mostMentionedEntity.empty())
      computeMostMentionedEntity();
   return mostMentionedEntity;
}

void News::computeMostMentionedEntity()
{
   std::uint32_t mostMentionedTimes = 0;
   for (auto& mentionedEntity : mentionedEntities)
   {
      if (mentionedEntity.second > mostMentionedTimes)
      {
         mostMentionedTimes = mentionedEntity.second;
         mostMentionedEntity = mentionedEntity.first;
      }
   }
}

void News::setMentionedEntities(std::vector<std::string> wordsInNews)
{
   for (auto& word : wordsInNews)
   {
      if (isFirstCharacterCapitalLetter(word) and (not exclusionList.isWordInExclusionList(word)))
      {
         if (mentionedEntities.find(word) != std::end(mentionedEntities))
            mentionedEntities[word] += 1u;
         else
            mentionedEntities[word] = 1u;
      }
   }
}

bool News::isFirstCharacterCapitalLetter(const std::string& word) const
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

bool News::isNonAsciiCharacterUpper(const std::string& multiByteRepresentation) const
{
   std::setlocale(LC_ALL, Utf8Constants::currentLocale);
   wchar_t wideRepresentation;
   std::mbtowc(&wideRepresentation, multiByteRepresentation.c_str(), multiByteRepresentation.size());
   return std::isupper(wideRepresentation, std::locale(Utf8Constants::currentLocale));
}
