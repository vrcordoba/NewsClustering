
#include "TwitterNews.h"

#include "ExclusionList.h"
#include "StringUtilities.h"
#include "NewsDiscriminator.h"
#include "StringUtilities.h"

TwitterNews::TwitterNews(const ExclusionList& exclusionList) : exclusionList(exclusionList),
   id(0), user()
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
   std::vector<std::string> wordsInTuit;
   StringUtilities::breakTextIntoWords(subject, wordsInTuit);
   setMentionedEntities(wordsInTuit);
}

void TwitterNews::setId(unsigned int id)
{
   this->id = id;
}

unsigned int TwitterNews::getId() const
{
   return id;
}

void TwitterNews::setUser(const std::string& user)
{
   this->user = user;
}

std::string TwitterNews::getUser() const
{
   return user;
}
