#ifndef FT_H
#define FT_H

#include "Vec.h"

#include <iostream>
#include <cmath>
#include <iomanip>

#define PI 3.141592653589793238

typedef Vector<double> Vd;

template <typename _FTp>
class DiscreteFourierTransform: public Vector<_FTp>, public Matrix<_FTp> {
public:
    DiscreteFourierTransform(int fs): signal_Len(fs), Vector<_FTp>(fs) {};

    std::pair<Vd, Vd> compute_dft1d(int n_pts);
    Vd compute_idft1d(std::pair<Vd, Vd> &spe, int n_pts);

private:
    int signal_Len; 
};


template <typename _FTp>
std::pair<Vd, Vd> DiscreteFourierTransform<_FTp>::compute_dft1d(int n_pts) {
    
    Vd Xrl(n_pts);
    Vd Xim(n_pts);

    Vector<_FTp> Xs(n_pts);

    Xs.RandomV();
    Xs.PrintVec();

    /* for (int i = 0; i < n_pts; i++) {
        std::cout << "Input Point: ";
        std::cin >> Xs.v_Vec[i];
    } */

    int N;
    std::cout << "Sampling how many pts: ";
    std::cin >> N;

    std::cout << std::setprecision(6) << std::fixed;
    for (int i = 0; i < N; i++) {
        Xrl.v_Vec[i] = 0.0;
        Xim.v_Vec[i] = 0.0;
        for (int j = 0; j < n_pts; j++) {
            Xrl.v_Vec[i] = (Xrl.v_Vec[i] + Xs.v_Vec[j] * std::cos((2*PI*i*j)/N));
            Xim.v_Vec[i] = (Xim.v_Vec[i] + Xs.v_Vec[j] * std::sin((2*PI*i*j)/N));
            
        }
        std::cout << Xrl.v_Vec[i] << " + j" << Xim.v_Vec[i] << "\n";
    }

    return std::make_pair(Xrl, Xim);
}


template <typename _FTp>
Vd DiscreteFourierTransform<_FTp>::compute_idft1d(std::pair<Vd, Vd> &spe, int n_pts) {

    Vd Xrl_inv(n_pts);
    Vd Xim_inv(n_pts);

    Vector<_FTp> Xs_inv(n_pts);

    const int Points = spe.first.Size;
    for (int i = 0; i < Points; i++) {
        Xrl_inv.v_Vec[i] = spe.first.v_Vec[i];
        Xim_inv.v_Vec[i] = spe.second.v_Vec[i];
    }

    // Xrl_inv.PrintVec();
    // Xim_inv.PrintVec();

    int N;
    std::cout << "Sampling how many pts: ";
    std::cin >> N;

    for (int i = 0; i < N; i++) {
        Xs_inv.v_Vec[i] = 0.0;
        for (int j = 0; j < N; j++) {
            Xs_inv.v_Vec[i] = Xs_inv.v_Vec[i] + (Xrl_inv.v_Vec[j] * std::cos((2*PI*i*j)/N)) + (Xim_inv.v_Vec[j] * std::sin((2*PI*i*j)/N));
        }
        Xs_inv.v_Vec[i] /= N;
    }
    return Xs_inv;
}


#endif