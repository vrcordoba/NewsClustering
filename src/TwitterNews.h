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

   void accept(NewsDiscriminator* newsDiscriminator) const;

private:
   const ExclusionList& exclusionList;
};

#endif
