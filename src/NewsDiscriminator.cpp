
#include "NewsDiscriminator.h"

NewsDiscriminator::NewsDiscriminator() : firstReceived(TypeOfNews::notDetermined),
   secondReceived(TypeOfNews::notDetermined)
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
   if (TypeOfNews::newspaperNews == firstReceived and TypeOfNews::twitterNews == secondReceived)
      result = firstFromNewspaperSecondFromTwitter;
   else if (TypeOfNews::twitterNews == firstReceived and TypeOfNews::newspaperNews == secondReceived)
      result = firstFromTwitterSecondFromNewspaper;
   else if (TypeOfNews::twitterNews == firstReceived and TypeOfNews::twitterNews == secondReceived)
      result = bothFromTwitter;
   firstReceived = TypeOfNews::notDetermined;
   secondReceived = TypeOfNews::notDetermined;
   return result;
}

void NewsDiscriminator::visit(const NewspaperNews* news)
{
   if (TypeOfNews::notDetermined == firstReceived)
      firstReceived = TypeOfNews::newspaperNews;
   else
      secondReceived = TypeOfNews::newspaperNews;
}

void NewsDiscriminator::visit(const TwitterNews* news)
{
   if (TypeOfNews::notDetermined == firstReceived)
      firstReceived = TypeOfNews::twitterNews;
   else
      secondReceived = TypeOfNews::twitterNews;
}

