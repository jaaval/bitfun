

#include <iostream>

#include "bitworld.h"
#include <time.h> //sleep

int main() {
  std::cout << "This is a game of life!" << std::endl;

  struct timespec ts = {2, 0};

  BitWorld *bw = new BitWorld(10,10);
  for (int i = 0; i < 20; i++) {
    bw->debug_print();
    nanosleep(&ts, NULL);
    bw->update(0,0);
  }


  return 0;
}
