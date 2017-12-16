#ifndef ABC_INCLUDE_ARG_H_INCLUDE
#define ABC_INCLUDE_ARG_H_INCLUDE

#include <memory>
#include <string>

namespace abc
{
    class Arg
    {
    public:
        Arg(int argc, char* argv[]);
        virtual ~Arg();
    public:
        std::string GetOptString(const char* opt_name);
    protected:
        class Impl;
        std::shared_ptr<Impl> _impl;
    };
}
#endif// ABC_INCLUDE_ARG_H_INCLUDE
