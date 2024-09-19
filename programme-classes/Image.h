//
// Created by sakhd on 17.09.2024.
//

#ifndef EFFECTIVEMOBILE_IMAGE_H
#define EFFECTIVEMOBILE_IMAGE_H

#include <iostream>

///Интерфейс от которого будет имплементироваться наш класс ImageBMP, ну и остальные в дальнейшей разработке
class Image {
public:
    virtual void open(const std::string &fileName) = 0;

    virtual void display() = 0;

    virtual void close() = 0;

    virtual ~Image() = default;

};


#endif //EFFECTIVEMOBILE_IMAGE_H
