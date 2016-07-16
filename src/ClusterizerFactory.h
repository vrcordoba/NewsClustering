#ifndef CLUSTERIZERFACTORY_H_
#define CLUSTERIZERFACTORY_H_

#include "ClusterizerOptions.h"

class ExclusionList;
class ClusteringCriterion;
class Reader;
class ClusterWriter;

class ClusterizerFactory final
{
public:
   static ClusterizerFactory& getInstance(const ClusterizerOptions& options)
   {
      static ClusterizerFactory instance(options);
      return instance;
   }
   ~ClusterizerFactory();

   ClusteringCriterion* getClusteringCriterion();
   Reader* getNewsReader();
   Reader* getTuitsReader();
   ClusterWriter* getClusterWriter();

private:
   explicit ClusterizerFactory(const ClusterizerOptions& clusterizerOptions);

   const ClusterizerOptions clusterizerOptions;
   ExclusionList* exclusionList;
   ClusteringCriterion* clusteringCriterion;
   Reader* newsReader;
   Reader* tuitsReader;
   ClusterWriter* clusterWriter;
};

#endif
