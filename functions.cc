/*
File: functions.cc
Author: Georgios Kamaras
Purpose: classes functions' file for OOP Exercise 3
*/
#include "header.h"
#include "names.h"

using namespace std;

/* creature class constructor */
creature::creature(const string n, const int L, position* posp) : name(n), pp(posp), life(L) {
  cout << "A creature named " << name << " has just been created!" << endl; // creature's construction message
}
/* creature class copy constructor */
creature::creature(const creature& c, const bool cloning, position* pos = NULL){
  this->name = c.name;    // copy c's name
  this->life = c.life;    // copy c's life
  if(!cloning) this->pp = c.pp; // if we're not cloning copy c's position (when cloning, we do not want (*this)'s initial position pointer to be lost)
  else this->pp = pos;    // if we are cloning, we want the creature to be able to point back to his position
  cout << "A creature named " << name << " has just been created by copying!" << endl;  // creature's copy construction message
}
/* creature class destructor (is a virtual function) */
creature::~creature(){
  cout << "A creature named " << name << " is about to be destroyed" << endl; // creature's destruction message
}
/* is a creature zombie or not? */
bool creature::is_a_zobie() const{
  return (life == 0);   // if life is 0 then true (is a zobie), else false (is not a zobie)
}
/* clone a creature in another creature's place in society */
void creature::clone(creature* &c, position* pos){
  if(is_a_zobie()) return;  // we can't clone a zobie
  delete c;                 // delete the creature in whose position we want to clone (*this) creature
  if(is_a_good()) c = new good_creature(*this, true, pos);  // if (*this) is a good, then we're cloning a good...
  else c = new bad_creature(*this, true, pos);              // ...else, we're cloning a bad
  cout << "A creature named " << name << " has just been cloned!" << endl;  // creature's cloning message
}
/* beat a creature */
void creature::beat(){
  if(is_a_zobie()) return;  // we can't beat a zobie
  life--;   // beat creature
  cout << "A creature named " << name << " just got beaten!" << endl; // creature's beating message
}
/* bless a creature */
void creature::bless(){
  if(is_a_zobie()) return;  // we can't bless a zobie
  life++;   // bless creature
  cout << "A creature named " << name << " just got blessed!" << endl; // creature's blessing message
}
/* good creature class constructor */
good_creature::good_creature(const string n, const int L, position* posp) : creature(n, L, posp) {
  cout << "A good creature has been created!" << endl;  // good creature's construction message
}
/* good creature class copy constructor */
good_creature::good_creature(const creature& c, const bool cloning, position* pos = NULL) : creature(c, cloning, pos){  // for copy construction we call the (general) creature's copy constructor
  cout << "A good creature has just been created by copying!" << endl;  // good creature's copy construction message
}
/* good creature class destructor */
good_creature::~good_creature(){
  cout << "A good creature is about to be destroyed" << endl; // good creature's destruction message
}
/* bless a good creature */
void good_creature::bless(){
  if(is_a_zobie()) return;  // we can't bless a zobie
  creature::bless();        // typical blessing actions
  if(life > good_thrsh) pp->crsocp->clone_next(pp->pos);  // if good creature is robust (eurosto) then clone it to it's next position
  cout << "A good creature just got blessed!" << endl;    // good creature's blessing message
}
/* is a creature good or not? (is a pure virtual function) */
bool good_creature::is_a_good() const{
  return true;
}
/* bad creature class constructor */
bad_creature::bad_creature(const string n, const int L, position* posp) : creature(n, L, posp) {
  cout << "A bad creature has been created!" << endl; // bad creature's construction message
}
/* bad creature class copy constructor */
bad_creature::bad_creature(const creature& c, const bool cloning, position* pos = NULL) : creature(c, cloning, pos) {
  cout << "A bad creature has just been created by copying!" << endl; // bad creature's copy construction message
}
/* bad creature class destructor */
bad_creature::~bad_creature(){
  cout << "A bad creature is about to be destroyed" << endl;  // bad creature's destruction message
}
/* bless a good creature */
void bad_creature::bless(){
  if(is_a_zobie()) return;  // we can't bless a zobie
  creature::bless();        // typical blessing actions
  if(life > bad_thrsh) pp->crsocp->clone_zobies(pp->pos); // if bad creature is robust (eurosto) then clone it to all it's next positions that are currently occupied by zobies
  cout << "A bad creature just got blessed!" << endl;     // bad creature's blessing message
}
/* is a creature good or not? (is a pure virtual function) */
bool bad_creature::is_a_good() const{
  return false;
}
/* creature society class constructor */
creature_society::creature_society(const int N) : CREATURENUM(N) {
  positionArr = new position[N]; // create (an array of) N positions (1 for each of the society's creatures)
  stringstream sstm;      // our stringstream
  string name;            // creature's final name
  int i, random, namepos;
  for(i = 0; i < N; i++){ // in each of the array's positions
    namepos = rand() % ARRSIZE; // pick a random number [0, ARRSIZE-1], which will be the (position of the) name of the created creature in the bad of good names' array
    random = rand();  // generate number randomly
    if(!(random%2)){  // if random number is even, create a good creature
      sstm << goodName[namepos] << i; // creature's name will be unique...
      name = sstm.str();  // ...a random name and it's position in the society's array added to the end
      sstm.str("");       // emptying sstm stringstream
      positionArr[i].crp = new good_creature(name, L, &(positionArr[i]));
    }else{            // else, create a bad creature
      sstm << badName[namepos] << i;  // creature's name will be unique...
      name = sstm.str();  // ...a random name and it's position in the society's array added to the end
      sstm.str("");       // emptying sstm stringstream
      positionArr[i].crp = new bad_creature(name, L, &(positionArr[i]));
    }
    positionArr[i].crsocp = this;   // society's pointer points to (*this) creature society
    positionArr[i].pos = i;         // current creature's position in the society
  }
  cout << "A creature society has just been created!" << endl;  // creature society's construction message
}
/* creature society class destructor */
creature_society::~creature_society(){
  cout << "A creature society is about to be destroyed" << endl;  // creature society's destruction message
  delete[] positionArr; // call the destructor of each one of the positions created (destroy the positions' array)
}
/* beat the creature of a specific society's position */
void creature_society::beatPosition(const int i){
  positionArr[i].crp->beat();   // beat the creature of the i position in the array
}
/* bless the creature of a specific society's position */
void creature_society::blessPosition(const int i){
  positionArr[i].crp->bless();  // bless the creature of the i position in the array
}
/* clone the creature of a specific society's position, in it's next position */
void creature_society::clone_next(const int i){
  (positionArr[i].crp)->clone(positionArr[(i+1)%N].crp, getPosition((i+1)%N));  // clone next position (if we are at the end, next is the beginning)
}
/* clone the creature of a specific society's position, in all it's next positions that have creatures that are zobies */
void creature_society::clone_zobies(const int i){
  for(int j = i+1; j < CREATURENUM; j++){ // for as far as we can, but within the limits of the positions' array
    if(positionArr[j].crp->is_a_zobie()) (positionArr[i].crp)->clone(positionArr[j].crp, getPosition(j)); // if j position occupied by a zobie, do the cloning...
    else break; // ...else, clone no more
  }
}
/* number of good creatures in a society */
int creature_society::no_of_good() const{
  int counter = 0;    // initialize counter
  for(int i = 0; i < CREATURENUM; i++) if(positionArr[i].crp->is_a_good()) counter++; // count the good creatures
  return counter;     // return number of goods
}
/* number of bad creatures in a society */
int creature_society::no_of_zobies() const{
  int counter = 0;    // initialize counter
  for(int i = 0; i < CREATURENUM; i++) if(positionArr[i].crp->is_a_zobie()) counter++; // count the zobies
  return counter;     // return number of zobies
}
/* get the address of a specific position in the society */
position* creature_society::getPosition(const int i){
  return &(positionArr[i]);   // return the address of the requested position
}
