#ifndef COMMON_H
#define COMMON_H

#define FPS 30
#define EPS 0.0001

// for bpm
#define SIZE_BPM 150
#define HALF_SIZE_BPM 75

#define SIZE_BPM_ZEROPAD 1000 
#define HALF_SIZE_BPM_ZEROPAD 500
#define BPM_ZEROPAD_WAVE_TABLE 2015

// for hrv
#define MAX_SIZE 4096 
#define HALF_MAX_SIZE 2048
#define WAVE_TABLE 8207

double std(double* in, int size, int ddof);

// for debug
void check_arr_double(double* input, int len);
void check_arr_int(int* input, int len);

#endif  /* COMMON_H */ 