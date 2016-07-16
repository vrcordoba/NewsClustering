
#include "gmock/gmock.h"

#include <vector>
#include <set>
#include <string>
#include <iostream>
#include "Clusterizer.h"
#include "MostMentionedEntityClusteringCriterion.h"
#include "ThematicSimilarityClusteringCriterion.h"
#include "ExclusionListFromFile.h"
#include "NewsReaderFromPlainText.h"
#include "NewsReaderFromTuit.h"
#include "NewsCluster.h"

class RealClusterizerTestSuite : public ::testing::Test
{
protected:
   RealClusterizerTestSuite() : exclusionList("../data/ES_stopList.txt") {}

   void checkMostMentionedEntities(const std::vector<NewsCluster>& obtainedResult,
      std::set<std::string>& expectedMentionedEntities)
   {
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

   void checkThematicSimilarity(const std::vector<NewsCluster>& obtainedResult,
      std::vector<std::set<std::string>> expectedResult)
   {
      std::size_t i = 0;
      for (auto& newsCluster : obtainedResult)
      {
         for (auto& news : newsCluster)
         {
            std::set<std::string>::iterator it = expectedResult[i].find(news->getSubject());
            EXPECT_TRUE(it != std::end(expectedResult[i]));
            expectedResult[i].erase(it);
         }
         ++i;
      }
      for (auto& result : expectedResult)
      {
         if (not result.empty())
         {
            EXPECT_TRUE(false);
            for (auto& notObtained : result)
            {
               std::cout << notObtained << " ";
            }
            std::cout << "not obtained" << std::endl;
         }
      }
   }

   Clusterizer clusterizer;
   ExclusionListFromFile exclusionList;
};

TEST_F(RealClusterizerTestSuite, mostMentionedEntityCriterionOnlyNewspaperNews)
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
   checkMostMentionedEntities(obtainedResult, expectedMentionedEntities);
}

TEST_F(RealClusterizerTestSuite, mostMentionedEntityCriterionOnlyTwitterNews)
{
   MostMentionedEntityClusteringCriterion mostMentionedEntityCriterion;
   NewsReaderFromTuit newsReaderFromTuit("../data/tuits.txt", exclusionList);
   clusterizer.setCriterion(&mostMentionedEntityCriterion);
   clusterizer.setTuitsReader(&newsReaderFromTuit);

   clusterizer.obtainClusters();

   std::vector<NewsCluster> obtainedResult = clusterizer.getClusters();
   EXPECT_THAT(obtainedResult.size(), ::testing::Eq(3));

   std::set<std::string> expectedMentionedEntities{u8"Detienen", u8"Liberan", u8"Liverpool"};
   checkMostMentionedEntities(obtainedResult, expectedMentionedEntities);
}

TEST_F(RealClusterizerTestSuite, mostMentionedEntityCriterionNewspaperAndTwitterNews)
{
   MostMentionedEntityClusteringCriterion mostMentionedEntityCriterion;
   NewsReaderFromPlainText newsReaderFromPlainText("../data/news", exclusionList);
   NewsReaderFromTuit newsReaderFromTuit("../data/tuits.txt", exclusionList);
   clusterizer.setCriterion(&mostMentionedEntityCriterion);
   clusterizer.setNewsReader(&newsReaderFromPlainText);
   clusterizer.setTuitsReader(&newsReaderFromTuit);

   clusterizer.obtainClusters();

   std::vector<NewsCluster> obtainedResult = clusterizer.getClusters();
   EXPECT_THAT(obtainedResult.size(), ::testing::Eq(29));

   std::set<std::string> expectedMentionedEntities{u8"Rhys", u8"Liverpool", u8"Policía",
      u8"Jones", u8"Chávez", u8"FARC", u8"Irak", u8"Princesa", u8"Diana", u8"Guatemala",
      u8"Pérez", u8"Nacional", u8"Iglesia", u8"PJD", u8"Justicia", u8"Nacional",
      u8"Gobierno", u8"Marruecos", u8"Istiqlal", u8"Bhutto", u8"Pakistán", u8"Sharif",
      u8"Fatah", u8"Bared", u8"Líbano", u8"Cuba", u8"México", u8"Dean",
      u8"Detienen", u8"Liberan"};
   checkMostMentionedEntities(obtainedResult, expectedMentionedEntities);
}

TEST_F(RealClusterizerTestSuite, thematicSimilarityCriterionOnlyNewspaperNews)
{
   ThematicSimilarityClusteringCriterion mostMentionedEntityCriterion;
   NewsReaderFromPlainText newsReaderFromPlainText("../data/news", exclusionList);
   clusterizer.setCriterion(&mostMentionedEntityCriterion);
   clusterizer.setNewsReader(&newsReaderFromPlainText);

   clusterizer.obtainClusters();

   std::vector<NewsCluster> obtainedResult = clusterizer.getClusters();
   EXPECT_THAT(obtainedResult.size(), ::testing::Eq(8));

   std::vector<std::set<std::string>> expectedResult{
      {
         u8"Liberan a los dos sospechosos detenidos por el asesinato de un niño de 11 años en Liverpool",
         u8"Detienen a seis jóvenes más en relación con el asesinato de el niño de Liverpool",
         u8"Siguen los interrogatorios a los detenidos por el asesinato de el niño de Liverpool",
         u8"Liberan a los dos sospechosos de el asesinato de un niño en Liverpool",
         u8"La policía pone en libertad a los sospechosos de el asesinato de el niño de Liverpool",
         u8"Detienen a otro sospechoso de 15 años por la muerte de el niño de 11 en Liverpool",
         u8"Detenidos cinco menores en relación con el asesinato de el niño de Liverpool",
         u8"Detenidos en Reino Unido dos adolescentes sospechosos de matar de un disparo a un menor"
      },
      {
         u8"Chávez llega a Bogotá para mediar en la liberación de secuestrados por las FARC",
         u8"Chávez llega a Bogotá para entrevistar se con Uribe sobre los secuestrados de las FARC",
         u8"Las FARC rechazan el ofrecimiento de Chávez de liberar rehenes en Venezuela",
         u8"Chávez anuncia ante Álvaro Uribe que recibirá en Venezuela a un enviado de las FARC",
         u8"Chávez se reunirá en Caracas con delegados de las FARC"
      },
      {
         u8"Más de 200 muertos en Irak en el ataque más sangriento desde 2003",
         u8"Buscan supervivientes entre las ruinas de el mayor atentado en Irak desde 2003"
      },
      {
         u8"Camila no irá a el funeral por Diana",
         u8"Numerosos actos recuerdan a Diana a los 10 años de su muerte",
         u8"' La mejor madre de el mundo '"
      },
      {
         u8"Los islamistas moderados acarician la victoria en las elecciones parlamentarias en Marruecos",
         u8"Baja participación en las elecciones marroquíes",
         u8"El Gobierno marroquí prevé que la participación electoral alcance el 41 %",
         u8"Los observadores piden a Rabat acometer reformas para alentar la participación",
         u8"Los nacionalistas Istiqlal ganan las elecciones en Marruecos",
         u8"Asesinan a tiros a dos candidatos locales de el partido de Rigoberta Menchú en Guatemala",
         u8"Los dos principales candidatos a la Presidencia de Guatemala cierran sus campañas",
         u8"Guatemala vota en medio de la peor ola de violencia de las últimas décadas",
         u8"Guatemala inicia la recta final de la campaña electoral",
         u8"Los islamista moderados , favoritos en los comicios legislativos que celebra hoy Marruecos",
         u8"Los marroquíes votan hoy con los islamistas moderados como favoritos"
      },
      {
         u8"La ex primera ministra paquistaní Bhutto anuncia que regresará ' muy pronto ' de el exilio",
         u8"Bhutto anuncia que regresará \" muy pronto \" a Pakistán",
         u8"El Tribunal Supremo permite a Sharif , ex primer ministro de Pakistán , volver de el exilio",
         u8"El ex primer ministro Sharif volverá a Pakistán el 10 de septiembre para medir se a Musharraf"
      },
      {
         u8"a el Fatah refuerza la seguridad en el campo de refugiados palestinos de Ain el Helu",
         u8"Evacuan de Nahr a el Bared a las familias de los milicianos de Fatah a el Islam",
         u8"El Ejército de el Líbano anuncia la muerte en combate de el líder de Fatah a el Islam",
         u8"Líbano toma el control de Naher a el Bared",
         u8"Evacuadas de Nahar a el Bared las familias de los milicianos de Fatah a el Islam",
      },
      {
         u8"Más de 400.000 evacuados en Cuba ante la amenaza de inundaciones por el ' Dean '",
         u8"' Dean ' llega a el Caribe mexicano convertido en un huracán ' potencialmente catastrófico '",
         u8"Las lluvias y vientos devastadores de el Dean se sienten ya en la costa oeste de México",
         u8"El ' Dean ' se debilita y en las próximas horas podría convertir se en tormenta tropical",
         u8"El huracán Dean baja a categoría 1 tras atravesar el Yucatán mexicano",
         u8"' Dean ' deja Yucatán debilitado pero podría fortalecerse en el Golfo de México",
         u8"El huracán Dean podría cobrar fuerza a el volver a las aguas cálidas de el Golfo de México",
         u8"' Dean ' provoca otros tres muertos antes de extinguir se en el interior de México",
         u8"Dean pasa a ser tormenta tropical",
         u8"Dean pierde fuerza a el adentrar se en México"
      }
   };
   checkThematicSimilarity(obtainedResult, expectedResult);
}

