
#include "ClusterizerFactory.h"

#include "ExclusionListFromFile.h"
#include "MostMentionedEntityClusteringCriterion.h"
#include "ThematicSimilarityClusteringCriterion.h"
#include "NewsReaderFromPlainText.h"
#include "PlainTextClusterWriter.h"

ClusterizerFactory::ClusterizerFactory(const ClusterizerOptions& clusterizerOptions)
   : clusterizerOptions(clusterizerOptions), exclusionList(nullptr),
   clusteringCriterion(nullptr), newsReader(nullptr), clusterWriter(nullptr)
{
}

ClusterizerFactory::~ClusterizerFactory()
{
   delete exclusionList;
   delete clusteringCriterion;
   delete newsReader;
   delete clusterWriter;
}

ClusteringCriterion* ClusterizerFactory::getClusteringCriterion()
{
   if (nullptr == clusteringCriterion)
   {
      if (ClusteringCriterionOption::MostMentionedEntity ==
         clusterizerOptions.clusteringCriterionOption)
         clusteringCriterion = new MostMentionedEntityClusteringCriterion();
      else
         clusteringCriterion = new ThematicSimilarityClusteringCriterion();
   }

   return clusteringCriterion;
}

NewsReader* ClusterizerFactory::getNewsReader()
{
   if (nullptr == exclusionList)
      exclusionList = new ExclusionListFromFile(clusterizerOptions.exclusionListFile);
   if (nullptr == newsReader)
      newsReader = new NewsReaderFromPlainText(clusterizerOptions.inputDirectory, *exclusionList);
   return newsReader;
}

ClusterWriter* ClusterizerFactory::getClusterWriter()
{
   if (nullptr == clusterWriter)
      clusterWriter = new PlainTextClusterWriter(clusterizerOptions.outputFile);
   return clusterWriter;
}
