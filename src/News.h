#ifndef NEWS_H_
#define NEWS_H_

#include <string>
#include <vector>
#include <map>
#include <cstdint>

class ExclusionList;

class News final
{
public:
   explicit News(const ExclusionList& exclusionList);
   ~News();

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
