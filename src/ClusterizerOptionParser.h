#ifndef CLUSTERIZEROPTIONPARSER_H_
#define CLUSTERIZEROPTIONPARSER_H_

#include "ClusterizerOptions.h"

class ClusterizerOptionParser final
{
public:
   ClusterizerOptionParser(int numArgs, char** args);
   ~ClusterizerOptionParser();

   ClusterizerOptions getClusterizerOptions() const;

   static const char* const plainTextExtension;
   static const char* const jsonExtension;

private:
   void showHelp() const;
   void showErrorHelpAndClose(const std::string& error) const;
   void parseOptions(int numArgs, char** args);
   void parseClusteringCriterion(char* option);
   void parseClusteringOutput(char* option);
   void hasValidArgument(char* arg) const;

   ClusterizerOptions clusterizerOptions;
};

#endif
