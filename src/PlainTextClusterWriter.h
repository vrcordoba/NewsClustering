#ifndef PLAINTEXTCLUSTERWRITER_H_
#define PLAINTEXTCLUSTERWRITER_H_

#include "ClusterWriter.h"

#include <vector>
#include <string>
#include "NewsCluster.h"

class PlainTextClusterWriter final : public ClusterWriter
{
public:
   explicit PlainTextClusterWriter(const std::string& destination);
   ~PlainTextClusterWriter();

   void write(const std::vector<NewsCluster>& newsClusters);

private:
   void writeCluster(const NewsCluster& newsCluster);
};

#endif
