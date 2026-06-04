#include "func.h"

void Skaityti(const std::string& filename, std::map<std::string, std::vector<int>>& wordMap){
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr<<"Failo nepavyko atidaryti\n";
        return;
    }
    const std::vector<std::string> unicodePunct = {
        "\xE2\x80\x93", // –  en dash
        "\xE2\x80\x94", // —  em dash
        "\xE2\x80\x9E", // „  opening quote
        "\xE2\x80\x9C", // "  left quote
        "\xE2\x80\x9D", // "  right quote
        "\xE2\x80\xA6", // …  ellipsis
    };
    std::string line;
    int lineNum=1;
    while(std::getline(file, line)){
        // replace non-breaking spaces
        std::string::size_type pos;
        while((pos = line.find("\xC2\xA0")) != std::string::npos)
            line.replace(pos, 2, " ");
    std::istringstream iss(line);
    std::string word;
    while(iss >> word){
        word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c){ return ispunct(c); }), word.end());
        for(const auto& seq : unicodePunct) {
            size_t p;
            while((p = word.find(seq)) != std::string::npos)
                word.erase(p, seq.size());
        }

        std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c){ return c < 128 ? std::tolower(c) : c; });
        if(word.empty()) continue;
        if(std::all_of(word.begin(), word.end(), ::isdigit)) continue;
        wordMap[word].push_back(lineNum);
    }
    lineNum++;
    }
    file.close();
}

void Rasyti(const std::string& countFilename, const std::string& linesFilename, const std::map<std::string, std::vector<int>>& wordMap, bool sortByCount){
    //lines
    std::ofstream linesFile(linesFilename);
    if(!linesFile.is_open()){
        std::cerr << "Nepavyko atidaryti: " << linesFilename << "\n";
        return;
    }
    std::vector<std::pair<std::string, std::vector<int>>> entries(wordMap.begin(), wordMap.end());
    if(sortByCount)
        std::sort(entries.begin(), entries.end(), [](const auto& a, const auto& b){
            return a.second.size() > b.second.size();
        });


    
    for(const auto& entry : entries){
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

    for(const auto& entry : entries){
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
    std::set<std::string> tlds;
    std::ifstream tldFile("tlds.txt");
    std::string tldLine;
    while(std::getline(tldFile, tldLine)){
        std::transform(tldLine.begin(), tldLine.end(), tldLine.begin(), ::tolower);
        tlds.insert(tldLine);
    }

    while(std::getline(file, line)) {
        std::istringstream iss(line);
        std::string word;
        while(iss>>word){
            size_t pos = word.find("https://");
            if(pos == std::string::npos) pos = word.find("http://");
            if(pos == std::string::npos) pos = word.find("www.");
            if(pos != std::string::npos) {
                word = word.substr(pos);
                word.erase(std::remove_if(word.end()-1, word.end(), ispunct), word.end());
                urlFile << word << "\n";
            } else {
                size_t dot = word.find('.');
                if(dot != std::string::npos && dot < word.size() - 1){
                    std::string tld = word.substr(dot + 1);
                    tld.erase(std::remove_if(tld.begin(), tld.end(), ispunct), tld.end());
                    std::transform(tld.begin(), tld.end(), tld.begin(), ::tolower);
                    if(tlds.count(tld)){
                        word.erase(std::remove_if(word.end()-1, word.end(), ispunct), word.end());
                        urlFile << word << "\n";
                    }
                }
            }
        }
    }
    file.close();

    


}