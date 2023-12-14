#include <iostream>
#include <exception>
#include <stdexcept>﻿
#ifndef OPTIONAL
#define OPTIONAL

class BadOptionalAccess : public std::runtime_error {
public:
  BadOptionalAccess() : std::runtime_error("Out of range") {
  }
};

template <typename T>
class Optional {
 private:
  bool has_value_ = false;
  char value_[sizeof(T)];

  const T& Object() const {
    return *reinterpret_cast<const T*>(value_);
  }
  T& Object() {
    return *reinterpret_cast<T*>(value_);
  }

 public:
  // странно, вроде в задании swap не просят, но в тестах он нужен
  void Swap(Optional&);
  Optional() = default;
  Optional(const T&);  // NOLINT
  Optional(T&&);       // NOLINT
  Optional(const Optional&);
  Optional(Optional&&) noexcept;
  bool HasValue() const;
  T& Value();
  const T& Value() const;
  T& operator*();
  const T& operator*() const;
  template <class... Args>
  T& Emplace(Args&&...);
  void Reset();
  ~Optional();

  Optional& operator=(const T& that) {
    if (has_value_) {
      Object() = that;
    } else {
      has_value_ = true;
      new (value_) T(that);
    }
    return *this;
  }

  Optional& operator=(T&& that) {
    if (has_value_) {
      Object() = std::move(that);
      return *this;
    }
    has_value_ = true;
    new (value_) T(std::move(that));
    return *this;
  }

  Optional& operator=(const T& that) {
    if (this == &that) {
      return *this;
    }
    if (that.has_value_) {
      if (has_value_) {
        Object() = that.Object();
      } else {
        has_value_ = true;
        new (value_) T(that.Object());
      }
      return *this;
    }
    this->Reset();
    return *this;
  }

  Optional& operator=(T&& that) noexcept {
    if (this == &that) {
      return *this;
    }
    if (that.has_value_) {
      if (has_value_) {
        Object() = std::move(that.Object());
      } else {
        has_value_ = true;
        new (value_) T(std::move(that.Object()));
      }
      return *this;
    }
    this->Reset();
    return *this;
  }

  explicit operator bool() const noexcept {
    return has_value_;
  }
};

template <typename T>
void Optional<T>::Swap(Optional& optional) {
  std::swap(*this, optional);
}

template <typename T>
Optional<T>::Optional(const T& object) {  // NOLINT
  new (value_) T(object);
  has_value_ = true;
}

template <typename T>
Optional<T>::Optional(T&& object) {  // NOLINT
  new (value_) T(std::move(object));
  has_value_ = true;
}

template <typename T>
Optional<T>::Optional(const Optional& optional) {
  has_value_ = optional.has_value_;
  if (has_value_) {
    new (value_) T(optional.Object());
  }
}

template <typename T>
Optional<T>::Optional(Optional&& optional) noexcept {
  has_value_ = optional.has_value_;
  if (has_value_) {
    new (value_) T(std::move(optional.Object()));
  }
}

template <typename T>
bool Optional<T>::HasValue() const {
  return has_value_;
}

template <typename T>
T& Optional<T>::Value() {
  if (has_value_) {
    return *reinterpret_cast<T*>(value_);
  }
  throw BadOptionalAccess{};
}

template <typename T>
const T& Optional<T>::Value() const {
  if (has_value_) {
    return *reinterpret_cast<const T*>(value_);
  }
  throw BadOptionalAccess{};
}

template <typename T>
T& Optional<T>::operator*() {
  return *reinterpret_cast<T*>(value_);
}

template <typename T>
const T& Optional<T>::operator*() const {
  return *reinterpret_cast<const T*>(value_);
}

template <typename T>
template <class... Args>
T& Optional<T>::Emplace(Args&&... args) {
  if (has_value_) {
    Object().~T();
  }
  has_value_ = true;
  return *(new (value_) T(std::forward<Args>(args)...));
}

template <typename T>
void Optional<T>::Reset() {
  if (has_value_) {
    Object().~T();
  }
  has_value_ = false;
}

template <typename T>
Optional<T>::~Optional() {
  this->Reset();
}
#endif
