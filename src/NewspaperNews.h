#ifndef NEWSPAPERNEWS_H_
#define NEWSPAPERNEWS_H_

#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include "News.h"

class ExclusionList;

class NewspaperNews final : public News
{
public:
   explicit NewspaperNews(const ExclusionList& exclusionList);
   ~NewspaperNews();

   std::string getMostMentionedEntity();
   void setMentionedEntities(std::vector<std::string> wordsInNews);

private:
   void computeMostMentionedEntity();
   bool isFirstCharacterCapitalLetter(const std::string& word) const;
   bool isNonAsciiCharacterUpper(const std::string& multiByteRepresentation) const;

   const ExclusionList& exclusionList;
   std::string mostMentionedEntity;
   std::map<std::string, std::uint32_t> mentionedEntities;
};

#endif
