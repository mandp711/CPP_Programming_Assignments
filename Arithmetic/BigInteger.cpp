/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
List.cpp
Implementation file for BigInteger
*/
#include "BigInteger.h"
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <cstdlib>

const long base = 1000000000; // Base 10^9
const int power = 9;

// Negate each element of the List L (multiply by -1)
void negateList(List& L) {
   L.moveFront();
   while (L.position() < L.length()) {
       L.setAfter(-L.peekNext());
       L.moveNext();
   }
}


// Sum two lists A and B, storing the result in S
void sumList(List& S, List A, List B, int sgn) {
   S.clear();

   A.moveBack();
   B.moveBack();


   long remainder = 0;
   while (A.position() > 0 || B.position() > 0 || remainder != 0) {
       long DigitA = (A.position() > 0) ? A.peekPrev() : 0;
       long DigitB = (B.position() > 0) ? sgn * B.peekPrev() : 0;
       long sum = DigitA + DigitB + remainder;
       remainder = sum / base;
       sum %= base;

       S.moveFront();
       S.insertBefore(sum);

       if (A.position() > 0) A.movePrev();
       if (B.position() > 0) B.movePrev();
   }


   while (S.length() > 1 && S.front() == 0) {
       S.moveFront();
       S.eraseAfter();
   }
}


int normalizeList(List& L) {
   if (L.length() == 0) {
       return 0;
   }

   L.moveBack();
   long rem = 0;
   while (L.position() > 0) {
       long num = L.peekPrev() + rem;
       if (num < 0) {

           rem = -1;
           num += base;
       } else {
           rem = num / base;
           num %= base;
       }

       L.setBefore(num);
       L.movePrev();
   }


   if (rem > 0) {
       L.moveFront();
       L.insertAfter(rem);
   } else if (rem < 0) {
       return -1;
   }

   while (L.length() > 1 && L.front() == 0) {
       L.eraseAfter();
   }

   return (L.length() > 1 || L.front() != 0) ? 1 : 0;
}


void shiftList(List& L, int p) {
   L.moveBack();
   for (int i = 0; i < p; i++) {
       L.insertBefore(0);
   }
}


void scalarMultList(List& L, ListElement m) {
   L.moveFront();
   while (L.position() < L.length()) {
       L.setAfter(L.peekNext() * m);
       L.moveNext();
   }
}

// Constructor: Default
BigInteger::BigInteger(): signum(0), digits() {}

// Constructor: Long
BigInteger::BigInteger(long x) {
  if (x == 0) {
       signum = 0;
       digits.insertBefore(0);
   } else {
       signum = (x > 0) ? 1 : -1;
       x = std::abs(x);


       while (x > 0) {
           digits.insertBefore(x % base);
           x /= base;
       }
   }
}

// Constructor: String
BigInteger::BigInteger(std::string s) {
   if (s.empty()) {
       throw std::invalid_argument("BigInteger: Constructor: empty string");
   }


   signum = (s[0] == '-') ? -1 : 1;
   if (s[0] == '+' || s[0] == '-') {
       s.erase(0, 1);
   }


   if (s.empty()) {
       throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
   }


   for (char c : s) {
       if (!isdigit(c)) {
           throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
       }
   }


   int pos = s.length() % power;
   if (pos > 0) {
       digits.insertBefore(std::stol(s.substr(0, pos)));
   }
   for ( ; pos < static_cast<int>(s.length()); pos += power) {
       digits.insertBefore(std::stol(s.substr(pos, power)));
   }


   digits.moveFront();
   while (digits.length() > 1 && digits.peekNext() == 0) {
       digits.eraseAfter();
       digits.moveFront();
   }


   if (digits.length() == 0) {
       signum = 0;
       digits.insertBefore(0);
   }
}


// Constructor: Copy
BigInteger::BigInteger(const BigInteger & N): signum(N.signum), digits(N.digits) {}

// Accessor: Sign
int BigInteger::sign() const {
  return signum;
}

// Accessor: Compare
int BigInteger::compare(const BigInteger& N) const {
    if (signum != N.signum) {
        return (signum > N.signum) ? 1 : -1;
    }
    if (signum == 0) {
        return 0;
    }

    int result = 0;
    int lengthA = digits.length();
    int lengthB = N.digits.length();

    if (lengthA != lengthB) {
        result = (lengthA > lengthB) ? 1 : -1;
    } else {
        List listA = digits;
        List listB = N.digits;

        listA.moveFront();
        listB.moveFront();

        while (listA.position() < listA.length() && result == 0) {
            long elemA = listA.peekNext();
            long elemB = listB.peekNext();

            if (elemA != elemB) {
                result = (elemA > elemB) ? 1 : -1;
            }

            listA.moveNext();
            listB.moveNext();
        }
    }

    return (signum == 1) ? result : -result;
}


// Manipulation: MakeZero
void BigInteger::makeZero() {
  signum = 0;
  digits.clear();
}

