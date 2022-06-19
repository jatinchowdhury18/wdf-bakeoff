#pragma once

class lp_filter2
{
public:
    void setSampleRate(float sampleRate);
    void reset();
    void process(float *x, float *y__out__, int nSamples);

    float getcutoff();
    void setcutoff(float value);

private:


    float Rr_7;
    float lp_filter2__extra__1;
    float Rr_8;
    float Gr_8;
    float dl_8;
    float lp_filter2__extra__2;
    float dr_8;
    float lp_filter2__extra__3;
    float __delayed__4;
    float lp_filter2__extra__5;
    float __delayed__6;


    float cutoff = 0;


    float cutoff_z1;
    char cutoff_CHANGED;


    float fs;
    char firstRun;

};
