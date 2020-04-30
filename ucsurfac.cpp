//
//******************************************************************************
//                              UCSURFAC.CPP
//******************************************************************************
// 
//                   SOURCE FILE FOR CLASS UCsurface
//
//********************************************************************************
//
//            David Sansot                  (C) UCLA 1994,1995
//            Chris Anderson                (C) UCLA 1996
//********************************************************************************
//
#include "ucsurfac.h"
#include "camgraphexit.h"
#include <math.h>
// #include <stdlib.h>
#include <iostream>
using namespace std;
//
// define external flag array classes    cra 9/29/95
//
//#ifndef __BCPLUSPLUS__
//#define __MPWcplusplus
//#endif
//******************************************************************************
//                         COPY CONSTRUCTOR
//******************************************************************************
//
UCsurface::UCsurface(const UCsurface&  A) : UC3dgraph(A)
{  
//
//  Data Pointers Set To Null Instances
//
    data_array         = 0;
    data_function      = 0;

    X                  = 0;
    Y                  = 0;
    rows               = 0;
    columns            = 0;
//
    Fortran_array_flag = A.Fortran_array_flag;
//
//  Don't deal with colors for now => set to null instances
//
	n_colors           = A.n_colors;
    color_zones        = 0;
    colors             = 0;
}
//
//******************************************************************************
//                 UCsurface(UCdriver *driver)
//******************************************************************************
//
UCsurface::UCsurface(UCdriver *driver) : UC3dgraph(driver)
{
    data_array         = 0;
    data_function      = 0;

    X                  = 0;
    Y                  = 0;
    rows               = 0;
    columns            = 0;

    Fortran_array_flag = 0;

    n_colors           = 0;
    color_zones        = 0;
    colors             = 0;
}
//
//********************************************************************************
//              SURFACE PLOTTING ROUTINES FOR BASIC C DATA TYPES
//********************************************************************************
//
//
//********************************************************************************
//              SURFACE ROUTINES
//********************************************************************************
// 
void UCsurface::surface()
{  
    if((data_array == 0)&&(data_function == 0))
    {
     cerr << " Surface Plot Data or Function Unspecifed " << endl;
     CAMgraphicsExit();
    }
     
    create_surface();
}

void UCsurface::surface(double* A, long r, long c)
{  
    data_array         = A;
    data_function      = 0;

    X                  = 0;
    Y                  = 0;
    rows               = r;
    columns            = c;
 
    create_surface();
}

void UCsurface::surface(double* A, long r, long c, double *x, double *y)
{ 
    data_array         = A;
    data_function      = 0;

    X                  = x;
    Y                  = y;
    rows               = r;
    columns            = c;
 
    create_surface();
} 

