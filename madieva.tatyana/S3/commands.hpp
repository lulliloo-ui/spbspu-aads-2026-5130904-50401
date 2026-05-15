#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "graph_storage.hpp"

namespace madieva {
  void cmd_graphs(std::istream & in, std::ostream & out, GraphStorage & storage);
  void cmd_vertexes(std::istream & in, std::ostream & out, GraphStorage & storage);




  void cmd_graphs(std::istream & in, std::ostream & out, GraphStorage & storage)
  {
    std::string line;
    std::getline(in, line);
    if (!line.empty()) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (!storage.size()) {
      out << "\n";
      return;
    }
    List< std::string > list_name = storage.getAllNames();
    LIter< std::string > it = list_name.begin();
    for (size_t i = 0; i < storage.size(); ++i) {
      out << (*it) << '\n';
      ++it;
    }
  }

  void cmd_vertexes(std::istream & in, std::ostream & out, GraphStorage & storage)
  {
    std::string name;
    if (!(in >> name)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    std::string remainder;
    std::getline(in, remainder);
    if (!remainder.empty()) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (!storage.hasGraph(name)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    Graph graph = storage.getGraph(name);
    List< std::string > vertex = graph.getVertices();
    if (!vertex.size()) {
      out << "\n";
      return;
    }
    LIter<std::string > it = vertex.begin();
    for (size_t i = 0; i < vertex.size(); ++i) {
      out << (*it) << "\n";
      ++it;
    }
  }

}

#endif