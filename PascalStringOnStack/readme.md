# c++ string  on stack
One of the biggest bottlenecks(ok not the biggest, but definitely big) is unnecessary memory allocations on the heap. 
This project is an attempt to mimic std::string except that the allocation will be on stack insted of heap just like
old style c char arrays. Obviously this added constraint will reduce the flexibility that std::string offers to some extent. 
