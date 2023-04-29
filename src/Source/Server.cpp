#include "../Headers/Server.h"


bool Server::set_listener() {
    this->listener.setBlocking(false);
    if (this->listener.listen(53000) != sf::Socket::Done) {
        std::cerr << "Error setting up listener\n";
        return false;
    }
    this->active = true;
    std::cout << "Server running..\n";
    return active;
}

bool Server::send_all_bytes(const void *data, std::size_t size, sf::TcpSocket &socket) {
    std::size_t total_sent = 0;
    int retries = 0;
    while (total_sent < size) {
        std::size_t sent;
        if (socket.send(static_cast<const char *>(data) + total_sent, size - total_sent, sent) != sf::Socket::Done) {
            if (++retries > 50000) {
                std::cerr << "Error sending data: too many retries\n";
                return false;
            }
            continue;
        }
        total_sent += sent;
        retries = 0;
    }
    return true;
}

void Server::receive_data() {
    for (auto client = clients.begin(); client != clients.end();) {
        int buffer_length = max_players * sizeof(Object);
        char buffer[buffer_length];
        std::size_t data_len = 0;
        int retries = 0;
        while (retries < 50000){
            auto status = (*client)->socket.receive(buffer, sizeof(buffer), data_len);
            if (status == sf::Socket::Done) {
                #ifdef SERVER_DEBUG
                std::cout << "+";
                #endif
                std::vector<char> data(buffer, buffer + data_len);
                object::deserialize_object(data, (*client)->object);
                objects[(*client)->id] = (*client)->object;
                client++;
                break;
            } else if (status == sf::Socket::Disconnected) {
                std::cout << "ERASING OBJECT AND CLIENT DATA FROM SERVER\n";
                objects.erase((*client)->id);
                client = clients.erase(client);
                std::cout << "SOCKET DISCONNECTED\n";
                break;
            } else if (status == sf::Socket::NotReady) {
                #ifdef SERVER_DEBUG
                std::cout << "-";
                std::cout << retries;
                #endif
                //game.freeze()
                retries++;
            } else {
                client++;
                break;
            }
        }
    }
}
/*
 * store data in the map with tick as key
 *
 * hashmap<uint64_t, hashmap<uint64t, Object> multiplayer_game;
 *
 *  server.send_data
 *
 *  server.receive_data
 *
 *
 * */

bool Server::send_data() {
    tick++;
    auto new_client = std::make_unique<Client>();
    new_client->socket.setBlocking(false);
    MessageType message_type;
    if (listener.accept(new_client->socket) == sf::Socket::Done) {
        // A new connection was accepted, add it to the container
        message_type = MessageType::ID;
        new_client->id = tick;
        new_client->object.id = new_client->id;

        if (!send_all_bytes(&message_type, sizeof(message_type), new_client->socket) ||
            !send_all_bytes(&new_client->object.id, sizeof(new_client->id), new_client->socket)) {
            std::cerr << "Error sending id to client\n";
        } else {
            std::cout << "NEW CLIENTS ID: " << new_client->id << " AND OBJECT ID: " << new_client->object.id << "\n";
            clients.push_back(std::move(new_client));
            std::cout << "NEW CLIENT CONNECTED!\n";
            return true;
        }
    }


    for (auto client = clients.begin(); client != clients.end();) {

        (*client)->objects.clear();

        for (auto &[object_id, object]: objects) {
            (*client)->objects.push_back(object);
        }

        auto data = object::serialize_objects((*client)->objects);
        auto data_size = static_cast<std::uint32_t>(data.size());

        if (!data.empty()) {

            message_type = MessageType::OBJECTS;


            if (!send_all_bytes(&message_type, sizeof(message_type), (*client)->socket) ||
                !send_all_bytes(&data_size, sizeof(data_size), (*client)->socket) ||
                !send_all_bytes(data.data(), data.size(), (*client)->socket)) {
                std::cerr << "Error sending data to client, with id: " << (*client)->id << "\n";
            } else {
                // std::cerr << "Sent data to client, with id: " << (*client)->id << "\n";
            }
        } else {

            message_type = MessageType::EMPTY;
            if (send_all_bytes(&message_type, sizeof(message_type), (*client)->socket)) {
                std::cerr << "Sent empty message to client, with id: " << (*client)->id << "\n";
            }


        }
        client++;
    }
    return true;
}

void Server::printObjects() {
    std::cout << "\n\nOBJECTS: \n";
    for (auto &[id, obj]: this->objects) {
        std::cout << "id: " << obj.id << " posx: " << obj.pos_x << " posy : " << obj.pos_y << " Action: "
                  << obj.action << "\n";
    }
    std::cout << "\n\n";
}