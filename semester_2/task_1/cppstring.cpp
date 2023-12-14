#include <iostream>
#include <stdexcept>
#include "cppstring.h"

String::String() {
  array_ = new char[1];
  size_ = 0;
  capacity_ = 0;
  array_[0] = '\0';
}
 
String::String(size_t size, char symbol) {
  array_ = new char[size + 1];
  size_ = size;
  capacity_ = size;
  memset(array_, symbol, size);
  array_[size] = '\0';
}

String::String(const char* cstring) {
  array_ = new char[strlen(cstring) + 1];
  size_ = strlen(cstring);
  capacity_ = size_;
  memcpy(array_, cstring, size_ + 1);
}

String::String(const char* cstring, size_t size) {
  array_ = new char[size + 1];
  size_ = size;
  capacity_ = size;
  memcpy(array_, cstring, size + 1);
}

String::String(const String& string) {
  String(string.size_, '\0');
  memcpy(array_, string.array_, size_ + 1);
}

String::~String() {
  delete[] array_;
}

char& String::operator[](size_t i) {
  return array_[i];
}

const char& String::operator[](size_t i) const {
  return array_[i];
}

const char& String::At(size_t i) const {
  if (i >= size_) {
    throw StringOutOfRange{};
  }
  return array_[i];
}

char& String::At(size_t i) {
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
  array_[0] = '\0';
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
    capacity_ = size_;
    if (size_ > 0) {
      array_ = new char[capacity_ + 1];
      for (size_t i = 0; i < size_; ++i) {
        array_[i] = string.array_[i];
      }
      array_[size_] = '\0';
    } else {
      array_ = nullptr;
    }
  }
  return *this;
}

void String::PopBack() {
  --size_;
}

void String::PushBack(char symbol) {
  if (capacity_ == 0) {
    delete[] array_;
    capacity_ += 1;
    size_ += 1;
    array_ = new char[2];
    array_[0] = symbol;
    array_[1] = '\0';
    return;
  }
  if (capacity_ != size_) {
    array_[size_] = symbol;
    ++size_;
    array_[size_] = '\0';
  } else {
    capacity_ *= 2;
    char* new_array = new char[capacity_ + 1];
    memcpy(new_array, array_, size_);
    new_array[size_] = symbol;
    new_array[size_ + 1] = '\0';
    delete[] array_;
    array_ = new_array;
    size_++;
  }
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
  int pos = size_;
  while (pos < capacity_) {
    array_[pos] = symbol;
    ++pos;
  }
  array_[new_size] = '\0';
  size_ = new_size;
}

void String::ShrinkToFit() {
  if (capacity_ > size_) {
    char* new_array = new char[size_ + 1];
    capacity_ = size_;
    memcpy(new_array, array_, capacity_);
    new_array[capacity_] = '\0';
    delete[] array_;
    array_ = new_array;
  }
}
String operator+(const String& string1, const String& string2) {
  String string = string1;
  string += string2;
  return string;
}

bool operator==(String string1, String string2) {
  if (string1.Size() != string2.Size()) {
    return false;
  }
  for (size_t i = 0; i < string1.Size(); ++i) {
    if (string1[i] != string2[i]) {
      return false;
    }
  }
  return true;
}
bool operator!=(String string1, String string2) {
  return !(string1.Size() == string2.Size());
}
bool operator<(String string1, String string2) {
  if (string1.Size() < string2.Size()) {
    return true;
  }
  if (string1.Size() > string2.Size()) {
    return false;
  }
  for (size_t i = 0; i < string1.Size(); ++i) {
    if (string1[i] < string2[i]) {
      return true;
    }
    if (string1[i] > string2[i]) {
      return false;
    }
  }
  return false;
}

bool operator>(String string1, String string2) {
  return (string1 < string2 || string1 == string2);
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
