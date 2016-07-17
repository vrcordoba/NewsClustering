
#include "JsonClusterWriter.h"
#include "JsonCpp/json/json.h"
#include "TypeOfNews.h"
#include "NewspaperNews.h"
#include "TwitterNews.h"

JsonClusterWriter::JsonClusterWriter(const std::string& destination) :
   ClusterWriter(destination), root(), typeOfNews(TypeOfNews::notDetermined)
{
}

JsonClusterWriter::~JsonClusterWriter()
{
}

void JsonClusterWriter::write(const std::vector<NewsCluster>& newsClusters)
{
   root["grupos"] = Json::arrayValue;
   for (auto& newsCluster : newsClusters)
   {
      Json::Value cluster;
      addSubject(newsCluster, cluster);
      addEntities(newsCluster, cluster);
      addNews(newsCluster, cluster);
      root["grupos"].append(cluster);
   }
   writeToJson();
}

void JsonClusterWriter::addSubject(const NewsCluster& newsCluster, Json::Value& cluster)
{
   if (newsCluster.empty())
      cluster["titulo"] = "";
   else
      cluster["titulo"] = (*newsCluster.begin())->getSubject();
}

void JsonClusterWriter::addEntities(const NewsCluster& newsCluster, Json::Value& cluster)
{
   std::set<std::string> mentionedEntities = newsCluster.getMentionedEntities();
   for (auto& mentionedEntity : mentionedEntities)
      cluster["entidades"].append(mentionedEntity);
}

void JsonClusterWriter::addNews(const NewsCluster& newsCluster, Json::Value& cluster)
{
   for (auto& news : newsCluster)
   {
      Json::Value newsElement;
      news->accept(this);
      if (TypeOfNews::newspaperNews == typeOfNews)
         addNewspaperNews(static_cast<NewspaperNews*>(news.get()), newsElement);
      else
         addTwitterNews(static_cast<TwitterNews*>(news.get()), newsElement);
      cluster["elementos"].append(newsElement);
   }
}

void JsonClusterWriter::addNewspaperNews(const NewspaperNews* news, Json::Value& newsElement)
{
   newsElement["titulo"] = news->getSubject();
   for (auto& paragraph : news->getParagraphs())
      newsElement["parrafos"].append(paragraph);

}

void JsonClusterWriter::addTwitterNews(const TwitterNews* news, Json::Value& newsElement)
{
   newsElement["id"] = news->getId();
   newsElement["usuario"] = news->getUser();
   newsElement["tuit"] = news->getSubject();
}

void JsonClusterWriter::writeToJson()
{
   Json::StreamWriterBuilder builder;
   builder["commentStyle"] = "None";
   builder["indentation"] = "   ";
   std::unique_ptr<Json::StreamWriter> writer(
      builder.newStreamWriter());
   writer->write(root, &file);
   file << std::endl;
}

void JsonClusterWriter::visit(const NewspaperNews* news)
{
   typeOfNews = TypeOfNews::newspaperNews;
}

void JsonClusterWriter::visit(const TwitterNews* news)
{
   typeOfNews = TypeOfNews::twitterNews;
}

