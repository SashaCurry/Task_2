#include <iostream>
#include "cmath"
#include "vector"
#include "string"
#include "chrono"
#include "map"
#include "fstream"
#include "boost/multiprecision/cpp_int.hpp"

using namespace std;
using namespace std::chrono;
using namespace boost::multiprecision;

map <char, string> book{ {'0', "111"}, {'1', "112"}, {'2', "113"}, {'3', "114"}, {'4', "115"}, {'5', "116"}, {'6', "117"}, {'7', "118"}, {'8', "119"},
                         {'9', "121"}, {' ', "122"}, {'!', "123"}, {'"', "124"}, {'#', "125"}, {'$', "126"}, {'%', "127"}, {'^', "128"}, {'&', "129"},
                         {'\'', "131"}, {'(', "132"}, {')', "133"}, {'*', "134"}, {'+', "135"}, {',', "136"}, {'-', "137"}, {'.', "138"}, {'/', "139"},
                         {':', "141"}, {';', "142"}, {'<', "143"}, {'=', "144"}, {'>', "145"}, {'?', "146"}, {'@', "147"}, {'[', "148"}, {'\\', "149"},
                         {']', "151"}, {'_', "152"}, {'`', "153"}, {'{', "154"}, {'}', "155"}, {'|', "156"}, {'~', "157"}, {'\n', "158"}, {'a', "159"},
                         {'b', "161"}, {'c', "162"}, {'d', "163"}, {'e', "164"}, {'f', "165"}, {'g', "166"}, {'h', "167"}, {'i', "168"}, {'j', "169"},
                         {'k', "171"}, {'l', "172"}, {'m', "173"}, {'n', "174"}, {'o', "175"}, {'p', "176"}, {'q', "177"}, {'r', "178"}, {'s', "179"},
                         {'t', "181"}, {'u', "182"}, {'v', "183"}, {'w', "184"}, {'x', "185"}, {'y', "186"}, {'z', "187"}, {'A', "188"}, {'B', "189"},
                         {'C', "191"}, {'D', "192"}, {'E', "193"}, {'F', "194"}, {'G', "195"}, {'H', "196"}, {'I', "197"}, {'J', "198"}, {'K', "199"},
                         {'L', "211"}, {'M', "212"}, {'N', "213"}, {'O', "214"}, {'P', "215"}, {'Q', "216"}, {'R', "217"}, {'S', "218"}, {'T', "219"},
                         {'U', "221"}, {'V', "222"}, {'W', "223"}, {'X', "224"}, {'Y', "225"}, {'Z', "226"} };

map <string, char> bookRvs{ {"111", '0'}, {"112", '1'}, {"113", '2'}, {"114", '3'}, {"115", '4'}, {"116", '5'}, {"117", '6'}, {"118", '7'}, {"119", '8'},
                            {"121", '9'}, {"122", ' '}, {"123", '!'}, {"124", '"'}, {"125", '#'}, {"126", '$'}, {"127", '%'}, {"128", '^'}, {"129", '&'},
                            {"131", '\''}, {"132", '('}, {"133", ')'}, {"134", '*'}, {"135", '+'}, {"136", ','}, {"137", '-'}, {"138", '.'}, {"139", '/'},
                            {"141", ':'}, {"142", ';'}, {"143", '<'}, {"144", '='}, {"145", '>'}, {"146", '?'}, {"147", '@'}, {"148", '['}, {"149", '\\'},
                            {"151", ']'}, {"152", '_'}, {"153", '`'}, {"154", '{'}, {"155", '}'}, {"156", '|'}, {"157", '~'}, {"158", '\n'}, {"159", 'a'},
                            {"161", 'b'}, {"162", 'c'}, {"163", 'd'}, {"164", 'e'}, {"165", 'f'}, {"166", 'g'}, {"167", 'h'}, {"168", 'i'}, {"169", 'j'},
                            {"171", 'k'}, {"172", 'l'}, {"173", 'm'}, {"174", 'n'}, {"175", 'o'}, {"176", 'p'}, {"177", 'q'}, {"178", 'r'}, {"179", 's'},
                            {"181", 't'}, {"182", 'u'}, {"183", 'v'}, {"184", 'w'}, {"185", 'x'}, {"186", 'y'}, {"187", 'z'}, {"188", 'A'}, {"189", 'B'}, 
                            {"191", 'C'}, {"192", 'D'}, {"193", 'E'}, {"194", 'F'}, {"195", 'G'}, {"196", 'H'}, {"197", 'I'}, {"198", 'J'}, {"199", 'K'}, 
                            {"211", 'L'}, {"212", 'M'}, {"213", 'N'}, {"214", 'O'}, {"215", 'P'}, {"216", 'Q'}, {"217", 'R'}, {"218", 'S'}, {"219", 'T'}, 
                            {"221", 'U'}, {"222", 'V'}, {"223", 'W'}, {"224", 'X'}, {"225", 'Y'}, {"226", 'Z'} };


