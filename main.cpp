#include <iostream>

#include "programme-classes/ImageBMP.h"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "Usage : ./EffectiveMobile <path_to_bmp_file>" << std::endl;
        return 1;
    }
    try {
        Image *image = new ImageBMP();
        image->open(argv[1]);
        image->display();
        image->close();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
