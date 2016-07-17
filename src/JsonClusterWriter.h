#ifndef JSONCLUSTERWRITER_H_
#define JSONCLUSTERWRITER_H_

#include "ClusterWriter.h"
#include "NewsVisitor.h"

#include "JsonCpp/json/json.h"
#include "NewsCluster.h"
#include "TypeOfNews.h"

class NewspaperNews;
class TwitterNews;

class JsonClusterWriter final : public ClusterWriter, public NewsVisitor
{
public:
   explicit JsonClusterWriter(const std::string& destination);
   ~JsonClusterWriter();

   void write(const std::vector<NewsCluster>& newsClusters);

   void visit(const NewspaperNews* news);
   void visit(const TwitterNews* news);

private:
   void addSubject(const NewsCluster& newsCluster, Json::Value& cluster);
   void addEntities(const NewsCluster& newsCluster, Json::Value& cluster);
   void addNews(const NewsCluster& newsCluster, Json::Value& cluster);
   void addNewspaperNews(const NewspaperNews* news, Json::Value& newsElement);
   void addTwitterNews(const TwitterNews* news, Json::Value& newsElement);
   void writeToJson();

   Json::Value root;
   TypeOfNews typeOfNews;
};

#endif
