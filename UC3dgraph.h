//
//******************************************************************************
//                              UC3DGRAPH.H
//******************************************************************************
// 
//                  HEADER FILE FOR CLASS UC3dgraph      
//
//********************************************************************************
//
//            Initial Version             : David Sansot
//            Additions and Modifications : Chris Anderson 
//
//                            (C) UCLA 1994, 1995
//********************************************************************************
//
#include <cmath>

#include "UCgraph.h"

#ifndef UC3DGARPH_
#define UC3DGARPH_

class UC3dgraph : public UCgraph
{
public:
//
//  Constructors
//           
    UC3dgraph(UCdriver *d) : UCgraph(d)
    { VPx = -231; VPy = 320; VPz = 200; Fx = 20; Fy  = 20; Fz  = 0; 
       scale_factor = 1; xoffset = 0; yoffset = 0;};
       
    UC3dgraph(UCdriver *d, double *vp, double *f) : UCgraph(d)
    { set_view_point(vp); set_focus(f); scale_factor = 1;
      xoffset = yoffset = 0; };
//
//
//
    void map_coordinates(double Px, double Py, double Pz,double &xp, double &yp); 
                       
    void scale_and_translate(double &x, double &y);

    void set_view_point(double x, double y, double z)
         { VPx = x; VPy = y; VPz = z;};
    void set_view_point(double *vp)
         { VPx = vp[0]; VPy = vp[1]; VPz = vp[2];};

    void get_view_point(double &x, double &y, double &z)
         { x = VPx; y = VPy; z = VPz;} ;
    void get_view_point(double *vp)
         { vp[0] = VPx; vp[1] = VPy; vp[2] = VPz;};

    void set_focus(double x, double y, double z)
         { Fx = x; Fy = y; Fz = z;};
    void set_focus(double *f)
         { Fx = f[0]; Fy = f[1]; Fz = f[2];};

    void get_focus(double &x, double &y, double &z)
         { x = Fx; y = Fy; z = Fz;};
    void get_focus(double *f)
         { f[0] = Fz; f[1] = Fy; f[2] = Fz;};

    void set_scale_factor(double sf) { scale_factor = sf;};
    void set_xoffset(double xo) { xoffset = xo;};
    void set_yoffset(double yo) { yoffset = yo;};

    double get_scale_factor() { return scale_factor;};
    double get_xoffset() { return xoffset;};
    double get_yoffset() { return yoffset;};

protected:
//
//  Internal Data
//
//  Mapping information   

    double VPx;       // View point
    double VPy;
    double VPz;

    double Fx;        // Focus point
    double Fy;
    double Fz;

    double D;         // Distance to view plane.  For our purposes, the
                      // distance between Vp and F.

    double trans_matrix[16];  // Transformation matrix
//
//  Scaling and offsetting information.  Used so that plots can
//    be centered and made to fill the frame.
//
    double scale_factor;
    double xoffset;
    double yoffset;
//
//  Internal Helper functions  
//
    void matmult(double *trans, double *m);
    void idmat(double *m);
    void set_up_transformation();
};
#endif

 
