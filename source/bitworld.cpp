


 #include "bitworld.h"


 BitWorld::BitWorld(size_t x, size_t y):
  size_x(x), size_y(y)
 {
   data = new char[x*y];
   buff = new char[x*y];
   std::memset(buff, 0, x*y);
   for (size_t i = 0; i < x*y; i++) {
     data[i] = rand() % 256;
   }
 }

 BitWorld::~BitWorld(){
   delete[] data;
   delete[] buff;
 }

 void BitWorld::update(size_t start, size_t stop) {
   size_t size = size_x * size_y;
   short int friends;
   std::vector<size_t> nhs(8, STMAX);

   for (size_t i = 0; i < size; i++) {

     size_t ofset = i / 8;
     short int mask_index = i % 8;
     unsigned char mask = 1;
     mask = mask << mask_index;

     friends = check_condition(i, nhs);
     if (friends != 2) {
       buff[ofset] = buff[ofset] & ~mask;
     } else {
       buff[ofset] = buff[ofset] | mask;
     }
   }

   char* temp = data;
   data = buff;
   buff = temp;
 }

 void BitWorld::get_neighbor_indices(size_t index, std::vector<size_t>& nhs){

  size_t row = index / size_x;
  size_t col = index % size_x;

  int numn = 8;
  if (row==0 || row==size_y-1) {
    numn -= 3;
  }
  if (col==0 || col==size_x-1) {
    numn = std::max(3, numn-3);
  }
  std::fill(nhs.begin(), nhs.end(), STMAX);



  int i = 0;

  if (col > 0) {
    nhs[i++] = index - 1;
    //std::cout << 1 << std::endl;
  }
  if (row > 0) {
    nhs[i++] = index - size_x;
    //std::cout << 2 << std::endl;
  }
  if (col > 0 && row > 0) {
    nhs[i++] = index - size_x - 1;
    //std::cout << 3 << std::endl;
  }
  if (col < size_x-1) {
    nhs[i++] = index + 1;
    //std::cout << 4 << std::endl;
  }
  if (row < size_y-1) {
    nhs[i++] = index + size_x;
    //td::cout << 5 << std::endl;
  }
  if (col < size_x-1 && row < size_y-1) {
    nhs[i++] = index + size_x + 1;
    //std::cout << 6 << std::endl;
  }
  if (col > 0 && row < size_y-1) {
    nhs[i++] = index + size_x - 1;
    //std::cout << 7 << std::endl;
  }
  if (col < size_x-1 && row > 0) {
    nhs[i++] = index - size_x + 1;
    //std::cout << 8 << std::endl;
  }
  /*
  for (auto iter = nhs.begin(); iter < nhs.end(); iter++) {
    if (*iter == STMAX) {
      std::cout << "STMAX    ";
    } else {
      std::cout << *iter << "   ";
    }
  }
  std::cout<< std::endl;
  */
 }


 short int BitWorld::check_condition(size_t index, std::vector<size_t>& nhs) {
   get_neighbor_indices(index, nhs);

   short int num_alive = 0;
   for (auto iter = nhs.begin(); iter < nhs.end(); iter++) {
     if (*iter == STMAX) {
       break;
     }
     size_t ofset = *iter / 8;
     short int mask_index = *iter % 8;
     unsigned char mask = 1;
     mask = mask << mask_index;

     if (data[ofset] & mask) {
       num_alive++;
     }
   }
   return num_alive;
 }


 void BitWorld::debug_print() {
   size_t index;
   std::cout << "\n----------------------------" << std::endl;
   for (size_t i = 0; i < size_y; i++) {
     for (size_t j = 0; j < size_x; j++) {
       index = i*size_x + j;
       size_t ofset = index / 8;
       short int mask_index = index % 8;
       unsigned char mask = 1;
       mask = mask << mask_index;
       if (data[ofset] & mask) {
         std::cout << "X";
       } else {
         std::cout << "O";
       }
     }
     std::cout << std::endl;
   }
   std::cout << "----------------------------" << std::endl;

 }
