
#include "gmock/gmock.h"
#include "ClusterizerOptionParser.h"
#include "ClusterizerOptions.h"

TEST(ClusterizerOptionParserTestSuite, setExclusionListFile)
{
   char const* input[] = {"./newsClustering", "-e", "exclusionListFile.txt"};
   ClusterizerOptionParser optionParser(sizeof(input) / sizeof(char const*), const_cast<char**>(input));
   EXPECT_THAT(optionParser.getClusterizerOptions().exclusionListFile,
      ::testing::Eq("exclusionListFile.txt"));
}

TEST(ClusterizerOptionParserTestSuite, defaultClusteringCriterion)
{
   char const* input[] = {"./newsClustering", "-e", "exclusionListFile.txt"};
   ClusterizerOptionParser optionParser(sizeof(input) / sizeof(char const*), const_cast<char**>(input));
   EXPECT_THAT(optionParser.getClusterizerOptions().clusteringCriterionOption,
      ::testing::Eq(ClusteringCriterionOption::MostMentionedEntity));
}

TEST(ClusterizerOptionParserTestSuite, setClusteringCriterion)
{
   char const* input[] = {"./newsClustering", "-c", "thematicsimilarity"};
   ClusterizerOptionParser optionParser(sizeof(input) / sizeof(char const*), const_cast<char**>(input));
   EXPECT_THAT(optionParser.getClusterizerOptions().clusteringCriterionOption,
      ::testing::Eq(ClusteringCriterionOption::ThematicSimilarity));
}

TEST(ClusterizerOptionParserTestSuite, setInputDirectory)
{
   char const* input[] = {"./newsClustering", "-i", "/tmp/inputDir"};
   ClusterizerOptionParser optionParser(sizeof(input) / sizeof(char const*), const_cast<char**>(input));
   EXPECT_THAT(optionParser.getClusterizerOptions().inputDirectory,
      ::testing::Eq("/tmp/inputDir"));
}

TEST(ClusterizerOptionParserTestSuite, setOutputFile)
{
   char const* input[] = {"./newsClustering", "-o", "/tmp/OutputFile.txt"};
   ClusterizerOptionParser optionParser(sizeof(input) / sizeof(char const*), const_cast<char**>(input));
   EXPECT_THAT(optionParser.getClusterizerOptions().outputFile,
      ::testing::Eq("/tmp/OutputFile.txt"));
}

TEST(ClusterizerOptionParserTestSuite, setAllOptions)
{
   char const* input[] = {"./newsClustering", "-e", "exclusionListFile.txt",
      "-c", "thematicsimilarity", "-i", "/tmp/inputDir", "-o", "/tmp/OutputFile.txt"};
   ClusterizerOptionParser optionParser(sizeof(input) / sizeof(char const*), const_cast<char**>(input));
   EXPECT_THAT(optionParser.getClusterizerOptions().exclusionListFile,
      ::testing::Eq("exclusionListFile.txt"));
   EXPECT_THAT(optionParser.getClusterizerOptions().clusteringCriterionOption,
      ::testing::Eq(ClusteringCriterionOption::ThematicSimilarity));
   EXPECT_THAT(optionParser.getClusterizerOptions().inputDirectory,
      ::testing::Eq("/tmp/inputDir"));
   EXPECT_THAT(optionParser.getClusterizerOptions().outputFile,
      ::testing::Eq("/tmp/OutputFile.txt"));
}
