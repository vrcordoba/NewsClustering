
#include <iterator>
#include <algorithm>
#include <fstream>
#include "NewsReaderFromTuit.h"
#include "ExclusionList.h"
#include "TwitterNews.h"
#include "InvalidLocationException.h"
#include "JsonCpp/json/json.h"

NewsReaderFromTuit::NewsReaderFromTuit(const std::string& tuitsFile,
   const ExclusionList& exclusionList) : tuitsFile(tuitsFile), exclusionList(exclusionList)
{
}

NewsReaderFromTuit::~NewsReaderFromTuit()
{
}

std::vector<std::shared_ptr<News>> NewsReaderFromTuit::getNews() const
{
   Json::Reader fileReader;
   Json::Value rootElement;
   std::ifstream tuitStream(tuitsFile, std::ifstream::binary);
   if (not fileReader.parse(tuitStream, rootElement, false))
      throw InvalidLocationException(tuitsFile);
   std::vector<std::shared_ptr<News>> tuitsVector;
   getTuitsFromFile(rootElement, tuitsVector);
   return tuitsVector;
}

void NewsReaderFromTuit::getTuitsFromFile(const Json::Value& rootElement,
   std::vector<std::shared_ptr<News>>& tuitsVector) const
{
   const Json::Value tuits = rootElement["tuits"];
   for (Json::ArrayIndex index = 0; index < tuits.size(); ++index)
   {
      std::string tuit = tuits[index]["tuit"].asString();
      std::istringstream iss(tuit);
      std::vector<std::string> wordsInTuit;
      std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
         std::back_inserter(wordsInTuit));
      std::shared_ptr<News> news(new TwitterNews(exclusionList));
      news->setHeadline(tuit);
      news->setMentionedEntities(wordsInTuit);
      tuitsVector.push_back(news);
   }
}

