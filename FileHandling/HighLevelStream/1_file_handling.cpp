#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void copyfile(const string &src_file, const string &dest_file){

    ifstream in(src_file, ios::in);
    if(!in){
        cerr<<"Error while opening the input file."<<endl;
        return;
    }

    ofstream out(dest_file, ios::out);
    if(!out){
        cerr<<"Error while opening the output file."<<endl;
        return;
    }

    const size_t bufferSize = 1024;
    char buffer[bufferSize];

    while (in.read(buffer, bufferSize)) {
        out.write(buffer, in.gcount());
    }
    out.write(buffer, in.gcount());
    in.close();
    out.close();
}

int main(){
    string src_file = "./assets/s_test.txt";
    string dest_file = "./assets/d_test.txt";
    copyfile(src_file, dest_file);
    return 0;
}
