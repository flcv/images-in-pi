#include <algorithm>
#include <cstddef>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

const int DESIRED_PATTERN[] = {
  0,1,1,
  1,0,0,
  1,1,1,
  1,0,1
};

const int WIDTH = 3;
const int LENGTH = (sizeof(DESIRED_PATTERN)/sizeof(*DESIRED_PATTERN));
const int HEIGHT = LENGTH/WIDTH;

std::string intArrayToString(const int arr[], int size){
  std::string ret = "";
  for (int i = 0; i < size; i++) {
    ret.append(std::to_string(arr[i]));
  }

  return ret;
}

std::string decimalToBinary(int dec) {
  return std::bitset<4>(dec).to_string();
}

// slightly modified version of the code found in:
// https://www.cs.ox.ac.uk/people/jeremy.gibbons/publications/spigot.pdf
// their obfuscation is pointless and infuriating
std::string getDigitsOfPi() {
  std::string ret = "";
  long a[52514],b=0,c=52514,d=0,e=0,f=1e4,g=0,h=0;
  for(;b=c-=14;h=4){ret.append(std::to_string(e+d/f));for(e=d%=f;g=--b*2;d/=g)d=d*b+f*(h?a[b]:f/5),a[b]=d%--g;}

  return ret.erase(0,1);
}

template<typename T>
void printPattern(T pattern, const int x, const int y){
  for(int i = 0; i < y; i++) {
    for(int j = 0; j < x; j++) {
      int a = (int)pattern[i*x+j];
      std::cout << ((a == 1 || a == 49) ? "\u2588\u2588" : "  ");
    }
    std::cout << "\n";
  }
}

int main() {

  // needs to check an area twice as long as the DESIRED_PATTERN's length

  // init; generate digits of pi then convert it to binary
  std::string x = getDigitsOfPi();
  std::string piBinary = "";
  for(auto c : getDigitsOfPi()) {
    piBinary.append(decimalToBinary(c));
  }

  // begin search for desired pattern
  auto start = std::chrono::high_resolution_clock::now();
  std::cout << "Searching for...\n";
  std::cout << "================\n";
  printPattern(DESIRED_PATTERN, WIDTH, HEIGHT);
  std::cout << "================\n";
  std::cout << "\n\n\n";  
  
  
  std::size_t pos = piBinary.find(intArrayToString(DESIRED_PATTERN, LENGTH));

  auto end = std::chrono::high_resolution_clock::now();
  if (pos == std::string::npos){
    std::cout << "The pattern was not found " << "\n";
  } else {
    std::cout << "The pattern was first found at position " << std::to_string(pos) << "\n\n";
    // min and max to ensure no indexing out-of-bounds errors,
    // but also want to show some of the surrounding patterns for context
    std::size_t l = std::min(pos+LENGTH+6*WIDTH, piBinary.size())-pos, m = 0;
    std::string excerpt = piBinary.substr(std::max(m,pos-3*WIDTH), l);
    printPattern(excerpt, WIDTH, (int)floor(excerpt.size()/(double)WIDTH));
  }
  
  std::cout << "Time elapsed: " << (duration_cast<std::chrono::microseconds>(end - start).count()/(pow(10,3))) << " ms";

  return 0;
}