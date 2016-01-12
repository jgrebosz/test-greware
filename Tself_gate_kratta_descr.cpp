/***************************************************************************
                          Tself_gate_kratta_descr.cpp  -  description
                             -------------------
    begin                : Mon Sep 8 2003
    copyright            : (C) 2003 by dr. Jerzy Grebosz, IFJ Krakow, Poland
    email                : jerzy.grebosz@ifj.edu.pl
 ***************************************************************************/

#include "Tself_gate_kratta_descr.h"
#include "Tfile_helper.h"
#include <iostream>

#define fif(x,y) Nfile_helper::find_in_file((x),(y))

//********************************************************************
Tself_gate_kratta_descr::Tself_gate_kratta_descr()
{

    sg_type =  Tselfgate_type::kratta ; // this is kratta

    enable_pd0_cal_gate = false ;
    pd0_cal_gate[0] = 0 ;
    pd0_cal_gate[1] = 4000;

    enable_pd1_cal_gate = false ;
    pd1_cal_gate[0] = 0 ;
    pd1_cal_gate[1] = 4000;

    enable_pd2_cal_gate = false ;
    pd2_cal_gate[0] = 0 ;
    pd2_cal_gate[1] = 4000;

    enable_pd0_time_cal_gate = false ;
    pd0_time_cal_gate[0] = 0 ;
    pd0_time_cal_gate[1] = 4000;

    enable_pd1_time_cal_gate = false ;
    pd1_time_cal_gate[0] = 0 ;
    pd1_time_cal_gate[1] = 4000;

    enable_pd2_time_cal_gate = false ;
    pd2_time_cal_gate[0] = 0 ;
    pd2_time_cal_gate[1] = 4000;


    //---------------    ????????????? degrees
    enable_geom_theta_gate = false ;
    geom_theta_gate[0] = 0;
    geom_theta_gate[1] = 360;

    enable_geom_phi_gate = false ;
    geom_phi_gate[0] = 0;
    geom_phi_gate[1] = 360;

    // gamma - particle angle    Radians !!!!!!!!!!!!!
    enable_gp_theta_gate = false ;
    gp_theta_gate[0] = 0;
    gp_theta_gate[1] = 6.28;

    enable_gp_phi_gate = false ;
    gp_phi_gate[0] = 0;
    gp_phi_gate[1] = 6.28;


}
//**********************************************************************

