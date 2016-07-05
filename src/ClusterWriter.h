#ifndef CLUSTERWRITER_H_
#define CLUSTERWRITER_H_

#include <vector>
#include "NewsCluster.h"

class ClusterWriter
{
public:
   virtual ~ClusterWriter() {};

   virtual void write(const std::vector<NewsCluster>& newsClusters) = 0;
};

#endif
