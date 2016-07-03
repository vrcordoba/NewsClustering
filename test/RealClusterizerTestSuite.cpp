
#include "gmock/gmock.h"

#include <vector>
#include <set>
#include <string>
#include <iostream>
#include "Clusterizer.h"
#include "MostMentionedEntityClusteringCriterion.h"
#include "ExclusionListFromFile.h"
#include "NewsReaderFromPlainText.h"
#include "NewsCluster.h"

class RealClusterizerTestSuite : public ::testing::Test
{
protected:
   RealClusterizerTestSuite() : exclusionList("../data/ES_stopList.txt") {}

   Clusterizer clusterizer;
   ExclusionListFromFile exclusionList;
};

TEST_F(RealClusterizerTestSuite, mostMentionedEntityCriterionNewsReaderFromPlainText)
{
   MostMentionedEntityClusteringCriterion mostMentionedEntityCriterion;
   NewsReaderFromPlainText newsReaderFromPlainText("../data/news", exclusionList);
   clusterizer.setCriterion(&mostMentionedEntityCriterion);
   clusterizer.setNewsReader(&newsReaderFromPlainText);

   clusterizer.obtainClusters();

   std::vector<NewsCluster> obtainedResult = clusterizer.getClusters();
   EXPECT_THAT(obtainedResult.size(), ::testing::Eq(27));

   std::set<std::string> expectedMentionedEntities{u8"Rhys", u8"Liverpool", u8"Policía",
      u8"Jones", u8"Chávez", u8"FARC", u8"Irak", u8"Princesa", u8"Diana", u8"Guatemala",
      u8"Pérez", u8"Nacional", u8"Iglesia", u8"PJD", u8"Justicia", u8"Nacional",
      u8"Gobierno", u8"Marruecos", u8"Istiqlal", u8"Bhutto", u8"Pakistán", u8"Sharif",
      u8"Fatah", u8"Bared", u8"Líbano", u8"Cuba", u8"México", u8"Dean"};
   for (auto& newsCluster : obtainedResult)
   {
      std::string obtainedMostMentionedEntity = (*newsCluster.begin())->getMostMentionedEntity();
      std::set<std::string>::iterator it = expectedMentionedEntities.find(obtainedMostMentionedEntity);
      if (expectedMentionedEntities.end() == it)
      {
         std::cout << obtainedMostMentionedEntity << " not found" << std::endl;
         EXPECT_TRUE(false);
      }
      else
      {
         expectedMentionedEntities.erase(it);
      }
   }
   if (not expectedMentionedEntities.empty())
   {
      EXPECT_TRUE(false);
      for (auto& notObtained : expectedMentionedEntities)
      {
         std::cout << notObtained << " ";
      }
      std::cout << "not obtained" << std::endl;
   }
}
