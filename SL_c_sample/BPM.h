#ifndef BPM_H
#define BPM_H
/*
"""
CHROM method on CPU using Numpy.
De Haan, G., & Jeanne, V. (2013).Robust pulse rate from chrominance - based rPPG.
IEEE Transactions on Biomedical Engineering, 60(10), 2878 - 2886.
"""
*/
int get_bpm_rgb(double* r, double* g, double* b);

/* 적외선용
    """
        GREEN method on CPU using Numpy
        Verkruysse, W., Svaasand, L.O., & Nelson, J.S. (2008).Remote plethysmographic imaging using ambient light.Optics express, 16(26), 21434 - 21445.
        """
     */
int get_bpm_single_channel(double* signal);

//int get_heartrate(double* freqs, double* amps, int n);

// for test
void cpu_CHROM(double* r, double* g, double* b, double* output);
void detrend_1d(double* signal, double* output);

#endif  /* BPM_H */ 