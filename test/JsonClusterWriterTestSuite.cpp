
#include "gmock/gmock.h"

#include <fstream>
#include <memory>
#include "JsonClusterWriter.h"
#include "InvalidLocationException.h"
#include "NewspaperNews.h"
#include "TwitterNews.h"
#include "ExclusionListMock.h"

class JsonClusterWriterTestSuite : public ::testing::Test
{
protected:
   JsonClusterWriterTestSuite() : destinationFile("/tmp/ClusterWriterTest.json") {}

   virtual void TearDown()
   {
      std::remove(destinationFile.c_str());
   }

   void verifyResult(std::ifstream& file, const std::vector<std::string>&
      expectedResult)
   {
      std::string obtainedLine;
      for (std::size_t i = 0; i < expectedResult.size(); ++i)
      {
         std::getline(file, obtainedLine);
         EXPECT_THAT(obtainedLine, ::testing::Eq(expectedResult[i]));
      }
      std::getline(file, obtainedLine);
      EXPECT_TRUE(file.eof());
   }

   ExclusionListMock exclusionList;
   std::string destinationFile;
};

TEST_F(JsonClusterWriterTestSuite, nonValidDirectory)
{
   EXPECT_THROW(JsonClusterWriter clusterWriter("/wrong_directory/ClusterWriterTest.json"),
      InvalidLocationException);
}

TEST_F(JsonClusterWriterTestSuite, noClustersToPrint)
{
   std::vector<NewsCluster> newsClusters;
   JsonClusterWriter clusterWriter(destinationFile);

   clusterWriter.write(newsClusters);

   std::ifstream file(destinationFile);
      std::vector<std::string> expectedResult{
         "{",
         "   \"grupos\" : []",
         "}"};
      verifyResult(file, expectedResult);
}

TEST_F(JsonClusterWriterTestSuite, onlyOneClusterSeveralNewspaperNews)
{
   NewspaperNews* newsA = new NewspaperNews(exclusionList);
   std::shared_ptr<News> ptrNewsA(newsA);
   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(3).WillRepeatedly(::testing::Return(false));
   newsA->setSubject("This is the A news");
   std::vector<std::string> mentionedEntitiesA{"One", "Two", "Three"};
   newsA->setMentionedEntities(mentionedEntitiesA);
   newsA->addParagraph("One.");
   newsA->addParagraph("Two.");
   newsA->addParagraph("Three.");

   NewspaperNews* newsB = new NewspaperNews(exclusionList);
   std::shared_ptr<News> ptrNewsB(newsB);
   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(3).WillRepeatedly(::testing::Return(false));
   newsB->setSubject("This is the B news");
   std::vector<std::string> mentionedEntitiesB{"Three", "Four", "Five"};
   newsB->setMentionedEntities(mentionedEntitiesB);
   newsB->addParagraph("Three.");
   newsB->addParagraph("Four.");
   newsB->addParagraph("Five.");

   NewsCluster newsCluster;
   newsCluster.addNews(ptrNewsA);
   newsCluster.addNews(ptrNewsB);
   std::vector<NewsCluster> newsClusters{newsCluster};
   JsonClusterWriter clusterWriter(destinationFile);

   clusterWriter.write(newsClusters);

   std::ifstream file(destinationFile);
   std::vector<std::string> expectedResult{
      "{",
      "   \"grupos\" : ",
      "   [",
      "      {",
      "         \"elementos\" : ",
      "         [",
      "            {",
      "               \"parrafos\" : [ \"One.\", \"Two.\", \"Three.\" ],",
      "               \"titulo\" : \"This is the A news\"",
      "            },",
      "            {",
      "               \"parrafos\" : [ \"Three.\", \"Four.\", \"Five.\" ],",
      "               \"titulo\" : \"This is the B news\"",
      "            }",
      "         ],",
      "         \"entidades\" : [ \"Five\", \"Four\", \"One\", \"Three\", \"Two\" ],",
      "         \"titulo\" : \"This is the A news\"",
      "      }",
      "   ]",
      "}"};
   verifyResult(file, expectedResult);
}

