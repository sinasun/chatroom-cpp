#include "server.h"


int main(){
    std::cout << "Welcome to the chat server!" << std::endl;
    std::cout << "Enter port: ";
    int port;
    std::cin >> port;
    std::cout << "Starting server on port " << port << std::endl;
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Error binding socket to address" << std::endl;
        close(server_fd);
        return 1;
    }

    if (listen(server_fd, 10) == -1) {
        std::cerr << "Error listening on socket" << std::endl;
        close(server_fd);
        return 1;
    }

    std::vector<int> client_fds;
    std::vector<std::thread> threads;
    std::mutex client_mutex;


    
    while (true) {
        int new_socket = accept(server_fd, nullptr, nullptr);

        if (new_socket == -1) {
            std::cerr << "Error accepting connection from client" << std::endl;
        } else {
            std::cout << "Accepted new client connection with socket fd " << new_socket << std::endl;

            UserManager* user_manager = new UserManager(new_socket);

            // Add client socket to the list
            std::lock_guard<std::mutex> lock(client_mutex);
            client_fds.push_back(new_socket);

            // Start a new thread to handle the client
            std::thread thread(&UserManager::receiveMessage, user_manager);
            threads.emplace_back(std::move(thread));
        }
    }

    for (int fd : client_fds) {
        close(fd);
    }

    // close server socket
    close(server_fd);

    return 0;




}


