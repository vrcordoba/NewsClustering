#ifndef NEWSMOCK_H_
#define NEWSMOCK_H_

#include <vector>
#include <string>
#include <set>
#include "News.h"
#include "gmock/gmock.h"

class NewsMock final : public News
{
public:
   MOCK_METHOD0(getMostMentionedEntity, std::string());
   MOCK_CONST_METHOD0(getHeadline, std::string());
   MOCK_METHOD1(setMentionedEntities, void(const std::vector<std::string>&));
   MOCK_METHOD1(setHeadline, void(const std::string&));
   MOCK_CONST_METHOD1(isContainedInHeadline, bool(const std::string& word));

   // TODO: Remove these methods when ThematicSimilarityClusteringCriterion is adapted
   // to handle NewspaperNews and TwitterNews
   MOCK_CONST_METHOD0(getRelevantEntities, std::set<std::string>());
   MOCK_CONST_METHOD1(isContainedInRelevantEntities, bool(const std::string& word));
};

#endif
