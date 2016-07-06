#ifndef NEWS_H_
#define NEWS_H_

#include <string>
#include <vector>
#include <set>

class News
{
public:
   virtual ~News() {};

   virtual std::string getMostMentionedEntity() = 0;
   virtual std::string getHeadline() const = 0;
   virtual std::set<std::string> getRelevantEntities() const = 0;
   virtual void setMentionedEntities(const std::vector<std::string>& wordsInNews) = 0;
   virtual void setHeadline(const std::string& headline) = 0;
   virtual bool isContainedInHeadline(const std::string& word) const = 0;
};

#endif
