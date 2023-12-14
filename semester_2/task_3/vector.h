#ifndef VECTOR
#define VECTOR
#include <iostream>

template <class T>
class Vector {
  T* data_ = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;

 public:
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = size_t;
  using Iterator = T*;
  using ConstIterator = const T*;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  // Конструкторы и деструктор
  Vector() = default;
  explicit Vector(size_t);
  Vector(size_t, const T&);
  //Чет я не понял, как пофиксить ошибку при вынесении шаблонного метода со значением по умолчанию за класс, так что
  //метод тут
  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator begin, Iterator end) {
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    size_t i = 0;
    if (end != begin) {
      size_ = std::distance(begin, end);
      capacity_ = end - begin;
      data_ = new T[capacity_];
      try {
        for (; begin < end; ++begin) {
          data_[i] = *(begin);
          ++i;
        }
      } catch (...) {
        delete[] data_;
        throw;
      }
    }
  }

  Vector(std::initializer_list<T>);
  Vector(const Vector&);
  Vector(Vector&& vector) noexcept;
  Vector& operator=(const Vector&);
  Vector& operator=(Vector&&) noexcept;
  ~Vector();

  // Всякие методы
  size_t Size() const noexcept;
  bool Empty() const noexcept;
  size_t Capacity() const noexcept;
  T& operator[](size_t) noexcept;
  const T& operator[](size_t) const noexcept;
  T& At(size_t);
  const T& At(size_t) const;
  T& Front();
  const T& Front() const;
  T& Back();
  const T& Back() const;
  T* Data();
  const T* Data() const;
  void Swap(Vector&);
  void Resize(size_t);
  void Resize(size_t, const T&);
  void Reserve(size_t);
  void ShrinkToFit();
  void Clear() noexcept;
  void PushBack(const T&);
  void PushBack(T&&);
  void PopBack() noexcept;

  // Итераторы
  Iterator begin() {  // NOLINT
    return data_;
  }

  Iterator end() {  // NOLINT
    return data_ + size_;
  }

  ConstIterator begin() const {  // NOLINT
    return data_;
  }

  ConstIterator cbegin() const {  // NOLINT
    return data_;
  }

  ConstIterator end() const {  // NOLINT
    return data_ + size_;
  }

  ConstIterator cend() const {  // NOLINT
    return data_ + size_;
  }

  ReverseIterator rbegin() {  // NOLINT
    return ReverseIterator(data_ + size_);
  }

  ConstReverseIterator rbegin() const {  // NOLINT
    return ConstReverseIterator(begin());
  }

  ConstReverseIterator crbegin() const {  // NOLINT
    return ConstReverseIterator(end());
  }

  ReverseIterator rend() {  // NOLINT
    return ReverseIterator(data_);
  }

  ConstReverseIterator rend() const {  // NOLINT
    return ConstReverseIterator(data_);
  }

  ConstReverseIterator crend() const {  // NOLINT
    return ConstReverseIterator(data_);
  }
};

template <class T>
Vector<T>::Vector(size_t size) : size_(size), capacity_(size) {
  if (size_ > 0) {
    data_ = new T[size]{};
  }
}

template <class T>
Vector<T>::Vector(size_t size, const T& value) : size_(size), capacity_(size) {
  if (size_ > 0) {
    data_ = new T[size]{};
    try {
      for (size_t i = 0; i < size; ++i) {
        data_[i] = value;
      }
    } catch (...) {
      delete[] data_;
      throw;
    }
  }
}

template <class T>
Vector<T>::Vector(std::initializer_list<T> list) : Vector(list.begin(), list.end()) {
}

template <class T>
Vector<T>::Vector(const Vector& vector) : size_(vector.size_), capacity_(vector.capacity_) {
  if (size_ == 0) {
    capacity_ = 0;
    return;
  }
  data_ = new T[vector.capacity_];
  try {
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = vector.data_[i];
    }
  } catch (...) {
    delete[] data_;
    throw;
  }
}

