
#include "InvalidLocationException.h"

InvalidLocationException::InvalidLocationException(const std::string& invalidLocation)
   : invalidLocation(invalidLocation)
{
}

InvalidLocationException::~InvalidLocationException()
{
}

const char* InvalidLocationException::what() const noexcept
{
   return (std::string("Invalid location: ") + invalidLocation).c_str();
}
