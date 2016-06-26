
#include "News.h"

#include <locale>
#include "ExclusionList.h"
#include "StringUtilities.h"

News::News(const ExclusionList& exclusionList) : exclusionList(exclusionList),
   mostMentionedEntity(), mentionedEntities()
{
}

News::~News()
{
}

News& News::operator=(const News& otherNews)
{
   this->mostMentionedEntity = otherNews.mostMentionedEntity;
   mentionedEntities = otherNews.mentionedEntities;
   return *this;
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
      if (StringUtilities::isFirstCharacterCapitalLetter(word) and (not exclusionList.isWordInExclusionList(word)))
      {
         if (mentionedEntities.find(word) != std::end(mentionedEntities))
            mentionedEntities[word] += 1u;
         else
            mentionedEntities[word] = 1u;
      }
   }
}