template <class T>
Vector<T>::Vector(Vector&& vector) noexcept {
  data_ = std::__exchange(vector.data_, nullptr);
  size_ = std::__exchange(vector.size_, 0);
  capacity_ = std::__exchange(vector.capacity_, 0);
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& vector) {
  if (this == &vector) {
    return *this;
  }
  if (capacity_ < vector.size_) {
    delete[] data_;
    try {
      data_ = new T[vector.size_];
    } catch (...) {
      size_ = 0;
      capacity_ = 0;
      data_ = nullptr;
      throw;
    }
    capacity_ = vector.size_;
  }
  size_ = vector.size_;
  try {
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = vector.data_[i];
    }
  } catch (...) {
    size_ = 0;
    throw;
  }
  return *this;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector&& vector) noexcept {
  if (this != &vector) {
    Vector(std::move(vector)).Swap(*this);
  }
  return *this;
}

template <class T>
Vector<T>::~Vector() {
  size_ = 0;
  capacity_ = 0;
  delete[] data_;
}

template <class T>
size_t Vector<T>::Size() const noexcept {
  return size_;
}

template <class T>
size_t Vector<T>::Capacity() const noexcept {
  return capacity_;
}

template <class T>
bool Vector<T>::Empty() const noexcept {
  return (size_ == 0);
}

template <class T>
const T& Vector<T>::operator[](size_t i) const noexcept {
  return data_[i];
}

template <class T>
T& Vector<T>::operator[](size_t i) noexcept {
  return data_[i];
}

template <class T>
const T& Vector<T>::At(size_t pos) const {
  if (pos < size_) {
    return data_[pos];
  }
  throw std::out_of_range("Out of range");
}

template <class T>
T& Vector<T>::At(size_t pos) {
  if (pos < size_) {
    return data_[pos];
  }
  throw std::out_of_range("Out of range");
}

template <class T>
const T& Vector<T>::Front() const {
  return *data_;
}

template <class T>
T& Vector<T>::Front() {
  return *data_;
}

template <class T>
const T& Vector<T>::Back() const {
  return data_[size_ - 1];
}

template <class T>
T& Vector<T>::Back() {
  return data_[size_ - 1];
}

template <class T>
const T* Vector<T>::Data() const {
  return data_;
}

template <class T>
T* Vector<T>::Data() {
  return data_;
}

template <class T>
void Vector<T>::Swap(Vector& vector) {
  std::swap(size_, vector.size_);
  std::swap(capacity_, vector.capacity_);
  std::swap(data_, vector.data_);
}

template <class T>
void Vector<T>::Resize(size_t size) {
  if (size <= capacity_) {
    size_ = size;
    return;
  }
  auto* new_data = new T[size]{};
  for (size_t i = 0; i < size_; ++i) {
    new_data[i] = std::move(data_[i]);
  }
  delete[] data_;
  data_ = new_data;
  size_ = size;
  capacity_ = size;
}

