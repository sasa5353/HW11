#include <iostream>
#include "rungeKuttas.h"

int main(int argc, char *argv[]) {
    std::srand(time(NULL));
    int variant = -1;
    if (argv[1]) {
        std::stringstream convert(argv[1]);
        convert >> variant;
    } else {
        std::cout << "Please, enter some number between 0 and 2." << std::endl;
    }
    
    switch (variant) {
        case 0 : {
            leftShoot("left.dat");
            break;
        }
        case 1 : {
            rightShoot("right.dat");
            break;
        }
        case 2 : {
            grid("grid.dat");
            break;
        }
        default : {
            std::cout << "Wrong argument! 0 - leftShoot, 1 - rightShoot, 2 - Grid.";
        }
    }
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    return 0;
}
