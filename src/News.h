#ifndef NEWS_H_
#define NEWS_H_

#include <string>
#include <vector>

class News
{
public:
   virtual ~News() {};

   virtual std::string getMostMentionedEntity() = 0;
   virtual std::string getTitle() const = 0;
   virtual void setMentionedEntities(const std::vector<std::string>& wordsInNews) = 0;
   virtual void setTitle(const std::string& title) = 0;
};

#endif
