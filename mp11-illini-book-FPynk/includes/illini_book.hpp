#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <string>
#include <vector>
#include <map>
#include <set>

class IlliniBook {
public:
  IlliniBook(const std::string &people_fpath, const std::string &relations_fpath);
  IlliniBook(const IlliniBook &rhs) = delete;
  IlliniBook &operator=(const IlliniBook &rhs) = delete;
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string &relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string &relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;
  size_t CountGroups() const;
  size_t CountGroups(const std::string &relationship) const;
  size_t CountGroups(const std::vector<std::string> &relationships) const;

private:
  void AddVertex(int uin);
  void AddEdge(int uin_1, int uin_2, const std::string &relationship);
  int BFS(int uin_1, int uin_2, const std::string &filter_relationship = "") const;
  void BFSVisit(int start_uin, std::set<int> &visited, const std::string &filter_relationship = "") const;
  void BFSVisit(int start_uin, std::set<int> &visited, const std::vector<std::string> &filter_rss) const;
  bool ContainsString(const std::vector<std::string>& vec, const std::string& str) const;
  
  std::map<int, std::map<int, std::string>> graph_;
};

#endif
