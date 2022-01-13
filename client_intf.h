#ifndef INCLUDED_client_intf_h
#define INCLUDED_client_intf_h

class ClientIntf {
public:
    void nb_send(uint8_t* buf, int num_bytes) = 0;
}

#endif