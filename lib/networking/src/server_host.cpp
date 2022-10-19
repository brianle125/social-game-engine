//connect to server:
// telnet localhost 9999

#include <sys/socket.h> // For socket functions, only unix
#include <netinet/in.h> // For sockaddr_in, only unix
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <unistd.h> // For read, only unix
#include <cstring>  // For building on non unix systems

int ask_for_game_choice(int connection){
    //send message - choose game number
    std::string message_choose_game_number = "We provide games below:\n";
    message_choose_game_number += "1. CoinGame\n";
    message_choose_game_number += "2. ZenGame\n";
    message_choose_game_number += "Enter the number to choose the game you want: \n";
    send(connection, message_choose_game_number.c_str(), message_choose_game_number.size(), 0);

    // Read from the connection
    char buffer_choose_game[100] = { 0 };
    read(connection, buffer_choose_game, 100);
   // std::cout << "The game you choose is: " << buffer_choose_game;

    //handle user input error
    int game_choice = atoi(buffer_choose_game);
    while(game_choice == 0 || game_choice > 2 || game_choice < 1){
        std::string str = "Please enter a number: (1/2)\n";
        send(connection, str.c_str(), str.size(), 0);
        memset(buffer_choose_game, 0, 100);
        read(connection, buffer_choose_game, 100); //get new message
        game_choice = atoi(buffer_choose_game);
    }

    std::cout << "The game you choose is: " << buffer_choose_game<<std::endl;
    return game_choice;
}

char ask_for_game_configuration(int connection){
    //send message - configure the game?
    std::string configure_message = "Do you want to configure the game? (yes: y, no:n): \n";
    send(connection, configure_message.c_str(), configure_message.size(), 0);
    char buffer_configure_game[100];
    read(connection, buffer_configure_game, 100);
    std::cout << "Do you want to configure the game? (yes: y, no:n): " << buffer_configure_game<<std::endl;

    char first_char = buffer_configure_game[0];
    while(first_char != 'y' && first_char !='n'){
        std::string str = "Please enter an valid char: (y/n)\n";
        send(connection, str.c_str(), str.size(), 0);//send message
        memset(buffer_configure_game, ' ', 100);
        read(connection, buffer_configure_game, 100); //get new message
        first_char = buffer_configure_game[0];
    }
    // Send a message to the connection
    std::cout << "You choose to configure the game: (y:yes/n:no) " << buffer_configure_game<<std::endl;
    std::string response = "Good talking to you\n";
    send(connection, response.c_str(), response.size(), 0);
    return buffer_configure_game[0];
}

int ask_about_configuration_information(int connection){
    std::string configure_message = "You can configure these things: \n";
    configure_message += "1. max number of players \n";
    configure_message += "2. min number of players \n";
    configure_message += "3. set audience（default: no audience）\n";
    configure_message += "4. set Rounds（default: 1 round）\n";
    configure_message += "Please enter one number each time: \n";

    send(connection, configure_message.c_str(), configure_message.size(), 0);

    char buffer_configure_info[100];
    read(connection, buffer_configure_info, 100);
    int configuration_choice;

    configuration_choice = atoi(buffer_configure_info);
    //handle error
    while(configuration_choice == 0 || configuration_choice > 4 || configuration_choice < 1){
        std::string str = "Please enter one number each time: (1/2/3/4)\n";
        send(connection, str.c_str(), str.size(), 0);
        memset(buffer_configure_info, 0, 100);
        read(connection, buffer_configure_info, 100); //get new message
        configuration_choice = atoi(buffer_configure_info);
    }

    std::cout << "The configuration you want to change is: " << configuration_choice<<std::endl;

    return configuration_choice;
}

//continue handle configuration information
//if uer choose 1 for function, ask_about_configuration_information()
int configuration_information_1(int connection){
    std::string configure_message = "Enter max number of players: \n";
    send(connection, configure_message.c_str(), configure_message.size(), 0);

    char buffer_configure_info[100];
    read(connection, buffer_configure_info, 100);

    int configuration_choice;
    configuration_choice = atoi(buffer_configure_info);

    while(configuration_choice == 0 || configuration_choice > 30 || configuration_choice < 1){
        std::string str = "Please enter a number: (<30, >1)\n";
        send(connection, str.c_str(), str.size(), 0);
        memset(buffer_configure_info, 0, 100);
        read(connection, buffer_configure_info, 100); //get new message
        configuration_choice = atoi(buffer_configure_info);
    }
    std::cout << "Set max number of player: " << configuration_choice<<std::endl;
    return configuration_choice;
}

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

    int game_choice = ask_for_game_choice(connection);
    std::cout << "game_choice: " << game_choice<<std::endl;
    char configure = ask_for_game_configuration(connection);
    std::cout << "configure ? : " << configure<<std::endl;

    if(configure == 'y'){
        int configuration_choice = ask_about_configuration_information(connection);
        std::cout << "configuration choice: " << configuration_choice<<std::endl;
        if(configuration_choice == 1){
            int max_player = configuration_information_1( connection);
            std::cout << "max_player: " << max_player<<std::endl;
        }
    }
    // Close the connections
    close(connection);
    close(sockfd);
}