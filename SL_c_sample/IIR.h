/**
 *  @file IIR.h
 *
 *  @copyright Copyright (c) 2023 Pattern Recognition Lab where Sangmyung Univ all rights reserved.
 *
 *  @details inline function definitions
 *
 */

#ifndef IIR_H
#define IIR_H

void IIR_Bandpass(const double* pSignal, double* pBandpassSignal, int Length, int fs);

#endif  /* IIR_H */ 