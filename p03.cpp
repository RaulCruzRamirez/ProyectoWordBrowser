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

  string stockName, date;
  float value;
  map<string,float> sumStockVal;

  // Loop to read the file. On each loop, the stockName, date and value
  // variables assume the values of a line in the file.
  while (file >> stockName >> date >> value) {
    // do something her
    if (sumStockVal.find(stockName)==sumStockVal.end()){
      sumStockVal.insert({stockName,value});}
    if (sumStockVal.find(stockName)!=sumStockVal.end()){
      sumStockVal.at(stockName) += value;
    }
  }

  cout << "Total volumes per company: " << endl;
  for (auto stocks: sumStockVal) {
    cout << stocks.first << ": " << stocks.second << endl;
  }
  
  file.close();
  return 0;
}
