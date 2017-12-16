#include "../include/arg.h"

#include <map>
#include <vector>

namespace abc
{
    class Arg::Impl
    {
    public:
        Impl(int argc, char* argv[])
        {
            Init(argc, argv);
        }
        virtual ~Impl()
        {

        }
    public:
        std::string GetOptString(const char* opt_name)
        {
            if (nullptr == opt_name)
                return "";
            auto iter = _arg_maps.find(opt_name);
            if (_arg_maps.end() != iter)
                return iter->second;
            return "";
        }
    protected:
        void Init(int argc, char* argv[])
        {
            for (int index = 0; argc > index; ++index)
                _argv.push_back(argv[index]);
            for (int index = 1; _argv.size() > index; ++index){
                auto arg = _argv[index];
                auto pos = arg.find("=");
                std::string key = arg;
                std::string value = "";
                if (arg.npos != pos){
                    std::string key = arg.substr(pos);
                    std::string value = arg.substr(pos + 1);
                }
                key = RemoveFirstCharIf(key, '-');
                key = RemoveFirstCharIf(key, '-');
                _arg_maps.insert(std::make_pair(key, value));
            }
        }
        std::string RemoveFirstCharIf(std::string str, char match)
        {
            if (!str.empty()){
                if (match == str[0])
                    return str.substr(1);
            }
            return str;
        }
    protected:
        int _argc;
        std::vector<std::string> _argv;
        std::map<std::string, std::string> _arg_maps;
    };
    Arg::Arg(int argc, char* argv[])
    {
        _impl = std::make_shared<Impl>(argc, argv);
    }
    Arg::~Arg()
    {
        
    }
    std::string Arg::GetOptString(const char* opt_name)
    {
        if (!_impl)
            return "";
        return _impl->GetOptString(opt_name);
    }
}