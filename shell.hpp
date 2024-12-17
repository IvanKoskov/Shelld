#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream> 
#include <pwd.h>
#include <unistd.h> 
#include <cstdio>
#include <sys/types.h>  
#include <sys/stat.h>   
#include <errno.h>      
#include <cstring>      
#include <dirent.h>
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

/*
Shelld structure is pretty similar and yet good in terms of compatibility. Linux and MacOS are supported natively. 

The Shell here is presented as class with its own private methods and clear entry point as a run shell function.
It is actually a root of the project and can be imported.

*/










class Shelld {
public:

   void runShell(); 

private:
    void displayPrompt(); 
    std::string readInput(); // Read 
    
    void executeCommand(const std::vector<std::string>& args); // Execute the command
    void listDirectoryContents(const std::vector<std::string>& args);
    void workingDirectory();
    void changeDirectory(const std::vector<std::string>& args);
    std::vector<std::string> parseInput(const std::string& input);
    void currentUser();
    void echoCommand(const std::vector<std::string>& args);
    void helpCommand();
    void crCommand(const std::vector<std::string>& args);
    void flashScreen();
    void deleteFiles(const std::vector<std::string>& args);
    void makeDirectory(const std::vector<std::string>& args);
    void deleteDirectoryRecursively(const std::vector<std::string>& args);
    void readCommand(const std::vector<std::string>& args);
};



