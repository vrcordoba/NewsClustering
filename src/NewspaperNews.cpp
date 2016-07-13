
#include "NewspaperNews.h"

#include "ExclusionList.h"
#include "StringUtilities.h"

NewspaperNews::NewspaperNews(const ExclusionList& exclusionList) : exclusionList(exclusionList),
   relevantEntities()
{
}

NewspaperNews::~NewspaperNews()
{
}

void NewspaperNews::setMentionedEntities(const std::vector<std::string>& wordsInNews)
{
   const float numRelevantWordsInNews = static_cast<float>(wordsInNews.size()) / 3.0f;
   std::size_t numWordsProcessedSoFar = 0;
   for (auto& word : wordsInNews)
   {
      if (StringUtilities::isFirstCharacterCapitalLetter(word) and (not exclusionList.isWordInExclusionList(word)))
      {
         if (mentionedEntities.find(word) != std::end(mentionedEntities))
            mentionedEntities[word] += 1u;
         else
            mentionedEntities[word] = 1u;

         if (numWordsProcessedSoFar < numRelevantWordsInNews)
            relevantEntities.insert(word);
      }
      ++numWordsProcessedSoFar;
   }
}

std::set<std::string> NewspaperNews::getRelevantEntities() const
{
   return relevantEntities;
}

bool NewspaperNews::isContainedInRelevantEntities(const std::string& word) const
{
   return (relevantEntities.find(word) != std::end(relevantEntities));
}

