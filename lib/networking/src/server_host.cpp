//connect to server:
// telnet localhost 9999

#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <unistd.h> // For read

int main() {
    // Create a socket (IPv4, TCP)
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cout << "Failed to create socket. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    // Listen to port 9999 on any address
    sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = htons(9999); // htons is necessary to convert a number to
    // network byte order
    if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
        std::cout << "Failed to bind to port 9999. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    // Start listening. Hold at most 10 connections in the queue
    if (listen(sockfd, 10) < 0) {
        std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    // Grab a connection from the queue
    auto addrlen = sizeof(sockaddr);
    int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
    if (connection < 0) {
        std::cout << "Failed to grab connection. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    //send message - choose game number
    std::string message_choose_game_number = "We provide games below:\n";
    message_choose_game_number += "1. CoinGame\n";
    message_choose_game_number += "2. ZenGame\n";
    message_choose_game_number += "Enter the number to choose the game you want: \n";
    send(connection, message_choose_game_number.c_str(), message_choose_game_number.size(), 0);

    // Read from the connection
    char buffer_choose_game[100];
    auto bytesRead = read(connection, buffer_choose_game, 100);
    std::cout << "The game you choose is: " << buffer_choose_game;

    //send message - configure the game?
    std::string configure_message = "Do you want to configure the game? (yes: y, no:n): \n";
    send(connection, configure_message.c_str(), configure_message.size(), 0);
    char buffer_configure_game[100];
    auto bytesRead_ = read(connection, buffer_configure_game, 100);
    std::cout << "Do you want to configure the game? (yes: y, no:n): " << buffer_configure_game;

    // Send a message to the connection
    std::string response = "Good talking to you\n";
    send(connection, response.c_str(), response.size(), 0);

    // Close the connections
    close(connection);
    close(sockfd);
}