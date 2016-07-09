#ifndef CLUSTERIZEROPTIONPARSER_H_
#define CLUSTERIZEROPTIONPARSER_H_

#include "ClusterizerOptions.h"

class ClusterizerOptionParser final
{
public:
   ClusterizerOptionParser(int numArgs, char** args);
   ~ClusterizerOptionParser();

   ClusterizerOptions getClusterizerOptions() const;
   void showHelp() const;

private:
   void parseOptions(int numArgs, char** args);
   void parseClusteringCriterion(char* option);
   void hasValidArgument(char* arg) const;

   ClusterizerOptions clusterizerOptions;
};

#endif
