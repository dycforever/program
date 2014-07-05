
#include "common.h"

class CmdArgs
{
public:
    CmdArgs();
    ~CmdArgs();

public:
    bool Parse(int argc, char *argv[]);
    void PrintHelp();

    const std::string& GetInputFile() const
    { return mInputFile; }

    uint32_t GetThreadPoolSize() const
    { return mThreadPoolSize; }

private:
    bool Validate();

private:
    std::string mInputFile;
    uint32_t mThreadPoolSize;
    
};


CmdArgs::CmdArgs()
    : mThreadPoolSize(24)
{}

CmdArgs::~CmdArgs()
{}

bool CmdArgs::Parse(int argc, char* argv[])
{
    int c;
    while((c = getopt(argc, argv, "i:t:")) != -1)
    {
        switch(c) 
        {
        case 'i':
            mInputFile.assign(optarg);
            break;
        case 't':
            mThreadPoolSize = atoi(optarg);
            break;
        default:
            return false;
        }
    }

    if (!Validate()) {
        return false;
    }

    return true;
}

bool CmdArgs::Validate()
{
    if(mInputFile.empty()) {
        return false;
    }
    return true;
}

void CmdArgs::PrintHelp()
{
    std::cerr <<"Usage:" << " partitioner -i input_file -t thread_count" << std::endl;
}


