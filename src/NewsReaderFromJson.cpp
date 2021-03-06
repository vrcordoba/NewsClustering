
#include "NewsReaderFromJson.h"

#include <fstream>
#include "JsonCpp/json/json.h"
#include "NewspaperNews.h"
#include "InvalidLocationException.h"
#include "StringUtilities.h"

NewsReaderFromJson::NewsReaderFromJson()
{
}

NewsReaderFromJson::~NewsReaderFromJson()
{
}

std::shared_ptr<News> NewsReaderFromJson::readNews(const std::string& filename,
   const ExclusionList& exclusionList) const
{
   Json::CharReaderBuilder builder;
   Json::Value rootElement;
   std::ifstream newsStream(filename, std::ifstream::binary);
   if (not Json::parseFromStream(builder, newsStream, &rootElement, nullptr))
      throw InvalidLocationException(filename);
   const Json::Value subject = rootElement["titulo"];
   NewspaperNews* newspaperNews = new NewspaperNews(exclusionList);
   newspaperNews->setSubject(subject.asString());
   std::vector<std::string> wordsInNews;
   StringUtilities::breakTextIntoWords(subject.asString(), wordsInNews);
   const Json::Value paragraphs = rootElement["parrafos"];
   for (Json::ArrayIndex index = 0; index < paragraphs.size(); ++index)
   {
      const std::string paragraph = paragraphs[index].asString();
      newspaperNews->addParagraph(paragraph);
      StringUtilities::breakTextIntoWords(paragraph, wordsInNews);
   }
   newspaperNews->setMentionedEntities(wordsInNews);
   std::shared_ptr<News> news(newspaperNews);
   return news;
}

