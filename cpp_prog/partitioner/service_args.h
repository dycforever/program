
class ServiceArgs
{
public:
    ServiceArgs();
    ~ServiceArgs();

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


ServiceArgs::ServiceArgs()
    : mThreadPoolSize(24)
{}

ServiceArgs::~ServiceArgs()
{}

bool ServiceArgs::Parse(int argc, char* argv[])
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

bool ServiceArgs::Validate()
{
    if(mInputFile.empty()) {
        return false;
    }
    return true;
}

void ServiceArgs::PrintHelp()
{
    std::cerr <<"Usage:" << " partitioner -i ip_file -t thread_count" << std::endl;
}


