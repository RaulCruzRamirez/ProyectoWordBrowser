#include <iostream>
#include <string>
#include <map>
#include <set>
#include <utility>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

//template <typename Information> class webBrowser {
//private:
multimap<string, pair<string,int>> fullDictionary;
//public:
string cleanupWord(string& word){//const{
    set<char> lastSpace = {',','.',';',':','"',']','}',')','>','%','!','?','/','_','-','+','=','|','\''};
    set<char> firstSpace = {'{','[','(','<','/','"','-','+','=','|','\''};
    string fullWord = word;

    if(lastSpace.count(fullWord[fullWord.length() - 1]) == true){fullWord.pop_back();}
    if(lastSpace.count(fullWord[fullWord.length() - 2]) == true){fullWord.pop_back();fullWord.pop_back();}
    if(firstSpace.count(fullWord[0]) == true){fullWord.erase(0,1);}

    for (auto& letterS : fullWord) {
        letterS = tolower(letterS);
    }

    return fullWord;
}

void catalogueWord(string &fileTitle, string fileWord){
    auto wordInDictionary = fullDictionary.find(fileWord);
    bool updatedCount = false;
    if(wordInDictionary == fullDictionary.end()){
        fullDictionary.insert({fileWord,{fileTitle, 1}});}
    if (wordInDictionary != fullDictionary.end()){
        bool updatedCount = false;
        while(wordInDictionary->first == fileWord && updatedCount == false){
            if(wordInDictionary->second.first == fileTitle){
                wordInDictionary->second.second += 1; updatedCount = true;}
            wordInDictionary++;
        }
        if(updatedCount==false){fullDictionary.insert({fileWord,{fileTitle, 1}});}
    }
}

int readFiles(const string& directory) {
  int counter = 0;
  string fileWord;
  for (const auto& entry : fs::directory_iterator(directory)) {
    if (entry.is_regular_file()) {
      std::ifstream file(entry.path());
      if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << entry.path() << '\n';
        continue;
      }
      counter++; 
      string fileName = entry.path().filename().string();       
      while(file >> fileWord){
        catalogueWord(fileName, cleanupWord(fileWord));
      }
    }
  }
    return counter;
}