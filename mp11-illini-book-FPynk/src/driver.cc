#include "illini_book.hpp"
#include <iostream>

int main() {
  IlliniBook illini_book("./example/persons.csv", "./example/relations.csv");
  //illini_book.PrintGraph();
  // Test AreRelated (direct or indirect relationships)
  std::cout << "AreRelated (1, 3): " << illini_book.AreRelated(1, 3) << std::endl;

  // Test AreRelated with specific relationship
  std::cout << "AreRelated (1, 6, 124): " << illini_book.AreRelated(1, 6, "124") << std::endl;

  // Test GetRelated (shortest path length)
  std::cout << "GetRelated (1, 8): " << illini_book.GetRelated(1, 8) << std::endl;

  // Test GetRelated with specific relationship
  std::cout << "GetRelated (1, 6, 124): " << illini_book.GetRelated(1, 6, "124") << std::endl;

  // Test GetSteps (UINs with shortest path of n)
  std::vector<int> steps = illini_book.GetSteps(1, 2);
  std::cout << "GetSteps (1, 2): ";
  for (int uin : steps) {
    std::cout << uin << " ";
  }
  std::cout << std::endl;

  // Test CountGroups (connected components)
  std::cout << "CountGroups: " << illini_book.CountGroups() << std::endl;

  // Test CountGroups with specific relationship
  std::cout << "CountGroups (128): " << illini_book.CountGroups("128") << std::endl;

  // Test CountGroups with multiple relationships
  std::vector<std::string> relationships = {"128", "124"};
  std::cout << "CountGroups (128, 124): " << illini_book.CountGroups(relationships) << std::endl;

  return 0;
}