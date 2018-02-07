/***************************************************************************
                          Tpinup.cpp  -  description
                             -------------------
    begin                : Tue Aug 5 2003
    copyright            : (C) 2003 by dr. Jerzy Grebosz, IFJ Krakow, Poland
    email                : jerzy.grebosz@ifj.edu.pl
 ***************************************************************************/
 
#include "Tpinup.h"
#include "swiat.h"
#include <qpainter.h>
#include <math.h>

//****************************************************************
void Tpinup::draw(swiatek * world, QPainter * pior, bool log_scale)
{
  double vert =  world->wy(log_scale ? log10(y) : y ) ;
  string ekran = info + "\0" ;
  pior->drawText(world->wx(x), (int) vert, info.c_str() );  
}
//****************************************************************
