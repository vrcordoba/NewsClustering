#ifndef CLUSTERWRITER_H_
#define CLUSTERWRITER_H_

#include <vector>
#include <fstream>
#include "NewsCluster.h"

class ClusterWriter
{
public:
   explicit ClusterWriter(const std::string& destination);
   virtual ~ClusterWriter();

   virtual void write(const std::vector<NewsCluster>& newsClusters) = 0;

protected:
   std::ofstream file;
};

#endif
