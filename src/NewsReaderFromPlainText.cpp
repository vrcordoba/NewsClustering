
#include "NewsReaderFromPlainText.h"

#include <dirent.h>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cstring>
#include "InvalidDirectoryException.h"
#include "NewsCluster.h"

NewsReaderFromPlainText::NewsReaderFromPlainText(const std::string& newsDirectory,
   const ExclusionList& exclusionList) : newsDirectory(newsDirectory),
   exclusionList(exclusionList)
{
}

NewsReaderFromPlainText::~NewsReaderFromPlainText()
{
}

std::vector<NewsCluster> NewsReaderFromPlainText::getNews()
{
   std::vector<NewsCluster> newsVector;
   std::vector<std::string> newsFilesInDirectory = getFilesInDirectory();
   for (auto& newsFile : newsFilesInDirectory)
   {
      News news = getNewsFromFile(newsDirectory + "/" + newsFile);
      NewsCluster newsCluster;
      newsCluster.addNews(news);
      newsVector.push_back(newsCluster);
   }
   return newsVector;
}

std::vector<std::string> NewsReaderFromPlainText::getFilesInDirectory()
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

News NewsReaderFromPlainText::getNewsFromFile(const std::string& filename)
{
   std::ifstream file(filename);
   std::vector<std::string> wordsInNews;
   for (std::string line; std::getline(file, line); )
   {
      std::istringstream iss(line);
      std::vector<std::string> wordsInLine;
      std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
         std::back_inserter(wordsInLine));
      wordsInNews.insert(wordsInNews.end(), wordsInLine.begin(), wordsInLine.end());
   }
   News news(exclusionList);
   news.setMentionedEntities(wordsInNews);
   return news;
}
