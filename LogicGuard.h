#ifndef LOGICGUARD_H
#define LOGICGUARD_H

#include <iostream>
#include <string>
#include <vector>
#include <random>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

inline int portable_getch() {
#ifdef _WIN32
    return _getch();
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}


using namespace std;

#define _S(str) LG::XorStr<sizeof(str)>(str)

namespace LG {

    inline char _key() {
        static random_device rd;
        static mt19937 gen(rd());
        static uniform_int_distribution<> dis(1, 255);
        return static_cast<char>(dis(gen));
    }

    template <size_t N>
    struct XorStr {
        char data[N];
        char key;

        constexpr XorStr(const char(&str)[N]) : data{}, key(0) {
            key = static_cast<char>(N * 33);
            for (size_t i = 0; i < N; ++i) {
                data[i] = str[i] ^ (key + i);
            }
        }
    };

    class String {
    private:
        vector<char> buffer;
        char key;

        void toggle() {
            for (auto& c : buffer) c ^= key;
        }

    public:
        // Constructor for Compile-Time Obfuscated Strings
        template <size_t N>
        String(const XorStr<N>& obs) {
            key = _key();
            buffer.reserve(N - 1);
            for (size_t i = 0; i < N - 1; ++i) {
                buffer.push_back(obs.data[i] ^ (obs.key + i));
            }
            toggle();
        }

        // Constructor for Runtime Secure Input
        String(const vector<char>& raw) {
            key = _key();
            buffer = raw;
            toggle();
        }

        ~String() {
            if (!buffer.empty()) {
                volatile char* p = buffer.data();
                for (size_t i = 0; i < buffer.size(); ++i) p[i] = 0;
            }
        }

        string str() {
            toggle();
            string s(buffer.begin(), buffer.end());
            toggle();
            return s;
        }

        friend ostream& operator<<(ostream& os, String& s) {
            return os << s.str();
        }
    };

    static String Input(bool mask = true) {
        vector<char> raw;
        raw.reserve(64);

        char ch;
        while ((ch = portable_getch()) != '\r') {
            if (ch == '\b') {
                if (!raw.empty()) {
                    if (mask) cout << "\b \b";
                    raw.pop_back();
                }
            } else {
                raw.push_back(ch);
                if (mask) cout << '*';
            }
        }
        cout << endl;

        String secure(raw);

        // Wipe traces
        volatile char* p = raw.data();
        for (size_t i = 0; i < raw.capacity(); ++i) p[i] = 0;
        raw.clear();

        return secure;
    }
}

#endif