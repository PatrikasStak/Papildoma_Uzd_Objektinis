#include "func.h"

void Skaityti(const std::string& filename, std::map<std::string, std::vector<int>>& wordMap){
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr<<"Failo nepavyko atidaryti\n";
        return;
    }
    std::string line;
    int lineNum=1;
    while(std::getline(file, line)){
    std::istringstream iss(line);
    std::string word;
    while(iss >> word){
        word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c){ return ispunct(c); }), word.end());
        if(word.empty()) continue;
        wordMap[word].push_back(lineNum);
    }
    lineNum++;
    }
}