#include <iostream>
#include <fstream>
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
  string fileWord, fileName;
  for (const auto& entry : fs::directory_iterator(directory)) {
    if (entry.is_regular_file()) {
      std::ifstream file(entry.path());
      if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << entry.path() << '\n';
        continue;
      }
      counter++; 
      fileName = entry.path().filename().string();       
      while(file >> fileWord){
        catalogueWord(fileName, cleanupWord(fileWord));
      }
    }
  }
    return counter;
}

//The single word search iterates over all the files containing the selected key word, searching for the ones 
//with the most occurences then it puts them into three pairs for 1st,2nd,3rd place, shifting the places as
//new files are looked at that have higher occurences than others.
void singleSearch(){
  string userWord0, searchWord;
  cout << "Search Word: ";
  cin >> userWord0;
  searchWord = cleanupWord(userWord0);
  pair<int, string> firstPlace = {0, "None"};
  pair<int, string> secondPlace = {0, "None"};
  pair<int, string> thirdPlace = {0, "None"};
  pair<int, string> temp;
  auto selectedWord = fullDictionary.equal_range(searchWord);
  for(auto search=selectedWord.first; search!=selectedWord.second;++search){
    if(search->second.second >= firstPlace.first){
      thirdPlace.first = secondPlace.first;
      thirdPlace.second = secondPlace.second;    
      temp.first = firstPlace.first;
      temp.second = firstPlace.second;
      firstPlace.first = search->second.second;
      firstPlace.second = search->second.first;
      secondPlace.first = temp.first;
      secondPlace.second = temp.second;          
    }
    else if(search->second.second >= secondPlace.first){
      thirdPlace.first = secondPlace.first;
      thirdPlace.second = secondPlace.second;
      secondPlace.first = search->second.second;
      secondPlace.second = search->second.first;
    }    
    else if(search->second.second >= thirdPlace.first){
      thirdPlace.first = search->second.second;
      thirdPlace.second = search->second.first;
    }
  }
  if(firstPlace.first == 0){cout << "No files contain the word " << searchWord << "." << endl;}
  else if(secondPlace.first == 0){
    cout << "Top three results for: " << searchWord << endl << 
    "1. File Name: " << firstPlace.second << " - Times Found: " << firstPlace.first << endl;
  }
  else if(thirdPlace.first == 0){
    cout << "Top three results for: " << searchWord << endl << 
    "1. File Name: " << firstPlace.second << " - Times Found: " << firstPlace.first << endl <<
    "2. File Name: " << secondPlace.second << " - Times Found: " << secondPlace.first << endl;
  }
  else{
    cout << "Top three results for: " << searchWord << endl << 
    "1. File Name: " << firstPlace.second << " - Times Found: " << firstPlace.first << endl <<
    "2. File Name: " << secondPlace.second << " - Times Found: " << secondPlace.first << endl <<
    "3. File Name: " << thirdPlace.second << " - Times Found: " << thirdPlace.first << endl;
  }
}

//The single word search iterates over the files containing the selected key wordS, searching for the ones 
//with the most total occurences then it puts them into three pairs for 1st,2nd,3rd place, shifting the places
//as new files are looked at that have higher total occurences than others.
void doubleSearch(){
  string userWord1, userWord2, searchWord;
  cout << "Search First Word: ";
  cin >> userWord1;
  string cleanWord1 = cleanupWord(userWord1);
  cout << "Search Second Word: ";
  cin >> userWord2;
  string cleanWord2 = cleanupWord(userWord2);
      
  map<string,int> countWord1;
  map<string,int> countWord2;

  //rango de 1ra palabra
  auto range1 = fullDictionary.equal_range(cleanWord1);
  for(auto it = range1.first; it != range1.second; ++it){
    countWord1[it->second.first] = it->second.second;
  }
  //rango dela 2da palabra
  auto range2 = fullDictionary.equal_range(cleanWord2);
  for(auto it = range2.first; it != range2.second; ++it){
    countWord2[it->second.first] = it->second.second;
  }
  //recorrer .txt que solo tengan ambas palabras
  map<string,int> combinedCount;

  //1ra
  for(auto &file1 : countWord1){
    string fileName = file1.first;
    int count1 = file1.second;
    //2da
    if(countWord2.count(fileName)){
      int count2 = countWord2[fileName];
      combinedCount[fileName] = count1 + count2;
    }
  }

  if(combinedCount.empty()){
    cout << "No files contain BOTH words." << endl;} 
    else {
      pair<int,string> firstPlace = {0,"None"};
      pair<int,string> secondPlace = {0,"None"};
      pair<int,string> thirdPlace = {0,"None"};
      pair<int,string> temp;

      for(auto &data : combinedCount){
        int totalCount = data.second;
        string fileName = data.first;
        if(totalCount >= firstPlace.first){
          thirdPlace = secondPlace;
          temp = firstPlace;
          firstPlace = {totalCount,fileName};
          secondPlace = temp;
        }
        else if(totalCount >= secondPlace.first){
          thirdPlace = secondPlace;
          secondPlace = {totalCount,fileName};
        }
        else if(totalCount >= thirdPlace.first){
          thirdPlace = {totalCount,fileName};
        }
      }

      cout << "Top results for BOTH words: " 
      << cleanWord1 << " & " << cleanWord2 << endl
      << "1. File: " << firstPlace.second 
      << " - Total: " << firstPlace.first << endl
      << "2. File: " << secondPlace.second 
      << " - Total: " << secondPlace.first << endl
      << "3. File: " << thirdPlace.second 
      << " - Total: " << thirdPlace.first << endl;
    }
  }