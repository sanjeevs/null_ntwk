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
