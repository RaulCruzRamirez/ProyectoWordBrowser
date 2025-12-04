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
      string cleanWord1 = cleanupWord(userWord1);

      cout << "Search Second Word: ";
      cin >> userWord2;
      string cleanWord2 = cleanupWord(userWord2);
      
      //MAKE THE TWO WORD SEARCH
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
             << cleanWord1 << " + " << cleanWord2 << endl;

        cout << "1. File: " << firstPlace.second 
            << " - Total: " << firstPlace.first << endl;

        cout << "2. File: " << secondPlace.second 
            << " - Total: " << secondPlace.first << endl;

        cout << "3. File: " << thirdPlace.second 
            << " - Total: " << thirdPlace.first << endl;
      }
    }
  }
  //The end of the function as it exits the progam when the user has finished browsing.
  cout << "Browser Exited" << endl;
  return 0;
}