template <class T>
void Vector<T>::Resize(size_t size, const T& value) {
  if (size <= capacity_) {
    try {
      for (size_t i = size_; i < size; ++i) {
        data_[i] = value;
      }
    } catch (...) {
      for (size_t i = size_; i < size; ++i) {
        data_[i].~T();
      }
      throw;
    }
    size_ = size;
  } else {
    auto* new_data = new T[size]{};
    try {
      for (size_t i = size_; i < size; ++i) {
        new_data[i] = value;
      }
    } catch (...) {
      delete[] new_data;
      throw;
    }
    for (size_t i = 0; i < size_; ++i) {
      new_data[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = new_data;
    size_ = size;
    capacity_ = size;
  }
}

template <class T>
void Vector<T>::Reserve(size_t capacity) {
  if (capacity > capacity_) {
    auto* new_data = new T[capacity];
    for (size_t i = 0; i < size_; ++i) {
      new_data[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = new_data;
  }
  capacity_ = capacity;
}

template <class T>
void Vector<T>::ShrinkToFit() {
  if (size_ == 0) {
    delete[] data_;
    data_ = nullptr;
    capacity_ = 0;
    return;
  }
  auto* new_data = new T[size_];
  for (size_t i = 0; i < size_; ++i) {
    new_data[i] = std::move(data_[i]);
  }
  delete[] data_;
  data_ = new_data;
  capacity_ = size_;
}

template <class T>
void Vector<T>::Clear() noexcept {
  size_ = 0;
}

template <class T>
void Vector<T>::PushBack(const T& value) {
  if (size_ != capacity_) {
    try {
      data_[size_] = value;
    } catch (...) {
      data_[size_].~T();
      throw;
    }
    ++size_;
  } else {
    if (size_ == 0) {
      auto* new_data = new T[1];
      try {
        *new_data = value;
      } catch (...) {
        delete[] new_data;
        throw;
      }
      delete[] data_;
      size_ = 1;
      capacity_ = 1;
      data_ = new_data;
    } else {
      auto* new_data = new T[capacity_ * 2];
      try {
        for (size_t i = 0; i < size_; ++i) {
          new_data[i] = data_[i];
        }
        new_data[size_] = value;
      } catch (...) {
        delete[] new_data;
        throw;
      }
      ++size_;
      capacity_ *= 2;
      delete[] data_;
      data_ = new_data;
    }
  }
}

template <class T>
void Vector<T>::PushBack(T&& value) {
  if (size_ != capacity_) {
    data_[size_] = std::move(value);
    ++size_;
  } else {
    if (size_ == 0) {
      auto* new_data = new T[1];
      *new_data = std::move(value);
      delete[] data_;
      data_ = new_data;
      capacity_ = 1;
      size_ = 1;
    } else {
      auto* new_data = new T[capacity_ * 2];
      for (size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
      }
      new_data[size_] = std::move(value);
      ++size_;
      capacity_ *= 2;
      delete[] data_;
      data_ = new_data;
    }
  }
}

template <class T>
void Vector<T>::PopBack() noexcept {
  if (size_ == 0) {
    return;
  }
  --size_;
  data_[size_].~T();
}

template <typename T>
bool operator<(const Vector<T>& vec1, const Vector<T>& vec2) noexcept {
  if (vec1.Empty() && vec2.Empty()) {
    return false;
  }
  if (vec1.Empty()) {
    return true;
  }
  if (vec2.Empty()) {
    return false;
  }
  for (size_t i = 0; i < std::min(vec2.Size(), vec1.Size()); ++i) {
    if (vec1[i] != vec2[i]) {
      return vec1[i] < vec2[i];
    }
  }
  if (vec2.Size() <= vec1.Size()) {
    return false;
  }
  return (vec2.Size() > vec1.Size());
}

template <typename T>
bool operator==(const Vector<T>& vec1, const Vector<T>& vec2) noexcept {
  if (vec1.Size() != vec2.Size()) {
    return false;
  }
  for (size_t i = 0; i < vec1.Size(); ++i) {
    if (vec1[i] != vec2[i]) {
      return false;
    }
  }
  return true;
}

template <typename T>
bool operator!=(const Vector<T>& vec1, const Vector<T>& vec2) noexcept {
  return !(vec1 == vec2);
}

template <typename T>
bool operator>(const Vector<T>& vec1, const Vector<T>& vec2) noexcept {
  return !(vec1 <= vec2);
}

template <typename T>
bool operator<=(const Vector<T>& vec1, const Vector<T>& vec2) noexcept {
  return (vec1 < vec2 || vec1 == vec2);
}

template <typename T>
bool operator>=(const Vector<T>& vec1, const Vector<T>& vec2) noexcept {
  return !(vec1 < vec2);
}
#endif
