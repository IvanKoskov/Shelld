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
#include <deque>
#include <signal.h>
#include <map>
#include <sstream>
#include <filesystem> 
#include <cstdlib>
#include <fcntl.h>
#include <sys/wait.h>
//our shell colrs. Red does not work by some reason...
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

//some text style

#define BOLD    "\033[1m"

/*
Shelld structure is pretty similar and yet good in terms of compatibility. Linux and MacOS are supported natively. 

The Shell here is presented as class with its own private methods and clear entry point as a run shell function.
It is actually a root of the project and can be imported.

*/
class Shelld {
public:

   void runShell(); //it is the entry and access to all functionality of the shell

private:
    std::string promttext = "From Shelld > ";
    void displayPrompt(std::string promttext); 
   
   std::string readInput(); // Read 
    
    void executeCommand(const std::vector<std::string>& args, std::ofstream& out_file); // Execute the command
   
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
    
    void dateCommand();
    
    std::deque<std::string> commandHistory; 
    
    void printHistory();
   
    void moveFileOrDirectory(const std::vector<std::string>& args);
    
    void renameCommand(const std::vector<std::string>& args);
    
    void dudeCommand(std::string nameofpc);
    
    void setPromptColor(const std::string& color);
    
    std::string promptColor = RESET;  // Default prompt color
    
    std::map<std::string, std::string> colorMap = {
        {"red", RED}, {"green", GREEN}, {"yellow", YELLOW},
        {"blue", BLUE}, {"magenta", MAGENTA}, {"cyan", CYAN},
        {"white", WHITE}
    };

    void copyCommand(const std::vector<std::string>& args);

    void chmodCommand(const std::vector<std::string>& args);

    void chownCommand(const std::vector<std::string>& args);

    void tarCommand(const std::vector<std::string>& args);

    void listProcesses();

    void searchFile(const std::vector<std::string>& args);

    void setPrompt(const std::vector<std::string>& args, std::string& promttext);

    void redirectOutput(const std::vector<std::string>& args);

    void pipeCommand(const std::vector<std::string>& args);

    void uptimeCommand();

    void freeCommand();

    void dfCommand();

    void killCommand(const std::vector<std::string>& args);
};




