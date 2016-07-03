#ifndef NEWSREADERMOCK_H_
#define NEWSREADERMOCK_H_

#include "NewsReader.h"

#include <vector>
#include "gmock/gmock.h"
#include "NewsCluster.h"

class NewsReaderMock final : public NewsReader
{
public:
   MOCK_CONST_METHOD0(getNews, std::vector<NewsCluster>());
};

#endif
