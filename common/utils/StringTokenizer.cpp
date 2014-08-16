
#include <string>
#include "utils/StringTokenizer.h"

using namespace std;

namespace dyc {

StringTokenizer::StringTokenizer(const string& str,
                                 const string& sep, Option opt)
{
    Tokenize(str, sep, opt);
}

StringTokenizer::StringTokenizer() { 
}

StringTokenizer::~StringTokenizer() { 
}

size_t StringTokenizer::Tokenize(const string& str,
                                 const string& sep, Option opt)
{
    size_t n = 0, old = 0;
    while (n != string::npos)
    {
        n = str.find(sep,n);
        if (n != string::npos)
        {
            if (n != old)
            {
                AddToken(str.substr(old, n - old), opt);
            }
            else 
            {
                AddToken("", opt);
            }
                        
            n += sep.length();
            old = n;
        }
    }
    AddToken(str.substr(old, str.length() - old), opt);    
    return mTokens.size();
}

void StringTokenizer::AddToken(const string& token, Option opt)
{
    size_t length = token.length();        
    if (opt & TOKEN_LEAVE_AS)
    {
        if ( !(opt & TOKEN_IGNORE_EMPTY))
        {
            mTokens.push_back(token);
        }
        else if (length > 0)
        {
            mTokens.push_back(token);
        }
    }
    else if (opt & TOKEN_TRIM)
    {
        size_t n = 0;
        while(n < length && IsSpace(token[n]))
        {
            n++;
        }
        size_t n2 = length;                    
        while(n2 > n && IsSpace(token[n2 - 1]))
        {
            n2--;
        }                        
        if (n2 > n)
        {
            mTokens.push_back(token.substr(n, n2 - n));
        }
        else if ( !(opt & TOKEN_IGNORE_EMPTY))
        {
            mTokens.push_back("");//insert an empty token
        }                    
    }
    else if (length > 0)
    {
        mTokens.push_back(token);
    }
}

}

