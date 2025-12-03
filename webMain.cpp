
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
  bool fileExit = false;
  int fileTotal = 0;

  cout << "Enter filename: ";
  //cin >> fileName;
  list<string> filesT = {"pokemon.txt", "rstocks-small01.txt", "rstocks-small02.txt"};// , "rstocks.txt"};


    for (auto title = filesT.begin(); title != filesT.end(); ++title){
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

  short browserChoose = 0;
  string searchWord;
  while (browserChoose!=-1){
    cout << "Search Word: ";
    cin >> searchWord;

    auto search = fullDictionary.find(searchWord);
    if(search != fullDictionary.end()){cout << "Word Found In " 
      << search->second.first << "Total: " << search->second.second;}

    cout << "Search Again: "; 
    cin >> browserChoose;
  }

  cout << "Exit";
  return 0;
}
