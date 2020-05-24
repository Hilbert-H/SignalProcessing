//
//  main.cpp
//  clockexample
//
//  Created by Hilbert_H on 2020/5/24.
//  Copyright © 2020 Crush-zh. All rights reserved.
//

#include <iostream>
#include <cmath>

const double PI = acos(-1);

struct Complex {
    double r, i;
    Complex() {r = 0; i = 0;}
    Complex(double real, double imag): r(real), i(imag) {}
};
Complex operator + (Complex a, Complex b) { return Complex(a.r + b.r, a.i + b.i);}
Complex operator - (Complex a, Complex b) { return Complex(a.r - b.r, a.i - b.i);}
Complex operator * (Complex a, Complex b) { return Complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);}

void FFT(Complex* a, int lim){
    if (lim == 1) return;
    Complex a0[lim / 2], a1[lim / 2];
    for (int i = 0; i < lim; i += 2){
        a0[i / 2] = a[i];
        a1[i / 2] = a[i + 1];
    }
    FFT(a0, lim / 2);
    FFT(a1, lim / 2);
    Complex wn = Complex(cos(2.0 * PI / lim), sin(2.0 * PI /lim));
    Complex w = Complex(1, 0);
    
    for (int  k = 0; k < (lim >> 1); ++k){
        a[k] = a0[k] + w * a1[k];
        a[k + (lim / 2)] = a0[k] - w * a1[k];
        w = w * wn;
    }
        
    
}

void ComplexShow(Complex* a, int lim){
    for (int k = 0; k < lim; k++){
        std::cout << a[k].r;
        (a[k].i > 0) ? std::cout << " + " : std::cout << " - ";
        std::cout << abs(a[k].i) << "I" << std::endl;
    }
}

int main(){
    Complex a[4] = {{-1, 0}, {1, 0}, {-2, 0}, {2, 0}};
    FFT(a, 4);
    ComplexShow(a, 4);
}
