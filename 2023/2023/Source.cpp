#include <iostream>
#include "CubeConundrum.h"

int main(int argc, char** argv) {
    CubeConundrum cc{ "CubeConundrum.txt" };
    std::cout << cc.sumGameIds();
    std::cout << std::endl;
    return 0;
}