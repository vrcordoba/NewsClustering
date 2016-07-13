
#include "NewsReaderFromPlainText.h"

#include <dirent.h>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cstring>
#include "InvalidDirectoryException.h"
#include "NewspaperNews.h"

NewsReaderFromPlainText::NewsReaderFromPlainText(const std::string& newsDirectory,
   const ExclusionList& exclusionList) : newsDirectory(newsDirectory),
   exclusionList(exclusionList)
{
}

NewsReaderFromPlainText::~NewsReaderFromPlainText()
{
}

std::vector<std::shared_ptr<News>> NewsReaderFromPlainText::getNews() const
{
   std::vector<std::shared_ptr<News>> newsVector;
   std::vector<std::string> newsFilesInDirectory = getFilesInDirectory();
   for (auto& newsFile : newsFilesInDirectory)
   {
      std::shared_ptr<News> news = getNewsFromFile(newsDirectory + "/" + newsFile);
      newsVector.push_back(news);
   }
   return newsVector;
}

std::vector<std::string> NewsReaderFromPlainText::getFilesInDirectory() const
{
   std::vector<std::string> files;
   DIR *dir;
   if ((dir = opendir(newsDirectory.c_str())) != nullptr)
   {
      struct dirent *ent;
      while ((ent = readdir(dir)) != nullptr)
      {
         if (std::strcmp(".", ent->d_name) and std::strcmp("..", ent->d_name))
            files.push_back(ent->d_name);
      }
      closedir(dir);
   }
   else
      throw InvalidDirectoryException(newsDirectory);
   return files;
}

std::shared_ptr<News> NewsReaderFromPlainText::getNewsFromFile(const std::string& filename) const
{
   std::ifstream file(filename);
   std::vector<std::string> wordsInNews;
   std::string title;
   for (std::string line; std::getline(file, line); )
   {
      if (title.empty())
      {
         line.erase(std::find_if(line.rbegin(), line.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), line.end());
         title = line;
      }
      std::istringstream iss(line);
      std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
         std::back_inserter(wordsInNews));
   }
   std::shared_ptr<News> news(new NewspaperNews(exclusionList));
   news->setHeadline(title);
   news->setMentionedEntities(wordsInNews);
   return news;
}
