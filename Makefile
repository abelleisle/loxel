@all:
	g++ -m64 -std=c++17 src/main.cpp -o main -Wall -Werror -Wextra -Wpedantic -Llib -Isrc -Ilib -llua5.3
