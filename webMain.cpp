//

#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

using namespace std;

int main() {
  string fileName;

  cout << "Enter filename for stocks: ";
  fileName = "rstocks-small01.txt";
  //cin >> fileName;

  ifstream file(fileName);
  if (!file.is_open()) {
    throw std::runtime_error("File not found");
  }
  
  string word;
  // Loop to read the file. On each loop, the stockName, date and value
  // variables assume the values of a line in the file.
  while (file >> word) {
    // do something here
  }
  
  file.close();
  return 0;
}
