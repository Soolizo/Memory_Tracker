#ifndef Memory_tracker_hpp
#define Memory_tracker_hpp
#include<iostream>
#include<vector>
#include<string>


class Memory_Tracker{
    public:
        static Memory_Tracker* Instance(){
            if(!s_Instance){
                s_Instance = new Memory_Tracker;
            }
            return s_Instance;
        }
        ~Memory_Tracker(){delete s_Instance;}
        void showStatus(){
            if(allocationAddress.size() == 0){
                std::cout<<"No memory leak."<<std::endl;
            }
            else{
                for (int i = 0; i<allocationAddress.size(); i++){
                    std::cout<<"Allocated: "<<allocationSize[i]<<" bytes on line: "<<allocationLine[i]<< " in file: "<<allocationFile[i]<<std::endl;
                }
                for (int i = 0 ; i<allocationAddress.size(); i++){
                    delete[] allocationAddress[i];
                }
                std::cout<<"Have fixed the leak memory, but you should check your code"<<std::endl;
            }
        }
    private:
        Memory_Tracker (){}
        Memory_Tracker (const Memory_Tracker& ){}
        Memory_Tracker& operator = (const Memory_Tracker& aCopy){
            s_Instance = aCopy.s_Instance;
            return *this;}
        static Memory_Tracker* s_Instance;
        std::vector<void*> allocationAddress;
        std::vector<int> allocationSize;
        std::vector<int> allocationLine;
        std::vector<std::string> allocationFile;
        
        friend void* operator new(size_t size, const char* file, const int line);
        friend void* operator new[](size_t size, const char* file, const int line);
        friend void operator delete  (void* p) noexcept;
        friend void operator delete[]  (void* p) noexcept;
};

Memory_Tracker* Memory_Tracker::s_Instance = Memory_Tracker::Instance();

void* operator new(size_t size, const char* file, const int line){
    void* p = malloc(size);
    Memory_Tracker :: s_Instance->allocationAddress.push_back(p);
    Memory_Tracker :: s_Instance->allocationSize.push_back(size);
    Memory_Tracker :: s_Instance->allocationLine.push_back(line);
    Memory_Tracker :: s_Instance->allocationFile.push_back(file);
    return p;
}

void* operator new[](size_t size, const char* file, const int line){
    void* p = malloc(size);
    Memory_Tracker :: s_Instance->allocationAddress.push_back(p);
    Memory_Tracker :: s_Instance->allocationSize.push_back(size);
    Memory_Tracker :: s_Instance->allocationLine.push_back(line);
    Memory_Tracker :: s_Instance->allocationFile.push_back(file);
    return p;
}

void operator delete (void* p) noexcept{
    for (int i = 0; i< Memory_Tracker :: s_Instance->allocationAddress.size();i++){
        if(Memory_Tracker:: s_Instance->allocationAddress[i] == p){
            Memory_Tracker:: s_Instance->allocationAddress.erase(Memory_Tracker:: s_Instance->allocationAddress.begin()+i);
            Memory_Tracker:: s_Instance->allocationSize.erase(Memory_Tracker:: s_Instance->allocationSize.begin()+i);
            Memory_Tracker:: s_Instance->allocationLine.erase(Memory_Tracker:: s_Instance->allocationLine.begin()+i);
            Memory_Tracker:: s_Instance->allocationFile.erase(Memory_Tracker:: s_Instance->allocationFile.begin()+i);
        }
    }
    free(p);
}

void operator delete[]  (void* p) noexcept{
    for (int i = 0; i< Memory_Tracker :: s_Instance->allocationAddress.size();i++){
        if(Memory_Tracker:: s_Instance->allocationAddress[i] == p){
            Memory_Tracker:: s_Instance->allocationAddress.erase(Memory_Tracker:: s_Instance->allocationAddress.begin()+i);
            Memory_Tracker:: s_Instance->allocationSize.erase(Memory_Tracker:: s_Instance->allocationSize.begin()+i);
            Memory_Tracker:: s_Instance->allocationLine.erase(Memory_Tracker:: s_Instance->allocationLine.begin()+i);
            Memory_Tracker:: s_Instance->allocationFile.erase(Memory_Tracker:: s_Instance->allocationFile.begin()+i);
        }
    }
}


#define new new(__FILE__, __LINE__)
#endif