vector <cpp_int> deg2(cpp_int el, cpp_int n) {
    vector <cpp_int> res;
    while (n != 0) {
        if (n / el == 1) {
            res.push_back(el);
            n -= el;
            el = 1;
        }
        else
            el *= 2;
    }
    return res;
}


cpp_int multMod(cpp_int n, cpp_int mod, vector <pair <cpp_int, cpp_int>> lst) {
    if (lst.size() == 1) {
        cpp_int res = 1;
        for (int i = 0; i < lst[0].second; i++)
            res = res * lst[0].first % mod;
        return res;
    }
    else if (lst[0].second == 1) {
        cpp_int el = lst[0].first;
        lst.erase(lst.begin());
        return (el * multMod(n, mod, lst)) % mod;
    }
    else {
        for (int i = 0; i < lst.size(); i++)
            if (lst[i].second > 1) {
                lst[i].first = (lst[i].first * lst[i].first) % mod;
                lst[i].second /= 2;
            }
        return multMod(n, mod, lst);
    }
}


cpp_int powClosed(cpp_int x, cpp_int y, cpp_int mod) {
    if (y == 0)
        return 1;

    vector <cpp_int> lst = deg2(1, y);
    vector <pair <cpp_int, cpp_int>> xDegs;
    for (int i = 0; i < lst.size(); i++)
        xDegs.push_back(make_pair(x, lst[i]));

    cpp_int res = multMod(x, mod, xDegs);
    return res;
}


cpp_int usualEuclid(cpp_int a, cpp_int b) {
    if (a < b)
        swap(a, b);
    if (a < 0 || b < 0)
        throw string{ "Выполнение невозможно: a < 0 или b < 0" };
    else if (b == 0)
        return a;

    cpp_int r = a % b;
    return usualEuclid(b, r);
}


cpp_int decForm(string x) {
    cpp_int res = 0, deg = 1;
    if (x.back() == '1')
        res += 1;
    for (int i = 1; i < x.length(); i++) {
        deg = deg * 2;
        if (x[x.length() - i - 1] == '1')
            res += deg;
    }
    return res;
}


bool miller_rabin(cpp_int n, int k = 10) {
    if (n == 0 || n == 1)
        return false;

    cpp_int d = n - 1;
    cpp_int s = 0;
    while (d % 2 == 0) {
        s++;
        d = d / 2;
    }

    cpp_int nDec = n - 1;
    for (int i = 0; i < k; i++) {
        cpp_int a = rand() % nDec;
        if (a == 0 || a == 1)
            a = a + 2;

        cpp_int x = powClosed(a, d, n);
        if (x == 1 || x == nDec)
            continue;

        bool flag = false;
        for (int j = 0; j < s; j++) {
            x = (x * x) % n;
            if (x == nDec) {
                flag = true;
                break;
            }
        }
        if (!flag)
            return false;
    }

    return true;
}


