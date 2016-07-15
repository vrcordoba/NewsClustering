
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
   firstNews->accept(this);
   secondNews->accept(this);
   DiscriminatorResult result = bothFromNewspaper;
   if (newspaperNews == firstReceived and twitterNews == secondReceived)
      result = firstFromNewspaperSecondFromTwitter;
   else if (twitterNews == firstReceived and newspaperNews == secondReceived)
      result = firstFromTwitterSecondFromNewspaper;
   else if (twitterNews == firstReceived and twitterNews == secondReceived)
      result = bothFromTwitter;
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

