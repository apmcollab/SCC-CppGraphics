//
//******************************************************************************
//                              UC2DGRAPH.H
//******************************************************************************
// 
//                  HEADER FILE FOR CLASS UC2dgraph      
//
//********************************************************************************
//
//            Initial Version             : David Sansot
//            Additions and Modifications : Chris Anderson 
//
//                            (C) UCLA 1994, 1995
//********************************************************************************
//
#include "ucgraph.h"

#ifndef UC2DGRAPH_
#define UC2DGRAPH_


class UC2dgraph : public UCgraph
{
public:
//
//  Constructors

    UC2dgraph(UCdriver *d) : UCgraph(d)
    { set_range(0,1,0,1); set_x_scale_type(LIN); set_y_scale_type(LIN);}
//
//  Range Manipulation
//
    void set_x_range(double x1, double x2)
         { if (x1 < x2) {xmin = x1; xmax = x2;} }
    void set_y_range(double y1, double y2)
         { if (y1 < y2) {ymin = y1; ymax = y2;} }
    void set_range(double x1, double x2, double y1, double y2)
         { set_x_range(x1, x2); set_y_range(y1, y2); }

    void get_x_range(double &x1, double &x2)
         { x1 = xmin; x2 = xmax; }
    void get_y_range(double &y1, double &y2)
         { y1 = ymin; y2 = ymax; }
    void get_range(double &x1, double &x2, double &y1, double &y2)
         { get_x_range(x1, x2); get_y_range(y1, y2); }
//
// Scale Type Manipulation
//
    void set_x_scale_type(int s) { x_scale_type = s;}
    void set_y_scale_type(int s) { y_scale_type = s;}

    int get_x_scale_type() {return int(x_scale_type);}
    int get_y_scale_type() {return int(y_scale_type);}
//
//  Class Enumerated types 
//
    enum {LIN, LOG};
//
protected:
//
//  Internal Data 
//
//  Range of the plot :  xmin corresponds to frame_l and xmax
//  corresponds to frame_r.  Likewise for ymin and ymax. 
//
    double xmin;
    double xmax;
    double ymin;
    double ymax;
//
//  Scale type - Determines what mapping to use.
//
    char x_scale_type;
    char y_scale_type;

    double normalize_x(double x);
    double normalize_y(double y);
};

#endif
 
