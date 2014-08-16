#ifndef UTIL_STRING_UTIL_H
#define UTIL_STRING_UTIL_H

#include <common.h>
#include <sstream>

namespace dyc {

template<typename T>
std::string ToString(const T& obj)
{
    std::ostringstream s;
    s << obj;
    return s.str();
}

class StringUtil
{
public:
    StringUtil();
    ~StringUtil();
public:

    static void Uint64ToHexStr(uint64_t value, char* hexStr, int len);
    static bool HexStrToUint64(const char* str, uint64_t& value);
    static bool IsSpace(const std::string& text);
    static std::string Trim(const std::string& s);
    static void TrimString(std::string &str);
    
    static void SplitTokensByDelimiter(
        const std::string& line,
        std::vector<std::string>& tokens,
        const char* delim,
        size_t size);

    /* valid utf-8 format
     * 0xxxxxxx                                         (00-7f）
     * 110xxxxx 10xxxxxx                                (c0-df)(80-bf)
     * 1110xxxx 10xxxxxx 10xxxxxx                       (e0-ef)(80-bf)(80-bf)
     * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx              (f0-f7)(80-bf)(80-bf)(80-bf)
     * 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx     (f8-fb)(80-bf)(80-bf)(80-bf)(80-bf)
     * 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx (fc-fd)(80-bf)(80-bf)(80-bf)(80-bf)(80-bf)
     * Checking the string from 3 points.
     * 1. A token has 1-6 bytes.
     * 2. In a token, the first 2 bits of the bytes except the first byte should be 10xxxxx.
     * 3. The count of the bytes should follow the first byte.
     */
     static bool IsValidUTF8(const std::string& str);

     static unsigned int GetCountOfCharUTF8(const std::string& str);

     static unsigned int GetCountOfLatinCharUTF8(const std::string& str);

     static std::string GetNextCharUTF8(const std::string& str, std::string::size_type start);

     static unsigned int CalEditDistanceUTF8(const std::string& first, const std::string& second);

};

}

#endif //STRING_UTIL_H
