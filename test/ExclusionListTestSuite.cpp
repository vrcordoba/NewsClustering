
#include "gmock/gmock.h"

#include "ExclusionListFromFile.h"

TEST(ExclusionListTestSuite, emptyExclusionList)
{
   ExclusionListFromFile exclusionList("dummyData/emptyStopList.txt");
   EXPECT_FALSE(exclusionList.isWordInExclusionList("Hello"));
}

TEST(ExclusionListTestSuite, wordsPresentInExclusionList)
{
   ExclusionListFromFile exclusionList("dummyData/litteStopList.txt");
   EXPECT_TRUE(exclusionList.isWordInExclusionList("hello"));
   EXPECT_TRUE(exclusionList.isWordInExclusionList("goodbye"));
   EXPECT_TRUE(exclusionList.isWordInExclusionList("black"));
   EXPECT_TRUE(exclusionList.isWordInExclusionList("white"));
   EXPECT_TRUE(exclusionList.isWordInExclusionList("green"));
   EXPECT_TRUE(exclusionList.isWordInExclusionList("red"));
   EXPECT_TRUE(exclusionList.isWordInExclusionList("blue"));
}

TEST(ExclusionListTestSuite, wordsNotPresentInExclusionList)
{
   ExclusionListFromFile exclusionList("dummyData/litteStopList.txt");
   EXPECT_FALSE(exclusionList.isWordInExclusionList("hell"));
   EXPECT_FALSE(exclusionList.isWordInExclusionList("blues"));
   EXPECT_FALSE(exclusionList.isWordInExclusionList("blackish"));
   EXPECT_FALSE(exclusionList.isWordInExclusionList("greenwich"));
}

TEST(ExclusionListTestSuite, wordsPresentInExclusionListDifferentCapitalization)
{
   ExclusionListFromFile exclusionList("dummyData/litteStopList.txt");
   EXPECT_TRUE(exclusionList.isWordInExclusionList("Hello"));
   EXPECT_TRUE(exclusionList.isWordInExclusionList("GoodBye"));
   EXPECT_TRUE(exclusionList.isWordInExclusionList("BLACK"));
}

TEST(ExclusionListTestSuite, nonAsciiWords)
{
   ExclusionListFromFile exclusionList("dummyData/litteSpanishStopList.txt");
   EXPECT_TRUE(exclusionList.isWordInExclusionList(u8"Ñoñería"));
   EXPECT_TRUE(exclusionList.isWordInExclusionList(u8"entremés"));
   EXPECT_TRUE(exclusionList.isWordInExclusionList(u8"canción"));
   EXPECT_TRUE(exclusionList.isWordInExclusionList(u8"CigÜeña"));
   EXPECT_TRUE(exclusionList.isWordInExclusionList(u8"repelÚs"));
   EXPECT_FALSE(exclusionList.isWordInExclusionList(u8"Óscar"));
   EXPECT_FALSE(exclusionList.isWordInExclusionList(u8"CAPITÁN"));
}
