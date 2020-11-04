#pragma once
#include "sfh_file.h"
#include <fstream>
#include <vector>

namespace sfh
{
    class JM_DLL_OUT ReadFile : public File
    {
    private:
        std::ifstream inFile;

    public:
        ReadFile();
        ReadFile(const char* path);

    public:
        char* ReadBuffer(size_t size);

    public:
        // Used to read primitive datatype like ints, floats ect...
        template<typename T>
        JM_DLL_OUT T ReadPrimitive()
        {
            char type[sizeof(T)];
            inFile.read(type, sizeof(T));
            return *(T*)type;
        }

    public:
        // Used to read a user defined datatype on the heap
        // Doesn't like to read non existing pointers 
        template<class T>
        JM_DLL_OUT T* ReadClassHeap()
        {
            char* type = new char[sizeof(T)];
            inFile.read(type, sizeof(T));
            return (T*)type;
        }
        // Used to read a user defined datatype
        // Doesn't like to read non existing pointers 
        template<class T>
        JM_DLL_OUT T ReadClass()
        {
            char type[sizeof(T)];
            inFile.read((char*)type, sizeof(T));
            return *(T*)&type;
        }

    public:
        // Used to read a std::vector containing any datatype on the heap
        // Doesn't like to read non existing pointers 
        template<class T>
        JM_DLL_OUT std::vector<T*> ReadHeapCollection()
        {
            int length = ReadPrimitive<long long>();
            std::vector<T*> types;
            types.reserve(length);

            for (int i = 0; i < length; i++)
                types.push_back(new T(ReadClass<T>()));

            return types;
        }
        // Used to read a std::vector containing any datatype
        // Doesn't like to read non existing pointers 
        template<class T>
        JM_DLL_OUT std::vector<T> ReadCollection()
        {
            int length = ReadPrimitive<long long>();
            std::vector<T> types;
            types.reserve(length);

            for (int i = 0; i < length; i++)
                types.push_back(ReadClass<T>());

            return types;
        }

        // Used to read a pre alocated array containing any datatype
        // Doesn't like to read non existing pointers 
        template<class T>
        JM_DLL_OUT T* ReadArray(T* types, long long length)
        {
            ReadSkip(8);

            for (int i = 0; i < length; i++)
                types[i] = ReadClass<T>();

            return types;
        }

        // Used to read a heap array containing any datatype
        // Doesn't like to read non existing pointers 
        template<class T>
        JM_DLL_OUT T* ReadArrayHeap(int* getLength = nullptr)
        {
            int length = ReadPrimitive<long long>();
            T* types = new T[length];

            for (int i = 0; i < length; i++)
                types[i] = ReadClass<T>();

            if (getLength != nullptr)
                *getLength = length;
            
            return types;
        }

    public:
        // Used to skip x amount of bytes
        void ReadSkip(int amount);

    private:
        virtual void Open() override;

    public:
        virtual void Close() override;

    public:
        std::ifstream& GetInFileStream();
    };
}