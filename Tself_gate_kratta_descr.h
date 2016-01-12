/***************************************************************************
                          Tself_gate_hec_descr.h  -  description
                             -------------------
    begin                : Mon Sep 8 2003
    copyright            : (C) 2003 by dr. Jerzy Grebosz, IFJ Krakow, Poland
    email                : jerzy.grebosz@ifj.edu.pl
***************************************************************************/


#ifndef TSELF_GATE_KRATTA_DESCR_H
#define TSELF_GATE_KRATTA_DESCR_H

#include <string>
using namespace std;

#include "Tself_gate_abstract_descr.h"


/**Text file which describes the gate on kratta crystal
  *@author dr. Jerzy Grebosz, IFJ Krakow, Poland
  */
//////////////////////////////////////////////////////////////////////////
class Tself_gate_kratta_descr : public Tself_gate_abstract_descr
{
public:

  bool enable_pd0_cal_gate ;
  double pd0_cal_gate[2];

  bool enable_pd1_cal_gate ;
  double pd1_cal_gate[2];

  bool enable_pd2_cal_gate ;
  double pd2_cal_gate[2];


  bool enable_pd0_time_cal_gate ;
  double pd0_time_cal_gate[2];

  bool enable_pd1_time_cal_gate ;
  double pd1_time_cal_gate[2];

  bool enable_pd2_time_cal_gate ;
  double pd2_time_cal_gate[2];


  //------------------
  bool enable_geom_theta_gate ;
  double geom_theta_gate[2];

  bool enable_geom_phi_gate ;
  double geom_phi_gate[2];

  // gamma - particle angle
  bool enable_gp_theta_gate ;
  double gp_theta_gate[2];

  bool enable_gp_phi_gate ;
  double gp_phi_gate[2];


  Tself_gate_kratta_descr();
  virtual ~Tself_gate_kratta_descr() {} ;
  void read_definition_from(string pathed_name);
  void write_definitions(string path_only);
};

#endif
