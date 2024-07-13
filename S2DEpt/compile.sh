#!/bin/bash

#!/bin/bash

echo "Write program name: "
read progName

echo "Please wait..."

# Компиляция программы
g++ -I../ -o "$progName" main.cpp -lthor -lSFGUI -lsfml-window -lsfml-system -lsfml-graphics -lsfml-audio -lbox2d

# Проверка успешности компиляции
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    ./"$progName"
else
    echo "Compilation failed."
fi
