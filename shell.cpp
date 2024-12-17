#include "shell.hpp" //all headers, files, libs combined.



 void Shelld::runShell() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::cout << YELLOW << std::put_time(std::localtime(&currentTime), "Now on %Y-%m-%d %H:%M:%S") << RESET << std::endl;

    while (true) {  
        displayPrompt();  
        std::string input = readInput();

 
        if (input.empty()) {
            continue;
        }

        else if (input == "flash" || input == "clear") {
        flashScreen();

        }

         else if (input.rfind("dldir", 0) == 0) {
         std::vector<std::string> args = parseInput(input); 
         deleteDirectoryRecursively(args);

        }

        else if (input.rfind("dlt", 0) == 0) {
         std::vector<std::string> args = parseInput(input); 
         deleteFiles(args);

        }

        else if (input == "wha") {
          helpCommand();


        }

        else if (input.rfind("mkd", 0) == 0) {
    std::vector<std::string> args = parseInput(input);
    makeDirectory(args);
       }

        else if (input.rfind("cat", 0) == 0) {
    std::vector<std::string> args = parseInput(input);
    readCommand(args);
        }


        else if (input == "LF") {
            break;
        }

         //same as in bash
         else if (input.rfind("echo", 0) == 0) {  
            std::vector<std::string> args = parseInput(input); 
            echoCommand(args);  // Call echo command
        }


        
        else if (input == "i_am") {
         currentUser();


        }

        else if (input.rfind("cr", 0) == 0) {
    std::vector<std::string> args = parseInput(input);
    crCommand(args); 
}

        else if (input.rfind("ls", 0) == 0) { 
    std::vector<std::string> args = parseInput(input); 
    listDirectoryContents(args);  
  }
        
        else if (input == "dir") {
            workingDirectory();
        }    else if (input.rfind("chd", 0) == 0) {  
            std::vector<std::string> args = parseInput(input); 
            changeDirectory(args);  
        }
        // Handle unknown commands
        else {
            std::cout << "Unknown command: " << input << std::endl;
        }
    }
}

void Shelld::displayPrompt() {
    std::cout << "From Shelld > ";  // Display prompt
    std::cout.flush();  // Ensure it's printed immediately
}

std::string Shelld::readInput() {
    std::string input;
    std::getline(std::cin, input);  // Read input from the user
    return input;
}

void Shelld::listDirectoryContents(const std::vector<std::string>& args) {
    std::cout << "Work Directory Contents:\n";

    std::string command = "/bin/ls";  // Use the absolute path for 'ls'

    // If there are any arguments, append them to the command
    for (size_t i = 1; i < args.size(); ++i) {  // Start from 1 to avoid adding the "ls" command itself
        command += " " + args[i];
    }

    // Debugging: Print the full command before executing
    std::cout << "Executing command: " << command << std::endl;

    // Execute the ls command using system()
    int result = system(command.c_str());

    if (result != 0) {
        std::cerr << "Error executing 'ls' command.\n";
    }
}


void Shelld::workingDirectory() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << GREEN << "Current working directory: " << cwd << RESET << std::endl;
    } else {
        std::perror("getcwd() error");
    }
}

void Shelld::changeDirectory(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "cd: missing argument\n";
        return;
    }
    if (chdir(args[1].c_str()) != 0) {
        std::perror("cd error");
    }
}



std::vector<std::string> Shelld::parseInput(const std::string& input) {
    std::vector<std::string> args;
    std::stringstream ss(input);
    std::string word;
    while (ss >> word) {
        args.push_back(word);
    }
    return args;
}

void Shelld::currentUser(){
 //const char* user = getlogin();
 //std::cout<< RED <<" U are " << user << RESET << std::endl;
   uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    if (pw != nullptr) {
        std::cout << "You are : " << pw->pw_name << std::endl;
    } else {
        std::cerr << "Error retrieving user information." << std::endl;
    }

 }



void Shelld::echoCommand(const std::vector<std::string>& args) {
    bool noNewline = false;

    // Check for the -n flag (no newline)
    if (args.size() > 1 && args[1] == "-n") {
        noNewline = true;
    }

    // Print the arguments
    for (size_t i = (noNewline ? 2 : 1); i < args.size(); ++i) {
        std::cout << args[i];
        if (i != args.size() - 1) {
            std::cout << " "; 
        }
    }

    if (!noNewline) {
        std::cout << std::endl; // Print newline unless -n flag is used
    }
}

