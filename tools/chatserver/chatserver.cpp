/////////////////////////////////////////////////////////////////////////////
//                         Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////


#include "Server.h"
#include "inputChoiceRule.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>


using networking::Server;
using networking::Connection;
using networking::Message;


std::vector<Connection> clients;
InputChoiceRule icr;
GameModel model;


void
onConnect(Connection c) {
  std::cout << "New connection found: " << c.id << "\n";
    if (icr.target.init == false) {
        icr.target = Player(c);
        icr.target.init = true;
    }
    icr.executeRule(model);
  clients.push_back(c);
}


void
onDisconnect(Connection c) {
  std::cout << "Connection lost: " << c.id << "\n";
  auto eraseBegin = std::remove(std::begin(clients), std::end(clients), c);
  clients.erase(eraseBegin, std::end(clients));
}


struct MessageResult {
  std::string result;
  bool shouldShutdown;
};


MessageResult
processMessages(Server& server, const std::deque<Message>& incoming) {
  std::ostringstream result;
  bool quit = false;
  for (auto& message : incoming) {
    if (message.text == "quit") {
      server.disconnect(message.connection);
    } else if (message.text == "shutdown") {
      std::cout << "Shutting down.\n";
      quit = true;
    } else {
      result << message.connection.id << "> " << message.text << "\n";
    }
  }
  return MessageResult{result.str(), quit};
}


std::deque<Message>
buildOutgoing(const std::string& log) {
  std::deque<Message> outgoing;
  for (auto client : clients) {
    outgoing.push_back({client, log});
  }
  return outgoing;
}


std::string
getHTTPMessage(const char* htmlLocation) {
  if (access(htmlLocation, R_OK ) != -1) {
    std::ifstream infile{htmlLocation};
    return std::string{std::istreambuf_iterator<char>(infile),
                       std::istreambuf_iterator<char>()};

  } else {
    std::cerr << "Unable to open HTML index file:\n"
              << htmlLocation << "\n";
    std::exit(-1);
  }
}


MessageResult
processMessagesResponse(Server& server, const std::deque<Message>& incoming) {
  std::ostringstream result;
  bool quit = false;
  for (auto& message : incoming) {
    if (message.text == "quit") {
      server.disconnect(message.connection);
    } else if (message.text == "shutdown") {
      std::cout << "Shutting down.\n";
      quit = true;
    } else if (!server.responseQueue.empty()) {
        std::unordered_map<uintptr_t, networking::Response>::iterator clientItr = server.responseQueue.find(message.connection.id);
        if (clientItr != server.responseQueue.end()) {
            bool valid = clientItr->second.rule->receiveResponse(message.text, clientItr->second.start);
            if (valid) { server.responseQueue.erase(clientItr); }
        }
    }
  }
  return MessageResult{result.str(), quit};
}


int
main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage:\n  " << argv[0] << " <port> <html response>\n"
              << "  e.g. " << argv[0] << " 4002 ./webchat.html\n";
    return 1;
  }

  unsigned short port = std::stoi(argv[1]);
  Server server{port, getHTTPMessage(argv[2]), onConnect, onDisconnect};
  myVariant one = std::string("one");
  myVariant two = std::string("two");
  myVariant three = std::string("three");
  std::vector<myVariant> choices = {one, two, three};
  std::string prompt("idk choose something");
  std::string result("whygod");
  InputChoiceRule rule(prompt, choices, result, &server, 5);
  icr = rule;

  while (true) {
    bool errorWhileUpdating = false;
    try {
      server.update();
    } catch (std::exception& e) {
      std::cerr << "Exception from Server update:\n"
                << " " << e.what() << "\n\n";
      errorWhileUpdating = true;
    }
    auto incoming = server.receive();
    auto [log, shouldQuit] = processMessagesResponse(server, incoming);
    auto outgoing = buildOutgoing(log);
    //server.send(outgoing);

    if (shouldQuit || errorWhileUpdating) {
      break;
    }

    sleep(1);
  }

  return 0;
}

