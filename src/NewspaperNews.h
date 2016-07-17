#ifndef NEWSPAPERNEWS_H_
#define NEWSPAPERNEWS_H_

#include <string>
#include <vector>
#include <cstdint>
#include <set>
#include "News.h"

class ExclusionList;
class NewsDiscriminator;

class NewspaperNews final : public News
{
public:
   explicit NewspaperNews(const ExclusionList& exclusionList);
   ~NewspaperNews();

   void setMentionedEntities(const std::vector<std::string>& wordsInNews);

   std::set<std::string> getRelevantEntities() const;
   bool isContainedInRelevantEntities(const std::string& word) const;

   void accept(NewsDiscriminator* newsDiscriminator) const;

   void addParagraph(const std::string& paragraph);
   std::vector<std::string> getParagraphs() const;

private:
   const ExclusionList& exclusionList;
   std::set<std::string> relevantEntities;
   std::vector<std::string> paragraphs;
};

#endif
