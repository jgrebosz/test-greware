#ifndef TFILE_LINE_DET_CAL_LOOKUP_H
#define TFILE_LINE_DET_CAL_LOOKUP_H

#include <vector>
#include <string>
///////////////////////////////////////////////////////////////
struct  Tfile_line_det_cal_lookup
{
    std::string channel;
    bool enable;
    std::string name_of_detector;
    double compton_thresh;
    double theta;
    double phi;
    int cal_order;
    std::vector<double> calib_factors;
} ;

#endif // TFILE_LINE_DET_CAL_LOOKUP_H
