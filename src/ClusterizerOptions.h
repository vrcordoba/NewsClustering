#ifndef CLUSTERIZEROPTIONS_H_
#define CLUSTERIZEROPTIONS_H_

#include <cstdint>
#include <string>

enum class ClusteringCriterionOption : std::uint8_t
{
   MostMentionedEntity,
   ThematicSimilarity
};

class ClusterizerOptions final
{
public:
   ClusterizerOptions() :
      exclusionListFile(),
      inputDirectory(),
      outputFile(),
      clusteringCriterionOption(ClusteringCriterionOption::MostMentionedEntity) {}

   std::string exclusionListFile;
   std::string inputDirectory;
   std::string outputFile;
   ClusteringCriterionOption clusteringCriterionOption;
};

#endif
