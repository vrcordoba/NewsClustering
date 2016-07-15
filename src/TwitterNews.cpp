
#include "TwitterNews.h"

#include <iterator>
#include <algorithm>
#include <sstream>
#include "ExclusionList.h"
#include "StringUtilities.h"
#include "NewsDiscriminator.h"

TwitterNews::TwitterNews(const ExclusionList& exclusionList) : exclusionList(exclusionList)
{
}

TwitterNews::~TwitterNews()
{
}

void TwitterNews::setMentionedEntities(const std::vector<std::string>& wordsInNews)
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

void TwitterNews::accept(NewsDiscriminator* newsDiscriminator) const
{
   newsDiscriminator->visit(this);
}

bool TwitterNews::shareMentionedEntities(const TwitterNews* otherTwitterNews) const
{
   for (auto& mentionedEntity : mentionedEntities)
   {
      if (otherTwitterNews->mentionedEntities.find(mentionedEntity.first)
         != std::end(otherTwitterNews->mentionedEntities))
         return true;
   }
   return false;
}

void TwitterNews::setSubject(const std::string& subject)
{
   News::setSubject(subject);
   std::istringstream iss(subject);
   std::vector<std::string> wordsInTuit;
   std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
      std::back_inserter(wordsInTuit));
   setMentionedEntities(wordsInTuit);
}
