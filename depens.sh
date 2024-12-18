#!/bin/bash


check_package() {
    if dpkg -s "$1" &>/dev/null; then
        echo "[OK] $1 is installed."
    else
        echo "[MISSING] $1 is not installed. Attempting to install..."
        sudo apt-get install -y "$1"
    fi
}

# Update package list
echo "Updating package list..."
sudo apt update

echo "Checking required libraries and headers..."

# Standard C++ libraries 
check_package "build-essential"

# POSIX libraries
check_package "libc6-dev"

# Check for C++17 (filesystem support requires it)
echo "Checking C++17 support..."
if echo | g++ -std=c++17 -x c++ -o /dev/null - >/dev/null 2>&1; then
    echo "[OK] C++17 is supported by your compiler."
else
    echo "[ERROR] C++17 is not supported. Please upgrade your compiler."
    exit 1
fi

# for POSIX headers
check_package "manpages-dev"

echo "Dependency check complete. All necessary libraries and headers should now be installed."
