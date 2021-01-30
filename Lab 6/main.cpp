#include <sys/types.h>
#include <sys/socket.h>
#include <cstdlib>
#include <netdb.h>
#include <zconf.h>
#include <csignal>
#include <sstream>
#include "../morze_converter/converter.h"

#define BUFFER_SIZE 512

int server;

void sigterm_handler(int) {

    close(server);

    exit(0);
}

void exit(int socket, int code) {
    close(socket);
    exit(code);
}

void *client_runner(void *arg) {

    int client = *((int *) arg);

    char buffer[BUFFER_SIZE];

    std::stringstream message;
    int read_res;

    while ((read_res = read(client, buffer, BUFFER_SIZE)) > 0) {
        message.write(buffer , read_res);
        if (read_res < BUFFER_SIZE || buffer[BUFFER_SIZE - 1] == '\n') break;
    }

    auto res = morze(message).str();

    sleep(3);

    write(client, res.c_str(), res.length());

    close(client);

    return nullptr;
}

int main(int argc, char **argv) {

    if (argc != 2) return 1;

    auto port = std::strtol(argv[1], nullptr, 10);

    server = socket(AF_INET, SOCK_STREAM, 0);

    signal(SIGTERM, sigterm_handler);

    if (server == 0) {
        exit(2);
    }

    sockaddr_in address = {
            .sin_family = AF_INET,
            .sin_port = htons(port),
            .sin_addr = {INADDR_ANY}
    };
    uint32_t address_len = sizeof(address);

    int res;

    res = bind(server, (sockaddr *) &address, address_len);
    if (res < 0) {
        exit(server, 3);
    }

    res = listen(server, 3);
    if (res < 0) {
        exit(server, 4);
    }


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    while (true) {
        int client = accept(server, (sockaddr *) &address, &address_len);
        if (client > 0) {
            pthread_t pid;
            pthread_create(&pid, nullptr, client_runner, &client);
        }
    }
#pragma clang diagnostic pop

}