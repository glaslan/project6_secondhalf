
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <cstring>
#include <iostream>
#include <vector>
#include <windows.h> 
#include <winsock.h>
#include <thread>
#include <chrono>
#include <random>

#include "../Server/constants.h"
#include "FileReader.h"
#include "Parser.h"
#include "Serializer.h"

#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")
/// @brief 
/// 
/// 
/// 
/// @return 

int main() {

    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "ERROR: Failed to start WSA" << std::endl;
        return 0;
    }

    // safe default value
    char input = ' ';

    // sets up the client socket
    int ClientSocket;
    ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ClientSocket == -1) {
        std::cout << "Error: failed to create clientsocket" << std::endl;
        return 0;
    };

    // connects to the server
    sockaddr_in svrAddr;
    svrAddr.sin_family = AF_INET;
    svrAddr.sin_port = htons(PORT);
    svrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(ClientSocket, (struct sockaddr*)&svrAddr, sizeof(svrAddr)) < 0) {
        perror("ERROR: Connection attempt failed");
        closesocket(ClientSocket);
        return 0;
    }

    // open file and modules
    std::vector<std::string> files;

    files.push_back("FlightData/katl-kefd-B737-700.txt");
    files.push_back("FlightData/Telem_2023_3_12 14_56_40.txt");
    files.push_back("FlightData/Telem_2023_3_12 16_26_4.txt");
    files.push_back("FlightData/Telem_2023_3_12 14_56_40.txt");

    std::random_device rd;
    std::mt19937 random_engine(rd());
    std::uniform_int_distribution<> random_generator(0, files.size() - 1);

    Reader reader(files.at(random_generator(random_engine)));
    Serializer serializer;
    Parser parser;

    // read each line in file and send data
    while (reader.IsOpen()) {

        std::string line = reader.ReadLine();
        if (line.empty()) break;

        std::vector<std::string> values = parser.split(line, ',');

        std::string datetime;
        float fuel_usage;

        if (values.size() > 3) {
            datetime = values.at(1);
            fuel_usage = std::stof(values.at(2));
        }
        else if (values.size() >= 2) {
            datetime = values.at(0);
            fuel_usage = std::stof(values.at(1));
        }
        else {
            continue;
        }

        serializer.Serialize(datetime, fuel_usage);
        
        send(ClientSocket, serializer.GetBuffer(), BUFFER_SIZE, 0);

        // 1 second delay
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }

    // send the end packet
    serializer.SerializeEndPacket();
    send(ClientSocket, serializer.GetBuffer(), BUFFER_SIZE, 0);


    closesocket(ClientSocket);

    WSACleanup();

    return 0;
}