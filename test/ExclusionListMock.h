#ifndef EXCLUSIONLISTMOCK_H_
#define EXCLUSIONLISTMOCK_H_

#include "ExclusionList.h"
#include "gmock/gmock.h"

class ExclusionListMock : public ExclusionList
{
public:
   MOCK_CONST_METHOD1(isWordInExclusionList, bool(const std::string& word));
};

#endif
