#ifndef TFILE_LINE_DET_CAL_LOOKUP_H
#define TFILE_LINE_DET_CAL_LOOKUP_H

#include <vector>
///////////////////////////////////////////////////////////////
struct  Tfile_line_det_cal_lookup
{
    string channel;
    bool enable;
    string name_of_detector;
    double compton_thresh;
    double theta;
    double phi;
    int cal_order;
    std::vector<double> calib_factors;
} ;

#endif // TFILE_LINE_DET_CAL_LOOKUP_H
