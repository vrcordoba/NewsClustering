#ifndef UTF8CONSTANTS_H_
#define UTF8CONSTANTS_H_

#include <string>
#include <cstdint>

namespace Utf8Constants
{
   static const char* currentLocale = "es_ES.UTF-8";
   static const std::uint32_t oneByteMaskShift = 7;
   static const std::uint32_t twoBytesMaskShift = 5;
   static const std::uint32_t threeBytesMaskShift = 4;
   static const std::uint32_t fourBytesMaskShift = 3;
   static const std::uint32_t oneByteCharacterMask = 0;
   static const std::uint32_t twoBytesCharacterMask = 6;
   static const std::uint32_t threeBytesCharacterMask = 14;
   static const std::uint32_t fourBytesCharacterMask = 30;
}

#endif
