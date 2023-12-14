#ifndef STACK
#define STACK
#include <iostream>
#include <queue>

template <class T, class Container = std::deque<T>>
class Stack {
 public:
  Container data_;
  size_t size_;

  Stack() = default;

  explicit Stack(const Container& data) {  // NOLINT
    data_ = Container(data.begin(), data.end());
    size_ = data_.size();
  }

  template <class Iterator>
  Stack(Iterator begin, Iterator end) {
    data_ = Container(begin, end);
    size_ = data_.size();
  }

  const T& Top() const {
    return data_.back();
  }

  T& Top() {
    return data_.back();
  }

  bool Empty() const {
    return data_.empty();
  }

  size_t Size() const {
    return data_.size();
  }

  void Push(T&& value) {
    data_.emplace_back(std::move(value));
    ++size_;
  }

  void Push(const T& value) {
    data_.emplace_back(value);
    ++size_;
  }

  template <class... Args>
  void Emplace(Args&&... args) {
    data_.emplace_back(std::forward<Args>(args)...);
  }

  void Pop() {
    if (size_ > 0) {
      data_.pop_back();
      --size_;
    }
  }

  void Clear() {
    while (!data_.empty()) {
      this->Pop();
    }
  }

  void Swap(Stack& other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
  }
};

#endif