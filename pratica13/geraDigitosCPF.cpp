#include <iostream>

int main() {
    int v[9];
    int n;
    int sum1 = 0;
    int sum2 = 0;
    int dig1;
    int dig2;

    std::cin >> n;  

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 9; j++) {
            char c;
            std::cin >> c;
            v[j] = c - '0';
        }
        
        for (int j = 0; j < 9; j++) {
            sum1 += v[j] * (10 - j);
        }
        for (int j = 0; j < 9; j++) {
            sum2 += v[j] * (11 - j);
        }
        dig1 = (10 * sum1)%11;
        if (dig1 == 10){
            dig1 = 0;
        }
        sum2 += dig1 * 2;
        dig2 = (10 * sum2)%11;
        std::cout << dig1;
        std::cout << dig2 << '\n';
        sum1 = 0;
        sum2 = 0;
    }

    return 0;
}