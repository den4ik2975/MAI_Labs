#!/bin/bash

show_usage() {
    echo "Usage: $0 <directory>"
    echo "Traverse the specified directory and display full paths of subdirectories."
}

# Проверка на аргументы
if [ $# -ne 1 ]; then
    echo "Error: Incorrect number of arguments."
    show_usage
    exit 1
fi

# Проврека на ?
if [ "$1" == "?" ]; then
    show_usage
    exit 0
fi

# Проверка на наличие введенной директории
if [ ! -d "$1" ]; then
    echo "Error: Directory not found."
    exit 1
fi

# Обходим директории
find "$1" -type d -print

exit 0
