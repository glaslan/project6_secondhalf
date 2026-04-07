#include <cstring>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <windows.h> 
#include <winsock.h> 
#include <ctime>
#include <sstream>

#include "constants.h"
#include "Deserializer.h"
#include "Logger.h"
#include "FuelUsageCalculator.h"

#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")


void ServerThread(int ServerSocket, int ConnectionSocket) {

    // Accept Connection 
    std::ofstream postFile;
    char buffer[BUFFER_SIZE] = { 0 }; 
    std::time_t unix_time = std::time(0); 
    
    //std::string log_path("./Logs/" + std::to_string(unix_time) + ".txt");
    //std::string error_path("./Errors/" + std::to_string(unix_time) + ".txt");

    //std::cout << log_path << std::endl;
    //std::cout << error_path << std::endl;

    // Logger logger(log_path, error_path);
    Deserializer deserializer;
    UsageCalculator calculator(0);

    // This block makes the data move
    // Recieve must come first
    bool quit = false;
    while (!quit) {
        recv(ConnectionSocket, buffer, sizeof(buffer), 0);
        deserializer.DeserializeBuffer(buffer);
        int flag = deserializer.GetFlag();
        std::stringstream stream;
        
        switch (flag) {
            case FLAG_CONTINUE:
                calculator.process_fuel_data(deserializer.GetFuel());
                stream << "Time: " << deserializer.GetDatetime() << ", Average Fuel Used: " << calculator.getAverageConsumption() << ", Current Fuel Used: " << calculator.getRecentDifference();
                // logger.WriteToFile(stream.str());
                break;
            case FLAG_END:
                quit = true;
                break;
            default:
                std::cout << "Bad Input" << std::endl;
                quit = true;
                break;
        }
    }
    closesocket(ConnectionSocket);
}

int main() {

    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "ERROR: Failed to start WSA" << std::endl;
        return 0;
    }

    // This block creates the socket
    struct sockaddr_in client_addr;
    int ServerSocket;

    ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ServerSocket < 0) {
        std::cout << "ERROR: Failed to create ServerSocket" << std::endl;
        return 0;
    }

    sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;
    SvrAddr.sin_addr.s_addr = INADDR_ANY;
    SvrAddr.sin_port = htons(PORT);

    if (bind(ServerSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr)) == -1) {
        closesocket(ServerSocket);
        std::cout << "ERROR: Failed to bind ServerSocket" << std::endl;
        return 0;
    }

    // wait for a incoming connection
    if (listen(ServerSocket, 1) == -1) {
        std::cout << "ERROR: listen failed to configure ServerSocket" << std::endl;
    }
    int ConnectionSocket;

    while (true) {

        if ((ConnectionSocket = accept(ServerSocket, NULL, NULL)) == -1) {
            continue;
        }

        // if the connection is succesful, create a new thread for the client
        // create thread for client
        std::thread NewThread(ServerThread, ServerSocket, ConnectionSocket);
        std::cout << "Made a thread" << std::endl;
        // Detach thread from main program to allow it to continue running
        NewThread.detach();
    }

    // Close socket

    closesocket(ServerSocket);
    WSACleanup();
    return 0;
}
