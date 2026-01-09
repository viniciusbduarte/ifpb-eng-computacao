#include <iostream>
#include <format>

const int alvo{3};

int main(){
    int arr[5];
    
    for(int i = 0; i<5; i++) std::cin >> arr[i] ;

    for(int i=0; i<5; i++)
        for(int j=0; i<5; i++)
            if( arr[i] + arr[j] == alvo) {
                std::cout << std::format("A soma do valores {} e {} resultam no alvo {} \n", arr[i], arr[j], alvo);
            }

    return 0;
}