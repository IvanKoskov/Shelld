#include "shell.hpp"

int main(){
   Shelld shelld; //shell entry
shelld.runShell();  //like a root the object allows for user to interact and run commands by expanding it with other functions
 //  Shelld::runShell(); possible, but the code is sticking to classes and static way of this would be just less useful.
   return 0;
}