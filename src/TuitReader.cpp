
#include <fstream>
#include "TuitReader.h"
#include "ExclusionList.h"
#include "TwitterNews.h"
#include "InvalidLocationException.h"
#include "JsonCpp/json/json.h"

TuitReader::TuitReader(const std::string& tuitsFile,
   const ExclusionList& exclusionList) : tuitsFile(tuitsFile), exclusionList(exclusionList)
{
}

TuitReader::~TuitReader()
{
}

std::vector<std::shared_ptr<News>> TuitReader::getNews() const
{
   Json::CharReaderBuilder builder;
   Json::Value rootElement;
   std::ifstream tuitStream(tuitsFile, std::ifstream::binary);
   if (not Json::parseFromStream(builder, tuitStream, &rootElement, nullptr))
      throw InvalidLocationException(tuitsFile);
   std::vector<std::shared_ptr<News>> tuitsVector;
   getTuitsFromFile(rootElement, tuitsVector);
   return tuitsVector;
}

void TuitReader::getTuitsFromFile(const Json::Value& rootElement,
   std::vector<std::shared_ptr<News>>& tuitsVector) const
{
   const Json::Value tuits = rootElement["tuits"];
   for (Json::ArrayIndex index = 0; index < tuits.size(); ++index)
   {
      const Json::Value tuit = tuits[index];
      TwitterNews* twitterNews = new TwitterNews(exclusionList);
      twitterNews->setSubject(tuit["tuit"].asString());
      twitterNews->setId(tuit["id"].asUInt());
      twitterNews->setUser(tuit["usuario"].asString());
      std::shared_ptr<News> news(twitterNews);
      tuitsVector.push_back(news);
   }
}

