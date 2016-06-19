#ifndef UTF8CONSTANTS_H_
#define UTF8CONSTANTS_H_

#include <string>
#include <cstdint>

namespace Utf8Constants
{
   const char* currentLocale = "es_ES.UTF-8";
   const std::uint32_t oneByteMaskShift = 7;
   const std::uint32_t twoBytesMaskShift = 5;
   const std::uint32_t threeBytesMaskShift = 4;
   const std::uint32_t fourBytesMaskShift = 3;
   const std::uint32_t oneByteCharacterMask = 0;
   const std::uint32_t twoBytesCharacterMask = 6;
   const std::uint32_t threeBytesCharacterMask = 14;
   const std::uint32_t fourBytesCharacterMask = 30;
}

#endif
