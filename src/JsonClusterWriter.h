#ifndef JSONCLUSTERWRITER_H_
#define JSONCLUSTERWRITER_H_

#include "ClusterWriter.h"
#include "NewsVisitor.h"

class NewspaperNews;
class TwitterNews;

class JsonClusterWriter final : public ClusterWriter, public NewsVisitor
{
public:
   JsonClusterWriter();
   ~JsonClusterWriter();

   void write(const std::vector<NewsCluster>& newsClusters);

   void visit(const NewspaperNews* news);
   void visit(const TwitterNews* news);
};

#endif