//*********************************************************************
void Tself_gate_kratta_descr::read_definition_from(string pathed_name)
{


    string file_name = pathed_name ;
    // path.user_def_spectra + name_of_spectrum + ".self_gate_kratta_crystal" ;
    ifstream plik(file_name.c_str());
    if(!plik)
    {
        throw runtime_error( " Can't open the file "  + file_name +  " for reading selfgate");
    }

    try
    {
        // I decided not to read this. It is already fixed
        // any errors will be automaticly fixed here

        // Tfile_helper::spot_in_file(plik, "type_of_self_gate") ;
        // plik >> sg_type;


        Nfile_helper::spot_in_file(plik, "name");
        plik >> name;   // will be without the path and extension

        //SPY NEEDS the extension to recognize the title
        //    unsigned int i = name.find( ".self_gate_kratta_crystal"); // != string::npos)
        //    if(i == string::npos)
        //    {
        //      name += ".self_gate_kratta_crystal" ;
        //    }

        enable_pd0_cal_gate = (bool) Nfile_helper::find_in_file(plik, "enable_pd0_cal_gate");
        pd0_cal_gate[0] = fif(plik, "pd0_cal_gate_low");
        pd0_cal_gate[1] = fif(plik, "pd0_cal_gate_high");

        enable_pd1_cal_gate = (bool) Nfile_helper::find_in_file(plik, "enable_pd1_cal_gate");
        pd1_cal_gate[0] = fif(plik, "pd1_cal_gate_low");
        pd1_cal_gate[1] = fif(plik, "pd1_cal_gate_high");

        enable_pd2_cal_gate = (bool) Nfile_helper::find_in_file(plik, "enable_pd2_cal_gate");
        pd2_cal_gate[0] = fif(plik, "pd2_cal_gate_low");
        pd2_cal_gate[1] = fif(plik, "pd2_cal_gate_high");

       // times

        enable_pd0_time_cal_gate = (bool) Nfile_helper::find_in_file(plik, "enable_pd0_time_cal_gate");
        pd0_time_cal_gate[0] = fif(plik, "pd0_time_cal_gate_low");
        pd0_time_cal_gate[1] = fif(plik, "pd0_time_cal_gate_high");

        enable_pd1_time_cal_gate = (bool) Nfile_helper::find_in_file(plik, "enable_pd1_time_cal_gate");
        pd1_time_cal_gate[0] = fif(plik, "pd1_time_cal_gate_low");
        pd1_time_cal_gate[1] = fif(plik, "pd1_time_cal_gate_high");

        enable_pd2_time_cal_gate = (bool) Nfile_helper::find_in_file(plik, "enable_pd2_time_cal_gate");
        pd2_time_cal_gate[0] = fif(plik, "pd2_time_cal_gate_low");
        pd2_time_cal_gate[1] = fif(plik, "pd2_time_cal_gate_high");



        //---------------
        enable_geom_theta_gate = (bool) fif(plik, "enable_geom_theta_gate");

        geom_theta_gate[0] = fif(plik, "geom_theta_gate_low");
        geom_theta_gate[1] = fif(plik, "geom_theta_gate_high");


        enable_geom_phi_gate = (bool) fif(plik, "enable_geom_phi_gate");

        geom_phi_gate[0] = fif(plik, "geom_phi_gate_low");
        geom_phi_gate[1] = fif(plik, "geom_phi_gate_high");

        //---------------
        enable_gp_theta_gate = (bool) fif(plik, "enable_gp_theta_gate");

        gp_theta_gate[0] = fif(plik, "gp_theta_gate_low");
        gp_theta_gate[1] = fif(plik, "gp_theta_gate_high");


        enable_gp_phi_gate = (bool) fif(plik, "enable_gp_phi_gate");

        gp_phi_gate[0] = fif(plik, "gp_phi_gate_low");
        gp_phi_gate[1] = fif(plik, "gp_phi_gate_high");

        //------------

    }
    catch(Tfile_helper_exception &m)
    {
        cout << "Error during reading the file "
             << file_name << " : "
             << m.message << endl;
    }
}
//*************************************************************************
void Tself_gate_kratta_descr::write_definitions(string path_only)
{
    string file_name = path_only + name;

    //  if(file_name.find(".self_gate_kratta_crystal") == string::npos)
    //  {
    //    file_name += ".self_gate_kratta_crystal" ;
    //  }

    ofstream plik(file_name.c_str());
    if(!plik)
    {
        cout << "Can't open the file " <<file_name
             << " for writing " << endl;
        return ;
    }

    plik
            << "// This is a definiton of the 'self_gate' for germanium crystal\n"
            << "// comments are marked using two slashes: // comment \n\n"
            << "\n//-----------------------------------------------------\n\n"

            << "type_of_self_gate\t\t" << sg_type << "\t\t// 1= Ger crystal, 2= Hec BaF\n"
            << "name\t\t " << name
               //<< ".self_gate_kratta_crystal"
            << "\n\n"


            << "enable_pd0_cal_gate\t\t" << enable_pd0_cal_gate
            << "\tpd0_cal_gate_low\t"  << pd0_cal_gate[0]
            << "\tpd0_cal_gate_high\t" << pd0_cal_gate[1] << "\n"

            << "enable_pd1_cal_gate\t\t" << enable_pd1_cal_gate
            << "\tpd1_cal_gate_low\t"  << pd1_cal_gate[0]
            << "\tpd1_cal_gate_high\t" << pd1_cal_gate[1] << "\n"

            << "enable_pd2_cal_gate\t\t" << enable_pd2_cal_gate
            << "\tpd2_cal_gate_low\t"  << pd2_cal_gate[0]
            << "\tpd2_cal_gate_high\t" << pd2_cal_gate[1] << "\n"


            << "enable_pd0_time_cal_gate\t\t" << enable_pd0_time_cal_gate
            << "\tpd0_time_cal_gate_low\t"  << pd0_time_cal_gate[0]
            << "\tpd0_time_cal_gate_high\t" << pd0_time_cal_gate[1] << "\n"

            << "enable_pd1_time_cal_gate\t\t" << enable_pd1_time_cal_gate
            << "\tpd1_time_cal_gate_low\t"  << pd1_time_cal_gate[0]
            << "\tpd1_time_cal_gate_high\t" << pd1_time_cal_gate[1] << "\n"

            << "enable_pd2_time_cal_gate\t\t" << enable_pd2_time_cal_gate
            << "\tpd2_time_cal_gate_low\t"  << pd2_time_cal_gate[0]
            << "\tpd2_time_cal_gate_high\t" << pd2_time_cal_gate[1] << "\n"


               //--------------
            << "enable_geom_theta_gate\t\t" << enable_geom_theta_gate
            << "\tgeom_theta_gate_low\t"  << geom_theta_gate[0]
            << "\tgeom_theta_gate_high\t" << geom_theta_gate[1] << "\t// geom_theta gate\n"

            << "enable_geom_phi_gate\t\t" << enable_geom_phi_gate
            << "\tgeom_phi_gate_low\t"  << geom_phi_gate[0]
            << "\tgeom_phi_gate_high\t" << geom_phi_gate[1] << "\t// geom_phi gate\n"

               //--------------
            << "enable_gp_theta_gate\t\t" << enable_gp_theta_gate
            << "\tgp_theta_gate_low\t"  << gp_theta_gate[0]
            << "\tgp_theta_gate_high\t" << gp_theta_gate[1] << "\t// gamma - scattered particle\n"

            << "enable_gp_phi_gate\t\t" << enable_gp_phi_gate
            << "\tgp_phi_gate_low\t"  << gp_phi_gate[0]
            << "\tgp_phi_gate_high\t" << gp_phi_gate[1] << "\t// gamma - scattered particle\n"




            << "\n//-----------------------------------------------------\n\n"

            << endl;


}
//*********************************************************************


