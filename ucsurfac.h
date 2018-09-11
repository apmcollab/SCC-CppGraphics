//
//******************************************************************************
//                              UCSURFAC.H
//******************************************************************************
// 
//                  HEADER FILE FOR CLASS UCsurface            
//
//********************************************************************************
//
//            Initial Version             : David Sansot
//            Additions and Modifications : Chris Anderson 
//
//                            (C) UCLA 1994,1995
//********************************************************************************
// 
#ifndef _UCSURFACE_
#define _UCSURFACE_

#include "uc3dgrph.h"
#include "camgraphimpexp.h"

class UCsurface : public UC3dgraph
{
public:
//
//  Constructors
//  
    UCsurface(const UCsurface& A); 
//
    UCsurface(UCdriver *d);
// 
//  Destructor
//
    ~UCsurface()
    { if(color_zones != 0) delete [] color_zones; 
      if(colors      != 0) delete [] colors;};
//
//  Surface Plot Routines
//  
    void show(){surface();};
    void surface();
    void surface(double* A, long r, long c);
    void surface(double* A, long r, long c, double *x, double *y);
    void surface(double (*data)(long,long), long r, long c, double *x, double *y);              
//  
    void turn_on_Fortran_array_flag()
    { Fortran_array_flag = 1; }
    void turn_off_Fortran_array_flag()
    { Fortran_array_flag = 0; }
    int  get_Fortran_array_flag()
    { return Fortran_array_flag;}
//
//  Useful Member Functions Which Are Inherited from UC3dgraph
//  
//  void set_view_point(double x, double y, double z)
//  void set_view_point(double *vp)
//  void get_view_point(double &x, double &y, double &z)
//  void get_view_point(double *vp)
//  void set_focus(double x, double y, double z)
//  void set_focus(double *f)
//  void get_focus(double &x, double &y, double &z)
//  void get_focus(double *f)
//  void set_scale_factor(double sf) 
//  double get_scale_factor() 
//  void set_xoffset(double xo) 
//  double get_xoffset()
//  void set_yoffset(double yo) 
//  double get_yoffset()
//
public:
//
// Internal Helper Classes
//
class vertex
{
    public:
      double x;
      double y;
      double z;
      double a;   // suedo-angle
      vertex *next;

      vertex() {x = y = z = a = 0; next = 0;}
      vertex(double nx, double ny, double nz, double na, vertex *n = 0)
    { x=nx; y = ny; z = nz; a = na; next = n;}

      friend int operator<(vertex& v, vertex& v2);
      friend int operator<=(vertex& v, vertex& v2);
      friend int operator==(vertex& v, vertex& v2);
};
class perimeter
{
    public:
      vertex *outer;
      vertex *inner;
      vertex *end;    // pointer to element before outer

      perimeter() { outer = inner = 0;}
      ~perimeter();

      void add_vertex_after(vertex *v, vertex *w);
      void add_segments_after(vertex *I, vertex *head, vertex *tail,
                               vertex *nx2last);
      void remove_next_vertex(vertex *v);
};
protected:
//
//  Internal Data 
//
    short Fortran_array_flag;  // If true array is in column major order
//
//  Color Data (For future color implementation)
//
    int n_colors;         // There are actually n_colors + 1 color zones
    double *color_zones;
    int *colors;
//
//  Internal Helper functions
//
    void create_surface();
    void draw_line(vertex *v, vertex *w);
    void calc_scale_factor_and_offsets();
    long is_in_array(double, double*, long);
    double suedo_angle(double x, double y);
    void initialize_perimeter(perimeter &p);
    void do_facet(long r, long c, perimeter& p);
    void get_vertex_list(long r, long c, vertex *&v, vertex *&w);
    void check_against_perimeter(vertex *f, perimeter &per, int dir);
    void set_colors(int n, double *cz, int *c)
      { n_colors = n; color_zones = cz; colors = c; }
//
//  Functions for getting data 
//
    double value(long r, long c);
    double row_value(long r);
    double col_value(long c);
//
//  Pointers to External Data : These are local "work variable" pointers.
//
//  The copy constructor and assignment operator (=) for the class
//  DO NOT copy the value of pointers nor the data associated 
//  with these pointers.  
//

    double *data_array;
    double (*data_function)(long r, long c);

    double *X;
    double *Y;
    long rows;
    long columns;
//
}; 
#endif

  
 
