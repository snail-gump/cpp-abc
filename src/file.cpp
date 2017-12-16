#include "../include/file.h"

#include <cstdint>
#include <cstdio>
#include <string>

namespace abc
{
    class File::Impl
    {
    public:
        Impl(const char* filename)
        {
            if (nullptr != filename)
                _filename = filename;
        }
        virtual ~Impl()
        {

        }
    public:
        std::vector<char> ReadAllToVector(int32_t* error_code)
        {
            std::vector<char> vc;
            FILE* fp = fopen(_filename.c_str(), "rb");
            if (nullptr != fp){
                fseek(fp, 0, SEEK_END);
                int32_t len = ftell(fp);
                fseek(fp, 0, SEEK_SET);
                vc.resize(len);
                fread(vc.data(), 1, len, fp);
                if (nullptr != error_code) *error_code = 0;
                fclose(fp);
                return vc;
            }
            if (nullptr != error_code) *error_code = -2;
            return vc;
        }
        int32_t WriteAllFromVector(std::vector<char>& data)
        {
            FILE* fp = fopen(_filename.c_str(), "wb");
            if (nullptr != fp){
                fwrite(data.data(), 1, data.size(), fp);
                fflush(fp);
                fclose(fp);
            }
            return -2;
        }
    protected:
        std::string _filename;
    };
    File::File(const char* filename)
    {
        _impl = std::make_shared<Impl>(filename);
    }

    File::~File()
    {
        _impl.reset();
    }

    std::vector<char> File::ReadAllToVector(int32_t* error_code)
    {
        std::vector<char> vc;
        if (!_impl){
            if (nullptr != error_code) * error_code = -1;
            return vc;
        }
        return _impl->ReadAllToVector(error_code);
    }
    std::string File::ReadAllToString(int32_t* error_code)
    {
        int32_t err = 0;
        std::vector<char> vc = ReadAllToVector(&err);
        if (0 != err){
            if (nullptr != error_code) *error_code = err;
            return "";
        }
        std::string res;
        res.resize(vc.size() + 1);
        res.assign(vc.data(), vc.size());
        if (nullptr != error_code)*error_code = 0;
        return res;
    }
    int32_t File::WriteAllFromVector(std::vector<char>& data)
    {
        if (nullptr == _impl)
            return -1;
        return _impl->WriteAllFromVector(data);
    }
}