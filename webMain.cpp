#include <iostream>
#include <string>
#include "webFunctions.hpp"
using namespace std;

int main() {
  string fileName, fileWord, filesDirectory;
  //Using filesystem it iterates over all the files in the directory, inside the same function is
  //where the registry is built for each word encountered in the files, it asks the user as to which
  //directory it will traverse. It requires the directory, string, to function.
  cout << "Input The File Directory: ";
  cin >> filesDirectory;
  int totalFiles = readFiles(filesDirectory);

  //The user interface of the browser, this is where the user chooses between searching one or two words
  //and exiting the browser. Its divided in two parts one for the single word search and another for the
  // double word search.
  string browserChoose = "0";
  cout << "There is a total of " << totalFiles << " files in the directory." << endl
  << "To choose an option enter the corresponding number." << endl;
  while (browserChoose!="-1"){
    cout << "====================================================================================" << endl;
    cout << "Search Functions: " <<
    "Search One Word (1) -" << "- Search Two Word (2) -" <<
    "- Exit Browser (-1)" << endl << "Select Function: ";
    cin >> browserChoose;
    if(browserChoose=="1"){
      //Single Search
      singleSearch();}
    if(browserChoose=="2"){
      //Double Word Search
      doubleSearch();}
    }

  //The end of the function as it exits the progam when the user has finished browsing.
  cout << "Browser Exited, Goodbye." << endl;
  return 0;
}