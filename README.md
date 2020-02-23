**Memory tracker for C++**

To use this, add *Memory_tracker.hpp* these instructions in your main file.  

``` c++
#include"Memory_tracker.hpp"
```
and add  

``` c++
Memory_Tracker::Instance()->showStatus();
```
in the last line to check the memory leak status. It will show you whether you have leaked the memory, if yes, then tell you which file and which line the leak happens.

 
