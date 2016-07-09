
#include "Clusterizer.h"
#include "ExclusionListFromFile.h"
#include "ThematicSimilarityClusteringCriterion.h"
#include "NewsReaderFromPlainText.h"
#include "PlainTextClusterWriter.h"

int main()
{
   ExclusionListFromFile exclusionList("../data/ES_stopList.txt");
   ThematicSimilarityClusteringCriterion mostMentionedEntityCriterion;
   NewsReaderFromPlainText newsReaderFromPlainText("../data/news", exclusionList);
   Clusterizer clusterizer;

   clusterizer.setCriterion(&mostMentionedEntityCriterion);
   clusterizer.setNewsReader(&newsReaderFromPlainText);

   clusterizer.obtainClusters();

   PlainTextClusterWriter writer("/tmp/clusterResult.txt");
   writer.write(clusterizer.getClusters());
}
