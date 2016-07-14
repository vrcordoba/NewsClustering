
#include "NewsDiscriminator.h"

NewsDiscriminator::NewsDiscriminator() : firstReceived(notDetermined),
   secondReceived(notDetermined)
{
}

NewsDiscriminator::~NewsDiscriminator()
{
}

NewsDiscriminator::DiscriminatorResult NewsDiscriminator::discriminateType(
   const std::shared_ptr<News>& firstNews, const std::shared_ptr<News>& secondNews)
{
   DiscriminatorResult result;
   firstNews->accept(this);
   secondNews->accept(this);
   if (newspaperNews == firstReceived)
   {
      if (newspaperNews == secondReceived)
         result = bothFromNewspaper;
      else
         result = firstFromNewspaperSecondFromTwitter;
   }
   else
   {
      if (newspaperNews == secondReceived)
         result = firstFromTwitterSecondFromNewspaper;
      else
         result = bothFromTwitter;
   }
   firstReceived = notDetermined;
   secondReceived = notDetermined;
   return result;
}

void NewsDiscriminator::visit(const NewspaperNews* news)
{
   if (notDetermined == firstReceived)
      firstReceived = newspaperNews;
   else
      secondReceived = newspaperNews;
}

void NewsDiscriminator::visit(const TwitterNews* news)
{
   if (notDetermined == firstReceived)
      firstReceived = twitterNews;
   else
      secondReceived = twitterNews;
}

