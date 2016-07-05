
#include "NewspaperNews.h"

#include "ExclusionList.h"
#include "StringUtilities.h"

NewspaperNews::NewspaperNews(const ExclusionList& exclusionList) : exclusionList(exclusionList),
   mostMentionedEntity(), mentionedEntities(), headline()
{
}

NewspaperNews::~NewspaperNews()
{
}

std::string NewspaperNews::getMostMentionedEntity()
{
   if (mostMentionedEntity.empty())
      computeMostMentionedEntity();
   return mostMentionedEntity;
}

void NewspaperNews::computeMostMentionedEntity()
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

void NewspaperNews::setMentionedEntities(const std::vector<std::string>& wordsInNews)
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

std::string NewspaperNews::getHeadline() const
{
   return headline;
}

void NewspaperNews::setHeadline(const std::string& headline)
{
   this->headline = headline;
}

bool NewspaperNews::isContainedInHeadline(const std::string& word) const
{
   return (headline.find(word) != std::string::npos);
}

