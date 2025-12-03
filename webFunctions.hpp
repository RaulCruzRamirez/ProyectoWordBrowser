#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <queue>
#include <map>
#include <set>
#include <utility>
using namespace std;

//template <typename Information> class webBrowser {
//private:
multimap<string, pair<string,int>> fullDictionary;
//public:
string cleanupWord(string& word){//const{
    set<char> lastSpace = {',','.',';',':','"',']','}',')','>','%','!','?','/','_','-','+','=','|','\''};
    set<char> firstSpace = {'{','[','(','<','/','"','-','+','=','|','\''};
    string fullWord = word;

    if(lastSpace.count(fullWord[fullWord.length() - 1]) == true){fullWord.pop_back();}
    if(firstSpace.count(fullWord[0]) == true){fullWord.erase(0,1);}

    for (auto& letterS : fullWord) {
        letterS = tolower(letterS);
    }

    return fullWord;
}

void catalogueWord(string &fileTitle, string fileWord){
    string wordInFile = fileWord;
    auto wordInDictionary = fullDictionary.find(wordInFile);
    auto selectedWord = fullDictionary.equal_range(fileWord);
    if(wordInDictionary == fullDictionary.end()){
        fullDictionary.insert({wordInFile,{fileTitle, 1}});}
    if (wordInDictionary != fullDictionary.end()){
        bool updatedCount = false;
        while(wordInDictionary->first == fileWord && updatedCount == false){
            if(wordInDictionary->second.first == fileTitle){
                wordInDictionary->second.second += 1; updatedCount = true;}
            wordInDictionary++;
        }
        if(updatedCount==false){fullDictionary.insert({wordInFile,{fileTitle, 1}});}
        updatedCount = false;
    }
}