TEST_F(JsonClusterWriterTestSuite, onlyOneClusterSeveralTwitterNews)
{
   TwitterNews* newsA = new TwitterNews(exclusionList);
   std::shared_ptr<News> ptrNewsA(newsA);
   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(4).WillRepeatedly(::testing::Return(false));
   newsA->setSubject("This is the A B C news");
   newsA->setId(1);
   newsA->setUser("FirstUser");

   TwitterNews* newsB = new TwitterNews(exclusionList);
   std::shared_ptr<News> ptrNewsB(newsB);
   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(3).WillRepeatedly(::testing::Return(false));
   newsB->setSubject("This is the D E news");
   newsB->setId(2);
   newsB->setUser("SecondUser");

   NewsCluster newsCluster;
   newsCluster.addNews(ptrNewsA);
   newsCluster.addNews(ptrNewsB);
   std::vector<NewsCluster> newsClusters{newsCluster};
   JsonClusterWriter clusterWriter(destinationFile);

   clusterWriter.write(newsClusters);

   std::ifstream file(destinationFile);
   std::vector<std::string> expectedResult{
      "{",
      "   \"grupos\" : ",
      "   [",
      "      {",
      "         \"elementos\" : ",
      "         [",
      "            {",
      "               \"id\" : 1,",
      "               \"tuit\" : \"This is the A B C news\",",
      "               \"usuario\" : \"FirstUser\"",
      "            },",
      "            {",
      "               \"id\" : 2,",
      "               \"tuit\" : \"This is the D E news\",",
      "               \"usuario\" : \"SecondUser\"",
      "            }",
      "         ],",
      "         \"entidades\" : [ \"A\", \"B\", \"C\", \"D\", \"E\", \"This\" ],",
      "         \"titulo\" : \"This is the A B C news\"",
      "      }",
      "   ]",
      "}"};
   verifyResult(file, expectedResult);
}

TEST_F(JsonClusterWriterTestSuite, onlyOneClusterNewspaperAndTwitterNews)
{
   NewspaperNews* newsA = new NewspaperNews(exclusionList);
   std::shared_ptr<News> ptrNewsA(newsA);
   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(3).WillRepeatedly(::testing::Return(false));
   newsA->setSubject("This is the A news");
   std::vector<std::string> mentionedEntitiesA{"One", "Two", "Three"};
   newsA->setMentionedEntities(mentionedEntitiesA);
   newsA->addParagraph("One.");
   newsA->addParagraph("Two.");
   newsA->addParagraph("Three.");

   TwitterNews* newsB = new TwitterNews(exclusionList);
   std::shared_ptr<News> ptrNewsB(newsB);
   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(3).WillRepeatedly(::testing::Return(false));
   newsB->setSubject("This is the D E news");
   newsB->setId(2);
   newsB->setUser("SecondUser");

   NewsCluster newsCluster;
   newsCluster.addNews(ptrNewsA);
   newsCluster.addNews(ptrNewsB);
   std::vector<NewsCluster> newsClusters{newsCluster};
   JsonClusterWriter clusterWriter(destinationFile);

   clusterWriter.write(newsClusters);

   std::ifstream file(destinationFile);
   std::vector<std::string> expectedResult{
      "{",
      "   \"grupos\" : ",
      "   [",
      "      {",
      "         \"elementos\" : ",
      "         [",
      "            {",
      "               \"parrafos\" : [ \"One.\", \"Two.\", \"Three.\" ],",
      "               \"titulo\" : \"This is the A news\"",
      "            },",
      "            {",
      "               \"id\" : 2,",
      "               \"tuit\" : \"This is the D E news\",",
      "               \"usuario\" : \"SecondUser\"",
      "            }",
      "         ],",
      "         \"entidades\" : [ \"D\", \"E\", \"One\", \"This\", \"Three\", \"Two\" ],",
      "         \"titulo\" : \"This is the A news\"",
      "      }",
      "   ]",
      "}"};
   verifyResult(file, expectedResult);
}

