#include "dna_strand.hpp"

#include <stdexcept>

DNAstrand::~DNAstrand() {
  //std::cout << "Destructor run" << std::endl;
  Node* next = head_;
  while (next != nullptr) {
    next = head_->next;
    delete head_;
    head_ = next;
  }
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (pattern[0] == '\0' || to_splice_in.head_ == nullptr) { return; }
  unsigned int length = 0;
  for (unsigned int i = 0; pattern[i] != '\0'; i++) { length++; }
  //Helper to find last occurence of pattern, if not match found throw exception
  Node* start = head_;
  Node* end = tail_;
  //FindPattern(Node* start, Node* end, const char* pattern);
  FindPattern(start, end, pattern);
  // std::cout << "start data is " << start->data << std::endl;
  // std::cout << "end data is " << end->data << std::endl;
  // Maintain pointers to nodes before/ after pattern
  Node* bef_start = nullptr;
  Node* aft_end = end->next;
  if (start != head_) {
    //std::cout << "BefStart exe" << std::endl;
    FindBefStart(bef_start, start);
  }
  //Special cases of start and end, end can be cat as normal case, start checks if bef_start exists
  //Insert the new DNAStrand
  if (bef_start == nullptr) {
    head_ = to_splice_in.head_;
    to_splice_in.tail_->next = aft_end;
    //std::cout << "DelStrand exe" << std::endl;
    DeleteStrand(start, length);
    to_splice_in.head_ = nullptr;
    to_splice_in.tail_ = nullptr; 
  } else {
    bef_start->next = to_splice_in.head_;
    to_splice_in.tail_->next = aft_end;
    //std::cout << "DelStrand exe" << std::endl;
    DeleteStrand(start, length);
    to_splice_in.head_ = nullptr;
    to_splice_in.tail_ = nullptr; 
  }
}

// Deletes start and end node + everything between
// Assumes del_end not snipped off yet
void DNAstrand::DeleteStrand(Node* del_start, unsigned int length) {
  Node* cur = del_start;
  for (unsigned int i = 0; i < length; i++) {
    cur = cur->next;
    //std::cout << "Char being del is " << del_start->data << std::endl;
    delete del_start;
    del_start = cur;
  }
}

// Uses Pass by reference
// Assumes that start != head_, checks using addresses rather than data
void DNAstrand::FindBefStart(Node*& bef_start, Node* start) {
  //std::cout << "start is" << start << std::endl;
  Node* cur = head_;
  while(cur->next != start) {
    //std::cout << "cur->next is" << cur->next << std::endl;
    cur = cur->next;
  }
  bef_start = cur;
  //std::cout << "BefStart finished" << std::endl;
}

// Uses Pass by reference
// Helper function to edit start and end to point to the nodes within DNA sequence that correspond to last occurrence of pattern, inclusive
// Linked list: a -> b -> c -> d -> nullptr, this fn when searching for 'bc' will edit start to point to node b and end to point to node c. if pattern is 1 char long, both point to the same thing
void DNAstrand::FindPattern(Node*& start, Node*& end, const char* pattern) {
  // Pointers to keep track of found patterns start and end. tmp is just a temporary marker.
  Node* found_start = nullptr;
  Node* tmp_found_start = start;
  Node* found_end = nullptr;
  // Pointer cur to cycle thru list, prev to track node before
  Node* cur = start;
  unsigned int i = 0;
  while (cur != nullptr) {
    // First char is found, i+1
    if (cur->data == pattern[i] && i == 0) {
      tmp_found_start = cur;
      i++;
    } 
    // Subsequent chars are found i+1
    // If mismatch, set i=0 and check that char against first char.
    else if (cur->data == pattern[i]) { 
      i++; 
    } else if (i != 0) { 
      i = 0;
      continue;
    } 
    //check last char reached
    if (pattern[i] == '\0') {
      found_start = tmp_found_start;
      found_end = cur;
      i = 0;
    }
    cur = cur->next;
  }
  // Checks if found_start is updated, if not, means no pattern was found
  if (found_start == nullptr) { throw std::runtime_error("No pattern found"); }
  start = found_start;
  end = found_end;
}

void DNAstrand::PushBack(char data) {
  Node* insert = new Node(data);
  if (tail_ == nullptr) {
      head_ = tail_ = insert; 
  } else {
      tail_->next = insert;
      tail_ = insert;
  }
}

void DNAstrand::PushFront(char data) {
  Node* insert = new Node(data);
  if (head_ == nullptr) {
    head_ = tail_ = insert; 
  } else {
    insert->next = head_;
    head_ = insert;
  }
}

// std::ostream& operator<<(std::ostream& os, const DNAstrand& dna_strand) {
//     for (Node* node = dna_strand.head_; node != nullptr; node = node->next) {
//       os << node->data;
//     }
//     return os;
// }