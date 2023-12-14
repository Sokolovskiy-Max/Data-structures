#include <iostream>
#include <stdexcept>
#include "cppstring.h"

String::String() {
  array_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

String::String(size_t size, const char symbol) {
  size_ = size;
  capacity_ = size;
  if (size_ == 0) {
    array_ = nullptr;
  } else {
    array_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size; ++i) {
      array_[i] = symbol;
    }
    array_[size_] = '\0';
  }
}

String::String(const char* cstring) {
  size_ = 0;
  for (; cstring[size_] != '\0'; ++size_) {
  }
  capacity_ = size_;
  if (size_ == 0) {
    array_ = nullptr;
  } else {
    array_ = new char[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      array_[i] = cstring[i];
    }
    array_[size_] = '\0';
  }
}

String::String(char* cstring, size_t size) {
  size_ = size;
  capacity_ = size;
  if (size_ == 0) {
    array_ = nullptr;
  } else {
    array_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size; ++i) {
      array_[i] = cstring[i];
    }
    array_[size_] = '\0';
  }
}

String::String(const char* cstring, size_t size) {
  size_ = size;
  capacity_ = size;
  if (size_ == 0) {
    array_ = nullptr;
  } else {
    array_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size; ++i) {
      array_[i] = cstring[i];
    }
    array_[size_] = '\0';
  }
}

String::String(const String& string) {
  size_ = string.size_;
  capacity_ = string.capacity_;
  if (size_ == 0) {
    array_ = nullptr;
  } else {
    array_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      array_[i] = string.array_[i];
    }
    array_[size_] = '\0';
  }
}

String::~String() {
  size_ = 0;
  capacity_ = 0;
  delete[] array_;
}

char& String::operator[](size_t i) {
  return array_[i];
}

const char& String::operator[](size_t i) const {
  return array_[i];
}

char& String::At(size_t i) {
  if (i >= size_) {
    throw StringOutOfRange{};
  }
  return array_[i];
}

const char& String::At(size_t i) const {
  if (i >= size_) {
    throw StringOutOfRange{};
  }
  return array_[i];
}

char& String::Front() {
  return array_[0];
}

const char& String::Front() const {
  return array_[0];
}

char& String::Back() {
  return array_[size_ - 1];
}

const char& String::Back() const {
  return array_[size_ - 1];
}

char* String::CStr() {
  return array_;
}

const char* String::CStr() const {
  return array_;
}

char* String::Data() {
  return array_;
}

const char* String::Data() const {
  return array_;
}

bool String::Empty() const {
  return (size_ == 0);
}

size_t String::Size() const {
  return size_;
}
size_t String::Length() const {
  return size_;
}
size_t String::Capacity() const {
  return capacity_;
}

void String::Clear() {
  size_ = 0;
}

void String::Swap(String& other) {
  std::swap(array_, other.array_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

String& String::operator=(const String& string) {
  if (this != &string) {
    delete[] array_;
    size_ = string.size_;
    capacity_ = string.capacity_;
    if (size_ == 0) {
      array_ = nullptr;
    } else {
      array_ = new char[capacity_ + 1];
      for (size_t i = 0; i < size_; ++i) {
        array_[i] = string.array_[i];
      }
      array_[size_] = '\0';
    }
  }
  return *this;
}

void String::PopBack() {
  --size_;
}

void String::PushBack(const char symbol) {
  if (capacity_ == 0) {
    delete[] array_;
    capacity_ += 1;
    size_ += 1;
    array_ = new char[2];
    array_[0] = symbol;
    array_[1] = '\0';
    return;
  }
  ++size_;
  if (capacity_ == size_ - 1) {
    capacity_ *= 2;
    auto* tmp = array_;
    array_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size_ - 1; ++i) {
      array_[i] = tmp[i];
    }
    delete[] tmp;
  }
  array_[size_ - 1] = symbol;
  array_[size_] = '\0';
}

String& String::operator+=(String string) {
  size_t n = string.size_;
  for (size_t i = 0; i < n; ++i) {
    PushBack(string.array_[i]);
  }
  return *this;
}

void String::Reserve(size_t capacity) {
  if (capacity > capacity_) {
    capacity_ = capacity;
    char* tmp = array_;
    array_ = new char[1 + capacity_];
    for (size_t i = 0; i < size_; ++i) {
      array_[i] = tmp[i];
    }
    array_[size_] = '\0';
    delete[] tmp;
  }
}

void String::Resize(size_t new_size, const char symbol) {
  if (new_size > capacity_) {
    capacity_ = new_size;
    char* tmp = array_;
    array_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      array_[i] = tmp[i];
    }
    delete[] tmp;
  }
  size_t pos = size_;
  while (pos < capacity_) {
    array_[pos] = symbol;
    ++pos;
  }
  array_[new_size] = '\0';
  size_ = new_size;
}

void String::ShrinkToFit() {
  if (capacity_ > size_) {
    capacity_ = size_;
    char* tmp = array_;
    array_ = new char[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i) {
      array_[i] = tmp[i];
    }
    array_[size_] = '\0';
    delete[] tmp;
  }
}
String operator+(String string1, String string2) {
  String string = string1;
  string += string2;
  return string;
}

bool operator==(String string1, String string2) {
  for (size_t i = 0; i < std::min(string1.Size(), string2.Size()); ++i) {
    if (string1[i] != string2[i]) {
      return false;
    }
  }
  return (string1.Size() == string2.Size());
}
bool operator!=(String string1, String string2) {
  return !(string1 == string2);
}
bool operator<(String string1, String string2) {
  for (size_t i = 0; i < std::min(string1.Size(), string2.Size()); ++i) {
    if (string1[i] < string2[i]) {
      return true;
    }
    if (string1[i] > string2[i]) {
      return false;
    }
  }
  return (string1.Size() < string2.Size());
}

bool operator>(String string1, String string2) {
  return (!(string1 < string2 || string1 == string2));
}

bool operator<=(String string1, String string2) {
  return (string1 == string2 || string1 < string2);
}
bool operator>=(String string1, String string2) {
  return (string1 == string2 || string1 > string2);
}

std::ostream& operator<<(std::ostream& out, const String& string) {
  for (size_t i = 0; i < string.Size(); ++i) {
    out << string[i];
  }
  return out;
}
