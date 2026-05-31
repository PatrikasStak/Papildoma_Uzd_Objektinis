#include "func.h"

int main() {
    std::map<std::string, std::vector<int>> wordMap;
    Skaityti("text.txt", wordMap);
    int choice;
    while(true){
        std::cout<<"Kaip rusiuoti? (1 - pagal zodziu kieki, 2 - pagal abecele): ";
        std::cin>>choice;
        if(choice==1 || choice==2)break;
        std::cout<<"Neteising ivestis\n";
    }
    if(choice==1)Rasyti("count.txt", "lines.txt", wordMap, true);
    else Rasyti("count.txt", "lines.txt", wordMap, false);
    URL("urls.txt", "text.txt");
    return 0;
}