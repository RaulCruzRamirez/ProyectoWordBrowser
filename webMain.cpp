
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include "webFunctions.hpp"
#include <list>


using namespace std;

int main() {
  string fileName, fileWord;

  list<string> filesT = {"rstocks-small02.txt","rstocks-small01.txt","pokemon.txt"};// , "rstocks.txt"};
  for (auto title = filesT.begin(); title != filesT.end(); title++){
    fileName = *title;
    ifstream file(fileName);
    if (!file.is_open()) {
      throw std::runtime_error("File not found");
    }
    while(file >> fileWord){
      //cout << cleanupWord(fileWord) << "--- ";;  
      catalogueWord(fileName, cleanupWord(fileWord));
      }
    }
    string oword = "r";
for(auto it = fullDictionary.begin(); it != fullDictionary.end(); it++){
  if(it->first == oword){
    cout << it->first << endl;
    cout << " " << it->second.first << " " << it->second.second << endl;  
      }
  }
  short browserChoose = 0;
  string searchWord, userWord;
      
  while (browserChoose!=-1){
    cout << "Search Functions" << endl <<
    "Search One Word (1) -" << "- Search Two Word (2) -" <<
    "- Exit Browser (-1)" << endl << "Select Function: ";
    cin >> browserChoose;
    
    if(browserChoose==1){
      //Single Search
      cout << "Search Word: ";
      cin >> userWord;
      searchWord = cleanupWord(userWord);
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
      cout << "Top three results for: " << searchWord << endl << 
      "File Name: " << firstPlace.second << " - Times Found: " << firstPlace.first << endl <<
      "File Name: " << secondPlace.second << " - Times Found: " << secondPlace.first << endl <<
      "File Name: " << thirdPlace.second << " - Times Found: " << thirdPlace.first << endl;
      //cout << search->second.first;
    }
  }

  cout << "Browser Exited";
  return 0;
}
