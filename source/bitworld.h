#ifndef BITWORLD_H
#define BITWORLD_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <cstddef>
#include <cstring>

const size_t STMAX = std::numeric_limits<std::size_t>::max();

class BitWorld {
public:
  BitWorld(size_t, size_t);
  ~BitWorld();

  void update(size_t, size_t);

  void debug_print();


private:
  size_t size_x;
  size_t size_y;
  char* data;
  char* buff;

  void get_neighbor_indices(size_t, std::vector<size_t>&);
  short int check_condition(size_t, std::vector<size_t>&);


};


#endif
