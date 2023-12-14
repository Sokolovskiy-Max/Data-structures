//#include <iostream>
//#ifndef UNIQUEPTR
//#define UNIQUEPTR
//template <class T>
//class UniquePtr {
// private:
//  T* ptr_;
//
// public:
//  UniquePtr();
//  explicit UniquePtr(T*);
//  UniquePtr(const UniquePtr&) = delete;
//  UniquePtr(UniquePtr&&) noexcept;
//  UniquePtr& operator=(const UniquePtr&) = delete;
//  UniquePtr& operator=(UniquePtr&&) noexcept;
//  T* Release();
//  void Reset(T* ptr = nullptr);
//  void Swap(UniquePtr&);
//  T* Get() const;
//  T& operator*() const;
//  T* operator->() const;
//  explicit operator bool() const;
//  ~UniquePtr();
//};
//
//template <class T>
//UniquePtr<T>::UniquePtr() {
//  ptr_ = nullptr;
//}
//
//template <class T>
//UniquePtr<T>::UniquePtr(T* ptr) {
//  ptr_ = ptr;
//}
//
//template <class T>
//UniquePtr<T>::UniquePtr(UniquePtr<T>&& ptr) noexcept {
//  ptr_ = ptr.ptr_;
//  ptr.ptr_ = nullptr;
//}
//
//template <class T>
//UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& ptr) noexcept {
//  if (this == &ptr) {
//    return *this;
//  }
//  delete ptr_;
//  ptr_ = ptr.ptr_;
//  ptr.ptr_ = nullptr;
//  return *this;
//}
//
//template <class T>
//T* UniquePtr<T>::Release() {
//  T* tmp = ptr_;
//  ptr_ = nullptr;
//  return tmp;
//}
//
//template <class T>
//void UniquePtr<T>::Reset(T* ptr) {
//  delete ptr_;
//  ptr_ = ptr;
//}
//
//template <class T>
//void UniquePtr<T>::Swap(UniquePtr<T>& ptr) {
//  T* tmp = ptr.ptr_;
//  ptr.ptr_ = ptr_;
//  ptr_ = tmp;
//}
//
//template <class T>
//T* UniquePtr<T>::Get() const {
//  return ptr_;
//}
//
//template <class T>
//T& UniquePtr<T>::operator*() const {
//  return *ptr_;
//}
//
//template <class T>
//T* UniquePtr<T>::operator->() const {
//  return ptr_;
//}
//
//template <class T>
//UniquePtr<T>::operator bool() const {
//  return ptr_;
//}
//
//template <class T>
//UniquePtr<T>::~UniquePtr() {
//  delete ptr_;
//}
//#endif