vector <cpp_int> generateKeys(cpp_int x) {
    cpp_int q = rand();
    while (!miller_rabin(q))
        q++;

    cpp_int s, p = 2, pDec;
    while (!miller_rabin(p)) {
        string sBin = "";
        int sBinSize = rand() % 50 + 1;
        for (int i = 0; i < sBinSize; i++)
            sBin = sBin + to_string(rand() % 2);
        s = decForm(sBin);

        p = (q * s) + 1;
        pDec = p - 1;
    }

    cpp_int a = 2, g;
    while (pDec > a) {
        g = powClosed(a, pDec / q, p);
        if (g == 1) {
            a++;
            continue;
        }
        break;
    }

    cpp_int y = powClosed(g, x % p, p);
    return vector <cpp_int> {p, g, y};
}


//////////////////////////////////////////////////////////////////////РЕЖИМ ШИФРОВАНИЯ///////////////////////////////////////////////////////////////////////
vector <pair <cpp_int, cpp_int>> encryption(vector <cpp_int> keysPGY, cpp_int x, string message) {
    vector <pair <cpp_int, cpp_int>> res;
    cpp_int p = keysPGY[0], g = keysPGY[1], y = keysPGY[2];

    string codeSymbs = "";
    for (int i = 0; i < message.length(); i++)
        codeSymbs += book[message[i]];

    int offset = to_string(p).size();
    for (int i = 0; i < codeSymbs.length(); i += offset) {
        cpp_int M(codeSymbs.substr(i, offset));
        if (M / p != 0) {
            string help = to_string(M);
            help.pop_back();
            cpp_int m(help);
            M = m;
            i--;
        }

        cpp_int k = 2;
        while (usualEuclid(k, p - 1) != 1) {
            string kBin = "";
            int kBinSize = rand() % offset;
            for (int i = 0; i < kBinSize; i++)
                kBin = kBin + to_string(rand() % 2);
            k = decForm(kBin + "1") % p;
        }

        res.push_back(make_pair(powClosed(g, k, p), powClosed(y, k, p) * M % p));
    }
    return res;
}


/////////////////////////////////////////////////////////////////////РЕЖИМ РАСШИФРОВАНИЯ//////////////////////////////////////////////////////////////////////
string decryption(vector <cpp_int> keysPGY, cpp_int x, vector <pair <cpp_int, cpp_int>> ciphertext) {
    string res = "";
    cpp_int p = keysPGY[0], g = keysPGY[1], y = keysPGY[2];

    string codeSymbs = "";
    for (int i = 0; i < ciphertext.size(); i++) {
        cpp_int M, a = ciphertext[i].first, b = ciphertext[i].second;
        M = powClosed(a, p - 1 - (x % p), p) * b % p;
        codeSymbs += to_string(M);
    }
  
    for (int i = 0; i < codeSymbs.length(); i += 3) {
        string M = codeSymbs.substr(i, 3);
        res += bookRvs[M];
    }
    return res;
}


