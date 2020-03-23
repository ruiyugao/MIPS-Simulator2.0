#ifndef TOKENSCANNER_HPP
#define TOKENSCANNER_HPP
#include <string>
using namespace std;

/*!
 * Here is tokenscanner class from CSC3002 with some adjustments.
 * There are 3 bugs to be fixed.
 * ts.index, ts, ts
 */
class tokenscanner
{
private:

    string str;
    int index, len{};

public:

    tokenscanner()
    {
        index = 0;
    }

    ~tokenscanner() = default;

    void set(string &s)
    {
        str = s;
        len = str.size();
        index = 0;
    }

    string nextToken()
    {
        string ret;
        bool   flag = false;
        while (str[index] == ' ' || str[index] == ',' || str[index] == '\t' || str[index] == '"' || str[index] == '(' ||
               str[index] == ')') {
            if (str[index] == '"') {
                flag = true;
                ++index;
                break;
            }
            ++index;
        }
        if (flag) {
            while (str[index] != '"' && index < len) {
                if (str[index] == '\\') {
                    if (str[index + 1] == 'n') ret += '\n';
                    else ret += '\"';
                    ++index;
                }
                else ret += str[index];
                ++index;
            }
            return ret;
        }
        while (str[index] != ' ' && str[index] != ',' && str[index] != '\n' && str[index] != '\t' &&
               str[index] != '"' && str[index] != '(' && str[index] != ')' && index < len) {
            if (str[index] == '\\') {
                if (str[index + 1] == 'n') ret += '\n';
                else ret += '\"';
                ++index;
            }
            else ret += str[index];
            ++index;
        }
        if (ret == "\tsyscall"){
            ret = "syscall";
        }
        return ret;
    }

    bool hasMoreTokens() {
        return index < len;
    }
};

int to_int(const string &s)
{
    int ret = 0, i = 0, len = s.size();
    bool flag = false;
    if(s[i] == '-'){
        flag = true;
        ++i;
    }
    while(i < len) ret = ret * 10 + s[i++] - '0';
    if(flag) ret = -ret;
    return ret;
}

#endif