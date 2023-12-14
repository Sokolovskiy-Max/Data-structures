#ifndef VECTOR
#define VECTOR
#define VECTOR_MEMORY_IMPLEMENTED

#include <iterator>
#include <memory>
#include <algorithm>
#include <stdexcept>

template <typename T>
class Vector {
  T* data_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;
  template <class Iter>
  using EnableIfForwardIter = std::enable_if_t<
    std::is_base_of_v<std::forward_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>>;

public:
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = size_t;
  using Iterator = Pointer;
  using ConstIterator = ConstPointer;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  // Конструкторы:
  Vector() noexcept = default;
  explicit Vector(size_t);
  Vector(size_t, const T&);
  template <typename InputIterator, typename = EnableIfForwardIter<InputIterator>>
  Vector(InputIterator, InputIterator);
  Vector(const std::initializer_list<T>&);
  Vector(const Vector&);
  Vector(Vector&&) noexcept;
  Vector& operator=(const Vector&);
  Vector& operator=(Vector&&) noexcept;
  ~Vector() noexcept(std::is_nothrow_destructible_v<ValueType>);
  template <typename InputIterator, typename = EnableIfForwardIter<InputIterator>>
  Vector(InputIterator begin, InputIterator end) {
    // я чет не понимыю, как пофиксить ошибку при вынесении метода с шаблоном по умолчанию, так что он здесь
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    size_t i = 0;
    try {
      if (end != begin) {
        size_ = end - begin;
        capacity_ = end - begin;
        data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
        for (; begin != end; ++begin) {
          new (data_ + i) T(*begin);
          ++i;
        }
      }
    }
    catch (...) {
      if (data_ != nullptr) {
        for (size_t j = 1; j <= i; ++j) {
          (data_ + i - j)->~T();
        }
        operator delete(data_);
      }
      data_ = nullptr;
      size_ = 0;
      capacity_ = 0;
      throw;
    }
  }

  // Всякая мелочь:
  ConstReference operator[](size_t pos) const noexcept {
    return data_[pos];
  }
  Reference operator[](size_t pos) noexcept {
    return data_[pos];
  }
  ConstReference At(size_t pos) const {
    if (pos >= size_) {
      throw std::out_of_range();
    }
    return (*this)[pos];
  }
  Reference At(size_t pos) {
    if (pos >= size_) {
      throw std::out_of_range();
    }
    return (*this)[pos];
  }
  ConstReference Front() const noexcept {
    return data_[0];
  }
  Reference Front() noexcept {
    return data_[0];
  }
  ConstReference Back() const noexcept {
    return data_[size_ - 1];
  }
  Reference Back() noexcept {
    return data_[size_ - 1];
  }
  ConstPointer Data() const noexcept {
    return data_;
  }
  Pointer Data() noexcept {
    return data_;
  }

  // Итереторы:
  Iterator begin() {  // NOLINT
    return Data();
  }

  ConstIterator end() const {  // NOLINT
    return cend();
  }

  Iterator end() {  // NOLINT
    return size_ + Data();
  }

  ConstIterator cbegin() const {  // NOLINT
    return Data();
  }

  ConstIterator cend() const {  // NOLINT
    return size_ + Data();
  }

  ConstReverseIterator rbegin() const {  // NOLINT
    return crbegin();
  }

  ReverseIterator rbegin() {  // NOLINT
    return ReverseIterator(end());
  }

  ConstReverseIterator rend() const {  // NOLINT
    return crend();
  }

  ReverseIterator rend() {  // NOLINT
    return ReverseIterator(begin());
  }

  ConstReverseIterator crbegin() const {  // NOLINT
    return ConstReverseIterator(cend());
  }

  ConstReverseIterator crend() const {  // NOLINT
    return ConstReverseIterator(cbegin());
  }

  // Остальные методы
  SizeType Size() const noexcept;
  SizeType Capacity() const noexcept;
  bool Empty() const noexcept;
  void Swap(Vector&) noexcept;
  void Resize(size_t);
  void Resize(size_t, const T&);
  void Reserve(size_t);
  void ShrinkToFit();
  void Clear();
  void PushBack(const T&);
  void PushBack(T&&);
  void PopBack() noexcept(std::is_nothrow_destructible_v<ValueType>);
  template <typename... Args>
  void EmplaceBack(Args...);
  ConstIterator begin() const noexcept {  // NOLINT
    return cbegin();
  }
};

//Реалтзация:
template <typename T>
Vector<T>::Vector(size_t size) {
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
  try {
    if (size > 0) {
      data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
      size_ = size;
      capacity_ = size_;
      for (size_t i = 0; i < capacity_; ++i) {
        new (data_ + i) T();
        ++i;
      }
    }
  }
  catch (...) {
    if (data_ != nullptr) {
      for (size_t j = 0; j < i; ++j) {
        (data_ + i - j - 1)->~T();
      }
      operator delete(data_);
    }
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    throw;
  }
}

