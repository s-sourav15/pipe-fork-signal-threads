all: program1 program2

program1:
	 g++ -o Admin.exe Admin.cpp -std=c++11 -pthread

program2:
	 g++ -o Client.exe Client.cpp
