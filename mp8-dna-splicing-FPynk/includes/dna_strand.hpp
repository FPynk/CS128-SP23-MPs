#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"
class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();
  void PushBack(char data);
  void PushFront(char data);
  void FindPattern(Node*& start, Node*& end, const char* pattern);
  void FindBefStart(Node*& bef_start, Node* start);
  void DeleteStrand(Node* del_start, unsigned int length);
  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);

  //friend std::ostream& operator<<(std::ostream& os, const DNAstrand& dna_strand);

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif