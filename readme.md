## Null Networking
This will create multiple clients that will transfer data to a server. The server will demux the client id and save the client data into 
individual files.
There is no networking. The null network is simulated in the main thread that just transfers the blocks between the client and the server.

## Client Interface
The client interface (send_client_intf) is just the send function with buffer and num bytes.

```
void async_send(uint8_t* buffer, int num_bytes);
```

## FileClient
This implements the client interface. It takes FILE* chops it into random sized [1, MaxPacketSize]. Each of these buffers are then copied over to a data gram and enqueued into the queue provided by the user.

```
FileClient(TsDeque& server_que, uint8_t client_id);

// Blocking call that reads the fp and enqueues it to the queue as a datagram.
void run(File* file);
```

## Server Interface
The server interface is a blocking recieve that waits for the datagram to arrive. 

```
std::smart_ptr<Datagram> receive();

```

## FileServer
The server implements the server interface. On getting datagram asserts that the sequence number and checksum is correct. Once validated, it will store the data into a client specific file.
On exit it will close all the files.

```
FileServer(TsDeque& server_que);

// blocking call that stores the data to a file
void run();

// Closes all the file pointers.
void close();

```

The filenames created are hardwired to "server_{client_id}.out".

## Main
1. Takes multiple filenames as command line args (not more than 4) and opens all the files. 
2. Create the file server and start the run method on a separate thread. The run method is a blocking call.
3. Start file client.run on a new thread.
4. Wait for all the client threads to be done.
6. Wait for server que to be empty.
7. Close the server. this will close all the output files.
8. Compare the input file and output file. Use the client id to match the pairs.

## Thread Safe Queue
This is a thread safe template deque.

```
// Push back entry into the item.
void push_back(T item);

// Waiting for item to arrive
void wait_for_item();

// Pop entry from the queue. If queue is empty then it will throw an exception.
T pop_front();

// Return the size of the queue.
int size();
```
