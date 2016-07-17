
#include "NewsReader.h"

#include <dirent.h>
#include <cstring>
#include "InvalidLocationException.h"
#include "ClusterizerOptionParser.h"

NewsReader::NewsReader(const std::string& newsDirectory,
   const ExclusionList& exclusionList) : newsDirectory(newsDirectory),
   exclusionList(exclusionList), newsReaderFromPlainText(), newsReaderFromJson()
{
}

NewsReader::~NewsReader()
{
}

std::vector<std::shared_ptr<News>> NewsReader::getNews() const
{
   std::vector<std::shared_ptr<News>> newsVector;
   getNewsFromPlainText(getFilesInDirectory(ClusterizerOptionParser::plainTextExtension), newsVector);
   getNewsFromJson(getFilesInDirectory(ClusterizerOptionParser::jsonExtension), newsVector);
   return newsVector;
}

std::vector<std::string> NewsReader::getFilesInDirectory(const char* extension) const
{
   std::vector<std::string> files;
   DIR *dir;
   if ((dir = opendir(newsDirectory.c_str())) != nullptr)
   {
      struct dirent *ent;
      while ((ent = readdir(dir)) != nullptr)
      {
         if (std::strcmp(".", ent->d_name) and std::strcmp("..", ent->d_name)
            and std::strstr(ent->d_name, extension))
            files.push_back(ent->d_name);
      }
      closedir(dir);
   }
   else
      throw InvalidLocationException(newsDirectory);
   return files;
}

void NewsReader::getNewsFromPlainText(
   const std::vector<std::string>& plainTextFiles,
   std::vector<std::shared_ptr<News>>& newsVector) const
{
   for (auto& file : plainTextFiles)
      newsVector.push_back(newsReaderFromPlainText.readNews(newsDirectory + "/" + file,
         exclusionList));
}

void NewsReader::getNewsFromJson(const std::vector<std::string>& jsonFiles,
   std::vector<std::shared_ptr<News>>& newsVector) const
{
   for (auto& file : jsonFiles)
      newsVector.push_back(newsReaderFromJson.readNews(newsDirectory + "/" + file,
         exclusionList));
}
