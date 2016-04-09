/*
File: header.h
Author: Georgios Kamaras
Purpose: header file for OOP Exercise 3
*/
#include "header.h"

using namespace std;

int N, L, good_thrsh, bad_thrsh; // global variables

int main(int argc, char *argv[]){
  /* take command line arguments, evaluate and assign them */
  if(argc != 6){  // if we don't have 6 arguments (5 for N, M, L, good_thrsh, bad_thrsh + 1 the executable's name)...
    cout << "ERROR! Wrong number of arguments!" << endl;  // ...print that something's wrong...
    return -1;                                            // ...and terminate
  }
  /* assigning N, M, L, good_thrsh, bad_thrsh variables' values */
  N = atoi(argv[1]);
  int M = atoi(argv[2]);
  L = atoi(argv[3]);
  good_thrsh = atoi(argv[4]);
  bad_thrsh = atoi(argv[5]);
  if(N <= 0 || M <= 0 || L <= 0 || good_thrsh <= 0 || bad_thrsh <= 0){ // L must be greater than 0
    cout << "ERROR! Wrong argument value. All arguments' values should be above 0!" << endl;
    return -2;
  }
  /* initialize random seed for generator: */
  srand(time(NULL));
  /* 1st objective, create a society of N creatures */
  creature_society world(N);
  cout << endl;
  /* 2nd objective, M times, at a random position, random action in that position */
  int random, position;
  for(int i = 1; i <= M; i++){  // for as many times as instructed
    random = rand();    // random integer
    position = rand()%N;  // random position in [0, N-1]
    if(!(random%2)){      // if random is even
      cout << "Blessing position " << position << endl; // debug, position that we are blessing
      world.blessPosition(position);  // bless the position
      cout << endl;
    }else{    // else (if random is odd)
      cout << "Beating position " << position << endl; // debug, position that we are beating
      world.beatPosition(position);   // beat the position
      cout << endl;
    }
  }
  cout << endl;
  /* 3rd objective, evaluate society and print a message about it */
  if(world.no_of_good() == N) cout << "Good Dominates in the World!" << endl;   // if the whole society has good creatures
  else if(world.no_of_zobies() == N) cout << "This is a dead society" << endl;  // if the whole society is zombies
  else cout << "Try again to improve the world" << endl;                        // if none of the above

  return 0;
}
