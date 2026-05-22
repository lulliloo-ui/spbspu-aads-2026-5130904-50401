#include "bstree.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace madieva {

  struct Dictionary {
    BSTree< size_t, std::string, std::less< size_t > > dictionary;
  };

  struct Dictionarycollection {
    BSTree< std::string,
      Dictionary, std::less< std::string > > collection;
  };

  bool read(std::istream & file, Dictionarycollection & storage)
  {
    std::string line;
    while (std::getline(file, line)) {
      if (line.empty()) {
        continue;
      }
      std::istringstream iss(line);
      std::string dictionary_name;
      if (!(iss >> dictionary_name)) {
        return false;
      }
      if (storage.collection.has(dictionary_name)) {
        return false;
      }
      Dictionary new_dictionary;
      size_t key;
      std::string value;
      while (iss >> key >> value) {
        new_dictionary.dictionary.push(key, value);
      }
      storage.collection.push(dictionary_name, new_dictionary);
    }
    return true;
  }
}

int main(int argc, char * argv[])
{
  if (argc != 2) {
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!(file.is_open())) {
    return 1;
  }
  madieva::Dictionarycollection storage;
  if (!madieva::read(file, storage)) {
    return 1;
  }
  return 0;

}
