#pragma once

#include "../world/entity.h"
#include "endpoint.h"
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/UdpSocket.hpp>
#include <SFML/System/Clock.hpp>
#include <common/network/commands.h>
#include <list>

namespace server {
    struct Packet {
        sf::Packet payload;
        u32 seq;
        bool isReliable;
        int triesLeft = 5;
        bool sendToAll = false;
    };

    class Server final {
      public:
        Server(int maxConnections, port_t port, EntityArray &entities);

        void recievePackets();
        void resendPackets();
        void sendPackets();
        void updatePlayers();

        int connectedPlayes() const;
        int maxConnections() const;
        int findEmptySlot() const;

        bool sendToClient(client_id_t id, Packet &packet);
        void sendToAllClients(Packet &packet);

        Packet createPacket(CommandToClient command, bool reliable);

      private:
        struct PackagedCommand {
            sf::Packet packet;
            sf::IpAddress address;
            CommandToServer command;
            port_t port;
        };

        bool getFromClient(PackagedCommand &package);

        void handleAckPacket(sf::Packet &packet);
        void handleIncomingConnection(const sf::IpAddress &address,
                                      port_t port);
        void handleDisconnect(sf::Packet &packet);
        void handleKeyInput(sf::Packet &packet);

        sf::UdpSocket m_socket;

        std::list<Packet> m_reliablePacketQueue;

        std::vector<ClientSession> m_clientSessions;
        std::vector<ClientStatus> m_clientStatuses;
        // std::queue<ClientEndpoint> m_pendingConnections;

        int m_maxConnections = 4;
        int m_connections = 0;
        int m_aliveEntities = 0;

        u32 m_currSequenceNumber = 0;
    };
} // namespace server