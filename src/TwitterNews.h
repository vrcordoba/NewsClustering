#ifndef TWITTERNEWS_H_
#define TWITTERNEWS_H_

#include "News.h"

class ExclusionList;
class NewsDiscriminator;

class TwitterNews final : public News
{
public:
   explicit TwitterNews(const ExclusionList& exclusionList);
   ~TwitterNews();

   void setMentionedEntities(const std::vector<std::string>& wordsInNews);
   void setSubject(const std::string& subject);

   void accept(NewsDiscriminator* newsDiscriminator) const;

   bool shareMentionedEntities(const TwitterNews* otherTwitterNews) const;

   void setId(unsigned int id);
   unsigned int getId() const;

   void setUser(const std::string& user);
   std::string getUser() const;

private:
   const ExclusionList& exclusionList;
   unsigned int id;
   std::string user;
};

#endif
