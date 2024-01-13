#include <iostream>
#include "CubeConundrum.h"

int main(int argc, char** argv) {
    CubeConundrum cc{ "CubeConundrum.txt" };
    std::cout << cc.sumGamePowers();
    std::cout << std::endl;
    return 0;
}