TEST_F(RealClusterizerTestSuite, thematicSimilarityCriterionOnlyTwitterNews)
{
   ThematicSimilarityClusteringCriterion mostMentionedEntityCriterion;
   NewsReaderFromTuit newsReaderFromTuit("../data/tuits.txt", exclusionList);
   clusterizer.setCriterion(&mostMentionedEntityCriterion);
   clusterizer.setTuitsReader(&newsReaderFromTuit);

   clusterizer.obtainClusters();

   std::vector<NewsCluster> obtainedResult = clusterizer.getClusters();
   EXPECT_THAT(obtainedResult.size(), ::testing::Eq(1));

   std::vector<std::set<std::string>> expectedResult{
      {
         u8"Liberan a los dos sospechosos detenidos por el asesinato de un niño de 11 años en Liverpool",
         u8"Detienen a seis jóvenes más en relación con el asesinato de el niño de Liverpool",
         u8"Siguen los interrogatorios a los detenidos por el asesinato de el niño de Liverpool"
      }
   };
   checkThematicSimilarity(obtainedResult, expectedResult);
}

TEST_F(RealClusterizerTestSuite, thematicSimilarityCriterionNewspaperAndTwitterNews)
{
   ThematicSimilarityClusteringCriterion mostMentionedEntityCriterion;
   NewsReaderFromPlainText newsReaderFromPlainText("../data/news", exclusionList);
   NewsReaderFromTuit newsReaderFromTuit("../data/tuits.txt", exclusionList);
   clusterizer.setCriterion(&mostMentionedEntityCriterion);
   clusterizer.setNewsReader(&newsReaderFromPlainText);
   clusterizer.setTuitsReader(&newsReaderFromTuit);

   clusterizer.obtainClusters();

   std::vector<NewsCluster> obtainedResult = clusterizer.getClusters();
   EXPECT_THAT(obtainedResult.size(), ::testing::Eq(8));

   std::vector<std::multiset<std::string>> expectedResult{
      {
         u8"Liberan a los dos sospechosos detenidos por el asesinato de un niño de 11 años en Liverpool",
         u8"Detienen a seis jóvenes más en relación con el asesinato de el niño de Liverpool",
         u8"Siguen los interrogatorios a los detenidos por el asesinato de el niño de Liverpool",
         u8"Liberan a los dos sospechosos de el asesinato de un niño en Liverpool",
         u8"La policía pone en libertad a los sospechosos de el asesinato de el niño de Liverpool",
         u8"Detienen a otro sospechoso de 15 años por la muerte de el niño de 11 en Liverpool",
         u8"Detenidos cinco menores en relación con el asesinato de el niño de Liverpool",
         u8"Detenidos en Reino Unido dos adolescentes sospechosos de matar de un disparo a un menor",
         u8"Liberan a los dos sospechosos detenidos por el asesinato de un niño de 11 años en Liverpool",
         u8"Detienen a seis jóvenes más en relación con el asesinato de el niño de Liverpool",
         u8"Siguen los interrogatorios a los detenidos por el asesinato de el niño de Liverpool"
      },
      {
         u8"Chávez llega a Bogotá para mediar en la liberación de secuestrados por las FARC",
         u8"Chávez llega a Bogotá para entrevistar se con Uribe sobre los secuestrados de las FARC",
         u8"Las FARC rechazan el ofrecimiento de Chávez de liberar rehenes en Venezuela",
         u8"Chávez anuncia ante Álvaro Uribe que recibirá en Venezuela a un enviado de las FARC",
         u8"Chávez se reunirá en Caracas con delegados de las FARC"
      },
      {
         u8"Más de 200 muertos en Irak en el ataque más sangriento desde 2003",
         u8"Buscan supervivientes entre las ruinas de el mayor atentado en Irak desde 2003"
      },
      {
         u8"Camila no irá a el funeral por Diana",
         u8"Numerosos actos recuerdan a Diana a los 10 años de su muerte",
         u8"' La mejor madre de el mundo '"
      },
      {
         u8"Los islamistas moderados acarician la victoria en las elecciones parlamentarias en Marruecos",
         u8"Baja participación en las elecciones marroquíes",
         u8"El Gobierno marroquí prevé que la participación electoral alcance el 41 %",
         u8"Los observadores piden a Rabat acometer reformas para alentar la participación",
         u8"Los nacionalistas Istiqlal ganan las elecciones en Marruecos",
         u8"Asesinan a tiros a dos candidatos locales de el partido de Rigoberta Menchú en Guatemala",
         u8"Los dos principales candidatos a la Presidencia de Guatemala cierran sus campañas",
         u8"Guatemala vota en medio de la peor ola de violencia de las últimas décadas",
         u8"Guatemala inicia la recta final de la campaña electoral",
         u8"Los islamista moderados , favoritos en los comicios legislativos que celebra hoy Marruecos",
         u8"Los marroquíes votan hoy con los islamistas moderados como favoritos"
      },
      {
         u8"La ex primera ministra paquistaní Bhutto anuncia que regresará ' muy pronto ' de el exilio",
         u8"Bhutto anuncia que regresará \" muy pronto \" a Pakistán",
         u8"El Tribunal Supremo permite a Sharif , ex primer ministro de Pakistán , volver de el exilio",
         u8"El ex primer ministro Sharif volverá a Pakistán el 10 de septiembre para medir se a Musharraf"
      },
      {
         u8"a el Fatah refuerza la seguridad en el campo de refugiados palestinos de Ain el Helu",
         u8"Evacuan de Nahr a el Bared a las familias de los milicianos de Fatah a el Islam",
         u8"El Ejército de el Líbano anuncia la muerte en combate de el líder de Fatah a el Islam",
         u8"Líbano toma el control de Naher a el Bared",
         u8"Evacuadas de Nahar a el Bared las familias de los milicianos de Fatah a el Islam",
      },
      {
         u8"Más de 400.000 evacuados en Cuba ante la amenaza de inundaciones por el ' Dean '",
         u8"' Dean ' llega a el Caribe mexicano convertido en un huracán ' potencialmente catastrófico '",
         u8"Las lluvias y vientos devastadores de el Dean se sienten ya en la costa oeste de México",
         u8"El ' Dean ' se debilita y en las próximas horas podría convertir se en tormenta tropical",
         u8"El huracán Dean baja a categoría 1 tras atravesar el Yucatán mexicano",
         u8"' Dean ' deja Yucatán debilitado pero podría fortalecerse en el Golfo de México",
         u8"El huracán Dean podría cobrar fuerza a el volver a las aguas cálidas de el Golfo de México",
         u8"' Dean ' provoca otros tres muertos antes de extinguir se en el interior de México",
         u8"Dean pasa a ser tormenta tropical",
         u8"Dean pierde fuerza a el adentrar se en México"
      }
   };
   std::size_t i = 0;
   for (auto& newsCluster : obtainedResult)
   {
      for (auto& news : newsCluster)
      {
         std::multiset<std::string>::iterator it = expectedResult[i].find(news->getSubject());
         EXPECT_TRUE(it != std::end(expectedResult[i]));
         expectedResult[i].erase(it);
      }
      ++i;
   }
   for (auto& result : expectedResult)
   {
      if (not result.empty())
      {
         EXPECT_TRUE(false);
         for (auto& notObtained : result)
         {
            std::cout << notObtained << " ";
         }
         std::cout << "not obtained" << std::endl;
      }
   }
}
