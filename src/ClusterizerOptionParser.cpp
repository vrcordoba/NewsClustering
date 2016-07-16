
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
   bool thereIsSomethingToAnalyze = false;
   bool exclusionListSet = false;
   bool outputFileSet = false;
   int opt;
   while ((opt = getopt(numArgs, args, "e:c:n:t:o:h")) != -1)
   {
      switch(opt)
      {
      case 'e':
         hasValidArgument(optarg);
         clusterizerOptions.exclusionListFile = optarg;
         exclusionListSet = true;
         break;
      case 'c':
         hasValidArgument(optarg);
         parseClusteringCriterion(optarg);
         break;
      case 'n':
         hasValidArgument(optarg);
         clusterizerOptions.newsDirectory = optarg;
         thereIsSomethingToAnalyze = true;
         break;
      case 't':
         hasValidArgument(optarg);
         clusterizerOptions.tuitsFile = optarg;
         thereIsSomethingToAnalyze = true;
         break;
      case 'o':
         hasValidArgument(optarg);
         clusterizerOptions.outputFile = optarg;
         outputFileSet = true;
         break;
      case 'h':
         showHelp();
         exit(0);
      case '?':
      default:
         showErrorHelpAndClose("Unknown option.");
      }
   }
   // Reset getopts in case parseOptions() is called multiple times during
   // the same execution. For example, getopts() is called several times in
   // ClusterizerOptionParserTestSuite (Once per test case)
   optind = 0;

   if (not thereIsSomethingToAnalyze)
      showErrorHelpAndClose("No news or tuits to analize.");

   if (not exclusionListSet)
      showErrorHelpAndClose("No exclusion list set.");

   if (not outputFileSet)
      showErrorHelpAndClose("No output file set.");
}

void ClusterizerOptionParser::hasValidArgument(char* arg) const
{
   if (*arg == '-')
      showErrorHelpAndClose("Invalid argument.");
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
      showErrorHelpAndClose("Invalid clustering criterion option.");
}

void ClusterizerOptionParser::showErrorHelpAndClose(const std::string& error) const
{
   std::cerr << error << std::endl;
   showHelp();
   exit(1);
}

void ClusterizerOptionParser::showHelp() const
{
   std::cout << "Usage: newsClustering -e <exclusionListFile> -n <newsDirectory> "
      "-t <tuitsFile> -o <outputFile> [-c <clusteringCriterion> -h]" << std::endl;
   std::cout << "Where:" << std::endl;
   std::cout << "-e <exclusionListFile> -> List with the words to be ignored during "
      "the analysis." << std::endl;
   std::cout << "-n <newsDirectory> -> Directory where the news are located." << std::endl;
   std::cout << "-t <tuitsFile> -> File where the tuits are located." << std::endl;
   std::cout << "-o <outputFile> -> File where the results of the clustering are dumped." << std::endl;
   std::cout << "-c <clusteringCriterion> - Optional attribute. It should be followed by:" << std::endl;
   std::cout << std::setfill(' ') << std::setw(10) << " "
      << "mostmentioned -> Most mentioned entity criterion." << std::endl;
   std::cout << std::setfill(' ') << std::setw(10) << " "
      << "thematicsimilarity -> Thematic similarity criterion." << std::endl;
   std::cout << "-h -> Shows this help" << std::endl;
}

