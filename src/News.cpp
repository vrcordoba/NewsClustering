
#include "News.h"

News::News() : mentionedEntities(), mostMentionedEntity(), headline()
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

std::string News::getHeadline() const
{
   return headline;
}

void News::setHeadline(const std::string& headline)
{
   this->headline = headline;
}

bool News::isContainedInHeadline(const std::string& word) const
{
   return (headline.find(word) != std::string::npos);
}

// TODO: Remove these methods when ThematicSimilarityClusteringCriterion is adapted
// to handle NewspaperNews and TwitterNews
std::set<std::string> News::getRelevantEntities() const
{
   std::set<std::string> emptySet;
   return emptySet;
}

bool News::isContainedInRelevantEntities(const std::string& word) const
{
   return false;
}
