#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "graph_storage.hpp"

namespace madieva {
  template<typename T>
  bool read_token(std::istream& in, std::ostream& out, T& value) {
  if (!(in >> value)) {
    out << "<INVALID COMMAND>\n";
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
  }
  return true;
}
  void cmd_graphs(std::istream & in, std::ostream & out, GraphStorage & storage);
  void cmd_vertexes(std::istream & in, std::ostream & out, GraphStorage & storage);
  List< size_t > sort_ascending_order(const List< size_t > & edge);
  void cmd_outbound(std::istream & in, std::ostream & out, GraphStorage & storage);
  void cmd_inbound(std::istream & in, std::ostream & out, GraphStorage & storage);
  void cmd_bind(std::istream & in, std::ostream & out, GraphStorage & storage);
  void cmd_cut(std::istream & in, std::ostream & out, GraphStorage & storage);




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

  void cmd_inbound(std::istream & in, std::ostream & out, GraphStorage & storage)
  {
    std::string name;
    if (!(in >> name)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    std::string b;
    if (!(in >> b)) {
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
    if (!graph.hasVertex(b)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    List< std::string > list_v = graph.getVertices();
    LIter< std::string > it = list_v.begin();
    for (size_t i = 0; i < list_v.size(); ++i) {
      const std::string & a = (*it);
      std::pair<std::string, std::string> key(a, b);
      if (graph.getEdges().has(key)) {
        List< size_t > edge = graph.getEdges().get(key);
        out << a;
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

  void cmd_bind(std::istream & in, std::ostream & out, GraphStorage & storage)
  {
    std::string name;
    if (!read_token(in, out, name)) return;
    std::string a;
    if (!read_token(in, out, a)) return;
    std::string b;
    if (!read_token(in, out, b)) return;
    size_t edge = 0;
    if (!read_token(in, out, edge)) return;
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
    Graph & graph = storage.getGraph(name);
    graph.addEdge(a, b, edge);
  }

  void cmd_cut(std::istream & in, std::ostream & out, GraphStorage & storage)
  {
    std::string name;
    if (!read_token(in, out, name)) return;
    std::string a;
    if (!read_token(in, out, a)) return;
    std::string b;
    if (!read_token(in, out, b)) return;
    size_t edge = 0;
    if (!read_token(in, out, edge)) return;
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
    Graph & graph = storage.getGraph(name);
    if (!graph.hasVertex(a) || !graph.hasVertex(b)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    std::pair<std::string, std::string> key(a, b);
    if (!graph.getEdges().has(key)) {
      out << "<INVALID COMMAND>\n";
      return;
    }
    List< size_t > & list = graph.getEdges().get(key);
    LIter< size_t > it = list.begin();
    for (size_t i = 0; i < list.size(); ++i) {
      if ((*it) == edge) {
        list.erase(it);
        if (list.size() == 0) {
          graph.getEdges().drop(key);
        }
        return;
      }
      ++it;
    }
    out << "<INVALID COMMAND>\n";
  }
}

#endif
