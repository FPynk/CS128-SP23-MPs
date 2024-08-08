#include "illini_book.hpp"
#include <fstream>
#include <set>
#include <queue>

// Your code here!
IlliniBook::IlliniBook(const std::string &people_fpath, const std::string &relations_fpath) {
  std::ifstream ppl_ifs(people_fpath);
  std::ifstream rs_ifs(relations_fpath);

  int uin = 0;
  while (ppl_ifs >> uin) { AddVertex(uin); }

  int uin_1 = 0;
  int uin_2 = 0;
  std::string rs;
  char delim = ' ';
  while (rs_ifs >> uin_1 >> delim >> uin_2 >> delim >> rs) {
    AddEdge(uin_1, uin_2, rs);
  }

  ppl_ifs.close();
  rs_ifs.close();
}

void IlliniBook::AddVertex(int uin) {
  if (graph_.find(uin) == graph_.end()) {
    graph_[uin] = std::map<int, std::string>();
  }
}

void IlliniBook::AddEdge(int uin_1, int uin_2, const std::string &relationship) {
  if (graph_.find(uin_1) == graph_.end() 
  || graph_.find(uin_2) == graph_.end()) {
    return;
  }

  if (graph_[uin_1].find(uin_2) == graph_[uin_1].end() 
  && graph_[uin_2].find(uin_1) == graph_[uin_2].end()) {
    graph_[uin_1][uin_2] = relationship;
    graph_[uin_2][uin_1] = relationship;
  }
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  return BFS(uin_1, uin_2) != -1;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string& relationship) const {
  return BFS(uin_1, uin_2, relationship) != -1;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  return BFS(uin_1, uin_2);
}

int IlliniBook::GetRelated(int uin_1, int uin_2, const std::string& relationship) const {
  return BFS(uin_1, uin_2, relationship);
}

int IlliniBook::BFS(int uin_1, int uin_2, const std::string &filter_relationship) const {
  if (graph_.find(uin_1) == graph_.end() || graph_.find(uin_2) == graph_.end()) {
    return -1;
  }

  std::queue<int> q;
  std::set<int> visited;
  std::map<int, int> distance;

  q.push(uin_1);
  visited.insert(uin_1);

  while (!q.empty()) {
    int current_uin = q.front();
    q.pop();

    for (const auto &adj_pair : graph_.at(current_uin)) {
      int neighbour_uin = adj_pair.first;
      std::string rs = adj_pair.second;

      if (visited.find(neighbour_uin) == visited.end() && (filter_relationship.empty() || rs == filter_relationship)) {
        q.push(neighbour_uin);
        visited.insert(neighbour_uin);
        distance[neighbour_uin] = distance[current_uin] + 1;

        if (neighbour_uin == uin_2) {
          return distance[neighbour_uin];
        } 
      }
    }
  }

  return -1;
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::vector<int> result;
  if (graph_.find(uin) == graph_.end()) {
    return result;  
  }

  std::queue<int> q;
  std::set<int> visited;
  std::map<int, int> distance;

  q.push(uin);
  visited.insert(uin);

  while (!q.empty()) {
    int cur_uin = q.front();
    q.pop();

    for (const auto &adj_pair : graph_.at(cur_uin)) {
      int neighbour_uin = adj_pair.first;

      if (visited.find(neighbour_uin) == visited.end()) {
        q.push(neighbour_uin);
        visited.insert(neighbour_uin);
        distance[neighbour_uin] = distance[cur_uin] + 1;

        if (distance[neighbour_uin] == n) {
          result.push_back(neighbour_uin);
        }
      }
    }
  }
  return result;
}

size_t IlliniBook::CountGroups() const {
  size_t count = 0;
  std::set<int> visited;

  for (const auto &pair : graph_) {
    if (visited.find(pair.first) == visited.end()) {
      BFSVisit(pair.first, visited);
      count++;
    }
  }

  return count;
}

size_t IlliniBook::CountGroups(const std::string &relationship) const {
  size_t count = 0;
  std::set<int> visited;

  for (const auto &pair : graph_) {
    int uin = pair.first;
    if (visited.find(uin) == visited.end()) {
      BFSVisit(uin, visited, relationship);
      count++;
    }
  }

  return count;
}

size_t IlliniBook::CountGroups(const std::vector<std::string> &relationships) const {
  size_t count = 0;
  std::set<int> visited;

  for (const auto &pair : graph_) {
    if (visited.find(pair.first) == visited.end()) {
      BFSVisit(pair.first, visited, relationships);
      count++;
    }
  }
  return count;
}

void IlliniBook::BFSVisit(int start_uin, std::set<int> &visited, const std::string &filter_relationship) const {
  std::queue<int> q;
  q.push(start_uin);
  visited.insert(start_uin);

  while (!q.empty()) {
    int cur_uin = q.front();
    q.pop();

    for (const auto &adj_pair : graph_.at(cur_uin)) {
      int neighbour_uin = adj_pair.first;
      std::string rs = adj_pair.second;

      if (visited.find(neighbour_uin) == visited.end() && (filter_relationship.empty() || rs == filter_relationship)) {
        q.push(neighbour_uin);
        visited.insert(neighbour_uin);
      }
    }
  }
}

void IlliniBook::BFSVisit(int start_uin, std::set<int> &visited, const std::vector<std::string> &filter_rss) const {
  std::queue<int> q;
  q.push(start_uin);
  visited.insert(start_uin);

  while (!q.empty()) {
    int cur_uin = q.front();
    q.pop();

    for (const auto &adj_pair : graph_.at(cur_uin)) {
      int neighbour_uin = adj_pair.first;
      std::string rs = adj_pair.second;

      if (visited.find(neighbour_uin) == visited.end()  && ContainsString(filter_rss, rs)) {
        q.push(neighbour_uin);
        visited.insert(neighbour_uin);
      }
    }
  }
}

bool IlliniBook::ContainsString(const std::vector<std::string>& vec, const std::string& str) const {
    for (const auto& s : vec) {
        if (s == str) {
            return true;
        }
    }
    return false;
}