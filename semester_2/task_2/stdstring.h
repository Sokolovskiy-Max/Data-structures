#ifndef CPPSTRING_H
#define CPPSTRING_H
class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 private:
  char* array_;
  size_t size_;
  size_t capacity_;

 public:
  String();
  String(size_t, const char);
  String(const char*);  // NOLINT
  String(char*, size_t);
  String(const char*, size_t);
  String(const String&);
  String& operator=(const String&);
  const char& operator[](size_t) const;
  char& operator[](size_t);
  char& At(size_t);
  const char& At(size_t) const;
  char& Front();
  const char& Front() const;
  char& Back();
  const char& Back() const;
  const char* CStr() const;
  char* CStr();
  const char* Data() const;
  char* Data();
  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void PopBack();
  void PushBack(const char);
  void Clear();
  void Swap(String&);
  String& operator+=(String);
  void Resize(size_t, const char);
  void Reserve(size_t);
  void ShrinkToFit();
  friend String operator+(String, String);
  friend bool operator<(String, String);
  friend bool operator>(String, String);
  friend bool operator<=(String, String);
  friend bool operator>=(String, String);
  friend bool operator==(String, String);
  friend bool operator!=(String, String);
  friend std::ostream& operator<<(std::ostream&, const String&);
  ~String();
};

#endif