void kerberos(pair <string, string>* users) {
    hash <string> hashStr;
    cpp_int keyUser1(hashStr(users[0].second)), keyUser2(hashStr(users[1].second));
    cout << "\nПользователь " << users[0].first << " зерегистрирован в системе Kerberos. Общий секретный ключ: " << keyUser1;
    cout << "\nПользователь " << users[1].first << " зарегистрирован в системе Kerberos. Общий секретный ключ: " << keyUser2;

    cout << "\n\nПользователь " << users[0].first << " отправляет Kerberos сообщение (" << users[0].first << ", " << users[1].first << ")";

    uint64_t sec = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
    cpp_int timestamp(sec), ttl = 300, mainKey = abs(rand() * rand() * rand());
    string messageForUser1 = "(" + to_string(timestamp) + ", " + to_string(ttl) + ", " + to_string(mainKey) + ", " + users[1].first + ")";
    vector <cpp_int> keysPGYforUser1 = generateKeys(keyUser1);
    vector <pair <cpp_int, cpp_int>> encMessageForUser1 = encryption(keysPGYforUser1, keyUser1, messageForUser1);
    cout << "\n\nKerberos создаёт сообщение (T, L, K, B) = " << messageForUser1 << " для пользователя " << users[0].first << ", генерирует открытые ключи ";
    cout << "(p, g, y) = (" << keysPGYforUser1[0] << ", " << keysPGYforUser1[1] << ", " << keysPGYforUser1[2] << ") и зашифровывает сообщение общим секретным ключом: ";
    for (int i = 0; i < encMessageForUser1.size(); i++)
        cout << "(" << encMessageForUser1[i].first << ":" << encMessageForUser1[i].second << ") ";

    string messageForUser2 = "(" + to_string(timestamp) + ", " + to_string(ttl) + ", " + to_string(mainKey) + ", " + users[0].first + ")";
    vector <cpp_int> keysPGYforUser2 = generateKeys(keyUser2);
    vector <pair <cpp_int, cpp_int>> encMessageForUser2 = encryption(keysPGYforUser2, keyUser2, messageForUser2);
    cout << "\n\nKerberos создаёт сообщение (T, L, K, A) = " << messageForUser2 << " для пользователя " << users[1].first << ", генерирует открытые ключи ";
    cout << "(p, g, y) = (" << keysPGYforUser2[0] << ", " << keysPGYforUser2[1] << ", " << keysPGYforUser2[2] << ") и зашифровывает сообщение общим секретным ключом: ";
    for (int i = 0; i < encMessageForUser2.size(); i++)
        cout << "(" << encMessageForUser2[i].first << ":" << encMessageForUser2[i].second << ") ";

    cout << "\n\nЗашифрованные сообщения и сгенерированные ключи отправляются пользователю " << users[0].first;

    string decMessageForUser1 = decryption(keysPGYforUser1, keyUser1, encMessageForUser1);
    cout << "\n\nПользователь " << users[0].first << " получает сообщения. Сообщение для пользователя " << users[0].first << ": " << decMessageForUser1;

    string message = "(" + users[0].first + ", " + to_string(timestamp) + ")";
    vector <cpp_int> keys = generateKeys(mainKey);
    vector <pair <cpp_int, cpp_int>> encMessage = encryption(keys, mainKey, message);
    cout << ". Далее пользователя формирует собщение (A, T) = " << message << " и зашифровывает сеансовым ключом : ";
    for (int i = 0; i < encMessage.size(); i++)
        cout << "(" << encMessage[i].first << ":" << encMessage[i].second << ") ";
    cout << "\nСообщения (A, T) и (T, L, K, A) передаёт пользователю " << users[1].first;

    string decMessageForUser2 = decryption(keysPGYforUser2, keyUser2, encMessageForUser2);
    string decMessage = decryption(keys, mainKey, encMessage);
    cout << "\n\nПользователь " << users[1].first << " получает свои сообщение и расшифровывает: ";
    cout << "(A, T) = " << decMessage << " и (T, L, K, A) = " << decMessageForUser2;

    timestamp += 1;
    message = to_string(timestamp);
    encMessage = encryption(keys, mainKey, message);
    cout << "\n\nПользователь " << users[1].first << " Создаёт сообщение (T + 1) = " << message << ", зашифровывает его сеансовым ключом и отправляет";
    cout << " пользователю " << users[0].first << ": ";
    for (int i = 0; i < encMessage.size(); i++)
        cout << "(" << encMessage[i].first << ":" << encMessage[i].second << ") ";

    cout << "\n\nПользователь " << users[0].first << " получает сообщение от " << users[1].first << " и расшифровывает его: " << decryption(keys, mainKey, encMessage);
}


int main() {
    srand(time(0));
    setlocale(LC_ALL, "ru");
    cout << "\tПротокол Kerberos";

    pair <string, string>* users = new pair <string, string>[2];
    string login, password;
    cout << "\nВведите логин и пароль пользователя 1: ";
    cin >> login >> password;
    users[0] = make_pair(login, password);
    cout << "Введите логин и пароль пользователя 2: ";
    cin >> login >> password;
    users[1] = make_pair(login, password);

    kerberos(users);
    cout << endl;
    return 0;
}
