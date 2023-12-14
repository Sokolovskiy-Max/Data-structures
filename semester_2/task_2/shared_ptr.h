#include <iostream>
#ifndef SHAREDPTR
#define SHAREDPTR
template <class T>
class SharedPtr {
private:
  T* ptr_ = nullptr;
  int* strong_counter_ = nullptr;

public:
  SharedPtr();
  SharedPtr(T*) noexcept;  // NOLINT
  SharedPtr(const SharedPtr&) noexcept;
  SharedPtr(SharedPtr&&) noexcept;
  SharedPtr& operator=(const SharedPtr&);
  SharedPtr& operator=(SharedPtr&&) noexcept;
  void Reset(T* ptr = nullptr);
  void Swap(SharedPtr&) noexcept;
  T* Get() const;
  int UseCount() const;
  T& operator*() const;
  T* operator->() const;
  explicit operator bool() const;
  void Clear();
  ~SharedPtr();
};

template <class T>
SharedPtr<T>::SharedPtr() noexcept {
  ptr_ = nullptr;
  strong_counter_ = new int(1);
}

template <class T>
SharedPtr<T>::SharedPtr(T* ptr) noexcept {
  ptr_ = ptr;
  strong_counter_ = new int(1);
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr& ptr) noexcept {
  if (ptr.strong_counter_ != nullptr) {
    *ptr.strong_counter_ += 1;
  }
  strong_counter_ = ptr.strong_counter_;
  ptr_ = ptr.ptr_;
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& ptr) {
  if (this == &ptr) {
    return *this;
  }
  --(*strong_counter_);
  if (*strong_counter_ == 0) {
    delete strong_counter_;
    delete ptr_;
  }
  ptr_ = ptr.ptr_;
  if (ptr.strong_counter_ != nullptr) {
    *ptr.strong_counter_ += 1;
  }
  strong_counter_ = ptr.strong_counter_;
  return *this;
}

template <class T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& ptr) noexcept {
  ptr_ = ptr.ptr_;
  strong_counter_ = ptr.strong_counter_;
  ptr.ptr_ = nullptr;
  ptr.strong_counter_ = nullptr;
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& ptr) noexcept {
  if (this == &ptr) {
    return *this;
  }
  *strong_counter_ -= 1;
  if (*strong_counter_ == 0) {
    delete strong_counter_;
    delete ptr_;
  }
  ptr_ = ptr.ptr_;
  strong_counter_ = ptr.strong_counter_;
  ptr.ptr_ = nullptr;
  ptr.strong_counter_ = nullptr;
  return *this;
}

template <class T>
void SharedPtr<T>::Reset(T* ptr) {
  *strong_counter_ -= 1;
  if (*strong_counter_ == 0) {
    delete strong_counter_;
    delete ptr_;
  }
  ptr_ = ptr;
  strong_counter_ = new int(1);
}

template <class T>
void SharedPtr<T>::Swap(SharedPtr<T>& ptr) noexcept {
  T* tmp_ptr = ptr.ptr_;
  int* tmp_counter = ptr.strong_counter_;
  ptr.ptr_ = ptr_;
  ptr.strong_counter_ = strong_counter_;
  ptr_ = tmp_ptr;
  strong_counter_ = tmp_counter;
}

template <class T>
T* SharedPtr<T>::Get() const {
  return ptr_;
}

template <class T>
int SharedPtr<T>::UseCount() const {
  if (ptr_ == nullptr) {
    return 0;
  }
  return *strong_counter_;
}

template <class T>
T& SharedPtr<T>::operator*() const {
  return *ptr_;
}

template <class T>
T* SharedPtr<T>::operator->() const {
  return ptr_;
}

template <class T>
SharedPtr<T>::operator bool() const {
  return ptr_;
}

template <class T>
void SharedPtr<T>::Clear() {
  if (strong_counter_ != nullptr) {
    if (*strong_counter_ == 1) {
      delete ptr_;
      delete strong_counter_;
    } else {
      ptr_ = nullptr;
      *strong_counter_ -= 1;
      strong_counter_ = nullptr;
    }
  }
}

template <class T>
SharedPtr<T>::~SharedPtr() {
  Clear();
}
#endif