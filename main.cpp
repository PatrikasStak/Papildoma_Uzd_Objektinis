#include "func.h"

int main() {
    std::map<std::string, std::vector<int>> wordMap;
    Skaityti("text.txt", wordMap);
    Rasyti("count.txt", "lines.txt", wordMap);
    URL("urls.txt", "text.txt");
    return 0;
}