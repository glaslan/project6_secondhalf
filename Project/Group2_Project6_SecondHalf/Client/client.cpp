
#include <cstring>
#include <iostream>
#include <vector>
#include <winsock.h>
#include <thread>
#include <chrono>

#include "../Server/constants.h"
#include "FileReader.h"
#include "Parser.h"
#include "Serializer.h"


int main() {

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
    Reader reader("FlightData/katl-kefd-B737-700.txt");
    Serializer serializer;
    Parser parser;

    // read each line in file and send data
    while (reader.IsOpen()) {

        std::string line = reader.ReadLine();
        std::vector<std::string> values = parser.split(line, ',');

        serializer.Serialize(values.at(0), std::stof(values.at(1)));
        
        
        send(ClientSocket, serializer.GetBuffer(), BUFFER_SIZE, 0);

        // 1 second delay
        std::this_thread::sleep_for(std::chrono::seconds(1));

    }

    // send the end packet
    serializer.SerializeEndPacket();
    send(ClientSocket, serializer.GetBuffer(), BUFFER_SIZE, 0);


    

    closesocket(ClientSocket);
    return 0;
}