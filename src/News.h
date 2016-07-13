#ifndef NEWS_H_
#define NEWS_H_

#include <string>
#include <vector>
#include <set>
#include <map>

class News
{
public:
   News();
   virtual ~News();

   virtual void setMentionedEntities(const std::vector<std::string>& wordsInNews) = 0;

   virtual std::string getMostMentionedEntity();
   virtual std::string getHeadline() const;
   virtual void setHeadline(const std::string& headline);
   virtual bool isContainedInHeadline(const std::string& word) const;

   // TODO: Remove these methods when ThematicSimilarityClusteringCriterion is adapted
   // to handle NewspaperNews and TwitterNews
   virtual std::set<std::string> getRelevantEntities() const;
   virtual bool isContainedInRelevantEntities(const std::string& word) const;

protected:
   std::map<std::string, std::uint32_t> mentionedEntities;

private:
   void computeMostMentionedEntity();

   std::string mostMentionedEntity;
   std::string headline;
};

#endif
