#ifndef RESERVE
#define RESERVE
template <typename T>
class ObjectForReversedL {
  T& data_;

public:
  ObjectForReversedL() = default;

  explicit ObjectForReversedL(T& data) : data_(data) {
  }

  auto begin() {  // NOLINT
    return data_.rbegin();
  }

  auto end() {  // NOLINT
    return data_.rend();
  }

  auto begin() const {  // NOLINT
    return data_.rbegin();
  }

  auto end() const {  // NOLINT
    return data_.rbegin();
  }

  auto rbegin() {  // NOLINT
    return data_.begin();
  }

  auto rend() {  // NOLINT
    return data_.end();
  }

  auto rbegin() const {  // NOLINT
    return data_.begin();
  }

  auto rend() const {  // NOLINT
    return data_.rbegin();
  }
};

template <typename T>
class ObjectForReversedR {
  T data_;

public:
  ObjectForReversedR() = default;

  explicit ObjectForReversedR(T&& data) : data_(std::move(data)) {
  }

  auto begin() {  // NOLINT
    return data_.rbegin();
  }

  auto end() {  // NOLINT
    return data_.rend();
  }

  auto begin() const {  // NOLINT
    return data_.rbegin();
  }

  auto end() const {  // NOLINT
    return data_.rbegin();
  }

  auto rbegin() {  // NOLINT
    return data_.begin();
  }

  auto rend() {  // NOLINT
    return data_.end();
  }

  auto rbegin() const {  // NOLINT
    return data_.begin();
  }

  auto rend() const {  // NOLINT
    return data_.rbegin();
  }
};
template <typename T>
ObjectForReversedL<T> Reversed(T& data) {
  return ObjectForReversedL<T>(data);
}

template <typename T>
ObjectForReversedR<T> Reversed(T&& data) {
  return ObjectForReversedR<T>(std::move(data));
}
#endif