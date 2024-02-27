#include <iostream>
int main() {

    // std::cout << 0%10 << std::endl;

    int w, n;

    std::cin >> n >> w;
    
    int ans = w;
	for (int i = 5; i < n; i++)
		for (int j = 3; j < n; j++)
			for (int k = 1; k < n; k++)
			{
				ans += 2;
                std::cout << ans << std::endl;
				if (ans % 10 == 0)
					break;
			}

    return 0;
}