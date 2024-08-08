#ifndef SHARED_POINTER_HPP
#define SHARED_POINTER_HPP

#include <iostream>

enum class kSharedPointerType { kArray, kObject };

template <typename T>
class SharedPointer {
public:
  SharedPointer(T* address,
                kSharedPointerType type = kSharedPointerType::kObject);
  ~SharedPointer();
  SharedPointer(const SharedPointer<T>& source);
  SharedPointer<T>& operator=(const SharedPointer<T>& source);

  // Provided, do not modify!
  SharedPointer() = default;
  T& operator*() { return *holder_; }
  T* operator->() { return holder_; }
  T* Get() { return holder_; }
  const T* Get() const { return holder_; }
  unsigned int UseCount() const {
    return (ref_count_ != nullptr) ? *ref_count_ : 0;
  }

private:
  T* holder_ = nullptr;
  kSharedPointerType type_ = kSharedPointerType::kObject;
  unsigned int* ref_count_ = nullptr;
};

// non-member helper function declarations

// non-member helper function definitions

// member function definitions

// member function definitions
template <typename T>
SharedPointer<T>::SharedPointer(T* address, kSharedPointerType type) {
    holder_ = address;
    type_ = type;
    ref_count_ = new unsigned int(1);
}

template <typename T>
SharedPointer<T>::~SharedPointer() {
  if (ref_count_ != nullptr) { //Checks for nullptr, remember, dereferencing a nullptr will segment fault
    *ref_count_ -= 1;
    if (*ref_count_ == 0) {
      switch (type_) {
        case kSharedPointerType::kArray:
            delete[] holder_;
            break;
        case kSharedPointerType::kObject:
            delete holder_;
            break;
      }
      delete ref_count_;
    }
  }
}

template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer<T>& source) {
  holder_ = source.holder_;
  type_ = source.type_;
  ref_count_ = source.ref_count_;
  if (ref_count_ != nullptr) {
    *ref_count_ += 1;
  }
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T>& source) {
  if (&source == this) {return *this;}

  if (ref_count_ != nullptr) {
    *ref_count_ -= 1;
    if (*ref_count_ == 0) {
      switch (type_) {
        case kSharedPointerType::kArray:
            delete[] holder_;
            break;
        case kSharedPointerType::kObject:
            delete holder_;
            break;
      }
      delete ref_count_;
    }
  }

  this->holder_ = source.holder_;
  this->type_ = source.type_;
  this->ref_count_ = source.ref_count_;
  if (ref_count_ != nullptr) {
     *ref_count_ += 1;
  }
  return *this;
}

#endif