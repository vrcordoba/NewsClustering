
#include "ClusterizerFactory.h"

#include "ExclusionListFromFile.h"
#include "MostMentionedEntityClusteringCriterion.h"
#include "ThematicSimilarityClusteringCriterion.h"
#include "NewsReaderFromPlainText.h"
#include "NewsReaderFromTuit.h"
#include "PlainTextClusterWriter.h"

ClusterizerFactory::ClusterizerFactory(const ClusterizerOptions& clusterizerOptions)
   : clusterizerOptions(clusterizerOptions), exclusionList(nullptr),
   clusteringCriterion(nullptr), newsReader(nullptr), tuitsReader(nullptr), clusterWriter(nullptr)
{
}

ClusterizerFactory::~ClusterizerFactory()
{
   delete exclusionList;
   delete clusteringCriterion;
   delete newsReader;
   delete tuitsReader;
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
   if (nullptr == newsReader and not clusterizerOptions.newsDirectory.empty())
      newsReader = new NewsReaderFromPlainText(clusterizerOptions.newsDirectory, *exclusionList);
   return newsReader;
}

NewsReader* ClusterizerFactory::getTuitsReader()
{
   if (nullptr == exclusionList)
      exclusionList = new ExclusionListFromFile(clusterizerOptions.exclusionListFile);
   if (nullptr == tuitsReader and not clusterizerOptions.tuitsFile.empty())
      tuitsReader = new NewsReaderFromTuit(clusterizerOptions.tuitsFile, *exclusionList);
   return tuitsReader;
}

ClusterWriter* ClusterizerFactory::getClusterWriter()
{
   if (nullptr == clusterWriter)
      clusterWriter = new PlainTextClusterWriter(clusterizerOptions.outputFile);
   return clusterWriter;
}
