#include "MTSText.h"
#include "ctype.h"

using namespace mts;

std::string Text::getLine(const std::string& source, const size_t& start, size_t& cursor) {
    char delimiters[2];
    delimiters[0] = '\n';
    delimiters[1] = '\r';
    size_t end = source.find_first_of(delimiters, start, 2);
    std::string line(source.substr(start, end - start));
    if (end < source.size()) {
        if (end < source.size() - 1)
            if ((source[end] == '\n' && source[end + 1] == '\r') || (source[end] == '\r' && source[end + 1] == '\n')) {
                //Advance an additional character in scenarios where lines end in \r\n or \n\r
                end++;
            }
        end++;
    }
    cursor = end;
    return line;
}

std::vector<std::string> Text::split(const std::string& str, char delimiter, int limit) {
    return split(str, std::string(1, delimiter), limit);
}

std::vector<std::string> Text::split(const std::string& str, const std::string& delimiter, int limit) {
    std::vector<std::string> result;
    if(str.size() == 0) {
        return result;
    }
    size_t start = 0;
    size_t end = str.find(delimiter, start);
    for (int i = 1; i < limit || (limit <= 0 && (end != std::string::npos)); ++i) {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    result.push_back(str.substr(start));
    return result;
}

std::string Text::readString(char* index, int length)
{
    std::string result = std::string(index, length);
    index += length;
    return result;
}

std::string Text::toUpper(const std::string str)
{
    std::string ret = str;

    for (unsigned int i = 0; i < ret.size(); i++)
    {
        ret[i] = toupper(ret[i]);
    }

    return ret;
}

std::string Text::bin2hexString(const std::vector<uint8_t>& data, const char* delim, bool leadingZeros) {
    return bin2hexString(data.data(), data.size(), delim, leadingZeros);
}

std::string Text::bin2hexString(const uint8_t* data, const uint32_t len, const char* delim, bool leadingZeros) {
    std::string str;
    char buf[32];
    char lead[] = "0x";

    for (uint32_t i = 0; i < len; i++) {
        if (leadingZeros)
            str.append(lead);
        snprintf(buf, sizeof(buf), "%02x", data[i]);
        str.append(buf, strlen(buf));
        if (i < len - 1)
            str.append(delim);
    }

    return str;
}
