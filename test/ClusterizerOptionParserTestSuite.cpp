
#include "gmock/gmock.h"
#include "ClusterizerOptionParser.h"
#include "ClusterizerOptions.h"

TEST(ClusterizerOptionParserTestSuite, setExclusionListFile)
{
   char const* input[] = {"./newsClustering", "-e", "exclusionListFile.txt", "-t", "tuits.json",
      "-o", "/tmp/OutputFile.txt"};
   ClusterizerOptionParser optionParser(sizeof(input) / sizeof(char const*), const_cast<char**>(input));
   EXPECT_THAT(optionParser.getClusterizerOptions().exclusionListFile,
      ::testing::Eq("exclusionListFile.txt"));
}

TEST(ClusterizerOptionParserTestSuite, defaultClusteringCriterion)
{
   char const* input[] = {"./newsClustering", "-e", "exclusionListFile.txt", "-t", "tuits.json",
      "-o", "/tmp/OutputFile.txt"};
   ClusterizerOptionParser optionParser(sizeof(input) / sizeof(char const*), const_cast<char**>(input));
   EXPECT_THAT(optionParser.getClusterizerOptions().clusteringCriterionOption,
      ::testing::Eq(ClusteringCriterionOption::MostMentionedEntity));
}

TEST(ClusterizerOptionParserTestSuite, setClusteringCriterion)
{
   char const* input[] = {"./newsClustering", "-e", "exclusionListFile.txt", "-c", "thematicsimilarity",
      "-t", "tuits.json", "-o", "/tmp/OutputFile.txt"};
   ClusterizerOptionParser optionParser(sizeof(input) / sizeof(char const*), const_cast<char**>(input));
   EXPECT_THAT(optionParser.getClusterizerOptions().clusteringCriterionOption,
      ::testing::Eq(ClusteringCriterionOption::ThematicSimilarity));
}

TEST(ClusterizerOptionParserTestSuite, setNewsDirectory)
{
   char const* input[] = {"./newsClustering", "-e", "exclusionListFile.txt", "-n", "/tmp/inputDir",
      "-o", "/tmp/OutputFile.txt"};
   ClusterizerOptionParser optionParser(sizeof(input) / sizeof(char const*), const_cast<char**>(input));
   EXPECT_THAT(optionParser.getClusterizerOptions().newsDirectory,
      ::testing::Eq("/tmp/inputDir"));
}

TEST(ClusterizerOptionParserTestSuite, setTuitsFile)
{
   char const* input[] = {"./newsClustering", "-e", "exclusionListFile.txt", "-t", "tuits.json",
      "-o", "/tmp/OutputFile.txt"};
   ClusterizerOptionParser optionParser(sizeof(input) / sizeof(char const*), const_cast<char**>(input));
   EXPECT_THAT(optionParser.getClusterizerOptions().tuitsFile,
      ::testing::Eq("tuits.json"));
}

TEST(ClusterizerOptionParserTestSuite, setOutputFile)
{
   char const* input[] = {"./newsClustering", "-e", "exclusionListFile.txt", "-o", "/tmp/OutputFile.txt",
      "-t", "tuits.json", "-o", "/tmp/OutputFile.txt"};
   ClusterizerOptionParser optionParser(sizeof(input) / sizeof(char const*), const_cast<char**>(input));
   EXPECT_THAT(optionParser.getClusterizerOptions().outputFile,
      ::testing::Eq("/tmp/OutputFile.txt"));
}

TEST(ClusterizerOptionParserTestSuite, setAllOptions)
{
   char const* input[] = {"./newsClustering", "-e", "exclusionListFile.txt",
      "-c", "thematicsimilarity", "-n", "/tmp/inputDir", "-t", "tuits.json", "-o", "/tmp/OutputFile.txt"};
   ClusterizerOptionParser optionParser(sizeof(input) / sizeof(char const*), const_cast<char**>(input));
   EXPECT_THAT(optionParser.getClusterizerOptions().exclusionListFile,
      ::testing::Eq("exclusionListFile.txt"));
   EXPECT_THAT(optionParser.getClusterizerOptions().clusteringCriterionOption,
      ::testing::Eq(ClusteringCriterionOption::ThematicSimilarity));
   EXPECT_THAT(optionParser.getClusterizerOptions().newsDirectory,
      ::testing::Eq("/tmp/inputDir"));
   EXPECT_THAT(optionParser.getClusterizerOptions().tuitsFile,
      ::testing::Eq("tuits.json"));
   EXPECT_THAT(optionParser.getClusterizerOptions().outputFile,
      ::testing::Eq("/tmp/OutputFile.txt"));
}
