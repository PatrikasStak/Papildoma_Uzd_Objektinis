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
        std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return c < 128 ? std::tolower(c) : c; });
        if(word.empty()) continue;
        wordMap[word].push_back(lineNum);
    }
    lineNum++;
    }
    file.close();
}

void Rasyti(const std::string& countFilename, const std::string& linesFilename, const std::map<std::string, std::vector<int>>& wordMap){
    //lines
    std::ofstream linesFile(linesFilename);
    if(!linesFile.is_open()){
        std::cerr << "Nepavyko atidaryti: " << linesFilename << "\n";
        return;
    }

    
    for(const auto& entry : wordMap){
        if(entry.second.size()>1){
        linesFile << entry.first << ": ";
        for(size_t i = 0; i < entry.second.size(); ++i){
            linesFile << entry.second[i];
            if(i < entry.second.size() - 1){
                linesFile << ", ";
            }
        }
        linesFile << "\n";
    }
    }
    linesFile.close();
    //count
    std::ofstream countFile(countFilename);
    if(!countFile.is_open()){
        std::cerr << "Nepavyko atidaryti: " << countFilename << "\n";
        return;
    }

    countFile << std::left << std::setw(20) << "Word" << "Count\n";

    for(const auto& entry : wordMap){
        if(entry.second.size()>1){
        int extraBytes = 0;
        for(unsigned char c : entry.first)
            if(c >= 0x80 && c <= 0xBF) extraBytes++;
        countFile << std::left << std::setw(20 + extraBytes) << entry.first <<std::setw(10) << entry.second.size() << "\n";


    }
    }
    countFile.close();

}

void URL(const std::string& urlFilename, const std::string& filename){

    std::ifstream file(filename);
    std::string line;
    if(!file.is_open()){
        std::cerr << "Nepavyko atidaryti: " << filename << "\n";
        return;
    }
    std::ofstream urlFile(urlFilename);
    if(!urlFile.is_open()){
        std::cerr << "Nepavyko atidaryti: " << urlFilename << "\n";
        return;
    }
    while(std::getline(file, line)) {
        std::istringstream iss(line);
        std::string word;
        while(iss>>word){
            if(word.find("https://")==0 || word.find("http://")==0 || word.find("www.")==0){
                word.erase(std::remove_if(word.end()-1, word.end(), ispunct), word.end());
                urlFile<<word<<"\n";
            }else{
            size_t dot = word.find('.');
            if(dot != std::string::npos && dot < word.size() - 1) {
                std::string tld = word.substr(dot + 1);
                // strip trailing punctuation from tld
                tld.erase(std::remove_if(tld.begin(), tld.end(), ispunct), tld.end());
                if(tld == "lt" || tld == "com" || tld == "org" || tld == "net" || tld == "gov") {
                    word.erase(std::remove_if(word.end()-1, word.end(), ispunct), word.end());
                    urlFile << word << "\n";
                }
            }
            }
        }

    }
    file.close();

    


}