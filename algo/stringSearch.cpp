#include "common.h"
#include "rawlog.h"

using namespace dyc;

int bruteForce(const char* text, const char* pattern) {
    int textLen = strlen(text);
    int patternLen= strlen(pattern);
    if(patternLen > textLen)
        return -1;
    for(int i=0;i<=textLen-patternLen;++i){
        bool found = false;
        int j=0;
        while(j < patternLen && text[i+j] == pattern[j]){
            ++j;
        }
        if(j == patternLen){
            found = true;
            return i;
        }
    }
    return -1;
}

int kmp(char* text, char* pattern) {
    
}

int main(){
    int ret = bruteForce("hahadyc", "dyc");
    NOTICE_LOG("ret: %d ", ret);
}
