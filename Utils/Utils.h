#ifndef UTILS_H
#define UTILS_H

struct Color {
    int r;
    int g;
    int b;
    int a;

    Color() : r(0), g(0), b(0), a(255) {}
    
    Color(int red, int green, int blue, int alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}
};

int random_num();
void random_initialize();


#endif 

