#include <sys/socket.h>
#include <cstdlib>
#include <netdb.h>
#include <zconf.h>
#include <libnet.h>
#include <iostream>
#include <sstream>

#define BUFFER_SIZE 512

int client;

void sigterm_handler(int) {

    close(client);

    exit(0);
}

int main(int argc, char **argv) {
//  1 - ip
//  2 - port

    if (argc != 3) return 1;

    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        return 2;
    }

    signal(SIGTERM, sigterm_handler);

    auto port = strtol(argv[2], nullptr, 10);

    sockaddr_in server_addr = {
            .sin_family = AF_INET,
            .sin_port = htons(port)
    };

    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) < 1) {
        close(client);
        return 3;
    }

    if (connect(client, (sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        close(client);
        return 4;
    }


    std::string line;
    std::getline(std::cin, line);

    auto message = line.c_str();

    write(client, message, sizeof(message));


    std::stringstream response;
    char buffer[BUFFER_SIZE];
    int read_res;

    while ((read_res = read(client, buffer, BUFFER_SIZE)) > 0) {
        response.write(buffer, read_res);
        if (read_res < BUFFER_SIZE || buffer[BUFFER_SIZE - 1] == '\n') break;
    }

    std::cout << response.str();

    close(client);

    return 0;
}
