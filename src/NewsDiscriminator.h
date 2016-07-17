#ifndef NEWSDISCRIMINATOR_H_
#define NEWSDISCRIMINATOR_H_

#include <memory>
#include "NewsVisitor.h"
#include "News.h"
#include "TypeOfNews.h"

class NewsDiscriminator final : public NewsVisitor
{
public:
   NewsDiscriminator();
   ~NewsDiscriminator();

   enum DiscriminatorResult
   {
      bothFromNewspaper,
      bothFromTwitter,
      firstFromTwitterSecondFromNewspaper,
      firstFromNewspaperSecondFromTwitter
   };

   DiscriminatorResult discriminateType(const std::shared_ptr<News>& firstNews,
      const std::shared_ptr<News>& secondNews);

   void visit(const NewspaperNews* news);
   void visit(const TwitterNews* news);

private:
   TypeOfNews firstReceived;
   TypeOfNews secondReceived;
};

#endif
