#!/bin/bash

# Проверяем была директория передана как аргумент
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

DIRECTORY=$1

# Проверяем есть ли директория
if [ ! -d "$DIRECTORY" ]; then
    echo "Error: Directory $DIRECTORY does not exist."
    exit 1
fi

# Рекурсивно обходим директории
find "$DIRECTORY" -type d -print
