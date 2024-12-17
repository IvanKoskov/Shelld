#include "shell.hpp" //all headers, files, libs combined.



 void Shelld::runShell() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    std::cout << YELLOW << std::put_time(std::localtime(&currentTime), "Now on %Y-%m-%d %H:%M:%S") << RESET << std::endl;

    while (true) {  
        displayPrompt(promttext);  
        std::string input = readInput();
          commandHistory.push_back(input);

        // Keep only the last 5 commands
        if (commandHistory.size() > 5) {
            commandHistory.pop_front();  // Remove the oldest command if there are more than 5
        }
 
        if (input.empty()) {
            continue;
        }

        if (input.find(">") != std::string::npos || input.find(">>") != std::string::npos) {
            std::vector<std::string> args = parseInput(input);
            redirectOutput(args);
        }



        else if (input == "flash" || input == "clear") {
        flashScreen();

        }

        else if (input.rfind("setentry", 0) == 0) {
          std::vector<std::string> args = parseInput(input);
            setPrompt(args, promttext);
        }

        else if (input.rfind("tar", 0) == 0) {
    std::vector<std::string> args = parseInput(input);
    tarCommand(args);
       }

       else if (input == "free") {

       freeCommand();

       }

        else if (input.rfind("chow", 0) == 0) {
            std::vector<std::string> args = parseInput(input);
            chownCommand(args);
        }

        else if (input.rfind("kill", 0) == 0) {
    std::vector<std::string> args = parseInput(input);
    killCommand(args);
}

        else if (input.rfind("chamo", 0) == 0) {
    std::vector<std::string> args = parseInput(input);
    chmodCommand(args);
      }


        else if (input == "nowtime") {
       dateCommand();



        }

        else if (input.rfind("cp", 0) == 0) {
    std::vector<std::string> args = parseInput(input);
    copyCommand(args);
        }

        else if (input == "dude") {
         const char* user = getlogin();
         
         dudeCommand(user);
        }

        else if (input == "his") {
        printHistory();


        }

        else if (input == "up_time") {
         uptimeCommand();

        }

        else if (input == "df") {
         dfCommand();

        }

         else if (input.rfind("dldir", 0) == 0) {
         std::vector<std::string> args = parseInput(input); 
         deleteDirectoryRecursively(args);

        }

        else if (input.find("|") != std::string::npos) {
    std::vector<std::string> args = parseInput(input);
    pipeCommand(args);  // Handle piped command
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


        else if (input == "lv") {
            break;
        }

        else if (input == "LPESHKA") {
          listProcesses();

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

  

 else if (input.rfind("srch", 0) == 0) {
    std::vector<std::string> args = parseInput(input);
    searchFile(args);
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

void Shelld::displayPrompt(std::string promttext) {
    std::cout << promptColor << promttext << RESET;  // Display prompt
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
    std::cout << MAGENTA << "chow: change owner like in bash actually" << RESET << std::endl;
    std::cout << MAGENTA << "cp: copy contents and other stuff" << RESET << std::endl;
    std::cout << MAGENTA << "chamo: change the permissions and allow other file patterns " << RESET << std::endl;
    std::cout << MAGENTA << "wha: Help" << RESET << std::endl;
    std::cout << "tar: creating tars, extracting them and etc." << std::endl;
    std::cout << "> / >>: redirect output and etc. Big support for commands." << std::endl;
    std::cout << "| : piping like in bash!" << std::endl;
    std::cout << "up_time: stats about how long you are booted in" << std::endl;
    std::cout << "df: df like in bash. System stats and etc." << std::endl;
    std::cout << YELLOW << "kill: be careful! this command can kill system processes, there is no cancel option!" << RESET << std::endl;
    std::cout << "tar: creating tars, extracting them and etc." << std::endl;
    std::cout << "LPESHKA: process monitoring stuff, pids and other info for unix systems." << std::endl;
    std::cout << "srch: just for search like in bash. Helps to find any key word or text from the file provided." << std::endl;
    std::cout << "setentry: customize the promt (aka the entry for each line). just write //setentry ''Your new entry''. The syntax is pretty clear." << std::endl;
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
 std::cout << "Though it is just a project for my practice and studies maybe it will be actually somehow very useful to study or something. \n";
 std::cout << " \n";
 std::cout << BOLD << "It is actually plain X)" << RESET << std::endl;
 std::cout << "The shell it self has to things to undertsand\n";
 std::cout << "• entry point : From Shelld \n";
 std::cout << "What essentially means you are good to go.. input the command!\n";
 std::cout << "• Flags with which you execute your commands cause it can affect your pc\n";

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


void Shelld::copyCommand(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        std::cerr << "cp: missing file/directory or destination operand\n";
        return;
    }

    const std::string& source = args[1];
    const std::string& destination = args[2];

    try {
        if (!std::filesystem::exists(source)) {
            std::cerr << "cp: source '" << source << "' does not exist\n";
            return;
        }

        if (std::filesystem::is_directory(source)) {
            // Use recursive copy for directories
            std::filesystem::copy(
                source, destination, 
                std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing
            );
            std::cout << "Directory copied successfully from '" << source << "' to '" << destination << "'\n";
        } else {
            // Use file copy for individual files
            std::filesystem::copy_file(
                source, destination, 
                std::filesystem::copy_options::overwrite_existing
            );
            std::cout << "File copied successfully from '" << source << "' to '" << destination << "'\n";
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "cp: error copying: " << e.what() << '\n';
    }
}

void Shelld::chmodCommand(const std::vector<std::string>& args) {
    if (args.size() < 3) { // At least "chmod", mode, and one file
        std::cerr << "chmod: missing operand\n";
        return;
    }

    // Convert the mode argument (e.g., "755") to an integer
    mode_t mode;
    try {
        mode = std::stoul(args[1], nullptr, 8); // Convert from octal
    } catch (const std::exception&) {
        std::cerr << "chmod: invalid mode: " << args[1] << "\n";
        return;
    }

    // Apply the mode to each file
    for (size_t i = 2; i < args.size(); ++i) {
        const std::string& file = args[i];
        if (chmod(file.c_str(), mode) == 0) {
            std::cout << "Changed mode of " << file << " to " << args[1] << "\n";
        } else {
            std::perror(("chmod: cannot change mode of " + file).c_str());
        }
    }
}

void Shelld::chownCommand(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        std::cerr << "chown: missing operand\n";
        return;
    }

    const std::string& owner = args[1];
    const std::string& file = args[2];
    struct passwd* pw = getpwnam(owner.c_str());

    if (pw == nullptr) {
        std::cerr << "chown: invalid user\n";
        return;
    }

    uid_t uid = pw->pw_uid;
    gid_t gid = pw->pw_gid;

    if (chown(file.c_str(), uid, gid) != 0) {
        std::cerr << "chown: failed to change ownership: " << strerror(errno) << std::endl;
    } else {
        std::cout << "Ownership of '" << file << "' changed to " << owner << std::endl;
    }
}

void Shelld::tarCommand(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        std::cout << "Usage: tar [options] [archive] [files...]" << std::endl;
        return;
    }

    std::string command;  // Start with an empty command string

    // Build the command by adding each argument
    for (const auto& arg : args) {
        command += arg + " ";  // Concatenate each argument
    }

    // Check for conflicting options like -r or -t
    if (command.find("-r") != std::string::npos && command.find("-t") != std::string::npos) {
        std::cout << "Error: Can't specify both -r and -t" << std::endl;
        return;
    }

    // Print the command being executed for debugging purposes
    std::cout << "Running command: " << command << std::endl;

    // Execute the tar command
    int result = std::system(command.c_str());

    if (result != 0) {
        std::cout << "Error executing tar command!" << std::endl;
    }
}

void Shelld::listProcesses() {
    FILE *fp = popen("ps aux", "r");  // macOS uses `ps aux` for process listing
    if (fp == nullptr) {
        std::cerr << "Error executing ps command!" << std::endl;
        return;
    }

    char buffer[512];  // Buffer to hold each line of output
    std::string line;

    // Print table header (adjusted for macOS ps format)
    std::cout << "USER\tPID\t%CPU\t%MEM\tCOMMAND" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    // Skip the first line (headers)
    fgets(buffer, sizeof(buffer), fp);

    // Read and print each line of output
    while (fgets(buffer, sizeof(buffer), fp)) {
        std::cout << buffer;
    }

    fclose(fp);
}

void Shelld::searchFile(const std::vector<std::string>& args) {
    if (args.size() != 2) {
        std::cout << "Usage: search <filename> <search_string>" << std::endl;
        return;
    }

    std::string filename = args[0];
    std::string search_string = args[1];

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    size_t line_number = 0;
    bool found = false;

    while (std::getline(file, line)) {
        line_number++;
        if (line.find(search_string) != std::string::npos) {
            std::cout << "Found at line " << line_number << ": " << line << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "No matches found for '" << search_string << "' in " << filename << std::endl;
    }

    file.close();
}

void Shelld::setPrompt(const std::vector<std::string>& args, std::string& promttext) {
    if (args.size() < 2) {
        std::cout << "Usage: setprompt <new_prompt>" << std::endl;
        return;
    }

    // Extract the new prompt from the arguments (skip the command itself)
    std::string new_prompt = args[1];  // The first argument after 'setprompt' is the new prompt text
    for (size_t i = 2; i < args.size(); ++i) {
        new_prompt += " " + args[i];  // Add any additional arguments to the new prompt
    }

    promttext = new_prompt;  // Update the original prompt text
    std::cout << "Prompt changed to: " << promttext << std::endl;
}

void Shelld::redirectOutput(const std::vector<std::string>& args) {
    bool append = false;
    size_t redir_pos = args.size();

    // Find if the output is being redirected (either > or >>)
    for (size_t i = 0; i < args.size(); ++i) {
        if (args[i] == ">" || args[i] == ">>") {
            redir_pos = i;
            append = (args[i] == ">>");
            break;
        }
    }

    if (redir_pos == args.size()) {
        std::cerr << "No redirection operator found.\n";
        return;
    }

    // Now extract the file to which to redirect
    std::string output_file = args[redir_pos + 1];

    // Open the file with the correct mode (append or overwrite)
    std::ofstream out_file;
    if (append) {
        out_file.open(output_file, std::ios::app);  // Open for appending
    } else {
        out_file.open(output_file, std::ios::trunc);  // Open for overwriting
    }

    if (!out_file.is_open()) {
        std::cerr << "Failed to open the file for writing: " << output_file << "\n";
        return;
    }

    // Now execute the command and redirect the output
    // Assuming the command doesn't need to be executed again for the redirection
    std::vector<std::string> command_args(args.begin(), args.begin() + redir_pos);
    executeCommand(command_args, out_file);  // Pass the output stream to the command execution

    out_file.close();
}


void Shelld::executeCommand(const std::vector<std::string>& args, std::ofstream& out_file) {
    // Example of executing a simple command like `echo`
    if (args[0] == "echo") {
        for (size_t i = 1; i < args.size(); ++i) {
            if (i > 1) out_file << " ";  // Add space between arguments
            out_file << args[i];
        }
        out_file << "\n";
    }
    // Handle other commands similarly...
}

void Shelld::pipeCommand(const std::vector<std::string>& args) {
    // Find the index of the pipe symbol
    auto pipe_index = std::find(args.begin(), args.end(), "|");

    if (pipe_index != args.end()) {
        // Split the arguments into two commands
        std::vector<std::string> first_command(args.begin(), pipe_index);
        std::vector<std::string> second_command(pipe_index + 1, args.end());

        // Create a pipe
        int pipefd[2];
        if (pipe(pipefd) == -1) {
            perror("pipe");
            return;
        }

        // Fork the first child process
        pid_t pid1 = fork();
        if (pid1 == -1) {
            perror("fork");
            return;
        }

        if (pid1 == 0) {
            // In the first child process
            // Close the read end of the pipe
            close(pipefd[0]);
            // Redirect stdout to the write end of the pipe
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);  // Close the original pipe write end

            // Execute the first command
            std::vector<const char*> cmd1;
            for (const auto& arg : first_command) {
                cmd1.push_back(arg.c_str());
            }
            cmd1.push_back(nullptr);  // Null-terminate the argument list
            execvp(cmd1[0], (char * const*)cmd1.data());
            perror("execvp");
            exit(1);
        }

        // Fork the second child process
        pid_t pid2 = fork();
        if (pid2 == -1) {
            perror("fork");
            return;
        }

        if (pid2 == 0) {
            // In the second child process
            // Close the write end of the pipe
            close(pipefd[1]);
            // Redirect stdin to the read end of the pipe
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);  // Close the original pipe read end

            // Execute the second command
            std::vector<const char*> cmd2;
            for (const auto& arg : second_command) {
                cmd2.push_back(arg.c_str());
            }
            cmd2.push_back(nullptr);  // Null-terminate the argument list
            execvp(cmd2[0], (char * const*)cmd2.data());
            perror("execvp");
            exit(1);
        }

        // Parent process
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(pid1, nullptr, 0);  // Wait for the first child to finish
        waitpid(pid2, nullptr, 0);  // Wait for the second child to finish
    } else {
        std::cout << "No pipe found in the command!" << std::endl;
    }
}

void Shelld::uptimeCommand() {
    system("uptime");
}

void Shelld::freeCommand() {
    system("vm_stat");
}

void Shelld::dfCommand() {
    system("df -h");
}

void Shelld::killCommand(const std::vector<std::string>& args) {
    if (args.size() != 2) {
        std::cout << "Usage: kill <PID>" << std::endl;
        return;
    }

    int pid = std::stoi(args[1]);  // Convert the second argument to an integer (PID)
    
    // Attempt to kill the process
    if (kill(pid, SIGTERM) == 0) {
        std::cout << "Process " << pid << " has been terminated." << std::endl;
    } else {
        perror("Error killing process");
    }
}
