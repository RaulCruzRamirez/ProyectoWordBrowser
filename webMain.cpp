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
  string fileName, fileWord, filesDirectory;
  //Using filesystem it iterates over all the files in the directory, inside the same function is
  //where the registry is built for each word encountered in the files, it asks the user as to which
  //directory it will traverse. It requires the directory, string, to function.
  cout << "Input The File Directory: ";
  cin >> filesDirectory;
  int totalFiles = readFiles(filesDirectory);

  //The user interface of the browser, this is where the user chooses between searching one or two words
  //and exiting the browser. Its divided in two parts one for the single word search: this one iterates over
  //all the files containing the selected key word, searching for the ones with the most occurences then it
  //puts them into three pairs for 1st,2nd,3rd place, shifting the places as new files are looked at that have
  //higher occurences than others. For the two word search it   FINISH HERE .
  short browserChoose = 0;
  string searchWord, userWord0, userWord1, userWord2;
  cout << "There is a total of " << totalFiles << " files in the directory." << endl
  << "To choose an option enter the corresponding number." << endl;
  while (browserChoose!=-1){
    cout << "====================================================================================" << endl;
    cout << "Search Functions: " <<
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
      //Double Word Search
      cout << "Search First Word: ";
      cin >> userWord1;
      searchWord = cleanupWord(userWord1);
      cout << "Search Second Word: ";
      cin >> userWord2;
      searchWord = cleanupWord(userWord2);
      //MAKE THE TWO WORD SEARCH
    }
  }
  //The end of the function as it exits the progam when the user has finished browsing.
  cout << "Browser Exited" << endl;
  return 0;
}