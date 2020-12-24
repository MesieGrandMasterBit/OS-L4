all:
	g++ -O2 -Wall -o client src/client.cpp 
	g++ -O2 -std=c++17 -Wall -o server src/server.cpp src/Lab2.cpp -lpthread -lstdc++fs
