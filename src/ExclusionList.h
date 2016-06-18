#ifndef EXCLUSIONLIST_H_
#define EXCLUSIONLIST_H_

#include <string>

class ExclusionList
{
public:
   virtual ~ExclusionList() {};
   virtual bool isWordInExclusionList(const std::string& word) const = 0;
};

#endif
