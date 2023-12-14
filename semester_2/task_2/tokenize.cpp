#include <variant>

#include "tokenize.h"

bool PlusToken::operator==(const PlusToken&) const {
  return true;
}

bool MinusToken::operator==(const MinusToken&) const {
  return true;
}

bool MultiplyToken::operator==(const MultiplyToken&) const {
  return true;
}

bool DivideToken::operator==(const DivideToken&) const {
  return true;
}

bool ResidualToken::operator==(const ResidualToken&) const {
  return true;
}

bool OpeningBracketToken::operator==(const OpeningBracketToken&) const {
  return true;
}

bool ClosingBracketToken::operator==(const ClosingBracketToken&) const {
  return true;
}

bool SqrToken::operator==(const SqrToken&) const {
  return true;
}

bool MaxToken::operator==(const MaxToken&) const {
  return true;
}

bool MinToken::operator==(const MinToken&) const {
  return true;
}

bool AbsToken::operator==(const AbsToken&) const {
  return true;
}

bool NumberToken::operator==(const NumberToken& other) const {
  return (value == other.value);
}

bool UnknownToken::operator==(const UnknownToken& other) const {
  return (value == other.value);
}

using Token = std::variant<PlusToken, MinusToken, MultiplyToken, DivideToken, ResidualToken, OpeningBracketToken,
                           ClosingBracketToken, SqrToken, MaxToken, MinToken, AbsToken, NumberToken, UnknownToken>;

bool operator==(const Token& first, const Token& second) {
  return (first == second);
}

NumberToken::NumberToken(int a) {
  value = a;
}

UnknownToken::UnknownToken(std::string unknown) {
  value = unknown;
}

std::vector<std::string> WordsSeperetion(std::string_view str) {
  std::string word;
  std::vector<std::string> words;
  size_t size = str.size();
  for (size_t i = 0; i < size; ++i) {
    if (str[i] != ' ') {
      word.push_back(str[i]);
    } else {
      if (!word.empty()) {
        words.push_back(word);
      }
    }
  }
  if (str[size - 1] != ' ') {
    words.push_back(word);
  }
  return words;
}

bool NunberChecker(std::string word) {
  if (!((word[0] == '-' && word.size() > 1) || (word[0] == '+' && word.size() > 1) ||
        (word[0] >= '0' && word[0] <= '9'))) {
    return false;
  }
  for (size_t i = 1; i < word.size(); ++i) {
    if ((word[0] < '0') || (word[0] > '9')) {
      return false;
    }
  }
  return true;
}
std::vector<Token> Tokenize(std::string_view str) {
  std::vector<Token> tokens;
  Token token;
  std::vector<std::string> words = WordsSeperetion(str);
  size_t size = words.size();
  for (size_t i = 0; i < size; ++i) {
    if (words[i] == "+") {
      token = PlusToken();
      tokens.push_back(token);
    } else if (words[i] == "-") {
      token = MinusToken();
      tokens.push_back(token);
    } else if (words[i] == "*") {
      token = MultiplyToken();
      tokens.push_back(token);
    } else if (words[i] == "/") {
      token = DivideToken();
      tokens.push_back(token);
    } else if (words[i] == "%") {
      token = ResidualToken();
      tokens.push_back(token);
    } else if (words[i] == "(") {
      token = OpeningBracketToken();
      tokens.push_back(token);
    } else if (words[i] == ")") {
      token = ClosingBracketToken();
      tokens.push_back(token);
    } else if (words[i] == "sqr") {
      token = SqrToken();
      tokens.push_back(token);
    } else if (words[i] == "max") {
      token = MaxToken();
      tokens.push_back(token);
    } else if (words[i] == "min") {
      token = MinToken();
      tokens.push_back(token);
    } else if (words[i] == "abs") {
      token = AbsToken();
      tokens.push_back(token);
    } else if (NunberChecker(words[i])) {
      token = NumberToken(static_cast<int>(std::stoi(words[i])));
      tokens.push_back(token);
    } else {
      token = UnknownToken(words[i]);
      tokens.push_back(token);
    }
  }
  return tokens;
}