
#include "ClusterizerOptionParser.h"

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <cstring>

ClusterizerOptionParser::ClusterizerOptionParser(int numArgs, char** args)
   : clusterizerOptions()
{
   parseOptions(numArgs, args);
}

ClusterizerOptionParser::~ClusterizerOptionParser()
{
}

ClusterizerOptions ClusterizerOptionParser::getClusterizerOptions() const
{
   return clusterizerOptions;
}

void ClusterizerOptionParser::parseOptions(int numArgs, char** args)
{
   int opt;
   while ((opt = getopt(numArgs, args, "e:c:i:o:h")) != -1)
   {
      switch(opt)
      {
      case 'e':
         hasValidArgument(optarg);
         clusterizerOptions.exclusionListFile = optarg;
         break;
      case 'c':
         hasValidArgument(optarg);
         parseClusteringCriterion(optarg);
         break;
      case 'i':
         hasValidArgument(optarg);
         clusterizerOptions.inputDirectory = optarg;
         break;
      case 'o':
         hasValidArgument(optarg);
         clusterizerOptions.outputFile = optarg;
         break;
      case 'h':
         showHelp();
         exit(0);
      case '?':
      default:
         std::cerr << "Unknown option." << std::endl;
         showHelp();
         exit(1);
      }
   }
   // Reset getopts in case parseOptions() is called multiple times during
   // the same execution. For example, getopts() is called several times in
   // ClusterizerOptionParserTestSuite (Once per test case)
   optind = 0;
}

void ClusterizerOptionParser::hasValidArgument(char* arg) const
{
   if (*arg == '-')
   {
      std::cerr << "Invalid argument." << std::endl;
      showHelp();
      exit(1);
   }
}

void ClusterizerOptionParser::parseClusteringCriterion(char* option)
{
   if (not(strcmp("mostmentioned", option)))
      clusterizerOptions.clusteringCriterionOption =
         ClusteringCriterionOption::MostMentionedEntity;
   else if (not(strcmp("thematicsimilarity", option)))
      clusterizerOptions.clusteringCriterionOption =
         ClusteringCriterionOption::ThematicSimilarity;
   else
   {
      std::cerr << "Invalid clustering criterion option." << std::endl;
      showHelp();
      exit(1);
   }
}

void ClusterizerOptionParser::showHelp() const
{
   std::cout << "Usage: newsClustering -e <exclusionListFile> -i <inputDirectory> "
      "-o <outputFile> [-c <clusteringCriterion> -h]" << std::endl;
   std::cout << "Where:" << std::endl;
   std::cout << "-e <exclusionListFile> -> List with the words to be ignored during "
      "the analysis." << std::endl;
   std::cout << "-i <inputDirectory> -> Directory where the news are located." << std::endl;
   std::cout << "-o <outputFile> -> File where the results of the clustering are dumped." << std::endl;
   std::cout << "-c <clusteringCriterion> - Optional attribute. It should be followed by:" << std::endl;
   std::cout << std::setfill(' ') << std::setw(10) << " "
      << "mostmentioned -> Most mentioned entity criterion." << std::endl;
   std::cout << std::setfill(' ') << std::setw(10) << " "
      << "thematicsimilarity -> Thematic similarity criterion." << std::endl;
   std::cout << "-h -> Shows this help" << std::endl;
}

