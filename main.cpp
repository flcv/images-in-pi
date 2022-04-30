#include <cstddef>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <chrono>

const int DESIRED_PATTERN[] = {
  0,1,0,
  1,1,1,
  0,1
};

const int WIDTH = 4;

const int HEIGHT = (sizeof(DESIRED_PATTERN)/sizeof(*DESIRED_PATTERN));

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
  bool found = false;
  auto start = std::chrono::high_resolution_clock::now();
  while(!found) {
    std::cout << "Searching for...\n";
    printPattern(DESIRED_PATTERN, WIDTH, HEIGHT);
    std::cout << "\n\n\n";
    // printPattern(piBinary, WIDTH, (int)floor(piBinary.size()/3.0));

  }
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << "Time elapsed: " << (duration_cast<std::chrono::microseconds>(end - start).count()/(pow(10,6)));

  return 0;
}