#include <climits>
#include <iostream>
#include <math.h>

using namespace std;
using ull = unsigned long long;
/**
 * @brief 互いに素か否か
 *
 * @param a
 * @param b
 * @return true
 * @return false
 */
bool isRelativelyPrime(ull a, ull b) {
    bool ret = true;
    ull minAB = min(a, b);
    if (a % 2 == 0 && b % 2 == 0) {
        ret = false;
        return ret;
    }

    for (ull i = 3; i <= minAB; i += 2) {
        // cout << "i:" << i << endl;
        if (a % i == 0 && b % i == 0) { // 互いに素ではない
            ret = false;
            break;
        }
    }

    return ret;
}

/**
 * @brief 二乗以上
 *
 * @param m message
 * @param e べき乗
 * @param n 素数の積
 * @return ull
 */
ull sendEncrypt(ull m, ull e, ull n) {
    ull send = m % n;// m (mod n)
    // cout << send << endl;

    for (ull i = 1; i < e; i++) {
        send = send * m;
        send = send % n;
        // cout << "i:" << i << " send:" << send << endl;
    }

    return send % n;
}

/**
 * @brief 二乗以上
 *
 * @param m message
 * @param e べき乗 秘密鍵
 * @param n 素数の積
 */
ull rcvDecrypt(ull m, ull d, ull n) {
    ull recv = m % n;// m (mod n)

    for (ull i = 1; i < d; i++) {
        recv = recv * m;
        recv = recv % n;
        // cout << "i:" << i << " recv:" << recv << endl;
    }

    return recv % n;
}

int main() {

    ull p, q;
    ull n = p * q; // 公開鍵
    ull e;         // (p - 1) * (q - 1) と互いに素なe  公開鍵
    ull d;         // 秘密鍵

    do {
        cout << "please input prime p and q: ";
        cin >> p >> q;
    } while (ULLONG_MAX < p * q);
    // cout << "please input prime p and q: ";
    n = p * q; // 公開鍵

    ull x; // message
    do {
        cout << "please input  message: ";
        cin >> x;
    } while (x > n);

    //cout << "ULLONG_MAX:    " << ULLONG_MAX << endl;
    cout << "n:             " << n << endl;
    // define e
        ull p_q = (p - 1) * (q - 1);
    for (ull i = 2; i < p_q; i++) { // iと(p-1)*)(q-1)は互いに素か
        if (isRelativelyPrime(i, p_q ) ) {
            e = i;
            break;
        }
    }

    cout << "e:" << e << endl;

    // define d
    for (ull i = 1; i <= p_q; i++) {
        if ((e * i) % p_q == 1) {
            d = i;
            break;
        }
    }
    cout << "d:" << d << endl;

    ull send;

    send = sendEncrypt(x, e, n);

    // cout << "send:" << send << endl;

    ull receive;
    // receive = sendEncrypt(x, e, d, n);
    // receive = pow(send, d);
    // receive = receive % n;

    receive = rcvDecrypt(send, d, n);

    cout << "receive:" << receive << endl;

    return 0;
}