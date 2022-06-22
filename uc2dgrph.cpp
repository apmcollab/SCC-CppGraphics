//
//******************************************************************************
//                              UC2dgrph.cpp
//******************************************************************************
// 
//            SOURCE FILE FOR CLASS UC2dgraph
//
//********************************************************************************
//
//            David Sansot             (C) UCLA 1994,1995
//********************************************************************************
//
#include <cmath>
#include <iostream>
#include "uc2dgrph.h"
//
//******************************************************************************
//                          NORMALIZE_X
//******************************************************************************
//
double UC2dgraph::normalize_x(double x)
{
  if (x_scale_type == LOG)
  {
	if (xmin <= 0 || x <= 0)
    {
      std::cerr << "UC2dgraph::normalize_x -\n";
      std::cerr << "Can't take log of negative number - Returning\n";
      return 0;
    }

	double log_xmin = log(xmin);
    return ((log(x) - log_xmin)/(log(xmax) - log_xmin));
  }
  else
    return ((x - xmin)/(xmax - xmin));
}
//
//******************************************************************************
//                          NORMALIZE_Y
//******************************************************************************
//
double UC2dgraph::normalize_y(double y)
{
  if (y_scale_type == LOG)
  {
	if (ymin <= 0.0 || y <= 0)
    {
      std::cerr << "UC2dgraph::normalize_y -\n";
      std::cerr << "Can't take log of negative number - Returning\n";
      return 0;
    }

	double log_ymin = log(ymin);
	return ((log(y) - log_ymin)/(log(ymax) - log_ymin));
  }
  else
    return ((y - ymin)/(ymax - ymin));
} 
