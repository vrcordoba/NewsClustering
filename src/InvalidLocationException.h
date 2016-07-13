#ifndef INVALIDLOCATIONEXCEPTION_H_
#define INVALIDLOCATIONEXCEPTION_H_

#include <exception>
#include <string>

class InvalidLocationException final : public std::exception
{
public:
   explicit InvalidLocationException(const std::string& invalidLocation);
   ~InvalidLocationException();
   const char* what() const noexcept;

private:
   std::string invalidLocation;
};

#endif
