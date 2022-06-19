#include "crm_lpf2.h"

static const float C = 0.000001f;
static const float C_6 = C;
static const float lp_filter2__extra__0 = (2.f * 3.141592653589793f);
static const float bR2 = 0.f;
static const float al_7 = bR2;
static const float C_4 = C;
static const float al_9 = bR2;


void lp_filter2::reset()
{
    firstRun = 1;
}

void lp_filter2::setSampleRate(float sampleRate)
{
    fs = sampleRate;
    Rr_7 = (0.5f / (C_6 * fs));
    Rr_8 = (0.5f / (C_4 * fs));
    Gr_8 = (1.f / Rr_8);

}

void lp_filter2::process(float *x, float *y__out__, int nSamples)
{
    if (firstRun) {
        cutoff_CHANGED = 1;
    }
    else {
        cutoff_CHANGED = cutoff != cutoff_z1;
    }

    if (cutoff_CHANGED) {
        static const float R = (1.f / ((lp_filter2__extra__0 * ((0.1f + (0.3f * cutoff)) * fs)) * C));
        static const float Rl_7 = R;
        lp_filter2__extra__1 = (Rr_7 / (Rl_7 + Rr_7));
        static const float Rl_8 = (Rl_7 + Rr_7);
        static const float Gl_8 = (1.f / Rl_8);
        static const float R0_8 = ((Rl_8 * Rr_8) / (Rl_8 + Rr_8));
        dl_8 = ((2.f * Gl_8) / (((1.f / R0_8) + Gl_8) + Gr_8));
        lp_filter2__extra__2 = (dl_8 - 1.f);
        dr_8 = (1.f - dl_8);
        static const float Rr_9 = R0_8;
        lp_filter2__extra__3 = (Rr_9 / (R + Rr_9));
        lp_filter2__extra__5 = (dr_8 - 1.f);
    }

    cutoff_CHANGED = 0;

    if (firstRun) {

        __delayed__4 = 0.f;
        __delayed__6 = 0.f;
    }

    for (int i = 0; i < nSamples; i++) {

        const float bC2 = __delayed__4;
        const float ar_7 = bC2;
        const float al_8 = -((al_7 + ar_7));
        const float bC1 = __delayed__6;
        const float ar_8 = bC1;
        const float ar_9 = ((dl_8 * al_8) + (dr_8 * ar_8));
        const float au_8 = (ar_9 - (lp_filter2__extra__3 * ((al_9 + ar_9) + bC1)));
        const float aC2 = (ar_7 - (lp_filter2__extra__1 * ((al_7 + ar_7) + (((lp_filter2__extra__2 * al_8) + (dr_8 * ar_8)) + au_8))));
        const float y = (0.5f * (aC2 + bC2));

        __delayed__4 = aC2;
        __delayed__6 = (((dl_8 * al_8) + (lp_filter2__extra__5 * ar_8)) + au_8);


        y__out__[i] = y;
    }


    cutoff_z1 = cutoff;
    firstRun = 0;
}


float lp_filter2::getcutoff() {
    return cutoff;
}
void lp_filter2::setcutoff(float value) {
    cutoff = value;
}
