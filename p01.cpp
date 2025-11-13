//

#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

using namespace std;

int main() {

  string fileName;

  cout << "Enter filename for pokemons: ";
  //fileName = "pokemon.txt";
  cin >> fileName;

  ifstream file(fileName);
  if (!file.is_open()) {
    throw std::runtime_error("File not found");
  }

  map<string,int> cardList;
  int totalCardAmount = 0, duplicates = 0;
  string cardName;

  while(getline(file,cardName)){cardList.insert({cardName,1});}

  auto it = cardList.begin();
  totalCardAmount += stoi(it->first);
  cardList.erase(it);
  it++;
  totalCardAmount += stoi(it->first);
  cardList.erase(it);

  duplicates = totalCardAmount-cardList.size();
  
  cout << duplicates << endl;
  file.close();
  return 0;
}
