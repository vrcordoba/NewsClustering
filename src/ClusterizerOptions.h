#ifndef CLUSTERIZEROPTIONS_H_
#define CLUSTERIZEROPTIONS_H_

#include <cstdint>
#include <string>

enum class ClusteringCriterionOption : std::uint8_t
{
   MostMentionedEntity,
   ThematicSimilarity
};

enum class ClusteringOutput : std::uint8_t
{
   PlainFile,
   JsonFile
};

class ClusterizerOptions final
{
public:
   ClusterizerOptions() :
      exclusionListFile(),
      newsDirectory(),
      tuitsFile(),
      outputFile(),
      clusteringCriterionOption(ClusteringCriterionOption::MostMentionedEntity),
      clusteringOutput(ClusteringOutput::PlainFile) {}

   std::string exclusionListFile;
   std::string newsDirectory;
   std::string tuitsFile;
   std::string outputFile;
   ClusteringCriterionOption clusteringCriterionOption;
   ClusteringOutput clusteringOutput;
};

#endif