// Manipulation: Negate
void BigInteger::negate() {
  signum = -signum;
}

// Arithmetic: Add
BigInteger BigInteger::add(const BigInteger& N) const {
    if (signum == 0) {
        return N;
    }
    if (N.signum == 0) {
        return *this;
    }

    BigInteger sumResult;

    if (signum == N.signum) {
        sumResult.signum = signum;
        List listA = digits;
        List listB = N.digits;

        listA.moveBack();
        listB.moveBack();
        long carryOver = 0;

        while (listA.position() > 0 || listB.position() > 0 || carryOver != 0) {
            long currentSum = carryOver;
            if (listA.position() > 0) {
                currentSum += listA.movePrev();
            }
            if (listB.position() > 0) {
                currentSum += listB.movePrev();
            }
            carryOver = currentSum / base;
            sumResult.digits.insertAfter(currentSum % base);
        }
    } else {
        BigInteger adjustedN = N;
        adjustedN.signum = -adjustedN.signum;
        sumResult = this->sub(adjustedN);
    }

    sumResult.digits.moveFront();
    while (sumResult.digits.length() > 0 && sumResult.digits.peekNext() == 0) {
        sumResult.digits.moveNext();
        sumResult.digits.eraseBefore();
    }
    if (sumResult.digits.length() == 0) {
        sumResult.signum = 0;
    }

    return sumResult;
}


// Arithmetic: Sub
BigInteger BigInteger::sub(const BigInteger & N) const {
  BigInteger result;


   if (this->signum != N.signum) {
       sumList(result.digits, this->digits, N.digits, 1);
       result.signum = this->signum;
   } else {
       int cmp = this->compare(N);


       if (cmp == 0) {
           result.makeZero();
           return result;
       }


       if ((cmp > 0 && this->signum > 0) || (cmp < 0 && this->signum < 0)) {
           sumList(result.digits, this->digits, N.digits, -1);
           result.signum = this->signum;
       } else {
           sumList(result.digits, N.digits, this->digits, -1);
           result.signum = -this->signum;
       }
   }


   normalizeList(result.digits);


   while (result.digits.length() > 1 && result.digits.front() == 0) {
       result.digits.eraseAfter();
   }
   if (result.digits.length() == 1 && result.digits.front() == 0) {
       result.signum = 0;
   }


   return result;
}


// Arithmetic: Mult
BigInteger BigInteger::mult(const BigInteger& N) const {
   BigInteger product;
   if (signum == 0 || N.signum == 0) {
       return product;
   }
   List sum;
   List NDigitsCopy = N.digits;
   List temp;


   NDigitsCopy.moveBack();


   for (int shift = 0; NDigitsCopy.position() > 0; shift++, NDigitsCopy.movePrev()) {
       temp = this->digits;
       scalarMultList(temp, NDigitsCopy.peekPrev());
       shiftList(temp, shift);
       List newSum = sum;
       sumList(sum, newSum, temp, 1);
       normalizeList(sum);
   }
   product.digits = sum;
   product.signum = signum * N.signum;
   return product;
}


// Conversion: to_string
std::string BigInteger::to_string() {
   if (this->signum == 0) return "0";

   std::string str = (this->signum == -1) ? "-" : "";

   digits.moveFront();
   while (digits.front() == 0 && digits.length() > 1) {
       digits.eraseAfter();
       digits.moveFront();
   }

   for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
       std::string d = std::to_string(digits.peekNext());
       std::string padding = "";

       while (static_cast<int>(padding.length() + d.length()) < power && digits.position() > 0) {
           padding += '0';
       }
       str += padding + d;
   }

   return str;
}

// Operators
std::ostream & operator << (std::ostream & stream, BigInteger N) {
  return stream << N.to_string();
}

bool operator == (const BigInteger & A,
  const BigInteger & B) {
  return A.compare(B) == 0;
}

bool operator < (const BigInteger & A,
  const BigInteger & B) {
  return A.compare(B) < 0;
}

bool operator <= (const BigInteger & A,
  const BigInteger & B) {
  return A.compare(B) <= 0;
}

bool operator > (const BigInteger & A,
  const BigInteger & B) {
  return A.compare(B) > 0;
}

bool operator >= (const BigInteger & A,
  const BigInteger & B) {
  return A.compare(B) >= 0;
}

BigInteger operator + (const BigInteger & A,
  const BigInteger & B) {
  return A.add(B);
}

BigInteger operator - (const BigInteger & A,
  const BigInteger & B) {
  return A.sub(B);
}

BigInteger operator * (const BigInteger & A,
  const BigInteger & B) {
  return A.mult(B);
}

BigInteger operator += (BigInteger & A,
  const BigInteger & B) {
  A = A.add(B);
  return A;
}

BigInteger operator -= (BigInteger & A,
  const BigInteger & B) {
  A = A.sub(B);
  return A;
}

BigInteger operator *= (BigInteger & A,
  const BigInteger & B) {
  A = A.mult(B);
  return A;
}
