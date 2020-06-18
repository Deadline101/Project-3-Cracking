#include <iostream>
#include <string>
#include <vector>
#include <climits>
using namespace std;

class KeyGen
{
private:
    string username;
    long long x;
    vector<int> key;
    bool sign;
public:
    long long getX() {
        return this->x;
    }
    void setX(long long x) {
        this->x = x;
    }
    string getUsername() {
        return this->username;
    }
    void setUsername(string username) {
        if (username.size() < 5) {
            cout << "**Username qua ngan**";
            return;
        }
        this->username = username;
    }
    KeyGen() : x(0), username(""), sign(0) {}
    KeyGen(string username) : x(0), username(username), sign(0) {}
    friend istream &operator >> (istream &in, KeyGen &key) {
        do {
            cout << "Nhap username: ";
            getline(in, key.username);
            if (key.username.size() >= 5) {
                break;
            }
            cout << "**Username qua ngan**";
        } while(true);
        
        
        return in;
    }
    friend ostream &operator << (ostream &out, KeyGen &key) {
        if (key.sign == 1) {
            out << "-";
        }
        for (int i = 0; i < key.key.size(); ++i) {
            out << key.key[key.key.size() - i - 1];
        }
        return out;
    }
    void KeyGenerate() {
        if (username == "") {
            return;
        }
        if (this->username.size() >= 7) {
            this->username = username.substr(0, 6);
        }
        //cout << "username: " << username << endl;
        // cout << "username(hex): ";
        //cout << endl;
        int EncryptedStr = 0x23E;
        for (int i = 0; i < username.size(); ++i) {
            EncryptedStr = EncryptedStr * (username[i] / 0x5) + username[i];
        }
        //cout << hex << EncryptedStr << endl;
        if (EncryptedStr < 0) {
            sign = 1;
            EncryptedStr = ~EncryptedStr + 1;
        }
        //cout << hex << EncryptedStr;
        
        while(EncryptedStr != 0x0) {
            key.push_back(EncryptedStr % 0xA);
            EncryptedStr /= 0xA;
        }
    }
};

int main(int argc, char * argv[])
{
    if (argc > 1) {
        KeyGen key;
        key.setUsername(argv[1]);
        key.KeyGenerate();
        cout << key;
    }
    else {
        KeyGen key;
        cin >> key;
        key.KeyGenerate();
        cout << key;
    }
    return 0;
    
}