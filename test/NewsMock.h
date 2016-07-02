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
   MOCK_METHOD1(setMentionedEntities, void(std::vector<std::string>));
};

#endif
