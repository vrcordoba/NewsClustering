
#include "InvalidDirectoryException.h"

InvalidDirectoryException::InvalidDirectoryException(const std::string& invalidDirectory)
   : invalidDirectory(invalidDirectory)
{
}

InvalidDirectoryException::~InvalidDirectoryException()
{
}

const char* InvalidDirectoryException::what() const noexcept
{
   return (std::string("Invalid directory: ") + invalidDirectory).c_str();
}
