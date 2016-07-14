
#include "TwitterNews.h"

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
