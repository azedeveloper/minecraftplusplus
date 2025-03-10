#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <cstring>
#include <stdio.h>

#define PORT 25565

class MinecraftPacketWriter {
    private:
        std::vector<uint8_t> buffer;
    
    public:
        void clear() {
            buffer.clear();
        }
    
        void writeVarInt(int32_t value) {
            uint32_t val = static_cast<uint32_t>(value);
            while ((val & 0xFFFFFF80) != 0) {
                buffer.push_back(((val & 0x7F) | 0x80));
                val >>= 7;
            }
            buffer.push_back(val & 0x7F);
        }
    
        void writeString(const std::string& str) {
            writeVarInt(str.length());
            for (char c : str) {
                buffer.push_back(c);
            }
        }
    
        const uint8_t* getData() const {
            return buffer.data();
        }
    
        size_t getSize() const {
            return buffer.size();
        }
    };

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    const char *message = "Hello!";

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address / Address not supported");
        return -1;
    }

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed!");
        return -1;
    }

    MinecraftPacketWriter writer;
    writer.writeVarInt(769);
    writer.writeString("127.0.0.1");
    writer.writeVarInt(25565);
    writer.writeVarInt(1);

    int bytes_sent = send(sock, writer.getData(), writer.getSize(), 0);
    if (bytes_sent == -1) {
        perror("Failed to send packet");
        close(sock);
        return -1;
    }

    writer.clear();

    writer.writeString("testgamer123");
    writer.writeString("uuid"); //UUID here

    bytes_sent = send(sock, writer.getData(), writer.getSize(), 0);
    if (bytes_sent == -1) {
        perror("Failed to send packet");
        close(sock);
        return -1;
    }

    char recv_buffer[4096];
    int bytes_recieved = recv(sock, recv_buffer, sizeof(recv_buffer), 0);
    printf("Recieved bytes:", bytes_recieved);
    
    close(sock);
    return 0;
}