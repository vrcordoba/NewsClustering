#ifndef NEWS_H_
#define NEWS_H_

#include <string>
#include <vector>
#include <set>
#include <map>
#include <cstdint>

class NewsVisitor;

class News
{
public:
   News();
   virtual ~News();

   virtual void setMentionedEntities(const std::vector<std::string>& wordsInNews) = 0;

   virtual std::string getMostMentionedEntity();
   virtual std::set<std::string> getMentionedEntities() const;
   virtual std::string getSubject() const;
   virtual void setSubject(const std::string& subject);
   virtual bool isContainedInSubject(const std::string& word) const;

   virtual std::set<std::string> getRelevantEntities() const;
   virtual bool isContainedInRelevantEntities(const std::string& word) const;

   virtual void accept(NewsVisitor* newsVisitor) const = 0;

protected:
   std::map<std::string, std::uint32_t> mentionedEntities;

private:
   void computeMostMentionedEntity();

   std::string mostMentionedEntity;
   std::string subject;
};

#endif