void UCsurface::surface(double (*data)(long,long), long r, long c, double *x, double *y)
{ 
    data_array         = 0;
    data_function      = data;

    X                  = x;
    Y                  = y;
    rows               = r;
    columns            = c;
 
    create_surface();
}  
//
//******************************************************************************
//                      INTERNAL HELPER FUNCTIONS
//******************************************************************************
//
//******************************************************************************
//                      DRAW_LINE 
//******************************************************************************
//
void UCsurface::draw_line(vertex *v, vertex *w)
{
  //  Function draw_line calls the line drawing routine frome drv to
  //    draw a line between vertex v and w in the proper color or
  //    colors.

  if (n_colors)   //  There are color zones to worry about
  {
    short fliped = 0;
    if (w->z < v->z)    //  Switch vertices so that v->z <= w->z
    {
      vertex *m = v;
      v = w;
      w = m;
      fliped = 1;
    }

    int c = 0, count = 0, done = 0;
    double x1, y1, x2, y2, z1, f;

    x1 = v->x, y1 = v->y, z1 = v->z;

         //  Get to the right color zone
    while (count < n_colors && z1 >= color_zones[count]) count++;
         //  Get the right color
    if (count) c = colors[count-1];

    while (!done)
    {
      if (count >= n_colors || w->z <= color_zones[count])
      {
             //  The last segment
         if (fliped)
           (*drv).line(frame_2_screen_x(w->x),frame_2_screen_y(w->y),
                  frame_2_screen_x(x1),frame_2_screen_y(y1),0,0,0,c,0);
         else
           (*drv).line(frame_2_screen_x(x1),frame_2_screen_y(y1),
              frame_2_screen_x(w->x),frame_2_screen_y(w->y),0,0,0,c,0);
         done = 1;
      }
      else
      {
         f = (color_zones[count] - z1)/(w->z - z1);

         x2 = (w->x - x1)*f + x1;
         y2 = (w->y - y1)*f + y1;

        if (fliped)
           (*drv).line(frame_2_screen_x(x2),frame_2_screen_y(y2),
                 frame_2_screen_x(x1),frame_2_screen_y(y1),0,0,0,c,0);
        else
           (*drv).line(frame_2_screen_x(x1),frame_2_screen_y(y1),
                 frame_2_screen_x(x2),frame_2_screen_y(y2),0,0,0,c,0);

         x1 = x2;     //  Advance segments
         y1 = y2;
         z1 = color_zones[count];

         count++;
         c = colors[count-1];
      }
    }
  }
  else    //  No color zones
    (*drv).line(frame_2_screen_x(v->x),frame_2_screen_y(v->y),
           frame_2_screen_x(w->x),frame_2_screen_y(w->y),0,0,0,0,0);
}
//
//******************************************************************************
//                      CREATE_SURFACE 
//******************************************************************************
//
void UCsurface::create_surface()
{
  // Function surface is called to draw the surface plot.  This is the
  //   main routine for the plot.


    // This part is sort of cheating.  It put here to avoid the
    //   special case where (Vpx,VPy) lies within the grid defined by
    //   the arrays X abd Y and that either VPx = X[i] for some i or
    //   VPy == Y[j] for some j, or both.
  if (VPx >= row_value(0) && VPx <= row_value(rows-1) &&
        VPy >= col_value(0) && VPy <= col_value(columns-1))
  {
    long c;
    if ((c = is_in_array(VPx,X,rows)) != -1)
      { VPx += (row_value(c+1)-row_value(c))*0.01;
        Fx += (row_value(c+1)-row_value(c))*0.01; }

    if ((c = is_in_array(VPy,Y,columns)) != -1)
      { VPy += (col_value(c+1)-col_value(c))*0.01;
        Fy += (col_value(c+1)-col_value(c))*0.01; }
  }


  set_up_transformation();
  calc_scale_factor_and_offsets();


  vertex *v;

  perimeter p;
  initialize_perimeter(p);

    //  Draw initial perimeter
  v = p.outer;
  if (p.inner != p.outer)
    while (v != p.inner)
    {
      draw_line(v,v->next);
      v = v->next;
    }
  else
    do
    {
      draw_line(v,v->next);
      v = v->next;
    }
    while (v != p.outer);


        // Draw facets in occlusion compatible order

  long K1 = 1, L1 = 1, Kn = rows-1, Lm = columns-1;

  long i = 0;
  while (VPx >= row_value(i) && i < rows) i++;

  if (i > K1) K1 = i;
  if (i-1 < Kn) Kn = i-1;

  i = 0;
  while (VPy >= col_value(i) && i < columns) i++;

  if (i > L1) L1 = i;
  if (i-1 < Lm) Lm = i-1;

  long j;
  for (j = L1; j <= columns-1; j++)
    for (i = K1; i <= rows-1; i++)
    {
      do_facet(i-1,j-1,p);
    }
  for (j = Lm; j >= 1; j--)
    for (i = K1; i <= rows-1; i++)
    {
      do_facet(i-1,j-1,p);
    }
  for (j = L1; j <= columns-1; j++)
    for (i = Kn; i >= 1; i--)
    {
      do_facet(i-1,j-1,p);
    }
  for (j = Lm; j >= 1; j--)
    for (i = Kn; i >= 1; i--)
    {
      do_facet(i-1,j-1,p);
    }

}
//
//******************************************************************************
//                      DO_FACET
//******************************************************************************
//
void UCsurface::do_facet(long r, long c, perimeter &p)
{
  //  Function do_facet gets the proper list of vertices of the facet
  //    i,j and then checks to see if they should be drawn.

  vertex *u, *v = 0, *w = 0;

  get_vertex_list(r,c,v,w);

  check_against_perimeter(v,p,1);
  check_against_perimeter(w,p,0);

          // Clean up
  while (v != 0)
  {
    u = v;
    v = v->next;
    delete u;
  }

  while (w != 0)
  {
    u = w;
    w = w->next;
    delete u;
  }
}
//
//******************************************************************************
//                      GET_VERTEX_LIST
//******************************************************************************
//
void UCsurface::get_vertex_list(long r, long c, vertex *&v, vertex *&w)
{
  //  Function returns two list of vertices.  v points to the list
  //    that needs to be checked agains the outside of the perimeter
  //    while w points to the list to check against the inside.

  enum {FACE_ON, EDGE_ON, CORNER_ON};

  short flag;

  if (VPx >= row_value(r) && VPx <= row_value(r+1)
      && VPy >= col_value(c) && VPy <= col_value(c+1))
  {
    flag = FACE_ON;
  }
  else if ( (VPx >= row_value(r) && VPx <= row_value(r+1))
            || (VPy >= col_value(c) && VPy <= col_value(c+1)))
  {
    flag = EDGE_ON;
  }
  else
  {
    flag = CORNER_ON;
  }


  double Fx[4], Fy[4], Z[4], A[4];
  int dr, dc, i;

  switch (flag)
  {
    case FACE_ON:
    {
      dr = 1;
      dc = 0;
      break;
    }

    case EDGE_ON:
    {
      if (VPx >= row_value(r) && VPx <= row_value(r+1))
      {
         if (VPy < col_value(c))
           { dr = 1; dc = 0; }
         else
           { dr = 0; dc = 1; }
      }
      else
      {
         if (VPx < row_value(r))
           { dr = dc = 0; }
        else
           { dr = dc = 1; }
      }
      break;
    }

    case CORNER_ON:
    {
      if (VPx < row_value(r))
      {
        if (VPy < col_value(c))
           { dr = 1; dc = 0; }
        else
           { dr = dc = 0; }
      }
      else
      {
         if (VPy < col_value(c))
           { dr = dc = 1; }
        else
           { dr = 0; dc = 1; }
      }
      break;
    }
  }

  for (i = 0; i < 4; i++)
  {
    Z[i] = value(r+dr,c+dc);
    map_coordinates(row_value(r+dr),col_value(c+dc),Z[i],Fx[i],Fy[i]);
    scale_and_translate(Fx[i],Fy[i]);
    A[i] = suedo_angle(row_value(r+dr),col_value(c+dc));

    (dr == dc) ? dr = (dr+1)%2 : dc = (dc+1)%2;
  }


  double cp1, cp2, cp3;
  vertex *m;


  switch (flag)
  {
    case FACE_ON:  // this only can happen once and is taken care of
    {              //   in initialize_perimeter
      v = 0;
      w = 0;
      break;
    }

    case EDGE_ON:  // four possibilities
    {
      cp1 = (Fx[3] - Fx[0])*(Fy[1] - Fy[0])
              - (Fx[1] - Fx[0])*(Fy[3] - Fy[0]);
      cp2 = (Fx[3] - Fx[0])*(Fy[2] - Fy[0])
              - (Fx[2] - Fx[0])*(Fy[3] - Fy[0]);

      if (cp1 == 0 && cp2 == 0)
      {
      }
      else if (cp1*cp2 >= 0)   // either both neg or both pos
      {
         w = 0;

         v = new vertex(Fx[0],Fy[0],Z[0],A[0]);
         v->next = new vertex(Fx[1],Fy[1],Z[1],A[1]);
         v->next->next = new vertex(Fx[2],Fy[2],Z[2],A[2]);
         v->next->next->next = new vertex(Fx[3],Fy[3],Z[3],A[3]);

          if (cp1 >= 0 && cp2 >= 0)
          {
             w = v;
             v = 0;
          }
        }
        else              // one neg, one pos
        {
          v = new vertex(Fx[0],Fy[0],Z[0],A[0]);
          v->next = new vertex(Fx[1],Fy[1],Z[1],A[1]);
          v->next->next = new vertex(Fx[2],Fy[2],Z[2],A[2]);

          w = new vertex(Fx[1],Fy[1],Z[1],A[1]);
          w->next = new vertex(Fx[2],Fy[2],Z[2],A[2]);
          w->next->next = new vertex(Fx[3],Fy[3],Z[3],A[3]);

          if (cp1 > 0)
          {
             m = w; w = v; v = m;
          }
        }
        break;
     }

     case CORNER_ON:
     {
        cp1 = (Fx[2] - Fx[0])*(Fy[3] - Fy[0])
                      - (Fx[3] - Fx[0])*(Fy[2] - Fy[0]);
        cp2 = (Fx[3] - Fx[0])*(Fy[1] - Fy[0])
                      - (Fx[1] - Fx[0])*(Fy[3] - Fy[0]);
        cp3 = (Fx[2] - Fx[3])*(Fy[1] - Fy[3])
                      - (Fx[1] - Fx[3])*(Fy[2] - Fy[3]);

        w = 0;
        v = new vertex(Fx[0],Fy[0],Z[0],A[0]);
        v->next = new vertex(Fx[1],Fy[1],Z[1],A[1]);
        v->next->next = new vertex(Fx[2],Fy[2],Z[2],A[2]);

        if (cp2*cp3 >= 0)
        {
             // leave as is
          if (cp2 >= 0)
          {
                // switch w and v
             w = v;  v = 0;
          }
        }
        else if (cp1*cp2 >= 0)
        {
          w = new vertex(Fx[1],Fy[1],Z[1],A[1]);
          w->next = new vertex(Fx[2],Fy[2],Z[2],A[2]);

          if (cp1 >= 0)
          {
             m = w;  w = v;  v = m;
          }
        }
        else
        {
          w = new vertex(Fx[0],Fy[0],Z[0],A[0]);
          w->next = new vertex(Fx[1],Fy[1],Z[1],A[1]);

          if (cp1 >= 0)
          {
             m = w;  w = v;  v = m;
          }
        }
        break;
     }
  }

  // reverse order of w
  vertex *a, *b, *d;
  if (w != nullptr && w->next != nullptr)
  {
     a = w;
     b = w->next;
     w->next = nullptr;

     while (b->next != nullptr)
     {
        d = b->next;
        b->next = a;
        a = b;
        b = d;
     }

     b->next = a;  // finish

     w = b;
  }
}



