#ifndef STRINGUTILITIES_H_
#define STRINGUTILITIES_H_

#include <string>
#include <vector>

namespace StringUtilities
{
std::string toLower(const std::string& word);
std::string nonAsciiCharacterToLower(const std::string& multiByteRepresentation);
bool isFirstCharacterCapitalLetter(const std::string& word);
bool isNonAsciiCharacterUpper(const std::string& multiByteRepresentation);
void breakTextIntoWords(const std::string& text, std::vector<std::string>& words);
}

#endif
