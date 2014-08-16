#include <errno.h>
#include <stdlib.h>
#include "utils/StringUtil.h"

using namespace std;

namespace dyc {

static unsigned char gU8Mask[6] = { 0x80, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE };
static unsigned char gU8Mark[6] = { 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

StringUtil::StringUtil(){
}

StringUtil::~StringUtil() { 
}

string StringUtil::Trim(const std::string& s)
{
    static const char* whiteSpace = " \t\r\n";

    // test for null string
    if (s.empty())
        return s;

    // find first non-space character
    std::string::size_type b = s.find_first_not_of(whiteSpace);
    if (b == std::string::npos) // No non-spaces
        return "";

    // find last non-space character
    std::string::size_type e = s.find_last_not_of(whiteSpace);

    // return the remaining characters
    return std::string(s, b, e - b + 1);

}

void StringUtil::TrimString(std::string &str)
{
    static const char* whiteSpace = " \t\r\n";
    size_t start = str.find_first_not_of(whiteSpace);    
    if (start == std::string::npos) {
        str.clear();
        return;
    }
    size_t end = str.find_last_not_of(whiteSpace);
    if (start != 0 || end != str.length() - 1) {
        size_t cur = 0;
        for (; start <= end; ++start) {
            str[cur++] = str[start];
        }
        str.resize(cur);
    }
}

void StringUtil::Uint64ToHexStr(uint64_t value, char* hexStr, int len)
{
    assert(len > 16);
    snprintf(hexStr, len, "%016lx", value);
}

bool StringUtil::HexStrToUint64(const char* str, uint64_t& value) 
{
    if (NULL == str || *str == 0) 
    {
        return false;
    }
    char* endPtr = NULL;
    errno = 0;
    value = (uint64_t)strtoull(str, &endPtr, 16);
    if (errno == 0 && endPtr && *endPtr == 0) 
    {
        return true;
    }
    return false;
}

bool StringUtil::IsSpace(const string& text) {
    if (text == string("　")) {
        return true;
    }
    if (text.length() > 1) {
        return false;
    }
    return isspace(text[0]);
}

void StringUtil::SplitTokensByDelimiter(
    const std::string& line,
    std::vector<std::string>& tokens,
    const char* delim,
    size_t size)
{
    tokens.clear();
    std::string::size_type startPos = 0;
    while (startPos != std::string::npos)
    {
        std::string::size_type endPos = line.find(delim, startPos, size);
        if (endPos == std::string::npos)
        {
            tokens.push_back(line.substr(startPos));
            startPos = std::string::npos;
        }
        else if (startPos == line.length())
        {
            tokens.push_back(std::string(""));
            startPos = std::string::npos;
        }
        else
        {
            tokens.push_back(line.substr(startPos, endPos - startPos));
            startPos = endPos + size;
        }
    }
}

/* valid utf-8 format
 * 0xxxxxxx                                        (00-7f）
 * 110xxxxx 10xxxxxx                               (c0-df)(80-bf)
 * 1110xxxx 10xxxxxx 10xxxxxx                      (e0-ef)(80-bf)(80-bf)
 * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx              (f0-f7)(80-bf)(80-bf)(80-bf)
 * 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx     (f8-fb)(80-bf)(80-bf)(80-bf)(80-bf)
 * 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx (fc-fd)(80-bf)(80-bf)(80-bf)(80-bf)(80-bf)
 * Checking the string from 3 points.
 * 1. A token has 1-6 bytes.
 * 2. In a token, the first 2 bits of the bytes except the first byte should be 10xxxxx.
 * 3. The count of the bytes should follow the first byte.
 */
bool StringUtil::IsValidUTF8(const std::string& str)
{
    std::string::size_type i, s;
    for (i = 0U, s = 0U; i < str.length(); ++i)
    {
        unsigned char value = str[i];
        if (s == 0)
        {
            for (; s < 6U && ((value & gU8Mask[s]) != gU8Mark[s]); ++s)
            {}

            if (s == 6U)
            {
                return false;
            }
        }
        else
        {
            if ((value & 0xC0) != 0x80)
            {
                return false;
            }

            --s;
        }
    }

    return (s == 0U);
}

unsigned int StringUtil::GetCountOfCharUTF8(const std::string& str)
{
    unsigned int count = 0;
    for (std::string::size_type i = 0U; i < str.length();)
    {
        unsigned char value = str[i];
        unsigned int j;
        for (j = 0U; j < 6U; ++j)
        {
            if ((value & gU8Mask[j]) == gU8Mark[j])
            {
                i = i + j + 1;
                ++count;
                break;
            }
        }

        if (j == 6U)
        {
            return 0;
        }
    }

    return count;
}

unsigned int StringUtil::GetCountOfLatinCharUTF8(const std::string& str)
{
    unsigned int count = 0;
    for (std::string::size_type i = 0U; i < str.length();)
    {
        unsigned char value = str[i];
        unsigned int j;
        for (j = 0U; j < 6U; ++j)
        {
            if ((value & gU8Mask[j]) == gU8Mark[j])
            {
                i = i + j + 1;
                if (j == 0U)
                {
                    ++count;
                }

                break;
            }
        }

        if (j == 6U)
        {
            return 0;
        }
    }

    return count;
}

std::string StringUtil::GetNextCharUTF8(
    const std::string& str,
    std::string::size_type start)
{
    if (start < str.length())
    {
        unsigned char value = str[start];
        unsigned int i;
        for (i = 0U; i < 6U; ++i)
        {
            if ((value & gU8Mask[i]) == gU8Mark[i])
            {
                if (start + i < str.length())
                {
                    return str.substr(start, i + 1);
                }
                else
                {
                    break;
                }
            }
        }
    }

    return "";
}

unsigned int StringUtil::CalEditDistanceUTF8(
    const std::string& first,
    const std::string& second)
{
    unsigned int n = GetCountOfCharUTF8(first);
    unsigned int m = GetCountOfCharUTF8(second);
    unsigned int* value[2];
    value[0] = new unsigned int[m + 1];
    value[1] = new unsigned int[m + 1];

    for (unsigned int i = 0; i <= m; ++i)
    {
        value[0][i] = i;
    }

    std::string::size_type iStart, jStart;
    iStart = 0;
    int index = 1;
    for (unsigned int i = 1; i <= n; ++i)
    {
        value[index][0] = i;
        std::string nextI = GetNextCharUTF8(first, iStart);
        iStart += nextI.length();
        jStart = 0;

        unsigned int preIndex = (index + 1) % 2;
        for (unsigned int j = 1; j <= m; ++j)
        {
            std::string nextJ = GetNextCharUTF8(second, jStart);
            jStart += nextJ.length();
            unsigned delta = (nextI == nextJ ? 0 : 1);

            if (value[preIndex][j] < value[index][j - 1])
            {
                value[index][j] = value[preIndex][j] + 1;
            }
            else
            {
                value[index][j] = value[index][j - 1] + 1;
            }

            if (value[index][j] > value[preIndex][j - 1] + delta)
            {
                value[index][j] = value[preIndex][j - 1] + delta;
            }
        }

        index = preIndex;
    }

    unsigned int result = value[(index + 1) % 2][m];
    delete[] value[0];
    delete[] value[1];
    return result;
}

}
