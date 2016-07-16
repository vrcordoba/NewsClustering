#ifndef NEWSREADERMOCK_H_
#define NEWSREADERMOCK_H_

#include "gmock/gmock.h"

#include <vector>
#include "Reader.h"
#include "NewsCluster.h"

class NewsReaderMock final : public Reader
{
public:
   MOCK_CONST_METHOD0(getNews, std::vector<std::shared_ptr<News>>());
};

#endif
