#ifndef CLUSTERINGCRITERIONMOCK_H_
#define CLUSTERINGCRITERIONMOCK_H_

#include "ClusteringCriterion.h"

#include "gmock/gmock.h"

class NewsCluster;

class ClusteringCriterionMock final : public ClusteringCriterion
{
public:
   MOCK_CONST_METHOD2(areBothInTheSameCluster, bool(NewsCluster& clusterA, NewsCluster& clusterB));
};

#endif
