
#include "NewsReaderFromPlainText.h"

#include <fstream>
#include <algorithm>
#include "NewspaperNews.h"
#include "StringUtilities.h"

NewsReaderFromPlainText::NewsReaderFromPlainText()
{
}

NewsReaderFromPlainText::~NewsReaderFromPlainText()
{
}

std::shared_ptr<News> NewsReaderFromPlainText::readNews(const std::string& filename,
   const ExclusionList& exclusionList) const
{
   std::ifstream file(filename);
   std::vector<std::string> wordsInNews;
   std::string subject;
   NewspaperNews* newspaperNews = new NewspaperNews(exclusionList);
   for (std::string line; std::getline(file, line); )
   {
      if (subject.empty())
      {
         line.erase(std::find_if(line.rbegin(), line.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), line.end());
         subject = line;
      }
      else
         newspaperNews->addParagraph(line);
      StringUtilities::breakTextIntoWords(line, wordsInNews);
   }
   newspaperNews->setSubject(subject);
   newspaperNews->setMentionedEntities(wordsInNews);
   std::shared_ptr<News> news(newspaperNews);
   return news;
}

