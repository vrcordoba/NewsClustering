
#include "PlainTextClusterWriter.h"

#include <ostream>
#include <iomanip>

PlainTextClusterWriter::PlainTextClusterWriter(const std::string& destination) : ClusterWriter(destination)
{
}

PlainTextClusterWriter::~PlainTextClusterWriter()
{
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

