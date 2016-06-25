#ifndef INVALIDDIRECTORYEXCEPTION_H_
#define INVALIDDIRECTORYEXCEPTION_H_

#include <exception>
#include <string>

class InvalidDirectoryException final : public std::exception
{
public:
   explicit InvalidDirectoryException(const std::string& invalidDirectory);
   ~InvalidDirectoryException();
   const char* what() const noexcept;

private:
   std::string invalidDirectory;
};

#endif
