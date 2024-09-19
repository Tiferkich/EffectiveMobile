//
// Created by sakhd on 17.09.2024.
//

#ifndef EFFECTIVEMOBILE_IMAGEBMP_H
#define EFFECTIVEMOBILE_IMAGEBMP_H

#include "Image.h"
#include <windows.h>

///Класс обрабатывающий картинку с расширением BMP
class ImageBMP : public Image {
private:
    unsigned char *data; ///< Место хранения пикселей
    ///fileHeader и infoHeader хранят информацию о картинке
    BITMAPFILEHEADER fileHeader{};
    BITMAPINFOHEADER infoHeader{};
public:
    ImageBMP() {
        data = nullptr;
    }

    ///Метод считывающий картинку по названию файла, на винде лучше указывать полный путь
    void open(const std::string &fileName) override;

    ///Отрисовывает картинку символами "#" если цвет полностью черный, " " если цвет белый
    /// и "?" если какой то другой цвет.
    void display() override;

    ///Метод освобождения памяти
    void close() override;

    ///Деструктор
    ~ImageBMP() override {
        delete[] data;
        data = nullptr;
    }


};


#endif //EFFECTIVEMOBILE_IMAGEBMP_H
