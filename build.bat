echo off

g++ -c *.cpp
g++ -c features/*.cpp
g++ -c program/*.cpp

move *.o build/
g++ -o main build/*.o

echo on
