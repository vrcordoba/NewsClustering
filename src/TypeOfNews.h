#ifndef TYPEOFNEWS_H_
#define TYPEOFNEWS_H_

#include <cstdint>

enum class TypeOfNews : std::uint8_t
{
   notDetermined,
   newspaperNews,
   twitterNews
};

#endif
