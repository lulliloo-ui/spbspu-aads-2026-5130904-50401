#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "graph_storage.hpp"

namespace madieva {
  void cmd_graphs(std::istream & in, std::ostream & out, GraphStorage & storage);
  void cmd_vertexes(std::istream & in, std::ostream & out, GraphStorage & storage);
  List< size_t > sort_ascending_order(const List< size_t > & edge);
  void cmd_outbound(std::istream & in, std::ostream & out, GraphStorage & storage);




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
    std::string line;
    std::getline(in, line);
    if (!line.empty()) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (!storage.hasGraph(name)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    const Graph & graph = storage.getGraph(name);
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

  List< size_t > sort_ascending_order(const List< size_t > & edge)
  {
    List< size_t > sort_edge = edge;
    for (size_t i = 0; i < sort_edge.size(); ++i) {
      LIter< size_t > it = sort_edge.begin();
      for (size_t j = 0; j < sort_edge.size() - i - 1; ++j) {
        LIter< size_t > next = it;
        ++next;
        if ((*it) > (*next)) {
          size_t temp = *it;
          *it = *next;
          *next = temp;
        }
        ++it;
      }
    }
    return sort_edge;
  }

  void cmd_outbound(std::istream & in, std::ostream & out, GraphStorage & storage)
  {
    std::string name;
    if (!(in >> name)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    std::string a;
    if (!(in >> a)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    std::string line;
    std::getline(in, line);
    if (!line.empty()) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    if (!storage.hasGraph(name)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    const Graph & graph = storage.getGraph(name);
    if (!graph.hasVertex(a)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    List< std::string > list_v = graph.getVertices();
    LIter< std::string > it = list_v.begin();
    for (size_t i = 0; i < list_v.size(); ++i) {
      const std::string & b = (*it);
      std::pair<std::string, std::string> key(a, b);
      if (graph.getEdges().has(key)) {
        List< size_t > edge = graph.getEdges().get(key);
        out << b;
        List< size_t > sort_edge = sort_ascending_order(edge);
        LIter<size_t> e_it = sort_edge.begin();
        for (size_t j = 0; j < sort_edge.size(); ++j) {
          out << " " << *e_it;
          ++e_it;
        }
        out << "\n";
      }
      ++it;
    }
  }
}

#endif