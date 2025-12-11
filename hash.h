#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
      // Add your code here
      unsigned long long w[5] = {0};
      int pos = k.length() - 1;
      bool flagBreak = false;
      for(int i=0; i<5; i++){
        if(flagBreak){
          break;
        }
        for(int j=0; j<6; j++){ // takes 6 chars
          if(pos < 0){
            flagBreak = true;
            break;
          }
          //std::cout << "j is " << j << std::endl;
          HASH_INDEX_T x = 1;
          HASH_INDEX_T base = 36;
          HASH_INDEX_T exp = j;
          for(int l=0; exp != 0; l++){
            if(exp%2){
              x = x*base;
            }
            base = base*base;
            exp /= 2;
          }
          w[4-i] += letterDigitToNumber(k[pos]) * x;
          pos--;
          // std::cout << "w at index " << 4-i << " is " << w[4-i] << std::endl;
        }
        //std::cout << "final w at index " << 4-i << " is " << w[4-i] << std::endl;
      }
      
      unsigned long long h = 0;
      for(int i=0; i<5; i++){
        h += rValues[i]*w[i];
      }
      
      return h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
      // Add code here or delete this helper function if you do not want it
      HASH_INDEX_T value;
      if(letter >= 'a' && letter <= 'z'){
        value = letter - 'a';
      }
      else if(letter >= 'A' && letter <= 'Z'){
        value = letter - 'A';
      }
      else if(letter >= '0' && letter <= '9'){
        value = (letter - '0') + 26;
      }
      return value;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
