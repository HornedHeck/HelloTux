#include "executor.h"

#include <iostream>
#include <filesystem>
#include <fstream>

#include <pthread.h>

#include <vector>

void usage() {
    std::cout << "Usage:\n"
              << "calc res_path/to/catalog res_path/to/result/file\n";
    exit(1);
}

std::string res_path;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t address_lock = PTHREAD_MUTEX_INITIALIZER;

void *launch(void *arg) {
    std::ifstream file;
    std::string path = std::string(*((std::string *) arg));
    pthread_mutex_unlock(&address_lock);
    file.open(path);
    std::string raw((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
    file.close();

    auto res = path + " - " + calc(raw);
    std::ofstream res_file;

    pthread_mutex_lock(&lock);

    res_file.open(res_path , std::ios::app | std::ios::out);
    res_file << res << std::endl;
    pthread_mutex_unlock(&lock);

    return nullptr;
}


int main(int argc, char **argv) {
//  1 - catalog
//  2 - results

    if (argc != 3) {
        usage();
    }

    std::string dir(argv[1]);
    res_path = std::string(argv[2]);

    std::vector<pthread_t> pid_list;

    for (const auto &entry : std::filesystem::directory_iterator(dir)) {
        pthread_t pid;
        pthread_mutex_lock(&address_lock);
        auto path = entry.path().string();
        pthread_create(&pid, nullptr, launch, (void *) &path);
        pid_list.push_back(pid);
    }

    void *res;

    for (auto pid : pid_list) {
        pthread_join(pid, &res);
    }

    return 0;
}

