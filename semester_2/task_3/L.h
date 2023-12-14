#ifndef OPTIONAL
#define OPTIONAL
#include <iostream>

class BadOptionalAccess : public std::exception {
public:
  const char* what() const noexcept override {
    return "Bad Optional Access";
  }
};

template <class T>
class Optional {
private:
  bool has_value_;
  char memory_[sizeof(T)];
  T& Obj() {
    return *reinterpret_cast<T*>(memory_);
  }
  const T& Obj() const {
    return *reinterpret_cast<const T*>(memory_);
  }

public:
  Optional() : has_value_(false) {
  }

  Optional(const T& obj) {  // NOLINT
    has_value_ = true;
    new (memory_) T(obj);
  }

  Optional(T&& obj) {  // NOLINT
    has_value_ = true;
    new (memory_) T(std::move(obj));
  }

  Optional(const Optional& optional) noexcept {
    has_value_ = optional.has_value_;
    if (has_value_) {
      new (memory_) T(optional.Obj());
    }
  }

  Optional(Optional&& optional) noexcept {
    has_value_ = optional.has_value_;
    if (has_value_) {
      new (memory_) T(optional.Obj());
    }
  }

  Optional& operator=(const T& optional) {
    if (has_value_) {
      Obj() = optional;
      return *this;
    }
    has_value_ = true;
    new (memory_) T(optional);
    return *this;
  }

  Optional& operator=(T&& optional) {
    if (has_value_) {
      Obj() = std::move(optional);
      return *this;
    }
    has_value_ = true;
    new (memory_) T(std::move(optional));
    return *this;
  }

  Optional& operator=(const Optional& optional) {
    if (this == &optional) {
      return *this;
    }
    if (optional.has_value_) {
      if (!has_value_) {
        has_value_ = !has_value_;
        new (memory_) T(optional.Obj());
      } else {
        Obj() = optional.Obj();
      }
    } else {
      if (has_value_) {
        Obj().~T();
      }
      has_value_ = !has_value_;
    }
    return *this;
  }

  Optional& operator=(Optional&& optional) noexcept {
    if (this == &optional) {
      return *this;
    }
    if (optional.has_value_) {
      if (!has_value_) {
        has_value_ = true;
        new (memory_) T(std::move(optional.Obj()));
      } else {
        Obj() = std::move(optional.Obj());
      }
    } else {
      if (has_value_) {
        Obj().~T();
      }
      has_value_ = false;
    }
    return *this;
  }

  bool HasValue() const noexcept;
  explicit operator bool() const noexcept;
  T& Value();
  const T& Value() const;
  T& operator*();
  const T& operator*() const;

  template <class... Args>
  T& Emplace(Args&&... args);
  void Reset();
  void Swap(Optional&);
  ~Optional();
};

template <class T>
bool Optional<T>::HasValue() const noexcept {
  return has_value_;
}

template <class T>
Optional<T>::operator bool() const noexcept {
  return has_value_;
}

template <class T>
T& Optional<T>::Value() {
  if (!has_value_) {
    throw BadOptionalAccess{};
  }
  return *reinterpret_cast<T*>(memory_);
}

template <class T>
const T& Optional<T>::Value() const {
  if (!has_value_) {
    throw BadOptionalAccess{};
  }
  return *reinterpret_cast<const T*>(memory_);
}

template <class T>
T& Optional<T>::operator*() {
  return *reinterpret_cast<T*>(memory_);
}

template <class T>
const T& Optional<T>::operator*() const {
  return *reinterpret_cast<const T*>(memory_);
}

template <class T>
template <class... Args>
T& Optional<T>::Emplace(Args&&... args) {
  if (has_value_) {
    Obj().~T();
  }
  has_value_ = true;
  return *(new (memory_) T(std::forward<Args>(args)...));
}

template <class T>
void Optional<T>::Reset() {
  if (has_value_) {
    Obj().~T();
  }
  has_value_ = false;
}

template <class T>
void Optional<T>::Swap(Optional& optional) {
  Optional temp = std::move(*this);
  *this = std::move(optional);
  optional = std::move(temp);
}

template <class T>
Optional<T>::~Optional() {
  if (has_value_) {
    Obj().~T();
  }
  has_value_ = false;
}
#endif