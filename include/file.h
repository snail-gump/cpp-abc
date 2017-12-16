#ifndef ABC_INCLUDE_FILE_H
#define ABC_INCLUDE_FILE_H
#pragma once

#include <cstdint>
#include <memory>
#include <vector>

namespace abc
{
    class File
    {
    public:
        File(const char* filename);
        virtual ~File();
    public:
        std::vector<char> ReadAllToVector(int32_t* error_code = nullptr);
        std::string ReadAllToString(int32_t* error_code = nullptr);

        int32_t WriteAllFromVector(std::vector<char>& data);
    protected:
        class Impl;
        std::shared_ptr<Impl> _impl;
    };
}

#endif// ABC_INCLUDE_FILE_H
