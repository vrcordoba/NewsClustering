
#include "News.h"

#include <algorithm>

News::News() : mentionedEntities(), mostMentionedEntity(), subject()
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

std::set<std::string> News::getMentionedEntities() const
{
   std::set<std::string> mentionedEntitiesSet;
   std::transform(std::begin(mentionedEntities), std::end(mentionedEntities), std::inserter(mentionedEntitiesSet,
      mentionedEntitiesSet.begin()), [](const std::pair<std::string, std::uint32_t>& mapItem) {
           return mapItem.first;});
   return mentionedEntitiesSet;
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

std::string News::getSubject() const
{
   return subject;
}

void News::setSubject(const std::string& subject)
{
   this->subject = subject;
}

bool News::isContainedInSubject(const std::string& word) const
{
   return (subject.find(word) != std::string::npos);
}

std::set<std::string> News::getRelevantEntities() const
{
   std::set<std::string> emptySet;
   return emptySet;
}

bool News::isContainedInRelevantEntities(const std::string& word) const
{
   return false;
}