//
//******************************************************************************
//                      CHECK_AGAINST_PERIMETER 
//******************************************************************************
//
void UCsurface::check_against_perimeter(vertex *f1, perimeter &per, int dir)
{

  //    Function checks the list of vertices against the perimeter,
  //    draws any lines that need to be drawn, and updates the
  //    perimeter.  If dir == 0, routine checks against the inner
  //    perimeter, else the outer.

  if ((f1 == nullptr) || (f1->next == nullptr)) return;

  vertex *p1 = (dir == 1) ? per.outer : per.inner;
  if (dir == 1)
     while ( (*(p1->next) <= *f1) || (*f1 < *p1)) p1 = p1->next;
  else
     while ( (*f1 <= *(p1->next)) || (*p1 < *f1)) p1 = p1->next;

  enum {INSIDE, OUTSIDE};
  int flag = 2;

  double dpx, dpy, dfx, dfy, cp1, cp2, cp3, cp4;
  double d, s, a, x, y, z;

  vertex *I = p1;                // insertion points

  vertex *head, *tail, *nx2last; // for list of vertex to add to perim

  head = 0; tail = 0; nx2last = 0;
  vertex *m;                     // for random tranversing

  vertex *p2;
  vertex *f2;

  vertex *vtest;
  //vertex *vnextdelete;  // for vertex removal code (CRA)

  p2 = p1->next;
  f2 = f1->next;


  while((f2 != nullptr)&&(p2 != nullptr))
  {

     dpx = p2->x - p1->x;
     dpy = p2->y - p1->y;
     dfx = f2->x - f1->x;
     dfy = f2->y - f1->y;

     cp1 = dpy*(f1->x - p1->x) - dpx*(f1->y - p1->y);
     cp2 = dpy*(f2->x - p1->x) - dpx*(f2->y - p1->y);
     cp3 = dfx*(p1->y - f1->y) - dfy*(p1->x - f1->x);
     cp4 = dfx*(p2->y - f1->y) - dfy*(p2->x - f1->x);

         // going out   CRA  changed -12 to -8
     if ((flag != OUTSIDE) && (cp1 <= 1e-8) && cp2 > 1e-8
          && cp3 <= 1e-8 && cp4 >= -1e-8)
     {
        d = -dfx*dpy + dfy*dpx;
        s = ((p1->y - f1->y)*dpx - (p1->x - f1->x)*dpy)/d;
        x = f1->x + s*dfx;
        y = f1->y + s*dfy;
        z = f1->z + s*(f2->z - f1->z);
        a = f1->a + s*(f2->a - f1->a);

        head = new vertex(x,y,z,a);
        nx2last = head;
        tail    = head;

        // CRA change  above from : tail = nx2last = head;

        flag = OUTSIDE;
     }

         // going in
     else if ((flag == OUTSIDE) && cp1 > 1e-8 && cp2 <= 1e-8
                 && cp3 >= -1e-8 && cp4 <= 1e-8)
     {
        d = -dfx*dpy + dfy*dpx;
        s = ((p1->y - f1->y)*dpx - (p1->x - f1->x)*dpy)/d;
        x = f1->x + s*dfx;
        y = f1->y + s*dfy;
        z = f1->z + s*(f2->z - f1->z);
        a = f1->a + s*(f2->a - f1->a);

                // Add last segment
        vertex* vp     = new vertex(x,y,z,a);
        tail->next     = vp;
        nx2last        = tail;
        tail           = vp;

              // draw lines
        m = head;
        while (m != tail)
        {
          draw_line(m,m->next);
          m = m->next;
        }


// UPDATE PERIMETER
// Remove past vertexes from perimeter
              
 // while (I->next != p2) per.remove_next_vertex(I);
 //
 //  CRA modification : changed above call to  the following. Essentially
 //  the same call as before, but I updated I->next in the
 //  else if(I->next == per.outer) --- it wasn't there before.
 //

 		while(I->next != p2)
        {
         if(per.outer == nullptr){}
         else if (I->next == I)
         {
         delete per.outer;
         per.outer = nullptr; per.inner = nullptr; per.end = nullptr;
         }
         else if (I->next == per.outer)
         {
         if(per.inner == per.outer){per.inner = (per.outer)->next;}
         per.outer       = (per.outer)->next;
         (per.end)->next = per.outer;
         vtest           = (I->next)->next;
         delete I->next;
         I->next          = vtest;
         }
         else if(I->next == per.end)
         {
         if(per.inner == per.end) per.inner = I;
         per.end   = I;
         vtest     = (I->next)->next;
         delete I->next;
         I->next      = vtest;
         }
         else
         {
         if(per.inner == I->next) per.inner = I;
         vtest        = (I->next)->next;
         //delete I->next;                          //  CRA 4.30.2020 - commented out this delete to stop valgrind access errors
                                                    //  a logic problem. Leaving it till later -- this doesn't cause a memory leak.
                                                    //  The whole update perimeter segment needs to be reworked.
         I->next      = vtest;
         }

        }
 //
 //
 // Add new segments

        per.add_segments_after(I,head,tail,nx2last);

        tail = head = 0;

        flag = INSIDE;
     }


     // advance pointer and possibly update
     if ((dir == 1) ? (*p2 < *f2) : (*f2 < *p2))
     {
        p1 = p2;
        p2 = p1->next;

        if (flag != OUTSIDE) I = p1;
     }
     else
     {
        f1 = f2;
        f2 = f1->next;

        if (flag == OUTSIDE)
        {
          tail->next = new vertex(f1->x,f1->y,f1->z,f1->a);
          nx2last = tail;
          tail = tail->next;
        }
     }

  }
}
//
//******************************************************************************
//                      CALC_SCALE_FACTOR_AND_OFFSETS
//******************************************************************************
//
void UCsurface::calc_scale_factor_and_offsets()
{
  //  Function calculates m and the offsets so that image is centered
  //    fills the frame.  Routine only checks the corners so it may not
  //    be exact but probably is.

  double minx, maxx, miny, maxy;
  double tx, ty;

  map_coordinates(row_value(0),col_value(0),value(0,0),tx,ty);
  minx = maxx = tx;
  miny = maxy = ty;

  map_coordinates(row_value(rows-1),col_value(0),value(rows-1,0),tx,ty);
  if (minx > tx) minx = tx; else if (maxx < tx) maxx = tx;
  if (miny > ty) miny = ty; else if (maxy < ty) maxy = ty;

  map_coordinates(row_value(rows-1),col_value(columns-1),
                  value(rows-1,columns-1),tx,ty);
  if (minx > tx) minx = tx; else if (maxx < tx) maxx = tx;
  if (miny > ty) miny = ty; else if (maxy < ty) maxy = ty;

  map_coordinates(row_value(0),col_value(columns-1),
                  value(0,columns-1),tx,ty);
  if (minx > tx) minx = tx; else if (maxx < tx) maxx = tx;
  if (miny > ty) miny = ty; else if (maxy < ty) maxy = ty;


  set_scale_factor(1/(maxx-minx));
  if (get_scale_factor() > 1/(maxy-miny))
    set_scale_factor(1/(maxy-miny));


     // The offsets are for centering the image
  xoffset = 0.5 - get_scale_factor()*(maxx+minx)/2;
  yoffset = 0.5 + get_scale_factor()*(maxy+miny)/2;
}
//
//******************************************************************************
//                      IS_IN_ARRAY 
//******************************************************************************
//
long UCsurface::is_in_array(double val, double *A, long length)
{
  // Performs a simble binary search.
  // Assumes (val >= A[0] && val <= A[length-1])
  //   and that A is increasing.

  int done = 0;
  long rtn = -1;
  long a = 0, b = length-1, c;

  if (val == ((A) ? A[a] : a))
    {done = 1; rtn = a;}
  if (val == ((A) ? A[b] : b))
    {done = 1; rtn = b;}

  double d;
  while (!done)
  {
     c = (b+a)/2;

    d = ((A) ? A[c] : double(c));
     if (d == val)
        { done = 1; rtn = c; }
     else if (d > val)
        { b = c; }
     else
        { a = c; }

     if (a+1 == b) done = 1;
  }

  return rtn;
}


