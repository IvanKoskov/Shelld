#include "shell.hpp" //all headers, files, libs combined.



 void Shelld::runShell() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::cout << YELLOW << std::put_time(std::localtime(&currentTime), "Now on %Y-%m-%d %H:%M:%S") << RESET << std::endl;

    while (true) {  
        displayPrompt();  
        std::string input = readInput();
          commandHistory.push_back(input);

        // Keep only the last 5 commands
        if (commandHistory.size() > 5) {
            commandHistory.pop_front();  // Remove the oldest command if there are more than 5
        }
 
        if (input.empty()) {
            continue;
        }

        else if (input == "flash" || input == "clear") {
        flashScreen();

        }

        else if (input == "nowtime") {
       dateCommand();



        }

        else if (input == "dude") {
         const char* user = getlogin();
         
         dudeCommand(user);
        }

        else if (input == "his") {
        printHistory();


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

        else if (input.rfind("readit", 0) == 0) {
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

     else if (input.rfind("mv", 0) == 0) {
    std::vector<std::string> args = parseInput(input);
    moveFileOrDirectory(args);
}

else if (input.rfind("rename", 0) == 0) {
    std::vector<std::string> args = parseInput(input);
    renameCommand(args);
}

  else if (input.rfind("setpromptcolor", 0) == 0) {
            std::stringstream ss(input);
            std::string cmd, color;
            ss >> cmd >> color;  // Extract command and color
            setPromptColor(color);
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
    std::cout << promptColor << "From Shelld > " << RESET;  // Display prompt
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
    std::cout << GREEN << "chd: Change the current directory" << RESET << std::endl;
    std::cout << GREEN << "dir: Show current directory" << RESET << std::endl;
    std::cout << GREEN << "i_am: Show current user" << RESET << std::endl;
    std::cout << GREEN << "cr: touch alternative, creates file(s)" << RESET << std::endl;
    std::cout << GREEN << "readit: read file(s)" << RESET << std::endl;
    std::cout << GREEN << "mkd: create directory(s)" << RESET << std::endl;
    std::cout << GREEN << "dldir: delete directory(s)" << RESET << std::endl;
    std::cout << GREEN << "dlt: delete file(s)" << RESET << std::endl;
    std::cout << GREEN << "setpromptcolor: changes the entry point color, but does not chnage anything else though." << RESET << std::endl;
    std::cout << GREEN << "setpromptcolor colors: to see all supported colors" << RESET << std::endl;
    std::cout << CYAN << "LF: Exit the shell" << RESET << std::endl;
    std::cout << CYAN << "his: prints recent history" << RESET << std::endl;
    std::cout << BLUE << "nowtime: the accurate time in that moment" << RESET << std::endl;
    std::cout << BLUE << "flash // Clear : Both can clear the screen or just leave the entry point for Shelld" << RESET << std::endl;
    std::cout << BLUE << "rename: change name of files or directories" << RESET << std::endl;
    std::cout << BLUE << "mv: standard command to move everythings as you like" << RESET << std::endl;
    std::cout << MAGENTA << "wha: Help" << RESET << std::endl;
    std::cout << CYAN << "dude: general documentation and instructions" << RESET << std::endl;
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


void Shelld::dateCommand() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::cout <<BLUE<< "Current date and time: " << RESET <<std::ctime(&currentTime);
}

void Shelld::printHistory(){
  std::cout << BLUE <<"Command History:" << RESET << std::endl;
    int index = 1;
    for (const auto& command : commandHistory) {
        std::cout << index++ << ": " << command << std::endl;
    }
}

void Shelld::moveFileOrDirectory(const std::vector<std::string>& args){
 if (args.size() < 3) { // Ensure there are source and destination arguments
        std::cerr << "mv: missing operand\n";
        return;
    }

    const std::string& source = args[1];
    const std::string& destination = args[2];

    struct stat statBuf;

    // Check if the source exists
    if (stat(source.c_str(), &statBuf) != 0) {
        std::cerr << "mv: source file/directory does not exist: " << source << std::endl;
        return;
    }

    // Check if the destination is a directory
    if (stat(destination.c_str(), &statBuf) == 0 && S_ISDIR(statBuf.st_mode)) {
        // If destination is a directory, append the source file name to it
        std::string newDestination = destination + "/" + source.substr(source.find_last_of("/") + 1);
        if (rename(source.c_str(), newDestination.c_str()) == 0) {
            std::cout << "Moved: " << source << " -> " << newDestination << std::endl;
        } else {
            std::cerr << "mv: failed to move: " << strerror(errno) << std::endl;
        }
    } else {
        // If destination is not a directory, just rename the source file
        if (rename(source.c_str(), destination.c_str()) == 0) {
            std::cout << "Renamed: " << source << " -> " << destination << std::endl;
        } else {
            std::cerr << "mv: failed to rename: " << strerror(errno) << std::endl;
        }
    }

}

void Shelld::renameCommand(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        std::cerr << "rename: missing operands\n";
        return;
    }

    const std::string& oldName = args[1];
    const std::string& newName = args[2];

    if (rename(oldName.c_str(), newName.c_str()) == 0) {
        std::cout << "File/Directory renamed: " << oldName << " -> " << newName << std::endl;
    } else {
        std::cerr << "Error renaming file: " << oldName << " to " << newName << std::endl;
    }
}

void Shelld::dudeCommand(std::string nameofpc){

 std::cout << YELLOW << "Good day, " << nameofpc << " !" << RESET << std::endl;
 std::cout << BLUE << "This is a small tour above the shelld. " << RESET << std::endl;
 std::cout << BOLD << "What is Shelld ?" << RESET << std::endl;
 std::cout << "Overall it is a custom unix systems compatible shell that can be used at personal computers and etc. It is pretty clear, reader friendly" << std::endl;
 std::cout << "and is useful in most of the daily tasks. It is important to mention that it was created as just a fun project that would make something interesting to play around and" << std::endl;
 std::cout << "be very cool in appearence and just fix what other shells are doing different. Shelld can not be better in any way. It is just something i was interested." << std::endl;
 std::cout << " \n";
 std::cout << BOLD << "What we mean?" << RESET << std::endl;
 std::cout << "Shelld is just a project that was made for me to undertand shells better, it is fun and yes actually can be usable, but bash for example is a freaking set of countless tools\n";
 std::cout << "so... it is something like a meme project and kinda can be considered a joke lol:))\n";
 std::cout << BOLD << "How to actually use?" << RESET << std::endl;
 std::cout << "This shell tries to resemble something like bash, but simplier and more primitive. \n";
 std::cout << "Use different commands with flags or without them similarly to bash that you can find by typing //wha// in terminal \n";
}

void Shelld::setPromptColor(const std::string& color) {
    auto it = colorMap.find(color);
    if (it != colorMap.end()) {
        promptColor = it->second;
        std::cout << "Prompt color changed to " << color << std::endl;
    } else {
        std::cout << "Invalid color. Available colors are: red, green, yellow, blue, magenta, cyan, white." << std::endl;
    }
}