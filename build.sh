SRC_FILES=$(ls *.cpp 2>/dev/null)

if [ -z "$SRC_FILES" ]; then
    echo "No .cpp files found in the current directory."
    exit 1
fi

g++ $SRC_FILES -o app $(sdl2-config --cflags --libs) -Iinclude/ -lm -lSDL2_ttf

if [ $? -eq 0 ]; then
    echo "Build successful! Executable created: ./app"
else
    echo "Build failed."
fi
