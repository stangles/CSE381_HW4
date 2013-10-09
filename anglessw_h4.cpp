/**
 * Author: Steven Angles
 * CSE381 Fall 2013
 * Dr. Rao
 *
 * This program reads in a roman numeral algebraic expression
 * and prints its decimal and english values.
 */
#include <iostream>
#include <unordered_map>
#include <vector>

/**
 * Function prototypes
 */
void getInput(std::vector<std::string>& words);
int getNumeralValue(bool isNeg, std::string numeral);
void printValsAndTotal(std::vector<std::string> wordVec);
std::string decToEnglish(int value);
std::string rangeEnglish(int value, int magnitude, std::string englishMag);

/**
 * Mapping of integers to english words.
 */
std::unordered_map<int, std::string> digitMap =
  {{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}, 
   {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}, {10, "ten"},
   {11, "eleven"}, {12, "twelve"}, {13, "thirteen"}, {14, "fourteen"},
   {15, "fifteen"}, {16, "sixteen"}, {17, "seventeen"}, {18, "eighteen"}, {19, "nineteen"},
   {20, "twenty"}, {30, "thirty"}, {40, "forty"}, {50, "fifty"},
   {60, "sixty"}, {70, "seventy"}, {80, "eighty"}, {90, "ninety"}, {100, "hundred"},
   {1000, "thousand"}};
/**
 * Mapping of roman numerals to their decimal equivalents.
 */
std::unordered_map<char, int> numeralMap =
  {{'m', 1000}, {'d', 500}, {'c', 100}, {'l', 50}, {'x', 10}, {'v', 5}, {'i', 1}};

/**
 * Main, intiates getInput() and printValsAndTotal() function calls
 */
int main() {
  std::cout << "Enter expression with roman numbers:" << std::endl;

  std::vector<std::string> wordVec;
  getInput(wordVec);
  printValsAndTotal(wordVec);

  return 0;
}

/**
 * Convenience method to read roman numerals into 
 * a vector that contains strings.
 */
void getInput(std::vector<std::string>& words) {
  std::string word;
  while (std::cin >> word) {
    words.push_back(word);
  }
}

/**
 * Reads a roman numeral string and returns its integer value.
 */
int getNumeralValue(bool isNeg, std::string numeral) {
  int value = 0;
  unsigned int i;
  for (i=0; (i<numeral.size()); i++) {
    // check to see if the current character is a valid roman numeral
    if (numeralMap.find(numeral[i]) != numeralMap.end()) {
      // check to see if the next character is a valid roman numeral
      // and if it is greater than the current one
      if ((numeralMap.find(numeral[i+1]) != numeralMap.end()) && numeralMap[numeral[i+1]] > numeralMap[numeral[i]]) {
	value += (numeralMap[numeral[i+1]] - numeralMap[numeral[i]]);
	i++;
      } else {
	value += numeralMap[numeral[i]];
      }
    }
  }
  return isNeg ? -(value) : value;
}

/**
 * Control method to print the decimal equivalences of
 * roman numerals in addition to the expression evaluation
 * and the english word equivalent of the expression value.
 */
void printValsAndTotal(std::vector<std::string> wordVec) {
  std::string sign = "*";
  int finalVal = 0;
  for (std::string & s : wordVec) {
    int value = 0;
    // if the current string is a sign
    if (s != "+" && s != "-") {
      if (sign == "-") {
	value = getNumeralValue(true, s);
      } else {
	value = getNumeralValue(false, s);
      }
      // print each roman numeral and its equivalent decimal value
      std::cout << s << " = " << abs(value) << std::endl;
    } else {
      sign = s;
    }
    finalVal += value;
  }
  std::cout << "Decimal value of equation = " << finalVal << std::endl;
  std::cout << "Result in words: " << decToEnglish(finalVal) << std::endl;
}

/**
 * Recursive method to convert an integer value
 * into english words.
 */
std::string decToEnglish(int value) {
  if (value == 0) return "zero";
  if (value > 0 && value <= 20) {
    return digitMap[value];
  }
  if (value > 20 && value < 100) {
    int tens = value - (value % 10);
    return digitMap[tens] + " " + decToEnglish(value%10);
  }
  if (value >= 100 && value < 1000) {
    return rangeEnglish(value, 100, "hundred");
  }
  if (value >= 1000 && value < 1000000) {
    return rangeEnglish(value, 1000, "thousand");
  }
  return "Cannot parse digit to english words";
}

/**
 * Convenience method to handle the recursive
 * calls to decToEnglish() for the ranges 100 to 1000
 * and 1000 to 1000000.
 */
std::string rangeEnglish(int value, int magnitude, std::string englishMag) {
  int extra = value % magnitude;
  int magNum = (value - extra) / magnitude;
  // value is one hundred or one thousand
  if (magNum == 0 && extra == 0) {
    return "one " + englishMag + " ";
  } else if (magNum == 0) { // value is one hundred/thousand <something>
    return "one " + englishMag + decToEnglish(extra) + " ";
  } else if (extra == 0) { // value is <something> hundred/thousand
    return decToEnglish(magNum) + englishMag + " ";
  } else { // value is <something> hundred/thousand <something>
    return decToEnglish(magNum) + " " + englishMag + " " + decToEnglish(extra);
  }
}