void Shelld::helpCommand() {
    std::cout << YELLOW << "+-------------------------------+" << RESET << std::endl;
    std::cout << YELLOW << "|          Available Commands    |" << RESET << std::endl;
    std::cout << YELLOW << "+-------------------------------+" << RESET << std::endl;
    std::cout << GREEN << "echo: Print text to the console" << RESET << std::endl;
    std::cout << GREEN << "ls: List directory contents" << RESET << std::endl;
    std::cout << GREEN << "cd: Change the current directory" << RESET << std::endl;
    std::cout << GREEN << "dir: Show current directory" << RESET << std::endl;
    std::cout << GREEN << "i_am: Show current user" << RESET << std::endl;
    std::cout << GREEN << "cr: touch alternative, creates file(s)" << RESET << std::endl;
    std::cout << CYAN << "LF: Exit the shell" << RESET << std::endl;
    std::cout << MAGENTA << "wha: Help" << RESET << std::endl;
    std::cout << YELLOW << "+-------------------------------+" << RESET << std::endl;
}

void Shelld::crCommand(const std::vector<std::string>& args) {
    if (args.size() < 2) { // No files specified
        std::cerr << "cr: missing file operand\n";
        return;
    }

    for (size_t i = 1; i < args.size(); ++i) {
        std::ofstream file(args[i]); // Create or open the file
        if (!file) {
            std::cerr << "cr: cannot create file '" << args[i] << "'\n";
        }
        // The file is automatically closed when `file` goes out of scope
    }
}

void Shelld::flashScreen(){
 #ifdef _WIN32
        system("cls"); // Windows clear screen (in case someone uses)
    #else
        system("clear"); // Unix/Linux/Mac clear screen (main)
    #endif

}

void Shelld::deleteFiles(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "dlt: missing file operand\n";
        return;
    }

    for (size_t i = 1; i < args.size(); ++i) {  // Skip the command itself
        if (remove(args[i].c_str()) == 0) {
            std::cout << "File deleted: " << args[i] << std::endl;
        } else {
            std::cerr << "Error deleting file: " << args[i] << std::endl;
        }
    }
}

void Shelld::makeDirectory(const std::vector<std::string>& args) {
    if (args.size() < 2) { // Ensure there's a directory name provided
        std::cerr << "mkd: missing directory name\n";
        return;
    }

    for (size_t i = 1; i < args.size(); ++i) { // Skip the command itself
        if (mkdir(args[i].c_str(), 0755) == 0) { // Create directory with default permissions
            std::cout << "Directory created: " << args[i] << std::endl;
        } else {
            std::cerr << "Error creating directory: " << args[i] << " (" << strerror(errno) << ")" << std::endl;
        }
    }
}

void Shelld::deleteDirectoryRecursively(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cerr << "dlt: missing directory operand\n";
        return;
    }

    for (size_t i = 1; i < args.size(); ++i) {  // Skip the command itself
        const std::string& dirPath = args[i];
        DIR* dir = opendir(dirPath.c_str());
        if (dir == nullptr) {
            std::cerr << "Error opening directory: " << dirPath << " - " << strerror(errno) << std::endl;
            continue;
        }

        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            const std::string entryName = entry->d_name;
            if (entryName == "." || entryName == "..") {
                continue;  // Skip current and parent directories
            }

            std::string fullPath = dirPath + "/" + entryName;
            struct stat statBuf;
            if (stat(fullPath.c_str(), &statBuf) == 0) {
                if (S_ISDIR(statBuf.st_mode)) {
                    deleteDirectoryRecursively({fullPath});  // Recursively delete subdirectories
                } else {
                    remove(fullPath.c_str());  // Delete files
                }
            }
        }

        closedir(dir);
        if (rmdir(dirPath.c_str()) == 0) {
            std::cout << "Directory and contents deleted: " << dirPath << std::endl;
        } else {
            std::cerr << "Error deleting directory: " << dirPath << " - " << strerror(errno) << std::endl;
        }
    }
}

void Shelld::readCommand(const std::vector<std::string>& args) {
  if (args.size() < 2) {
        std::cerr << "cat: missing file operand\n";
        return;
    }

    for (size_t i = 1; i < args.size(); ++i) {
        std::ifstream file(args[i]);
        if (file.is_open()) {
            std::cout << file.rdbuf();
            file.close();
        } else {
            std::cerr << "cat: cannot open file " << args[i] << std::endl;
        }
    }
}
