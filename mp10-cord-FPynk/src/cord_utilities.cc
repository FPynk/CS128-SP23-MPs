#include "cord_utilities.hpp"

SharedPointer<Cord> ConcatCords(const SharedPointer<Cord>& left_cord,
                                const SharedPointer<Cord>& right_cord) {
    if (left_cord.Get() == nullptr || right_cord.Get() == nullptr) {
        throw std::invalid_argument("Nullptrs detected");
    }
    SharedPointer<Cord> cord_sp = SharedPointer<Cord>(new Cord());
    cord_sp->left_ = left_cord;
    cord_sp->right_ = right_cord;
    cord_sp.Get()->length_ = left_cord.Get()->length_ + right_cord.Get()->length_;
    return cord_sp;
}

SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord,
                              unsigned int lower_idx,
                              unsigned int upper_idx) {
    std::cout << curr_cord.Get() << lower_idx << upper_idx << std::endl;
    return curr_cord;
}