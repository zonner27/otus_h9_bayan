#include <iostream>

int main()
{
    try {
        std::cout << "boost" <<std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}








