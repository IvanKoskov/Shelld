#include <iostream>
#include <ncurses.h>
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
#define URL "https://github.com/IvanKoskov/Shelld"
//some text style

#define BOLD    "\033[1m"

/*
Shelld structure is pretty similar and yet good in terms of compatibility. Linux and MacOS are supported natively. 

The Shell here is presented as class with its own private methods and clear entry point as a run shell function.
It is actually a root of the project and can be imported.

*/



//shell.hpp contains all headers, libs and blueprints to all methods. This file includes all definitions of used variables, constants, functions and etc
//here everything can be acessed easily and be helpful in finding soemthing specific like a feature or definiton.
//Shell.hpp serves a big role in making shell strcutured and separated.


class Shelld {
public:

   void runShell(); //it is the entry and access to all functionality of the shell
  
struct Job {
        int job_id;
        pid_t pid;
        std::string command;
        bool is_running;
    };

    Job* findJobByPid(pid_t pid);
    Job* findJobById(int job_id);

private:
bool isNumber(const std::string& s);
   std::vector<Job> jobs;  // List of jobs
    int next_job_id = 1; 

    
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





    void removeJob(pid_t pid);
    
    
    void listJobs();
    void addJob(pid_t pid, const std::string& command, bool is_running);

    void helppidCommand();

    void cleanupJobs();

    void wifeCommand();

    void executeScript(const std::vector<std::string>& args);

    void reverseCommand(const std::vector<std::string>& args);

    void installCommand(const std::vector<std::string>& args);

    void runCFile(const std::string& filename);

    void zipCommand(const std::vector<std::string>& args);

    void unzipCommand(const std::vector<std::string>& args);

    void gzipCommand(const std::vector<std::string>& args);

    void gunzipCommand(const std::vector<std::string>& args);

    void openFileEditor(const std::vector<std::string>& args);

    void loadFile(const std::string& filename, std::vector<std::string>& buffer);

    void saveFile(const std::string& filename, const std::vector<std::string>& buffer);

    void wgetCommand(const std::vector<std::string>& args);
};