//
//******************************************************************************
//                      SUEDO_ANGLE (David needs a spell checker!)
//******************************************************************************
//
double UCsurface::suedo_angle(double x, double y)
{
  //  This function calculates a suedo angle so that the vertices can
  //    be ordered.

  x = x-VPx;
  y = y-VPy;

  if (fabs(x) >= fabs(y))
    if (x > 0) return (y/x);
    else return (4+y/x);
  else
    if (y > 0) return (2-x/y);
    else return (6-x/y);
}
//
//******************************************************************************
//                      INITIALIZE_PERIMETER 
//******************************************************************************
//
void UCsurface::initialize_perimeter(perimeter &p)
{
  //  This function sets up the perimeter.

  vertex *v, *v2, *w;
  double x,y,z;
  long i; long j;

  if (VPx < row_value(rows-1) && VPx > row_value(0))    // edge or face on
  {
     if (VPy < col_value(columns-1) && VPy > col_value(0))   // face on
     {
		i = 1;
		j = 1;
        while (VPx > row_value(i)) i++;
        while (VPy > col_value(j)) j++;

        z = value(i,j);
        map_coordinates(row_value(i),col_value(j),z,x,y);
        scale_and_translate(x,y);
        v = new vertex(x,y,z,suedo_angle(row_value(i),col_value(j)));

        p.add_vertex_after(0,v);

        short a,b;
        if (Fz < VPz)
          { a = 0; b = 1; }
        else
          { a = 1; b = 0; }

        z = value(i-a,j-b);
        map_coordinates(row_value(i-a),col_value(j-b),z,x,y);
        scale_and_translate(x,y);
        v = new vertex(x,y,z,suedo_angle(row_value(i-a),col_value(j-b)));
        p.add_vertex_after(p.outer,v);

        z = value(i-1,j-1);
        map_coordinates(row_value(i-1),col_value(j-1),z,x,y);
        scale_and_translate(x,y);
        v = new vertex(x,y,z,suedo_angle(row_value(i-1),col_value(j-1)));
        p.add_vertex_after(p.outer,v);

        z = value(i-b,j-a);
        map_coordinates(row_value(i-b),col_value(j-a),z,x,y);
        scale_and_translate(x,y);
        v = new vertex(x,y,z,suedo_angle(row_value(i-b),col_value(j-a)));
        p.add_vertex_after(p.outer,v);

        p.inner = p.outer;
     }
     else
     {
        long yindex = (VPy <= col_value(0)) ? 0 : columns-1;

        z = value(0,yindex);
        map_coordinates(row_value(0),col_value(yindex),z,x,y);
        scale_and_translate(x,y);
        v = new vertex(x,y,z,suedo_angle(row_value(0),col_value(yindex)));
        p.add_vertex_after(0,v);

        z = value(rows-1,yindex);
        map_coordinates(row_value(rows-1),col_value(yindex),z,x,y);
        scale_and_translate(x,y);
        v = new vertex(x,y,z,
                     suedo_angle(row_value(rows-1),col_value(yindex)));
      p.add_vertex_after(p.outer,v);
      p.inner = v;
      w = p.outer;

	  for (i = 1; i < rows-1; i++)
        {
          z = value(i,yindex);
          map_coordinates(row_value(i),col_value(yindex),z,x,y);
        scale_and_translate(x,y);
          v = new vertex(x,y,z,
                       suedo_angle(row_value(i),col_value(yindex)));
          v2 = new vertex(x,y,z,
                        suedo_angle(row_value(i),col_value(yindex)));

        p.add_vertex_after(p.inner,v);
        p.add_vertex_after(w,v2);

        w = w->next;
      }

      if (VPy <= col_value(0))   // need to switch inner and outer
      {                  //  w is pointing to element behind inner
        p.end = w;
        w = p.outer;
        p.outer = p.inner;
        p.inner = w;
      }
    }
  }
  else       // corner or edge on
  {
    if (VPy > col_value(0) && VPy < col_value(columns-1))  // edge on
    {
      long xindex = (VPx <= row_value(0)) ? 0 : rows-1;

        z = value(xindex,0);
        map_coordinates(row_value(xindex),col_value(0),z,x,y);
      scale_and_translate(x,y);
        v = new vertex(x,y,z,suedo_angle(row_value(xindex),col_value(0)));
      p.add_vertex_after(0,v);

        z = value(xindex,columns-1);
        map_coordinates(row_value(xindex),col_value(columns-1),z,x,y);
        scale_and_translate(x,y);
        v = new vertex(x,y,z,
                 suedo_angle(row_value(xindex),col_value(columns-1)));
        p.add_vertex_after(p.outer,v);

      p.inner = v;
      w = p.outer;

	  for (i = 1; i < columns-1; i++)
        {
          z = value(xindex,i);
          map_coordinates(row_value(xindex),col_value(i),z,x,y);
		  scale_and_translate(x,y);
          v = new vertex(x,y,z,
                   suedo_angle(row_value(xindex),col_value(i)));
          v2 = new vertex(x,y,z,
                    suedo_angle(row_value(xindex),col_value(i)));

        p.add_vertex_after(p.inner,v);
        p.add_vertex_after(w,v2);

        w = w->next;
      }

      if (VPx >= row_value(rows-1))
      {
        p.end = w;
        w = p.outer;
        p.outer = p.inner;
        p.inner = w;
      }
    }
    else   // corner on - four cases
    {
      if (VPx <= row_value(0))
      {
        if (VPy <= col_value(0))
          {
             z = value(rows-1,0);
             map_coordinates(row_value(rows-1),col_value(0),z,x,y);
			 scale_and_translate(x,y);
             v = new vertex(x,y,z,
			 suedo_angle(row_value(rows-1),col_value(0)));
			 p.add_vertex_after(0,v);

             z = value(0,columns-1);
             map_coordinates(row_value(0),col_value(columns-1),z,x,y);
             scale_and_translate(x,y);
             v = new vertex(x,y,z,
			 suedo_angle(row_value(0),col_value(columns-1)));
			 p.add_vertex_after(p.outer,v);

			 p.inner = v;
			 w = p.outer;

		  for (i = rows-2; i >=0; i--)
             {
                z = value(i,0);
                map_coordinates(row_value(i),col_value(0),z,x,y);
                scale_and_translate(x,y);
                v = new vertex(x,y,z,
                       suedo_angle(row_value(i),col_value(0)));
                v2 = new vertex(x,y,z,
                        suedo_angle(row_value(i),col_value(0)));

            p.add_vertex_after(w,v);
            p.add_vertex_after(p.inner,v2);
    
            w = w->next;
          }

          for (i = 1; i < columns-1; i++)
             {
                z = value(0,i);
                map_coordinates(row_value(0),col_value(i),z,x,y);
            scale_and_translate(x,y);
                v = new vertex(x,y,z,
                       suedo_angle(row_value(0),col_value(i)));
                v2 = new vertex(x,y,z,
                        suedo_angle(row_value(0),col_value(i)));

            p.add_vertex_after(w,v);
            p.add_vertex_after(p.inner,v2);
    
            w = w->next;
          }
        }
        else
          {
             z = value(0,0);
             map_coordinates(row_value(0),col_value(0),z,x,y);
          scale_and_translate(x,y);
             v = new vertex(x,y,z,suedo_angle(row_value(0),col_value(0)));
          p.add_vertex_after(0,v);

             z = value(rows-1,columns-1);
             map_coordinates(row_value(rows-1),col_value(columns-1),z,x,y);
          scale_and_translate(x,y);
             v = new vertex(x,y,z,
                   suedo_angle(row_value(rows-1),col_value(columns-1)));
          p.add_vertex_after(p.outer,v);

          p.inner = v;
		  w = p.outer;
		  for (i = 1; i < columns; i++)
			 {
                z = value(0,i);
                map_coordinates(row_value(0),col_value(i),z,x,y);
            scale_and_translate(x,y);
                v = new vertex(x,y,z,
                       suedo_angle(row_value(0),col_value(i)));
                v2 = new vertex(x,y,z,
                        suedo_angle(row_value(0),col_value(i)));

            p.add_vertex_after(w,v);
            p.add_vertex_after(p.inner,v2);
    
            w = w->next;
          }

          for (i = 1; i < rows-1; i++)
             {
                z = value(i,columns-1);
                map_coordinates(row_value(i),col_value(columns-1),z,x,y);
            scale_and_translate(x,y);
                v = new vertex(x,y,z,
                       suedo_angle(row_value(i),col_value(columns-1)));
                v2 = new vertex(x,y,z,
                        suedo_angle(row_value(i),col_value(columns-1)));

            p.add_vertex_after(w,v);
            p.add_vertex_after(p.inner,v2);
    
            w = w->next;
          }
        }
      }
      else      // VPx >= X[rows-1]
      {
        if (VPy <= col_value(0))
          {
             z = value(rows-1,columns-1);
             map_coordinates(row_value(rows-1),col_value(columns-1),z,x,y);
          scale_and_translate(x,y);
             v = new vertex(x,y,z,
                     suedo_angle(row_value(rows-1),col_value(columns-1)));
          p.add_vertex_after(0,v);

             z = value(0,0);
             map_coordinates(row_value(0),col_value(0),z,x,y);
          scale_and_translate(x,y);
             v = new vertex(x,y,z,suedo_angle(row_value(0),col_value(0)));
          p.add_vertex_after(p.outer,v);

          p.inner = v;
          w = p.outer;

		  for (i = columns-1; i >=0; i--)
             {
                z = value(rows-1,i);
                map_coordinates(row_value(rows-1),col_value(i),z,x,y);
            scale_and_translate(x,y);
                v = new vertex(x,y,z,
                       suedo_angle(row_value(rows-1),col_value(i)));
                v2 = new vertex(x,y,z,
                        suedo_angle(row_value(rows-1),col_value(i)));

            p.add_vertex_after(w,v);
            p.add_vertex_after(p.inner,v2);

            w = w->next;
          }

          for (i = rows-1; i > 0; i--)
             {
                z = value(i,0);
                map_coordinates(row_value(i),col_value(0),z,x,y);
            scale_and_translate(x,y);
                v = new vertex(x,y,z,suedo_angle(row_value(i),col_value(0)));
                v2 = new vertex(x,y,z,suedo_angle(row_value(i),col_value(0)));

            p.add_vertex_after(w,v);
            p.add_vertex_after(p.inner,v2);

            w = w->next;
          }
        }
        else
          {
             z = value(0,columns-1);
             map_coordinates(row_value(0),col_value(columns-1),z,x,y);
          scale_and_translate(x,y);
             v = new vertex(x,y,z,
                     suedo_angle(row_value(0),col_value(columns-1)));
          p.add_vertex_after(0,v);

             z = value(rows-1,0);
             map_coordinates(row_value(rows-1),col_value(0),z,x,y);
          scale_and_translate(x,y);
             v = new vertex(x,y,z,
                     suedo_angle(row_value(rows-1),col_value(0)));
          p.add_vertex_after(p.outer,v);

          p.inner = v;
          w = p.outer;

          for (i = 1; i < rows; i++)
             {
                z = value(i,columns-1);
                map_coordinates(row_value(i),col_value(columns-1),z,x,y);
            scale_and_translate(x,y);
                v = new vertex(x,y,z,
                       suedo_angle(row_value(i),col_value(columns-1)));
                v2 = new vertex(x,y,z,
                        suedo_angle(row_value(i),col_value(columns-1)));

            p.add_vertex_after(w,v);
            p.add_vertex_after(p.inner,v2);

            w = w->next;
          }
 
          for (i = columns-2; i > 0; i--)
             {
                z = value(rows-1,i);
                map_coordinates(row_value(rows-1),col_value(i),z,x,y);
            scale_and_translate(x,y);
                v = new vertex(x,y,z,
                       suedo_angle(row_value(rows-1),col_value(i)));
                v2 = new vertex(x,y,z,
                        suedo_angle(row_value(rows-1),col_value(i)));

            p.add_vertex_after(w,v);
            p.add_vertex_after(p.inner,v2);

            w = w->next;
          }
        }
      }
    }
  }

  if (p.outer == 0)
  {
    cerr << "Something wrong with parameter initialization\n";
    CAMgraphicsExit();
  }
}
//
//******************************************************************************
//                          VALUE
//******************************************************************************
//
double UCsurface::value(long r, long c)
{
  //  This function returns the value stored in the array data
  if (data_array)
  {
    if (Fortran_array_flag)
      return data_array[r + c*rows];
    else
      return data_array[r*columns + c];
  }
  else
    return data_function(r,c);
}
//
//******************************************************************************
//                      ROW_VALUE
//******************************************************************************
//
double UCsurface::row_value(long r)
{
  if (X)
    return X[r];
  else
    return double(r);
}
//
//******************************************************************************
//                      COL_VALUE 
//******************************************************************************
//
double UCsurface::col_value(long c)
{
  if (Y)
    return Y[c];
  else
    return double(c);
}
//
//******************************************************************************
//                      OPERATOR<
//******************************************************************************
//
int operator<(UCsurface::vertex &v, UCsurface::vertex &v2)
{
  double ans = v.a - v2.a;
  return ((ans < 0 && ans > -4) || ans > 4);
}
//
//******************************************************************************
//                      OPERATOR <= 
//******************************************************************************
//
int operator<=(UCsurface::vertex &v, UCsurface::vertex &v2)
{
  return (v.a == v2.a || v < v2);
}
//
//******************************************************************************
//                      OPERATOR == 
//******************************************************************************
//
int operator==(UCsurface::vertex &v, UCsurface::vertex &v2)
{
  return (v.a == v2.a && v.x == v2.x && v.y == v2.y);
} 
//
//******************************************************************************
// SOURCE FOR COMPILERS WHICH CAN TOLERATE NESTED CLASS NAMES
//******************************************************************************
// 
#ifndef __MPWcplusplus
//
//******************************************************************************
//                     DESTRUCTOR
//******************************************************************************
//
UCsurface::perimeter::~perimeter()
{
  if (outer == 0) return;

  while (outer != 0) remove_next_vertex(outer);
}
//
//******************************************************************************
//                      ADD_VERTEX_AFTER 
//******************************************************************************
//
void UCsurface::perimeter::add_vertex_after(vertex *v, vertex *w)
{
  if (v == 0)
  {
     if (outer == 0)
     {
        outer = w;
        w->next = w;
        end = w;
     }
     else   // if v==0 add to front
     {
        end->next = w;
        w->next = outer;
        outer = w;
     }
  }
  else if (outer == 0)
  {
     return;
  }
  else if (v == end)
  {
     end->next = w;
     w->next = outer;
     end = w;
  }
  else
  {
     w->next = v->next;
     v->next = w;
  }
}
//
//******************************************************************************
//                      REMOVE_NEXT_VERTEX
//******************************************************************************
//
void UCsurface::perimeter::remove_next_vertex(vertex *v)
{
  if (outer == 0)
  {
     return;
  }

  if (v->next == v)
  {
     delete outer;
     outer = inner = end = 0;
  }
  else if (v->next == outer)
  {
     if (inner == outer) inner = outer->next;
     outer = outer->next;
     delete (end->next);
     end->next = outer;
  }
  else if (v->next == end)
  {
     if (inner == end) inner = v;
     delete end;
     v->next = outer;
     end = v;
  }
  else
  {
     if (inner == v->next) inner = v;
     vertex *vp = (v->next)->next;
     if(vp != 0) delete v->next;
     if(vp != 0) v->next = vp;
  }
}
//
//******************************************************************************
//                      ADD_SEGMENTS_AFTER
//******************************************************************************
//
void UCsurface::perimeter::add_segments_after(vertex *I, vertex *head,vertex *tail, vertex *nx2last)
{
  if (*(tail) == *(I->next))
  {
     delete tail;
     nx2last->next = I->next;
     if (I == end) end = nx2last;
  }
  else
  {
       tail->next = I->next;
       if (I == end) end = tail;
  }

  if (*I == *head)
  {
     I->next = head->next;
     delete head;
  }
  else
  {I->next = head;}
} 
#else
//
//**********************************************************************
// SOURCE FOR COMPILERS WHICH CAN'T TOLERATE NESTED CLASS NAMES
//**********************************************************************
//
//******************************************************************************
//                     DESTRUCTOR
//******************************************************************************
//
perimeter::~perimeter()
{
  if (outer == 0) return;

  while (outer != 0) remove_next_vertex(outer);
}
//
//******************************************************************************
//                      ADD_VERTEX_AFTER 
//******************************************************************************
//
void perimeter::add_vertex_after(vertex *v, vertex *w)
{
  if (v == 0)
  {
     if (outer == 0)
     {
        outer = w;
        w->next = w;
        end = w;
     }
     else   // if v==0 add to front
     {
        end->next = w;
        w->next = outer;
        outer = w;
     }
  }
  else if (outer == 0)
  {
     return;
  }
  else if (v == end)
  {
     end->next = w;
     w->next = outer;
     end = w;
  }
  else
  {
     w->next = v->next;
     v->next = w;
  }
}
//
//******************************************************************************
//                      REMOVE_NEXT_VERTEX
//******************************************************************************
//
void perimeter::remove_next_vertex(vertex *v)
{
  if (outer == 0)
  {
     return;
  }

  if (v->next == v)
  {
     delete outer;
     outer = inner = end = 0;
  }
  else if (v->next == outer)
  {
     if (inner == outer) inner = outer->next;
     outer = outer->next;
     delete end->next;
     end->next = outer;
  }
  else if (v->next == end)
  {
     if (inner == end) inner = v;
     delete end;
     v->next = outer;
     end = v;
  }
  else
  {
     if (inner == v->next) inner = v;
     vertex *vp = v->next->next;
     delete v->next;
     v->next = vp;
  }
}
//
//******************************************************************************
//                      ADD_SEGMENTS_AFTER
//******************************************************************************
//
void perimeter::add_segments_after(vertex *I, vertex *head,
                              vertex *tail, vertex *nx2last)
{
  if (*(tail) == *(I->next))
  {
     delete tail;
     nx2last->next = I->next;
     if (I == end) end = nx2last;
  }
  else
  {
     tail->next = I->next;
     // if (I == end) end = tail;     CRA killed this code
  }

  if (*I == *head)
  {
     I->next = head->next;
     delete head;
  }
  else
  {I->next = head;}
} 
#endif
 
