#ifndef HRV_ANALYSIS_H
#define HRV_ANALYSIS_H

typedef struct {
	double mean_nni;
    double sdnn;
    double sdsd;
    double nni_50;
    double  pnni_50;
    double  nni_20;
    double  pnni_20;
    double  rmssd;
    double  median_nni;
    double range_nni;
    double  cvsd;
    double  cvnni;
    double  mean_hr;
    double  max_hr;
    double min_hr;
    double std_hr;
}TimeFeatures;

typedef struct {
    double vlf;
    double lf;
    double hf;
    double lf_hf_ratio;
    double lf_normed;
    double hf_normed;
    double  total_power;
}FreqFeatures;

typedef struct {
	TimeFeatures timeFeatures;
	FreqFeatures freqFeatures;
}HRVFeatures;

typedef struct {
    double low;
    double high;
}BAND;

void hrv_use_bpm(int* bpms, int bpmsLength, HRVFeatures* hrvFeatures);
//void hrv_use_bpm(int* bpms, int bpmsLength);

#endif  /* HRV_ANALYSIS_H */ 