
#include "PlainTextClusterWriter.h"

#include <ostream>
#include <iomanip>
#include "InvalidLocationException.h"

PlainTextClusterWriter::PlainTextClusterWriter(const std::string& destination)
{
   file.open(destination);
   if (!file.is_open())
   {
      file.clear();
      throw InvalidLocationException(destination);
   }
}

PlainTextClusterWriter::~PlainTextClusterWriter()
{
   file.close();
}

void PlainTextClusterWriter::write(const std::vector<NewsCluster>& newsClusters)
{
   if (file.is_open())
   {
      std::size_t i = 1;
      for (auto& newsCluster : newsClusters)
      {
         file << "=== Cluster " << std::setfill('0') << std::setw(3) << i++ << " ===" << std::endl;
         file << std::setfill('=') << std::setw(19) << "=" << std::endl;
         file << std::endl;
         writeCluster(newsCluster);
         file << std::endl;
      }
   }
}

void PlainTextClusterWriter::writeCluster(const NewsCluster& newsCluster)
{
   for (auto& news : newsCluster)
   {
      file << news->getSubject() << std::endl;
   }
}

