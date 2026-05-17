#include <iostream>
#include <limits>
#include "hash_table.hpp"
#include "graph_storage.hpp"
#include "commands.hpp"



int main(int argc, char * argv[])
{
  madieva::GraphStorage storage;

  madieva::Graph g1("gr1");
  g1.addVertex("a");
  g1.addVertex("b");
  g1.addVertex("c");
  g1.addEdge("a", "b", 10);
  g1.addEdge("a", "b", 20);
  g1.addEdge("a", "c", 30);
  storage.addGraph("gr1", g1);
  std::cout << "storage.size() = " << storage.size() << "\n";

  using Commands = void(*)(std::istream &,
    std::ostream &, madieva::GraphStorage &);
  madieva::HashTable< std::string, Commands,
    madieva::StringHash, madieva::StringEqual> commands;
  commands.add("graphs", madieva::cmd_graphs);
  commands.add("vertexes", madieva::cmd_vertexes);
  commands.add("outbound", madieva::cmd_outbound);
  commands.add("inbound", madieva::cmd_inbound);
  commands.add("bind", madieva::cmd_bind);
  commands.add("cut", madieva::cmd_cut);
  commands.add("create", madieva::cmd_create);
  commands.add("merge", madieva::cmd_merge);
  commands.add("extract", madieva::cmd_extract);

  std::string cmd;
  while (std::cin >> cmd) {
    if (commands.has(cmd)) {
      commands.get(cmd)(std::cin, std::cout, storage);
    } else {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
