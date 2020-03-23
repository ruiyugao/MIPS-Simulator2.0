/*!
 *
 * CSC3050 Project 2: MIPS Simulator
 * Created by Ruiyu GAO on 2020/3/21
 *
 */
#include <fstream>
#include <cstring>
#include "tokenscanner.hpp"
#include "command.hpp"
#include "enumType.hpp"
using namespace std;

/*!
 * I used to use this to get the size but finally I choose to set a flag.
 * So now this one is useless. 2020/3/23
 * @param infile
 * @return
 */
int fileSize(ifstream & infile)
{
    int count = 0;
    string line;
    while(!infile.eof()) {
        getline(infile, line);
        (line.length() != 0) && ([&]()
        {
            count++;return 1;
        }());
    }
    return count;
}
/*!
 * Here is the main func to execute the program
 * @param argc
 * @param argv
 * @return
 */

int main(int argc, char *argv[])
{
	init();
	ifstream fin;
	fin.open("../testfile.asm"); // here to put the relative path of input file.
    string s;
	tokenscanner ts;
    char line[10000];
    if (!fin.is_open())
    {
        cout << "Unable to open file. Please try again." << endl;
    }

    //remove the comment
    while (fin.getline(line, 10000)){
        char *token = strtok(line, "#");
        if (token == nullptr)
        {
            continue;
        }
        strcpy(line, token);
        cout << token << endl;
        code.push_back(token);
    }
	fin.close();

    reg[sp] = SIZE;
	int cnt = 0, Size = code.size();
    while(cnt < Size){
        while(cnt < Size){
            ts.set(code[cnt++]);
            s = ts.nextToken();
            if (s  == "\tsyscall"){
                s == "syscall";
            }

            if(s == ".text") break;
			if (s.empty()) continue;
            int len = s.size();
            if(s[len - 1] == ':'){
                s.erase(len - 1, 1);
                lable[s] = heapLength;
				if (s == "main") break;
            }
            else{
                command cmd = parse(code[cnt - 1]);
                dataExcute(cmd);
            }
        }
        while(cnt < Size){
            ts.set(code[cnt++]);
            s = ts.nextToken();
            if (s  == "\tsyscall"){
                s == "syscall";
            }
            if(s == ".data") break;
			if (s.empty()) continue;
            int len = s.size();
            if(s[len - 1] == ':'){
                s.erase(len - 1, 1);
                lable[s] = cnt;
            }
        }
        cnt++;
    }
	for (int i = 0; i < Size; ++i) {
		ts.set(code[i]);
		COMMAND.regiSize = 0;
		COMMAND.flag = false;
		COMMAND.type = insType[ts.nextToken()];
		while (ts.hasMoreTokens()) {
			s = ts.nextToken();
            if (s  == "\tsyscall"){
                s == "syscall";
            }
			if (s[0] == '$') COMMAND.regi[COMMAND.regiSize++] = regType[s];
			else if (s[0] == '_') COMMAND.Lable = lable[s];
			else if (s[0] == '-' || (s[0] <= '9' && s[0] >= '0')) {
				COMMAND.num = to_int(s);
				COMMAND.flag = true;
			}
		}
		CMD.push_back(COMMAND);
	}
	reg[pc] = lable["main"];
    while(true){
        WB();
        MEM();
        EX();
        IDDP();
        IF();
        if(cnt >= Size) break;
    }
    return 0;
}
