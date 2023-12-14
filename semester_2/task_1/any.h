#include <stdexcept>
#include <memory>
#ifndef ANYH
#define ANYH
class BadAnyCast : public std::bad_cast {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "BadAnyCast error";
  }
};

class IHolder {
 public:
  virtual std::shared_ptr<IHolder> Clone() = 0;
};

template <class T>
class AnyHolder : public IHolder {
 public:
  T key_;

  AnyHolder(const T& object) {  // NOLINT
    key_ = object;
  }

  std::shared_ptr<IHolder> Clone() override {
    std::shared_ptr<AnyHolder<T>> new_ptr = std::make_shared<AnyHolder<T>>(key_);
    return new_ptr;
  }
};

class Any {
 public:
  std::shared_ptr<IHolder> ptr_;
  Any() {
    ptr_ = nullptr;
  }

  Any(const Any& other) {
    ptr_ = other.ptr_->Clone();
  }

  Any(Any&& other) noexcept {
    ptr_ = std::move(other.ptr_);
    other.ptr_ = nullptr;
  }
  template <class T>
  Any(const T&); //  NOLINT
  Any& operator=(const Any&);
  Any& operator=(Any&&);
  bool HasValue() const;
  void Reset();
  void Swap(Any&);
};

template <class T>
Any::Any(const T& accepted) : ptr_(new AnyHolder<T>(accepted)) {
}

inline void Any::Swap(Any& other) {
  ptr_.swap(other.ptr_);
}

inline Any& Any::operator=(const Any& other) {
  Any(other).Swap(*this);
  return *this;
}

inline Any& Any::operator=(Any&& other) {
  ptr_ = other.ptr_;
  other.ptr_ = nullptr;
  return *this;
}

inline bool Any::HasValue() const {
  return (ptr_ != nullptr);
}

inline void Any::Reset() {
  ptr_ = nullptr;
}

template <class T>
T AnyCast(const Any& object) {
  auto tmp = std::dynamic_pointer_cast<AnyHolder<T>>(object.ptr_);
  T key;
  if (tmp) {
    key = tmp->key_;
  } else {
    throw BadAnyCast{};
  }
  return key;
}
#endif