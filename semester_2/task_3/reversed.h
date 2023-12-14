//#ifndef RVERSED
//#define RVERSED
//#define REVERSE_REVERSED_IMPLEMENTED
//#define TEMPORARY_REVERSED_IMPLEMENTED
//
//template <typename T>
//class ObjectForReversedRval {
//private:
//  T data_;
//
//public:
//  ObjectForReversedRval() = default;
//
//  explicit ObjectForReversedRval(T&& data) : data_(std::move(data)) {
//  }
//
//  auto begin() {  // NOLINT
//    return data_.rbegin();
//  }
//
//  auto end() {  // NOLINT
//    return data_.rend();
//  }
//
//  auto begin() const {  // NOLINT
//    return data_.rbegin();
//  }
//
//  auto end() const {  // NOLINT
//    return data_.rend();
//  }
//
//  auto rbegin() {  // NOLINT
//    return data_.begin();
//  }
//
//  auto rend() {  // NOLINT
//    return data_.end();
//  }
//
//  auto rbegin() const {  // NOLINT
//    return data_.begin();
//  }
//
//  auto rend() const {  // NOLINT
//    return data_.end();
//  }
//};
//
//template <typename T>
//auto Reversed(T&& data) {
//  return ObjectForReversedRval<T>(std::move(data));
//}
//
//template <typename T>
//class ObjectForReversedLval {
//private:
//  T* begin_;
//  T* end_;
//
//public:
//  ObjectForReversedLval() = default;
//
//  explicit ObjectForReversedLval(T& data) : data_(data) {
//  }
//
//  auto begin() {  // NOLINT
//    return data_.rbegin();
//  }
//
//  auto end() {  // NOLINT
//    return data_.rend();
//  }
//
//  auto begin() const {  // NOLINT
//    return data_.rbegin();
//  }
//
//  auto end() const {  // NOLINT
//    return data_.rend();
//  }
//
//  auto rbegin() {  // NOLINT
//    return data_.begin();
//  }
//
//  auto rend() {  // NOLINT
//    return data_.end();
//  }
//
//  auto rbegin() const {  // NOLINT
//    return data_.begin();
//  }
//
//  auto rend() const {  // NOLINT
//    return data_.end();
//  }
//};
//
//template <typename T>
//auto Reversed(T& data) {
//  return ObjectForReversedLval<T>(data);
//}
//#endif