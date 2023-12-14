#ifndef RANGE
#define RANGE
#define REVERSE_RANGE_IMPLEMENTED

class Iterator {
 public:
  int value_ = 0;
  int step_ = 1;

  Iterator() = default;

  Iterator(int value, int step) : value_(value), step_(step) {
  }

  int operator*() {
    return value_;
  }

  Iterator operator++() {
    value_ += step_;
    return *this;
  }

  bool operator!=(const Iterator& other) const {
    return (value_ != other.value_);
  }
};

class ReverseIterator {
 public:
  int value_ = 0;
  int step_ = 1;

  ReverseIterator() = default;

  ReverseIterator(int value, int step) : value_(value), step_(step) {
  }

  int operator*() {
    return value_;
  }

  ReverseIterator operator++() {
    value_ -= step_;
    return *this;
  }

  bool operator!=(const ReverseIterator& other) const {
    return (value_ != other.value_);
  }
};

class Range {
 private:
  Iterator begin_;
  Iterator end_;
  ReverseIterator rbegin_;
  ReverseIterator rend_;

 public:
  Range() : begin_(Iterator()), end_(Iterator()), rbegin_(ReverseIterator()), rend_(ReverseIterator()) {
  }

  explicit Range(int end) {
    if (end > 0) {
      begin_ = Iterator(0, 1);
      end_ = Iterator(end, 1);
      rbegin_ = ReverseIterator(end - 1, 1);
      rend_ = ReverseIterator(-1, 1);
    }
  }

  explicit Range(int begin, int end) {
    if (end > begin) {
      begin_ = Iterator(begin, 1);
      end_ = Iterator(end, 1);
      rbegin_ = ReverseIterator(end - 1, 1);
      rend_ = ReverseIterator(begin - 1, 1);
    }
  }

  explicit Range(int begin, int end, int step) {
    if ((step > 0 && end > begin) || (step < 0 && end < begin)) {
      begin_ = Iterator(begin, step);
      end_ = Iterator(end, step);
      if ((end - begin) % step == 0) {
        rbegin_ = ReverseIterator(end - step, step);
        rend_ = ReverseIterator(begin - step, step);
      } else {
        rbegin_ = ReverseIterator(begin + (end - begin + step - 1) / step * step - step, step);
        rend_ = ReverseIterator(begin - step, step);
      }
    }
  }

  Iterator begin() {  // NOLINT
    return begin_;
  }

  Iterator end() {  // NOLINT
    return end_;
  }

  const Iterator begin() const {  // NOLINT
    return begin_;
  }

  const Iterator end() const {  // NOLINT
    return end_;
  }

  ReverseIterator rbegin() {  // NOLINT
    return rbegin_;
  }

  ReverseIterator rend() {  // NOLINT
    return rend_;
  }

  const ReverseIterator rbegin() const {  // NOLINT
    return rbegin_;
  }

  const ReverseIterator rend() const {  // NOLINT
    return rend_;
  }
};
#endif