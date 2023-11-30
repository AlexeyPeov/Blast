#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <csignal>


#include "Object.h"

//#define CLIENT_DEBUG_SEND
//#define CLIENT_DEBUG_RECEIVE

using namespace obj;

struct MessageType {
    static const uint8 ID = 1;
    static const uint8 CONNECT = 2;
    static const uint8 PLAYER_EVENT = 3;
    static const uint8 PLAYER_EVENT_HOST = 4;
    static const uint8 DISCONNECT = 5;
    static const uint8 EMPTY = 6;
};



struct Client {

    uint64 id = 0;
    uint64 tick = 0;
    sf::UdpSocket socket;
    sf::IpAddress client_ip;
    sf::IpAddress host_ip;
    uint16 host_port = 53000;
    std::vector<PlayerObject> player_objects;
    std::vector<MissileObject> missile_objects;
    PlayerEvent player_event = {0};

    PlayerObject player_object = {0};
    BombObject bomb_object = {0};

    bool active = false;
    bool host = false;

    Client();
    ~Client(){}

    Client(uint64 id, sf::IpAddress host_ip, sf::IpAddress client_ip, uint16 port){
        this->id = id;
        this->host_ip = host_ip;
        this->client_ip = client_ip;
        this->host_port = port;
    }

    bool connect(sf::IpAddress address, uint16 port);

    void disconnect();

    void receive_data();

    void send_data();

    std::string getServerIp();

    uint16_t getServerPort();

    std::string main_menu_event_to_string(PlayerObject &object);
};

#endif