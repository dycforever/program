#include <iostream>
#include <string>
#include <vector>

class Test {
public:
    Test(const std::string& text) {
        std::cout << "Test:" << text << ":" << this << std::endl;
    }

    ~Test() {
        std::cout << "~Test:" << this << std::endl;
    }

    void addSth(const std::string& str) {
        strVec_.push_back(str);
    }

    size_t getCount() const {
        return (strVec_.size());
    }

private:
    std::vector<std::string> strVec_;
};

static Test sObj("sObj");
Test gObj("gObj");

void hello() {
    std::cout << "static:" << &sObj << std::endl;
}


