#include "lib.h"

void Skaityti(const std::string& filename, std::map<std::string, std::vector<int>>& wordMap);
void Rasyti(const std::string& oyaFilename, const std::string& countFilename, const std::string& linesFilename, const std::map<std::string, std::vector<int>>& wordMap, bool sortByCount);
void URL(const std::string& urlFilename, const std::string& filename);