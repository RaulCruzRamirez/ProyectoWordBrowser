#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <list>
#include <map>
#include <filesystem>
#include "webFunctions.hpp"

using namespace std;
namespace fs = std::filesystem;

int main() {
  string fileName, fileWord;
  int totalFiles = readFiles("moviesdb2");

  short browserChoose = 0;
  string searchWord, userWord0, userWord1, userWord2;
      
  while (browserChoose!=-1){
    cout << "Search Functions" << endl <<
    "Search One Word (1) -" << "- Search Two Word (2) -" <<
    "- Exit Browser (-1)" << endl << "Select Function: ";
    cin >> browserChoose;
    
    if(browserChoose==1){
      //Single Search
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
      cout << "Top three results for: " << searchWord << endl << 
      "1. File Name: " << firstPlace.second << " - Times Found: " << firstPlace.first << endl <<
      "2. File Name: " << secondPlace.second << " - Times Found: " << secondPlace.first << endl <<
      "3. File Name: " << thirdPlace.second << " - Times Found: " << thirdPlace.first << endl;
    }
    if(browserChoose==2){
      cout << "Search First Word: ";
      cin >> userWord1;
      searchWord = cleanupWord(userWord1);
      cout << "Search Second Word: ";
      cin >> userWord2;
      searchWord = cleanupWord(userWord2);


    }
  }

  cout << "Browser Exited";
  return 0;
}