#include <iostream>
#include <fstream>
#include <stdexcept>
#include "ImageBMP.h"

void ImageBMP::open(const std::string &fileName) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file");
    }

    file.read(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char *>(&infoHeader), sizeof(infoHeader));

    if (fileHeader.bfType != 0x4D42) {
        throw std::runtime_error("Not a BMP file");
    }

    if (infoHeader.biBitCount != 24 && infoHeader.biBitCount != 32) {
        throw std::runtime_error("Unsupported bit count");
    }

    const int bytesPerPixel = infoHeader.biBitCount / 8;
    const int rowStride = (infoHeader.biWidth * bytesPerPixel + 3) & ~3;

    size_t dataSize = infoHeader.biWidth * infoHeader.biHeight * bytesPerPixel;
    data = new unsigned char[dataSize];

    unsigned char *rowData = new unsigned char[rowStride];
    file.seekg(fileHeader.bfOffBits, std::ios::beg);
    /// Так как BMP формат выравнивает ширину, чтобы она была кратна 4, пришлось считать картинку с учетом этого
    for (int y = 0; y < infoHeader.biHeight; ++y) {
        file.read(reinterpret_cast<char *>(rowData), rowStride);
        for (int x = 0; x < infoHeader.biWidth; ++x) {
            for (int c = 0; c < bytesPerPixel; ++c) {
                data[(y * infoHeader.biWidth + x) * bytesPerPixel + c] = rowData[x * bytesPerPixel + c];
            }
        }
    }

    delete[] rowData;
}


void ImageBMP::display() {
    if (!data) {
        throw std::runtime_error("No data to display");
    }

    int width = infoHeader.biWidth;
    int height = infoHeader.biHeight;
    int bytesPerPixel = infoHeader.biBitCount / 8;

    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            size_t index = (y * width + x) * bytesPerPixel;

            unsigned char b = data[index];
            unsigned char g = data[index + 1];
            unsigned char r = data[index + 2];
            if (r == 255 && g == 255 && b == 255) {
                std::cout << ' ';
            } else if (r == 0 && g == 0 && b == 0) {
                std::cout << "#";
            } else {
                std::cout << '?';
            }
        }
        std::cout << std::endl;
    }
}

void ImageBMP::close() {
    delete[] data;
    data = nullptr;
}
