#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void copyImg(string &src_img, string &dest_img){
    ifstream fin(src_img, ios::binary);
    if(!fin){
        cerr << "Error while opening source image: " << src_img << endl;
    }
    else{
        cout << "Source image opened: " << src_img << endl;
    }

    ofstream fout(dest_img, ios::binary);
    if(!fout){
        cerr << "Error while opening destination image: " << dest_img << endl;
    }
    else{
        cout << "Destination image opened: " << dest_img << endl;
    }
    string line;
    size_t bufferSize = 1024;
    char buffer[bufferSize];
    while(fin.read(buffer, bufferSize)){
        fout.write(buffer, fin.gcount());
    }
    fout.write(buffer, fin.gcount());

    cout << "Image copied succesfull to " << dest_img << " from " << src_img << endl;
    fin.close();
    fout.close();

}

int main(){
    string src = "./assets/s_img.jpg";
    string dest = "./assets/d_img.jpg";
    copyImg(src, dest);
}
