#include<iostream>
#include"Memory_tracker.hpp"

int main(){
    int *thePtr = new int;
    Memory_Tracker::Instance()->showStatus();
    return 0;
}