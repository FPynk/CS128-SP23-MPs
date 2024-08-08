#include "cord.hpp"

#include <stdexcept>

#include "cord_utilities.hpp"

Cord::Cord(std::string_view sv) {
    if (sv.empty()) {throw std::invalid_argument("sv_data is empty");}
    data_ = new char[sv.size() + 1];
    int i = 0;
    for (char c : sv) {
        data_[i++] = c;
    }
    data_[i] = '\0'; // Add null terminator manually
    length_ = sv.size(); // Set the length_ data member
}

Cord::~Cord() {
    delete[] data_; // Need to delete sub tree?
}

SharedPointer<char> Cord::ToString() const {
    if (length_ == 0) {   // if length is 0
        char* empty_char = new char[1]{0}; 
        SharedPointer<char> empty = SharedPointer<char>(empty_char, kSharedPointerType::kArray);
        return empty;
    }
    
    char* output = new char[length_ + 1]; // creates char of length_ + 1 for \0
    std::cout << "char* output has length: " << length_ + 1 << std::endl;
    output[length_] = '\0';
    // Helper function to call on both left and right that traverses, grabbing both length and data_ and outputing finished Char*
    unsigned int pos = 0;
    ToStringHelper(this, output, pos);

    auto sug_ma_dig = SharedPointer(output, kSharedPointerType::kArray);
    return sug_ma_dig;
}

// Helper Fn for ToString that recursively calls itself to edit output value that is passed by reference
// WIP
void Cord::ToStringHelper(const Cord* current, char* output, unsigned int& pos) const {
    std::cout << "ToStringHelper called on " << current << std::endl;
    // leaf node aka base case
    if (current->data_ != nullptr) {
        for (unsigned int i = 0; i < current->length_; i++) { //Increments thru output starting from pos and adds on each char ele of data_
            std::cout << "(pos, i) = (" << pos << ", " << i << ")" << std::endl;
            output[pos + i] = current->data_[i];
        }
        pos += current->length_;
        return;
    } 
    // internal node recursive calls
    ToStringHelper(current->left_.Get(), output, pos);
    ToStringHelper(current->right_.Get(), output, pos);
}