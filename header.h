/*
File: header.h
Author: Georgios Kamaras
Purpose: classes header file for OOP Exercise 3
*/
#ifndef __HEADER__
#define __HEADER__

#include <iostream>     // for opperations related to console output
#include <sstream>      // for stringstream
#include <cstdlib>      // for atoi()
#include <ctime>        // for initialising srand()

extern int N, L, good_thrsh, bad_thrsh;  // declaring the global variables (that are going to be defined in some linked file)

struct position;  // declaring the struct position, so, at compilation time, compiler takes it as known for the following classes' definitions
/* creature's class description */
class creature{
  std::string name;   // creature's name
protected:
  position* pp;       // pointer to the creature's position
  int life;           // creature's life
public:
  creature(const std::string, const int, position*);  // creature class constructor
  creature(const creature&, const bool, position*);   // creature class copy constructor
  virtual ~creature();                // creature class destructor (is a virtual function)
  bool is_a_zobie() const;            // is a creature zombie or not?
  virtual bool is_a_good() const = 0; // is a creature good or not? (is a pure virtual function)
  void clone(creature*&, position*);  // clone a creature in another creature's place in society
  void beat();                        // beat a creature
  virtual void bless();               // bless a creature
};
/* good creature's class description (a subclass of creature's class) */
class good_creature : public creature{
public:
  good_creature(const std::string, const int, position*); // good creature class constructor
  good_creature(const creature&, const bool, position*);  // good creature class copy constructor
  ~good_creature();                           // good creature class destructor
  virtual void bless();                       // bless a good creature
  virtual bool is_a_good() const;             // is a creature good or not? (is a pure virtual function)
};
/* bad creature's class description (a subclass of creature's class) */
class bad_creature : public creature{
public:
  bad_creature(const std::string, const int, position*); // bad creature class constructor
  bad_creature(const creature&, const bool, position*);  // bad creature class copy constructor
  ~bad_creature();                           // bad creature class destructor
  virtual void bless();                      // bless a good creature
  virtual bool is_a_good() const;            // is a creature good or not? (is a pure virtual function)
};
/* creature society's class description */
class creature_society{
  int CREATURENUM;        // number of creatures in a society
  position* positionArr;  // a pointer to the initial position (of the array(/sequence)) of the society
public:
  creature_society(const int);    // creature society class constructor
  ~creature_society();            // creature society class destructor
  void beatPosition(const int);   // beat the creature of a specific society's position
  void blessPosition(const int);  // bless the creature of a specific society's position
  void clone_next(const int);     // clone the creature of a specific society's position, in it's next position
  void clone_zobies(const int);   // clone the creature of a specific society's position, in all it's next positions that have creatures that are zobies
  int no_of_good() const;         // number of good creatures in a society
  int no_of_zobies() const;       // number of bad creatures in a society
  position* getPosition(const int); // get the address of a specific position in the society
};
/* position's structure description */
struct position{
  creature* crp;            // pointer to the creature that "lives" in this position
  creature_society* crsocp; // pointer to a creature society
  int pos;                  // position's number in the above creature society's array
  ~position(){              // position structure's destructor
    std::cout << "A position is about to be deleted" << std::endl;  // message of destruction
    delete crp;   // delete the creature (call creature's destructor)
  }
};

#endif
