#ifndef NEWSMOCK_H_
#define NEWSMOCK_H_

#include "gmock/gmock.h"

#include <vector>
#include <string>
#include <set>
#include "News.h"
#include "NewsDiscriminator.h"

class NewsMock final : public News
{
public:
   MOCK_METHOD0(getMostMentionedEntity, std::string());
   MOCK_CONST_METHOD0(getMentionedEntities, std::set<std::string>());
   MOCK_CONST_METHOD0(getSubject, std::string());
   MOCK_METHOD1(setMentionedEntities, void(const std::vector<std::string>&));
   MOCK_METHOD1(setSubject, void(const std::string&));
   MOCK_CONST_METHOD1(isContainedInSubject, bool(const std::string& word));
   MOCK_CONST_METHOD0(getRelevantEntities, std::set<std::string>());
   MOCK_CONST_METHOD1(isContainedInRelevantEntities, bool(const std::string& word));

   MOCK_CONST_METHOD1(accept, void(NewsDiscriminator* newsDiscriminator));
};

#endif
