#include <iostream>
#include <string>
#include <map>
#include <set>
#include <utility>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

//The main registry is a multimap, with the key being the word and the value being that of a pair which
//contains a string, for the name of the file, and an interger, for the number of times the word is present.
multimap<string, pair<string,int>> fullDictionary;
//This function serves to clean up the words, those recieved from the files in the directory and inputed by the user.
//It cleans up both at the beginning and the end of the string, removing commas, parenthesis, exclamation and question
//marks, among other characters that interfere with the recognition of the word, it also puts the word in lowercase.
//It requires a word, string, to function.
string cleanupWord(string& word){
    set<char> lastSpace = {',','.',';',':','"',']','}',')','>','%','!','?','/','_','-','+','=','|','\''};
    set<char> firstSpace = {'{','[','(','<','/','"','-','+','=','|','\''};
    string fullWord = word;
    if(lastSpace.count(fullWord[fullWord.length() - 2]) == true){fullWord.pop_back();fullWord.pop_back();}
    if(lastSpace.count(fullWord[fullWord.length() - 1]) == true){fullWord.pop_back();}
    if(firstSpace.count(fullWord[0]) == true){fullWord.erase(0,1);}
    for (auto& letterS : fullWord) {
        letterS = tolower(letterS);
    }
    return fullWord;
}

//The main function of the program; It takes the word that is inputed by the current string in the file
//it takes the key range, it contains all the keys that match with the current word. First it checks if the word 
//is in the multimap, if it is not the it inserts the word into the keys in the multimap, while also inserting
//the pair of the current file and a 1 for it being the first time it shows up. If the word is in the multimap
//it then checks to see if the file has already been added to the registry, if it has been added it then searches
//to see if any of the current pairs contains the current file, if it does then it updates the count adding a 1 to
//the total, instead if the file is not found then it inserts the pair, file name and 1 count, to the multimap.
//It requires a fileTitle and word in order to function, both in string.
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

//Here is where all the files in the directory are read and the words inside are registered into the registry.
//It opens the current file, making sure it works, then it updates a counter of the total amount of files searched,
//before starting the looking at the file string by string it isolates the name of the current file in a variable.
//It then goes string by string, calling the catalogueWord function to register it giving the function the file name
//and invoking the cleanupWord function to clean the word before it gets sent to the previous function. It does this
//for every file and every word inside it. It requires a directory, in string form.
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