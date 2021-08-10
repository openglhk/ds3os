// Dark Souls 3 - Open Server

#pragma once

#include "Server/Streams/Frpg2Packet.h"

#include <string>
#include <memory>
#include <Vector>

class NetConnection;

class Frpg2PacketStream
{
public:
    Frpg2PacketStream(std::shared_ptr<NetConnection> Connection);
    virtual ~Frpg2PacketStream() {};

    // Sends and recieves packets in this stream. If this function
    // returns true the stream is considered to be in an error state
    // and the client this stream goes to should be disconnected.
    virtual bool Pump();

    // Returns true if send was successful, if false is returned the send queue
    // is likely saturated or the packet is invalid.
    virtual bool Send(const Frpg2Packet& Packet);

    // Returns true if a packet was recieved and stores packet in OutputPacket.
    virtual bool Recieve(Frpg2Packet* OutputPacket);

    // Allows enabling or disabling of this streams attempts to retrieve packets
    // from the network connection. Can be used when you temporarily need to communicate
    // with raw data on the stream.
    virtual void SetRecieving(bool Recieving) { IsRecieving = Recieving; }

protected:

    bool BytesToPacket(const std::vector<uint8_t>& Buffer, Frpg2Packet& Packet);
    bool PacketToBytes(const Frpg2Packet& Packet, std::vector<uint8_t>& Buffer);

protected:

    std::shared_ptr<NetConnection> Connection;

private:

    std::vector<Frpg2Packet> RecieveQueue;

    std::vector<uint8_t> PacketBuffer;
    uint16_t PacketBytesRecieved = 0;
    bool RecievingPacketHeader = false;

    uint16_t PacketsSent = 0;

    bool InErrorState = false;

    bool IsRecieving = true;

};