template <typename T>
Vector<T>::Vector(size_t size, const T& value) {
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
  try {
    if (size != 0) {
      data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
      size_ = size;
      capacity_ = size_;
      for (size_t i = 0; i < capacity_; ++i) {
        new (data_ + i) T(value);
        ++i;
      }
    }
  }
  catch (...) {
    if (data_ != nullptr) {
      for (size_t j = 1; j <= i; ++j) {
        (data_ + i - j)->~T();
      }
      operator delete(data_);
    }
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    throw;
  }
}

template <typename T>
Vector<T>::Vector(const std::initializer_list<T>& initializer_list) {
  auto begin = initializer_list.begin();
  auto end = initializer_list.end();
  data_ = nullptr;
  size_ = 0;
  capacity_ = 0;
  size_t i = 0;
  try {
    if (begin != end) {
      size_ = end - begin;
      capacity_ = end - begin;
      data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
      for (; begin != end; ++begin) {
        new (data_ + i) T(*begin);
        ++i;
      }
    }
  }
  catch (...) {
    if (data_ != nullptr) {
      for (size_t j = 1; j <- i; ++j) {
        (data_ + i - j)->~T();
      }
      operator delete(data_);
    }
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    throw;
  }
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept : size_(other.size_), capacity_(other.capacity_) {
  if (size_ = 0) {
    capacity_ = 0;
  } else {

  }
  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
  if (this != &other) {
    auto save_data = std::exchange(data_, nullptr);
    auto save_size = std::exchange(size_, 0);
    auto save_capacity = std::exchange(capacity_, 0);
    try {
      Vector(other).Swap(*this);
      for (size_t i = 0; i < save_size; i++) {
        (save_data + i)->~T();
      }
      operator delete(save_data);
    }
    catch (...) {
      data_ = save_data;
      size_ = save_size;
      capacity_ = save_capacity;
      throw;
    }
  }
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
  if (this != &other) {
    Vector(std::move(other)).Swap(*this);
  }
  return *this;
}
template <typename T>
Vector<T>::~Vector() noexcept(std::is_nothrow_destructible_v<ValueType>) {
  for (size_t i = 0; i < size_; ++i) {
    (data_ + i)->~T();
  }
  operator delete(data_);
  data_ = nullptr;
}

template <typename T>
size_t Vector<T>::Size() const noexcept {
  return size_;
}

template <typename T>
size_t Vector<T>::Capacity() const noexcept {
  return capacity_;
}

template <typename T>
bool Vector<T>::Empty() const noexcept {
  return size_ == 0;
}

template <typename T>
void Vector<T>::Swap(Vector& other) noexcept {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
void Vector<T>::Resize(size_t size) {
  auto save_data = data_;
  auto save_size = size_;
  auto save_capacity = capacity_;
  try {
    if (!(size > capacity_)) {
      if (size > size_) {
        for (size_t i = size_; i < size; ++i) {
          new (data_ + i) T();
        }
        size_ = size;
        return;
      }
      for (size_t i = size; i < size_; ++i) {
        (data_ + i)->~T();
      }
    } else {
      data_ = nullptr;
      capacity_ = size;
      if (!(save_data == nullptr)) {
        size_t i = 0;
        try {
          data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
          while (i < size) {
            new (data_ + i) T;
            ++i;
          }
        }
        catch (...) {
          if (data_ != nullptr) {
            for (size_t j = 1; j <= i; ++j) {
              (data_ + i - j)->~T();
            }
            operator delete(data_);
          }
          data_ = nullptr;
          throw;
        }
        for (i = 0; i < save_size; ++i) {
          *(data_ + i) = T(std::move(save_data[i]));
        }
        for (i = 0; i < save_size; ++i) {
          (save_data + i)->~T();
        }
        operator delete(save_data);
      } else {
        size_t i = 0;
        try {
          data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
          while (i < size) {
            new (data_ + i) T();
            ++i;
          }
        }
        catch (...) {
          if (data_ != nullptr) {
            for (size_t j = 1; j <= i; ++j) {
              (data_ + i - j)->~T();
            }
            operator delete(data_);
          }
          data_ = nullptr;
          throw;
        }
      }
    }
    size_ = size;
  }
  catch (...) {
    if (data_ != nullptr) {
      for (size_t j = 1; j <= i; ++j) {
        (data_ + i - j)->~T();
      }
      operator delete(data_);
    }
    data_ = save_data;
    size_ = save_size;
    capacity_ = save_capacity;
    throw;
  }
}

template <typename T>
void Vector<T>::Resize(size_t size, const T& value) {
  auto save_data = data_;
  auto save_size = size_;
  auto save_capacity = capacity_;
  if (size_ == size) {
    return;
  }
  try {
    if (size <= capacity_) {
      if (size <= size_)) {
      for (size_t i = size; i < size_; ++i) {
        (data_ + i)->~T();
      }
      } else {
        for (size_t i = size_; i < size; ++i) {
          *(data_ + i) = T(value);
        }
      }
    } else {
      data_ = nullptr;
      capacity_ = size;
      if (save_data != nullptr) {
        size_t i = 0;
        try {
          data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
          while (i < size) {
            new (data_ + i) T();
            ++i;
          }
        }
        catch (...) {
          if (data_ != nullptr) {
            for (size_t j = 1; j <= i; ++j) {
              (data_ + i - j)->~T();
            }
            operator delete(data_);
          }
          data_ = nullptr;
          throw;
        }
        for (i = save_size; i < size; ++i) {
          *(data_ + i) = T(value);
        }
        for (i = 0; i < save_size; ++i) {
          *(data_ + i) = T(std::move(save_data[i]));
        }
        for (i = 0; i < save_size; ++i) {
          (save_data + i)->~T();
        }
        operator delete(save_data);
      } else {
        size_t i = 0;
        try {
          data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
          while (i < size) {
            new (data_ + i) T(value);
            ++i;
          }
        }
        catch (...) {
          if (data_ != nullptr) {
            for (size_t j = 1; j <= i; ++j) {
              (data_ + i - j)->~T();
            }
            operator delete(data_);
          }
          data_ = nullptr;
          throw;
        }
      }
    }
    size_ = size;
  }
  catch (...) {
    if (data_ != nullptr) {
      for (size_t i = 0; i < capacity_; ++i) {
        (data_ + i)->~T();
      }
      operator delete(data_);
    }
    data_ = save_data;
    size_ = save_size;
    capacity_ = save_capacity;
    throw;
  }
}

template <typename T>
void Vector<T>::Reserve(size_t capacity) {
  if (capacity <= capacity_) {
    return;
  }
  capacity_ = capacity;
  data_ = nullptr;
  if (save_data != nullptr) {
    size_t i = 0;
    data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
    while (i < size_) {
      new (data_ + i) T();
      ++i;
    }
    for (i = 0; i < save_size; ++i) {
      *(data_ + i) = T(std::move(save_data[i]));
    }
    for (i = 0; i < save_size; ++i) {
      (save_data + i)->~T();
    }
    operator delete(save_data);
  } else {
    size_t i = 0;
    data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
  }
}
template <typename T>
void Vector<T>::ShrinkToFit() {
  if (capacity_ == size_) {
    return;
  }
  if (size_ == 0) {
    capacity_ = size_;
    operator delete(data_);
    data_ = nullptr;
    return;
  }
  data_ = nullptr;
  capacity_ = size_;
  size_t i = 0;
  data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
  while (i < save_size) {
    new (data_ + i) T();
    ++i;
  }
  if (data_ != nullptr) {
    for (size_t j = 1; j <= i; ++j) {
      (data_ + i - j)->~T();
    }
    operator delete(data_);
  }
  data_ = nullptr;
  for (i = 0; i < save_size; ++i) {
    *(data_ + i) = T(std::move(save_data[i]));
  }
  for (i = 0; i < save_size; ++i) {
    (save_data + i)->~T();
  }
  operator delete(save_data);
}

template <typename T>
void Vector<T>::Clear() {
  for (size_t i = 0; i < size_; ++i) {
    (data_ + i)->~T();
  }
  size_ = 0;
  operator delete(data_);
  data_ = nullptr;
  capacity_ = 0;
}

template <typename T>
void Vector<T>::PushBack(const T& value) {
  auto save_data = data_;
  auto save_size = size_;
  auto save_capacity = capacity_;
  if (capacity_ > size_) {
    new (data_ + size_) T(value);
    ++size_;
    return;
  }
  try {
    if (capacity_ != 0) {
      capacity_ *= 2;
    } else {
      capacity_ = 1;
    }
    data_ = nullptr;
    size_t i = 0;
    try {
      data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
      while (i < size_ + 1) {
        new (data_ + i) T();
        ++i;
      }
    }
    catch (...) {
      if (data_ != nullptr) {
        for (size_t j = 1; j <= i; ++j) {
          (data_ + i - j)->~T();
        }
        operator delete(data_);
      }
      data_ = nullptr;
      throw;
    }
    for (i = 0; i < save_size; ++i) {
      *(data_ + i) = T(std::move(save_data[i]));
    }
    *(data_ + size_) = T(value);
    ++size_;
    for (i = 0; i < save_size; ++i) {
      (save_data + i)->~T();
    }
    operator delete(save_data);
  }
  catch (...) {
    if (data_ != nullptr) {
      for (size_t i = 0; i < capacity_; ++i) {
        (data_ + i)->~T();
      }
      operator delete(data_);
    }
    data_ = save_data;
    size_ = save_size;
    capacity_ = save_capacity;
    throw;
  }
}

template <typename T>
void Vector<T>::PushBack(T&& value) {
  if (capacity_ > size_) {
    new (data_ + size_) T(std::move(value));
    ++size_;
    return;
  }
  if (capacity_ == 0) {
    capacity_ = 1;
  } else {
    capacity_ *= 2;
  }
  data_ = nullptr;
  size_t i = 0;
  data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
  while (i < size_ + 1) {
    new (data_ + i) T();
    ++i;
  }
  if (data_ != nullptr) {
    for (size_t j = 1; j <= i; ++j) {
      (data_ + i - j)->~T();
    }
    operator delete(data_);
  }
  data_ = nullptr;
  for (i = 0; i < save_size; ++i) {
    *(data_ + i) = T(std::move(save_data[i]));
  }
  *(data_ + size_) = T(std::move(value));
  ++size_;
  for (i = 0; i < save_size; ++i) {
    (save_data + i)->~T();
  }
  operator delete(save_data);
  if (data_ != nullptr) {
    for (size_t i = 0; i < capacity_; ++i) {
      (data_ + i)->~T();
    }
    operator delete(data_);
  }
}

template <typename T>
void Vector<T>::PopBack() noexcept(std::is_nothrow_destructible_v<ValueType>) {
  if (size_ == 0) {
    return;
  }
  --size_;
  (data_ + size_)->~T();
}

template <typename T>
template <typename... Args>
void Vector<T>::EmplaceBack(Args... args) {
  auto save_data = data_;
  auto save_size = size_;
  auto save_capacity = capacity_;
  if (capacity_ > size_) {
    new (data_ + size_) T(std::forward<Args>(args)...);
    ++size_;
    return;
  }
  try {
    if (capacity_ != 0) {
      capacity_ *= 2;
    } else {
      capacity_ = 1;
    }
    data_ = nullptr;
    size_t i = 0;
    try {
      data_ = static_cast<T*>(operator new(sizeof(T) * capacity_));
      while (i < size_ + 1) {
        new (data_ + i) T;
        ++i;
      }
    }
    catch (...) {
      if (data_ != nullptr) {
        for (size_t j = 1; j <= i; ++j) {
          (data_ + i - j)->~T();
        }
        operator delete(data_);
      }
      data_ = nullptr;
      throw;
    }
    for (i = 0; i < save_size; ++i) {
      *(data_ + i) = T(std::move(save_data[i]));
    }
    *(data_ + size_) = T(std::forward<Args>(args)...);
    ++size_;
    for (i = 0; i < save_size; ++i) {
      (save_data + i)->~T();
    }
    operator delete(save_data);
  }
  catch (...) {
    if (data_ != nullptr) {
      for (size_t i = 0; i < capacity_; ++i) {
        (data_ + i)->~T();
      }
      operator delete(data_);
    }
    data_ = save_data;
    size_ = save_size;
    capacity_ = save_capacity;
    throw;
  }
}

template <typename T>
bool operator<(const Vector<T>& vec1, const Vector<T>& vec2) noexcept {
  for (size_t i = 0; i < std::min(vec1.Size(), vec2.Size()); ++i) {
    if (vec1.data_[i] == vec2.data_[i]) {
      continue;
    }
    return (vec1.data_[i] < vec2.data_[i]);
  }
  return (vec1.Size() < vec2.Size());
}

template <typename T>
bool operator==(const Vector<T>& vec1, const Vector<T>& vec2) noexcept {
  for (size_t i = 0; i < std::min(vec1.Size()_, vec2.Size()); ++i) {
    if (vec1.data_[i] == vec2.data_[i]) {
      continue;
    }
    return false;
  }
  return (vec1.Size() == vec2.Size());
}

template <typename T>
inline bool operator>(const Vector<T>& vec1, const Vector<T>& vec2) noexcept {
  return !(vec1 <= vec2);
}

template <typename T>
inline bool operator<=(const Vector<T>& vec1, const Vector<T>& vec2) noexcept {
  return (vec1 < vec2 || vec1 == vec2);
}

template <typename T>
inline bool operator>=(const Vector<T>& vec1, const Vector<T>& vec2) noexcept {
  return !(vec1 < vec2);
}

template <typename T>
inline bool operator!=(const Vector<T>& vec1, const Vector<T>& vec2) noexcept {
  return !(vec1 == vec2);
}
#endif