TEST_F(JsonClusterWriterTestSuite, twoClustersNewspaperAndTwitterNews)
{
   NewspaperNews* newsA = new NewspaperNews(exclusionList);
   std::shared_ptr<News> ptrNewsA(newsA);
   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(3).WillRepeatedly(::testing::Return(false));
   newsA->setSubject("This is the A news");
   std::vector<std::string> mentionedEntitiesA{"One", "Two", "Three"};
   newsA->setMentionedEntities(mentionedEntitiesA);
   newsA->addParagraph("One.");
   newsA->addParagraph("Two.");
   newsA->addParagraph("Three.");

   TwitterNews* newsB = new TwitterNews(exclusionList);
   std::shared_ptr<News> ptrNewsB(newsB);
   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(3).WillRepeatedly(::testing::Return(false));
   newsB->setSubject("This is the D E news");
   newsB->setId(1);
   newsB->setUser("FirstUser");

   NewsCluster newsCluster1;
   newsCluster1.addNews(ptrNewsA);
   newsCluster1.addNews(ptrNewsB);

   NewspaperNews* newsC = new NewspaperNews(exclusionList);
   std::shared_ptr<News> ptrNewsC(newsC);
   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(3).WillRepeatedly(::testing::Return(false));
   newsC->setSubject("This is the C news");
   std::vector<std::string> mentionedEntitiesC{"Four", "Five", "Six"};
   newsC->setMentionedEntities(mentionedEntitiesC);
   newsC->addParagraph("Four.");
   newsC->addParagraph("Five.");
   newsC->addParagraph("Six.");

   TwitterNews* newsD = new TwitterNews(exclusionList);
   std::shared_ptr<News> ptrNewsD(newsD);
   EXPECT_CALL(exclusionList, isWordInExclusionList(::testing::_)).Times(3).WillRepeatedly(::testing::Return(false));
   newsD->setSubject("This is the F G news");
   newsD->setId(2);
   newsD->setUser("SecondUser");

   NewsCluster newsCluster2;
   newsCluster2.addNews(ptrNewsC);
   newsCluster2.addNews(ptrNewsD);

   std::vector<NewsCluster> newsClusters{newsCluster1, newsCluster2};
   JsonClusterWriter clusterWriter(destinationFile);

   clusterWriter.write(newsClusters);

   std::ifstream file(destinationFile);
   std::vector<std::string> expectedResult{
      "{",
      "   \"grupos\" : ",
      "   [",
      "      {",
      "         \"elementos\" : ",
      "         [",
      "            {",
      "               \"parrafos\" : [ \"One.\", \"Two.\", \"Three.\" ],",
      "               \"titulo\" : \"This is the A news\"",
      "            },",
      "            {",
      "               \"id\" : 1,",
      "               \"tuit\" : \"This is the D E news\",",
      "               \"usuario\" : \"FirstUser\"",
      "            }",
      "         ],",
      "         \"entidades\" : [ \"D\", \"E\", \"One\", \"This\", \"Three\", \"Two\" ],",
      "         \"titulo\" : \"This is the A news\"",
      "      },",
      "      {",
      "         \"elementos\" : ",
      "         [",
      "            {",
      "               \"parrafos\" : [ \"Four.\", \"Five.\", \"Six.\" ],",
      "               \"titulo\" : \"This is the C news\"",
      "            },",
      "            {",
      "               \"id\" : 2,",
      "               \"tuit\" : \"This is the F G news\",",
      "               \"usuario\" : \"SecondUser\"",
      "            }",
      "         ],",
      "         \"entidades\" : [ \"F\", \"Five\", \"Four\", \"G\", \"Six\", \"This\" ],",
      "         \"titulo\" : \"This is the C news\"",
      "      }",
      "   ]",
      "}"};
   verifyResult(file, expectedResult);
}
