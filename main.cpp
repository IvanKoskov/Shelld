#include "shell.hpp" //shelld

// Shelld was originally conceived as a C-based project, but in recent days, it was refactored into C++ to take advantage of object-oriented principles and enhance its functionality.
// While it still relies on C libraries and headers, the shell is primarily designed with C++ features. The core concept is to represent the shell itself as an object, encapsulating all of its actions and implementations in private members.
// To start the shell, we simply create an instance of the shell object, initialize it, and let it run. This approach allows for clear separation of concerns, where the shell's functionality is organized into logical blocks.
// This can be seen in the main file, which is reduced to just a few lines of code. The runShell() function serves as the entry point, with subsequent layers representing different logical components and function implementations.
// By using object-oriented design, the shell is modular, easy to understand, and maintain. Each component operates at its own level and can only be accessed through the runShell() interface, ensuring clean separation and encapsulation of functionality.
// This object-oriented design approach offers several key advantages. By encapsulating functionality within a shell object, we achieve better modularity, which makes the code easier to manage, extend, and maintain. 
//The separation of concerns ensures that each part of the shell is independent and self-contained, allowing for easier testing and debugging. Additionally, this structure makes the shell more flexible, as new features can be added or modified without affecting the core logic.
// The clear interface provided by the runShell() function simplifies interaction with the shell, enhancing usability and readability for developers. Overall, this design improves code maintainability, scalability, and future-proofing, making it easier to evolve the shell over time.
//The features can be added without altering or breaking anything else in 99% becasue every function or whatever it is is following a pattern that can allow building shell brick by brick without lokking back.


int main(){
   Shelld shelld; //shell as an object
   shelld.runShell();  //like a root the object allows for user to interact and run commands by expanding it with other functions
 //  Shelld::runShell(); possible, but the code is sticking to classes and static way of this would be just less useful.
   return 0;
}



