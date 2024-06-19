//
// Created by Divine on 20/06/2024.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
struct Item {
  int item_id;
  string item_name;
  int item_quantity;
  string item_registration_date;
};
void addItem(int item_id, const string& item_name, int item_quantity, const string& item_registration_date) {
  ofstream file("inventory.csv", std::ios::app);
  if (file.is_open()) {
    file << item_id << "," << item_name << "," << item_quantity << "," << item_registration_date << "\n";
    file.close();
    cout << "Item added successfully!" << endl;
  } else {
    cout << "Unable to open file for writing." << endl;
  }
}
bool compareItems(const Item &a, const Item &b) {
  return a.item_name < b.item_name;
}
void listItems() {
  ifstream file("inventory.csv");
  if (file.is_open()) {
    vector<Item> items;
    string line, word;
    while (getline(file, line)) {
      stringstream s(line);
      Item item;
      getline(s, word, ','); item.item_id = stoi(word);
      getline(s, word, ','); item.item_name = word;
      getline(s, word, ','); item.item_quantity = stoi(word);
      getline(s, word, ','); item.item_registration_date = word;
      items.push_back(item);
    }
    file.close();
    sort(items.begin(), items.end(), compareItems);
    for (const auto& item : items) {
      cout << "Item ID:" << item.item_id
           << " Item Name:" << item.item_name
           << " Quantity:" << item.item_quantity
           << " Reg Date:" << item.item_registration_date << endl;
    }
  } else {
    cerr << "Unable to open file for reading." << endl;
  }
}
void displayHelp() {
  cout << "Commands syntax:" << endl;
  cout << "itemadd <item_id> <item_name> <quantity> <registration_date>" << endl;
  cout << "itemslist" << endl;
  cout << "help" << endl;
  cout << "exit" << endl;
}
int main() {
  string command;
  while (true) {
    cout << "Enter command: ";
    getline(cin, command);
    stringstream ss(command);
    string cmd;
    ss >> cmd;
    transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (cmd == "itemadd") {
      int item_id, item_quantity;
      string item_name, item_registration_date;
      ss >> item_id >> item_name >> item_quantity >> item_registration_date;
      addItem(item_id, item_name, item_quantity, item_registration_date);
    } else if (cmd == "itemslist") {
      listItems();
    } else if (cmd == "help") {
      displayHelp();
    } else if (cmd == "exit") {
      break;
    } else {
      cout << "Unknown command. Type 'help' for a list of commands." << std::endl;
    }
  }
  return 0;
}