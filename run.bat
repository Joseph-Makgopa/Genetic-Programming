echo off

g++ -c *.cpp
g++ -c features/*.cpp
g++ -c loader/*.cpp
g++ -c program/*.cpp

move *.o build/
g++ -o main build/*.o

main.exe

echo on
