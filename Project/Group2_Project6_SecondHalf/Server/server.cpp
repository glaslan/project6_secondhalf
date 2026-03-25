#include <cstring>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <windows.h> 
#include <winsock.h> 

#include "constants.h"

#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")


void ServerThread(int ServerSocket, int ConnectionSocket) {

    // Accept Connection
    std::ofstream postFile;
    char buffer[BUFFER_SIZE] = { 0 };

    // This block makes the data move
    // Recieve must come first
    bool quit = false;
    while (!quit) {
        recv(ConnectionSocket, buffer, sizeof(buffer), 0);
        
        switch (buffer[0]) {
            case '0':
                break;
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            default:
                std::cout << "Bad Input" << std::endl;
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
    return 0;
}
