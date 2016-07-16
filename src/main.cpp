
#include "Clusterizer.h"
#include "ClusterizerOptionParser.h"
#include "ClusterizerFactory.h"
#include "ClusteringCriterion.h"
#include "ClusterWriter.h"
#include "Reader.h"

int main(int argc, char** argv)
{
   ClusterizerOptionParser optionsParser(argc, argv);
   ClusterizerFactory clusterizerFactory = ClusterizerFactory::getInstance(
      optionsParser.getClusterizerOptions());
   ClusteringCriterion* clusteringCriterion = clusterizerFactory.getClusteringCriterion();
   Reader* newsReader = clusterizerFactory.getNewsReader();
   Reader* tuitsReader = clusterizerFactory.getTuitsReader();

   Clusterizer clusterizer;
   clusterizer.setCriterion(clusteringCriterion);
   clusterizer.setNewsReader(newsReader);
   clusterizer.setTuitsReader(tuitsReader);
   clusterizer.obtainClusters();

   ClusterWriter* writer = clusterizerFactory.getClusterWriter();
   writer->write(clusterizer.getClusters());
}
