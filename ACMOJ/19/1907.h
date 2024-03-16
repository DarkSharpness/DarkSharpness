#ifndef SRC_HPP
#define SRC_HPP

#include <bits/stdc++.h>

// You may include whatever you want.

void SendPacket(const uint8_t* data, int dataSize);

// You may add some functions or classes here.

enum class type : uint8_t {
    NO_ERR,
    LO_ERR,
    HI_ERR,
    HI_COST,
    CORRUPT
};

struct header {
    uint16_t bit_p :  3; /* Which bit. */
    uint16_t index : 13; /* Real index.*/
};

constexpr int TTTTTT = sizeof(header);


constexpr int N = 256;
constexpr int M = 256000;
constexpr int Length  = 254;
constexpr int Unit_Lo = 127;
constexpr int Unit_Hi = 60;
constexpr int Unit_Co = 160;

template <int U>
void Send(const uint8_t* data) {
    static uint8_t temp[N + 10];
    for(int i = 0 ; i <= M / U ; ++i) {
        int remain = std::min(M - i * U,Length);
        if(remain <= U) {
            memcpy(temp + sizeof(uint16_t),data + i * U,remain);
            memcpy(temp + sizeof(uint16_t) + remain,data,Length - remain);
            break; /* Not enough. */
        }
        memcpy(temp + sizeof(uint16_t),data + i * U,remain);
        *(uint16_t *)temp = i;
        SendPacket(temp,sizeof(uint16_t) + remain);
    }
}

// template <int U>
// void Send_bit(const uint8_t* data) {
//     constexpr int U = 255;
//     static uint8_t temp[N + 10];
//     for(int j = 0 ; j < 8 ; ++j) {
//         header test;
//         test.bit_p = j;
//         for(int i = 0 ; i <= M / (Length * 8) ; ++i) {
            
//         }
//     }
// }


template <int U>
void Receive(const uint8_t* data, int dataSize, uint8_t* answer) {
    uint16_t i = *(uint16_t *)data;
    dataSize -= 2;
    // if(i * U + dataSize <= M) {
    memcpy(answer + i * U ,data + 2,dataSize);
    // } else {
    //     int remain = M - i * U;
    //     memcpy(answer + i * U ,data + 2,remain);
    //     memcpy(answer,data + 2 + remain,dataSize - remain);
    // }
}


void Send_No_Error(const uint8_t* data, int dataSize, double a) {
    for(int i = 0 ; i < 60000 ; ++i)
        SendPacket(nullptr,0);
    for(int i = 0 ; i < M / N ; ++i)
        SendPacket(data + i * N,N);
}


void Send_Lo_Error(const uint8_t* data) {
    Send <Unit_Lo> (data);
}


void Send_Hi_Error(const uint8_t* data) {
    Send <Unit_Hi> (data);
}

void Send_Hi_Cost(const uint8_t* data) {
    for(int i = 0 ; i < 44000 ; ++i)
        SendPacket(nullptr,0);
    Send <Unit_Co> (data);
}

void Send_No_Corrupt(double p1,const uint8_t* data, int dataSize, double a) {
    if(p1 < 0.6) {
        for(int i = 0 ; i < 1500 ; ++i)
            SendPacket(nullptr,0);
        return
            a <= 3 ? 
                Send_Lo_Error(data) :
                Send_Hi_Cost (data);
    }
    else {
        for(int i = 0 ; i < 50 ; ++i)
            SendPacket(nullptr,0);
        return Send_Hi_Error(data);
    }
}

/**
 * Send the data to the receiver using the send_packet function above. The function
 * is called only once for each data. The data is completely uniform random.
 * @param maxPacketSize the maximum packet size, the extra bytes will be ignored
 * @param p1 the probability of the packet being lost
 * @param p2 the probability of a bit being corrupted
 * @param data the data to be sent
 * @param dataSize the size of the data
 */
void Send(int maxPacketSize, double p1, double p2, const uint8_t* data, int dataSize, double a) {
    if(p1 < 0.0001) return Send_No_Error(data,dataSize,a);
    if(p2 < 0.0001) return Send_No_Corrupt(p1,data,dataSize,a);
    /* Now there might be corrupted bits. */
}

type get_type(int count) {
    if(count ==      0) return type::CORRUPT;
    if(count <=     50) return type::HI_ERR;
    if(count <=   1500) return type::LO_ERR;
    if(count <=  45000) return type::HI_COST;
    else return type::NO_ERR;
}

inline void randomize(uint8_t *answer) {
    static bool flag = false;
    if(!flag) {
        for(int i = 0 ; i != M ; ++i)
            answer[i] = rand();
        flag = true;
    }
}

void Receive_No_Error(const uint8_t* data, int dataSize, uint8_t* answer) {
    static int cnt = 0;
    memcpy(answer + cnt * N,data,dataSize); ++cnt;
}


void Receive_Lo_Error(const uint8_t* data, int dataSize, uint8_t* answer) {
    return Receive <Unit_Lo> (data,dataSize,answer); 
}

void Receive_Hi_Error(const uint8_t* data, int dataSize, uint8_t* answer) {
    Receive <Unit_Hi> (data,dataSize,answer);
}

void Receive_Hi_Cost(const uint8_t* data, int dataSize, uint8_t* answer) {
    return Receive <Unit_Co> (data,dataSize,answer); 
}

void Receive_Corrupt(const uint8_t* data, int dataSize, uint8_t* answer) {
    Receive_Lo_Error(data,dataSize,answer);
}

/**
 * Reconstruct the data from the packets received. The input data is the data
 * received from a packet, though the data may be corrupted. The final answer
 * should be stored in the answer array.
 * @param data the data received from a packet
 * @param dataSize the size of the data (this one is not corrupted)
 * @param answer the answer array
 */
void ReceivePacket(const uint8_t* data, int dataSize, uint8_t* answer) {
    static int count   = 0;
    if(!dataSize) return (void)++count;
    static type __type = get_type(count);
    srand(time(NULL));
    randomize(answer);
    if(__type == type::NO_ERR) return Receive_No_Error(data,dataSize,answer);
    if(__type == type::LO_ERR) return Receive_Lo_Error(data,dataSize,answer);
    if(__type == type::HI_ERR) return Receive_Hi_Error(data,dataSize,answer);
    if(__type == type::HI_COST) return Receive_Hi_Cost(data,dataSize,answer);
    if(__type == type::CORRUPT) return Receive_Corrupt(data,dataSize,answer);
}

#endif
