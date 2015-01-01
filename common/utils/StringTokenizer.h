#ifndef UTIL_STRING_TOKENIZER_H
#define UTIL_STRING_TOKENIZER_H

#include "common.h"

namespace dyc {

class StringTokenizer
{
public:
    /// ignore empty tokens
    const static int32_t TOKEN_IGNORE_EMPTY = 1; 
    /// remove leading and trailing whitespace from tokens
    const static int32_t TOKEN_TRIM         = 2;
    /// leave the token as it is
    const static int32_t TOKEN_LEAVE_AS     = 4;

    typedef int32_t Option;
    typedef std::vector<std::string> TokenVector;
    typedef TokenVector::const_iterator Iterator;
public:
    StringTokenizer(const std::string& str, const std::string& sep,
                    Option opt = TOKEN_LEAVE_AS);
    StringTokenizer();
    ~StringTokenizer();
public:
    size_t Tokenize(const std::string& str, const std::string& sep,
                    Option opt = TOKEN_LEAVE_AS);
    
    inline Iterator Begin() const;
    inline Iterator End() const;

    inline const std::string& operator [] (size_t index) const;

    inline size_t GetNumTokens() const;
    inline const TokenVector& GetTokenVector() const;        
private:
    inline static bool IsSpace(char ch);
     
    void AddToken(const std::string& token, Option opt);     
private:
    StringTokenizer(const StringTokenizer&);
    StringTokenizer& operator = (const StringTokenizer&);
private:
    TokenVector mTokens;

};

///////////////////////////////////////////////////////////
// inlines
//
inline bool StringTokenizer::IsSpace(char ch)
{
    return (ch > 0 && std::isspace(ch));
}

inline StringTokenizer::Iterator StringTokenizer::Begin() const
{
    return mTokens.begin();
}

inline StringTokenizer::Iterator StringTokenizer::End() const
{
    return mTokens.end();
}

inline const std::string& StringTokenizer::operator [] (std::size_t index) const
{
    assert(index < mTokens.size());
    return mTokens[index];
}

inline size_t StringTokenizer::GetNumTokens() const
{
    return mTokens.size();
}

inline const StringTokenizer::TokenVector& StringTokenizer::GetTokenVector() const {
    return mTokens;
}


}

#endif //UTIL_STRING_TOKENIZER_H
