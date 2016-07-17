
#include "ClusterWriter.h"
#include "InvalidLocationException.h"

ClusterWriter::ClusterWriter(const std::string& destination)
{
   file.open(destination);
   if (!file.is_open())
   {
      file.clear();
      throw InvalidLocationException(destination);
   }
}

ClusterWriter::~ClusterWriter()
{
   file.close();
}
