Georgios Kamaras - 1115201400058

*Compile: make
*Clean: make clean
*Run: ./society {arg1} {arg2} {arg3} {arg4} {arg5}
    for example:
      ./society 100 1000 10 6 5



*Notes:
-In creature::clone(creature* &c, position* pos), when I am cloning a creature in another position,
I don't change the position number at the creature's suffix, because this is not requested at the
exercise's specifications and it also doesn't make sense. We are cloning, so the cloned creature
should not change at all between it's initial and it's new (second) position.
-In creature_society::clone_next(const int i) function, when I am in the last position N-1 of
the creature society's position array, I consider the first position N, as being the next one,
as the exercise's specifications demanded. This is achieved with cloning in position (i+1)%N .
-In creature_society::no_of_good(), when counting, I am counting all the good creatures, not caring
if they are also zobies or not, as this is not requested at the exercise's specifications.
