#pragma once
#include "sfh_file.h"
#include <fstream>
#include <vector>

namespace sfh
{
    class JM_DLL_OUT WriteFile : public File
    {
    private:
        std::ofstream outFile;

    public:
        WriteFile();
        WriteFile(const char* path);

    public:
        void WriteBuffer(char* buffer, size_t size);

    public:
        // Used to write primitive datatype like ints, floats ect...
        template<typename T>
        JM_DLL_OUT void WritePrimitive(T primitive)
        {
            outFile.write(reinterpret_cast<char const*>(&primitive), sizeof(T));
        }

        // Used to write an array of a primitive datatype like ints, floats ect...
        template<typename T>
        JM_DLL_OUT void WritePrimitives(T* primitives, int size)
        {
            for (int i = 0; i < size; i++)
                WritePrimitive<T>(primitives[i]);
        }

    public:
        // Used to write a user defined datatype
        // Be aware of pointers in your class
        template<class T>
        JM_DLL_OUT void WriteClass(T* type)
        {
            outFile.write((char*)type, sizeof(T));
        }

        // Used to write a user defined datatype
        // Be aware of pointers in your class
        template<class T>
        JM_DLL_OUT void WriteClass(T& type)
        {
            WriteClass(&type);
        }

    public:
        // Used to write a std::vector containing user defined datatype
        // Be aware of pointers in your class
        template<class T>
        JM_DLL_OUT void WriteCollection(std::vector<T*> types)
        {
            WritePrimitive<long long>(types.size());
            for (int i = 0; i < types.size(); i++)
                WriteClass<T>(*types[i]);
        }

        // Used to write a std::vector containing any datatype
        // Be aware of pointers in your class
        template<class T>
        JM_DLL_OUT void WriteCollection(std::vector<T> types)
        {
            WritePrimitive<long long>(types.size());
            for (int i = 0; i < types.size(); i++)
                WriteClass<T>(types[i]);
        }

    private:
        virtual void Open() override;

    public:
        virtual void Close() override;

    public:
        std::ofstream& GetOutFileStream();
    };
}