#ifndef NEWSMOCK_H_
#define NEWSMOCK_H_

#include <vector>
#include <string>
#include "News.h"
#include "gmock/gmock.h"

class NewsMock final : public News
{
public:
   MOCK_METHOD0(getMostMentionedEntity, std::string());
   MOCK_CONST_METHOD0(getTitle, std::string());
   MOCK_METHOD1(setMentionedEntities, void(const std::vector<std::string>&));
   MOCK_METHOD1(setTitle, void(const std::string&));
};

#endif
