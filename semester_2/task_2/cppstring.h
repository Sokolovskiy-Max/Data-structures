#ifndef STRING_H
#define STRING_H
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
  String(size_t, char);
  String(const char*);  // NOLINT
  String(const char*, size_t);
  String(char* s, size_t);
  String(const String&);
  String& operator=(const String&);
  ~String();
  const char& operator[](size_t) const;
  char& operator[](size_t);
  const char& At(size_t) const;
  char& At(size_t);
  const char& Front() const;
  char& Front();
  const char& Back() const;
  char& Back();
  const char* CStr() const;
  const char* Data() const;
  char* CStr();
  char* Data();
  bool Empty() const;
  size_t Size() const;
  size_t Length() const;
  size_t Capacity() const;
  void Clear();
  void Swap(String&);
  void PopBack();
  void PushBack(const char);
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
};

#endif
