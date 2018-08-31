//
//******************************************************************************
//                              UCPLOT.CPP
//******************************************************************************
//
//            SOURCE FILE FOR CLASS UCplot 
//
//********************************************************************************
//            David Sansot                (C) UCLA 1994, 1995
//
//           
// ---- Modifications ----
//
// 01/02/03 :  Improved clipping in create_plot. Chris Anderson, UCLA
// 04/14/03 :  Fixed bug in numerical label routine. Chris Anderson, UCLA                         
//        
//********************************************************************************
//
//#include <stdio.h>
//#include <stdlib.h>
#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

#include "ucplot.h"
#include "ucclip.h"
#include "camgraphexit.h"
//
//******************************************************************************
//                         COPY CONSTRUCTOR
//******************************************************************************
// 
UCplot::UCplot(const UCplot& A) : UC2dgraph(A)
{   
    auto_scale_flag = A.auto_scale_flag;
    majorx          = A.majorx;
    majory          = A.majory;
    minorx          = A.minorx;
    minory          = A.minory;

    label_type      = A.label_type;         
    label_width     = A.label_width;
    label_precision = A.label_precision;
    label_char_size = A.label_char_size;

    x_axis_flag     = A.x_axis_flag;    
    y_axis_flag     = A.y_axis_flag;
    x_label_flag    = A.x_label_flag;   
    y_label_flag    = A.y_label_flag;   

    x_axis_type     = A.x_axis_type;
    y_axis_type     = A.y_axis_type;
    x_intercept     = A.x_intercept;
    y_intercept     = A.y_intercept;
    axis_color      = A.axis_color; 

    if(A.axis_rgb != 0)
    { 
      axis_rgb = new double[3];
      axis_rgb[0] = A.axis_rgb[0];
      axis_rgb[1] = A.axis_rgb[1];
      axis_rgb[2] = A.axis_rgb[2];
    }
    else
    {axis_rgb = 0;}
        
    line_color = A.line_color;     
 
    if(A.line_rgb != 0)
    { 
      line_rgb = new double[3];
      line_rgb[0] = A.line_rgb[0];
      line_rgb[1] = A.line_rgb[1];
      line_rgb[2] = A.line_rgb[2];
    }
    else
    {line_rgb = 0;}
        
    line_dash_pattern = A.line_dash_pattern;
    user_dash_pattern = A.user_dash_pattern; 
    
    line_width = A.line_width;
    plot_style = A.plot_style;        
    point_type = A.point_type;        

    if(A.point_font != 0)
    { point_font = new char[strlen(A.point_font) + 1];
      strcpy(point_font,A.point_font);}
    else
    {point_font = 0;} 
          
    point_size   = A.point_size;
    n_fun_points = A.n_fun_points;     
//
//  Pointers to Data are Set To Null Instance 
//
    X   = 0; 
    Y   = 0; 
    n_points = 0;
    
    fun = 0; 
} 
//
//******************************************************************************
//                         UCplot(UCdriver *d)
//******************************************************************************
//
UCplot::UCplot(UCdriver *d) : UC2dgraph(d)
{ 
//
//  This constructor associates a graphics output driver with the
//  class instance and initializes internal variables
//
    n_fun_points = 101;
//
//  Variables from UC2dgraph
//
    xmin = 0.0; xmax = 1.0;
    ymin = 0.0; ymax = 1.0;
// 
//  Initialize other variables with default values
//
    init_vars(); 
// 
//  Set external data variables to their null instances
//
    X = 0;  Y = 0;
    n_points  = 0; 
//    
    fun          = 0; 
}
//
//******************************************************************************
//                      INTERNAL HELPER FUNCTIONS
//******************************************************************************
//
//
//******************************************************************************
//                      INIT_VARS
//******************************************************************************
//
void UCplot::init_vars()
{ 
//
//  Plot defaults are set in this routine 
//  (All variables associated with UCPlot)
//
//
//  Auto Scaling Feature
// 
    auto_scale_flag = 1; 
// 
//  Data Limit Defaults
//
    xmin = 0.0;
    xmax = 1.0;
    ymin = 0.0;
    ymax = 1.0;
//
//  Tick Mark Defaults
//    
    majorx = majory = 4;
    minorx = minory = 1;
//
//  Label Defaults
//
    label_type = FLOATING_POINT;
    label_width = 7;
    label_precision = 2;
    label_char_size = 0.03;
//
//  Axis Defaults
//
    x_axis_flag = y_axis_flag = x_label_flag = y_label_flag = 1;
    x_axis_type = y_axis_type = PERIMETER;

    x_intercept = y_intercept = 0;

    axis_color = 0;
    axis_rgb = 0;
//
//  Line Style Defaults
//
    line_color = 0;
    line_rgb = 0;

    line_dash_pattern = 0;
    user_dash_pattern = 0;

    line_width = 0;
//
//  Plot and Point Style Defaults
//
    plot_style = CURVE;
    point_type = '*';
    point_font = 0;
    point_size = 0.02;
}
//
//******************************************************************************
//                      X_TICK_MARK
//******************************************************************************
//
void UCplot::x_tick_mark(double xpos, double length, double ypos)
{             // length is length of tic mark, ypos is use for floating
  switch (x_axis_type)
  {
    case GRID:
    {
      drv->line(xpos,frame_b,xpos,frame_t,0,0,0,axis_color,axis_rgb);
      break;
    }

    case PERIMETER:
    {
      drv->line(xpos,frame_b,xpos,frame_b+length,
              0,0,0,axis_color,axis_rgb);
      drv->line(xpos,frame_t,xpos,frame_t-length,
              0,0,0,axis_color,axis_rgb);
      break;
    }

    case FLOATING:
    {
      drv->line(xpos,ypos-length/2,xpos,ypos+length/2,
              0,0,0,axis_color,axis_rgb);
      break;
    }
  }
}
//
//******************************************************************************
//                      Y_TICK_MARK
//******************************************************************************
//
void UCplot::y_tick_mark(double ypos, double length, double xpos)
{             // length is length of tic mark, ypos is use for floating
  switch (y_axis_type)
  {
    case GRID:
    {
      drv->line(frame_l,ypos,frame_r,ypos,0,0,0,axis_color,axis_rgb);
      break;
    }
   
    case PERIMETER:
    {
      drv->line(frame_l,ypos,frame_l+length,ypos,
              0,0,0,axis_color,axis_rgb);
      drv->line(frame_r,ypos,frame_r-length,ypos,
              0,0,0,axis_color,axis_rgb);
      break;
    }

    case FLOATING:
    {
      drv->line(xpos-length/2,ypos,xpos+length/2,ypos,
              0,0,0,axis_color,axis_rgb);
      break;
    }
  }
}
//
//******************************************************************************
//                       X_NUM_LABEL
//******************************************************************************
//
void UCplot::x_num_label(double x, double xpos, double ypos)
{                       // ypos only used if axis_type == FLOATING
  char str[15];
  char *s = new char[label_width + label_precision+25];

  if (label_type == SCIENTIFIC)
    sprintf(str, "%%%d.%de", label_width, label_precision);
  else
    sprintf(str, "%%.%df", label_precision);

  sprintf(s, str, x);

  double scale = ((frame_r - frame_l) < (frame_t - frame_b)) ?
  (frame_r - frame_l) : (frame_t - frame_b);

  if (x_axis_type == FLOATING)
    drv->text(xpos, ypos-0.015*scale, s, font, label_char_size*scale,
            0, 0, 1, text_color, text_rgb);
  else
    drv->text(xpos, frame_b-0.01*scale, s, font, label_char_size*scale,
            0, 0, 1, text_color, text_rgb);

  delete [] s;
}
//
//******************************************************************************
//                       Y_NUM_LABEL
//******************************************************************************
//
void UCplot::y_num_label(double y, double ypos, double xpos)
{                              
// ypos only used if axis_type == FLOATING
  char str[15];
  char *s = new char[label_width + label_precision+25];

  if (label_type == SCIENTIFIC)
    sprintf(str,"%%.%de",label_precision);
  else
	sprintf(str,"%%.%df",label_precision);

  sprintf(s,str,y);

  double scale = ((frame_r - frame_l) < (frame_t - frame_b)) ?
  (frame_r - frame_l) : (frame_t - frame_b);

  if (y_axis_type == FLOATING) 
    drv->text(xpos-0.015*scale, ypos, s, font, label_char_size*scale,
            0, 1, 0, text_color, text_rgb);

  else
  {
    if (ypos == frame_b && x_axis_type != FLOATING && x_label_flag)
	{         //  this is so labels don't overlap
      drv->text(frame_l-0.005*scale, ypos, s, font, label_char_size*scale,
              0, 1, -1, text_color, text_rgb);
    }
    else
    {
      drv->text(frame_l-0.005*scale, ypos, s, font, label_char_size*scale,
              0, 1, 0, text_color, text_rgb);
    }
  }

  delete [] s;
}
//
//******************************************************************************
//                       SET_RANGE_TO_MIN_MAX
//******************************************************************************
//
void UCplot::set_range_to_min_max()
{ 
//
//  This routine sets the values of  xmin, xmax, ymin, ymax        
//  in UC2dgraph based on the values of the variables to be
//  plotted.
//  
//
//  Case When Ordinates Specified
//
    if (X != 0)
    {
        xmin = xmax = *X;
        double *xptr = X+1;

        for (int i = 1; i < n_points; i++)
        {
        if (*xptr > xmax) xmax = *xptr;
        else if (*xptr < xmin) xmin = *xptr;

        xptr++;
        }
    } 
//
//  Case When Ordinates are Not Specified
//   
    if((X == 0)&&( Y != 0)) 
    {
        xmin = 0.0;
        xmax = n_points - 1;
    }
//
//  Scale based on Y values
//    
    if(Y != 0)
    {
    ymin = ymax = *Y;

    double *yptr = Y+1;
    for (int i = 1; i < n_points; i++)
    {
        if (*yptr > ymax) ymax = *yptr;
        else if (*yptr < ymin) ymin = *yptr;

        yptr++;
    } 
    }
//
//  No Data Specified - so use default box
//    
    if((X == 0) && (Y == 0))
    {   
        xmin = 0.0;
        xmax = 1.0;
        ymin = 0.0;
        ymax = 1.0;  
	}
//
//  case for constants
//
	if(ymin == ymax) ymax = ymin + 1;
//
//
}

void UCplot::set_range_to_min_max(double *XX, double* YY, long N)
{ 
//
//  This routine sets the values of  xmin, xmax, ymin, ymax        
//  in UC2dgraph based on the values of the variables to be
//  plotted.
//  
//
//  Case When Ordinates Specified
//
    if (XX != 0)
    {
        xmin = xmax = *XX;
        double *xptr = XX+1;

        for (int i = 1; i < N; i++)
        {
        if (*xptr > xmax) xmax = *xptr;
        else if (*xptr < xmin) xmin = *xptr;

        xptr++;
        }
    } 
//
//  Case When Ordinates are Not Specified
//   
    if((XX == 0)&&( YY != 0)) 
    {
        xmin = 0.0;
        xmax = N - 1;
    }
//
//  Scale based on YY values
//    
    if(YY != 0)
    {
    ymin = ymax = *YY;

    double *yptr = YY+1;
    for (int i = 1; i < N; i++)
    {
        if (*yptr > ymax) ymax = *yptr;
        else if (*yptr < ymin) ymin = *yptr;

        yptr++;
    } 
    }
//
//  No Data Specified - so use default box
//    
    if((XX == 0) && (YY == 0))
    {   
        xmin = 0.0;
        xmax = 1.0;
        ymin = 0.0;
        ymax = 1.0;  
    }
}
//
//******************************************************************************
//                       GET_DOUBLE_ARRAY
//******************************************************************************
//
double* UCplot::get_double_array(long length)
{
  double *array;
  if((array = new double[length]) == 0)
  {
    cerr << "\nOut of Memory -- Exiting\n\n";
    CAMgraphicsExit();
  }
  return array;
}
//
//******************************************************************************
//                       CREATE_PLOT
//******************************************************************************
//
void UCplot::create_plot()
{
    double *xPoint = get_double_array(n_points);
    double *yPoint = get_double_array(n_points);

    int c = get_graphics_low_color(line_color);
    int d = get_graphics_low_dash(line_dash_pattern);

    double x, y, h;
    
    x=0.0; y=0.0; h=0.0;
	int i;
    for (i = 0; i < n_points; i++)
    {
        if (fun)
        {
        if (i)
            x += h;
        else
            {
                h = (xmax - xmin)/(n_points-1);
                x = xmin;
            }
        y = fun(x);
        }
    else
        {
            y = Y[i];
            x = (X) ? X[i] : i;
        } 
        
     xPoint[i]  = x;
     yPoint[i]  = y;
    }
//
//  For functions - scale axis so that range is slightly larger than 
//  function value range
//    
    if((fun != 0)&&(auto_scale_flag == 1))
    {
    set_range_to_min_max(xPoint,yPoint,n_points);
    double range = (ymax - ymin);
    ymin = ymin - range/2.0;
    ymax = ymax + range/2.0; 
    }

    long plotPointCount;
    
    plotPointCount = UCclip::getClippedPlotPointCount(xPoint, yPoint, n_points, 
                     xmin, xmax,ymin, ymax);

    double *xClip = get_double_array(plotPointCount);
    double *yClip = get_double_array(plotPointCount);

    UCclip::createClippedPoints(xClip,yClip,xPoint,yPoint,n_points,xmin,xmax,ymin,ymax);
    //
    // normalize
    //
    for(i = 0; i < plotPointCount; i++)
    {
    xClip[i] = frame_2_screen_x(normalize_x(xClip[i]));
    yClip[i] = frame_2_screen_y(normalize_y(yClip[i]));
    }
 
    if (plot_style == CURVE || plot_style == CURVE_AND_POINTS)
    drv->lines(xClip, yClip, plotPointCount, d, user_dash_pattern, line_width,
            c, line_rgb);

    if (plot_style == POINTS || plot_style == CURVE_AND_POINTS)
    drv->points(xClip, yClip, plotPointCount, point_type, point_font,
              point_size, c, line_rgb);
/* 
//
//  Clip and Scale to Screen Coordinates
//
    for (i = 0; i < n_points; i++)
    {
    x = xnorm[i];
    y = ynorm[i];
    if (x > xmax)
      xnorm[i] = frame_r;
    else if (x < xmin)
      xnorm[i] = frame_l;
    else
      xnorm[i] = frame_2_screen_x(normalize_x(x));

    if (y > ymax)
      ynorm[i] = frame_t;
    else if (y < ymin)
      ynorm[i] = frame_b;
    else
      ynorm[i] = frame_2_screen_y(normalize_y(y));    
    }  
  


  if (plot_style == CURVE || plot_style == CURVE_AND_POINTS)
    drv->lines(xnorm, ynorm, n_points, d, user_dash_pattern, line_width,
            c, line_rgb);

  if (plot_style == POINTS || plot_style == CURVE_AND_POINTS)
    drv->points(xnorm, ynorm, n_points, point_type, point_font,
              point_size, c, line_rgb);
 */

  if (x_axis_flag) draw_x_axis();
  if (y_axis_flag) draw_y_axis();
  

  if(xPoint != 0) delete [] xPoint;
  if(yPoint != 0) delete [] yPoint;

  if(xClip != 0) delete [] xClip;
  if(yClip != 0) delete [] yClip;
}

//
//********************************************************************************
//           BASIC C DATA TYPE PLOTTING MEMBER FUNCTIONS
//********************************************************************************
// 
//
//******************************************************************************
//                      SET_POINT_FONT
//******************************************************************************
//
void UCplot::set_point_font(char *f)
{
  if (point_font) delete point_font;

  if (f)
  {
    point_font = new char[strlen(f) + 1];
    strcpy(point_font,f);
  }
  else
    font = 0;
}
//
//******************************************************************************
//                      GET_POINT_FONT
//******************************************************************************
//
char* UCplot::get_point_font()
{
  if (point_font)
  {
    char *s = new char[strlen(point_font) + 1];
    strcpy(s,point_font);
    return s;
  }
  else
    return 0;
}
//
//******************************************************************************
//                      DRAW_X_AXIS
//******************************************************************************
//
void UCplot::draw_x_axis()
{
  int i,j;                              // loop counters
  int scale_type = get_x_scale_type();  // save scale type  --
  set_x_scale_type(LIN);                // Always do ticks and labels with
										// linear scales ...

  double xmin_save = xmin;
  double xmax_save = xmax;
  if(scale_type == LOG)
  {
  xmin = log(xmin);
  xmax = log(xmax);
  }

  double x;

    //  Tick length
  double maj = scale_to_frame_width(0.02),
         min = scale_to_frame_width(0.01);

  double ypos = 0;

  if (x_axis_type == FLOATING)
  {
    ypos = frame_2_screen_y(normalize_y(y_intercept));

    if (ypos < frame_l) ypos = frame_l;
    else if (ypos > frame_r) ypos = frame_r;

    drv->line(frame_l,ypos,frame_r,ypos,0,0,0,axis_color,axis_rgb);
  }
  else
  {
    drv->line(frame_l,frame_b,frame_r,frame_b,0,0,0,axis_color,axis_rgb);
    drv->line(frame_l,frame_t,frame_r,frame_t,0,0,0,axis_color,axis_rgb);
  }


  double maj_int = (xmax-xmin)/majorx,
         min_int = (xmax-xmin)/(majorx*(minorx+1));
  double xpos;

  for (i = 0; i < majorx; i++)
  {
    x = xmin + i*maj_int;
    xpos = frame_2_screen_x(normalize_x(x));

    x_tick_mark(xpos,maj,ypos);

    if (x_label_flag)
      x_num_label(x,xpos,ypos);

    for (j = 1; j < minorx+1; j++)
    {
      x += min_int;
      xpos = frame_2_screen_x(normalize_x(x));
      x_tick_mark(xpos,min,ypos);
    }
  }

  x_tick_mark(frame_r,maj,ypos);

  if (x_label_flag)
	x_num_label(xmax,frame_r,ypos);

  set_x_scale_type(scale_type);               // restore scaling mode
  xmin = xmin_save;
  xmax = xmax_save;
}
//
//******************************************************************************
//                      DRAW_Y_AXIS
//******************************************************************************
//
void UCplot::draw_y_axis()
{                                         
  int i,j;                              // loop counters
  int scale_type = get_y_scale_type();  // save scale type  --
  set_y_scale_type(LIN);                // Always do ticks and labels with
										// linear scales ...

  double ymin_save = ymin;
  double ymax_save = ymax;
  if(scale_type == LOG)
  {
  ymin = log(ymin);
  ymax = log(ymax);
  }

  double y;
  double maj = scale_to_frame_height(0.02),
         min = scale_to_frame_height(0.01);
  double xpos = 0;

  if (y_axis_type == FLOATING)
  {
    xpos = frame_2_screen_x(normalize_x(x_intercept));

    if (xpos < frame_b) xpos = frame_b;
    else if (xpos > frame_t) xpos = frame_t;

    drv->line(xpos,frame_b,xpos,frame_t,0,0,0,axis_color,axis_rgb);
  }
  else
  {
    drv->line(frame_l,frame_b,frame_l,frame_t,0,0,0,axis_color,axis_rgb);
    drv->line(frame_r,frame_b,frame_r,frame_t,0,0,0,axis_color,axis_rgb);
  }

  double maj_int = (ymax-ymin)/majory,
         min_int = (ymax-ymin)/(majory*(minory+1));
  double ypos;
    
  for (i = 0; i < majory; i++)
  {
    y = ymin + i*maj_int;
    ypos = frame_2_screen_y(normalize_y(y));

    y_tick_mark(ypos,maj,xpos);
   
    if (y_label_flag)
      y_num_label(y,ypos,xpos);
 
    for (j = 1; j < minory+1; j++)
    {
      y += min_int;
      ypos = frame_2_screen_y(normalize_y(y));
      y_tick_mark(ypos,min,xpos);
    }
  }

  y_tick_mark(frame_t,maj,xpos);

  if (y_label_flag)
	y_num_label(ymax,frame_t,xpos);

  set_y_scale_type(scale_type);               // restore scaling mode
  ymin = ymin_save;
  ymax = ymax_save;
}
//
//******************************************************************************
//                      LABEL_X
//******************************************************************************
//
void UCplot::label_x(char *s, double size)
{
//  Draws string s centered below the frame in the pressent
//    font and  text_color.

//  Save variables so there are no side effects
  double h = horiz_just, v = vert_just;
  set_text_align(0,1);                  
  int a = text_angle;
  set_text_angle(0);

  double offset = 0.015;

  if (x_label_flag)
    offset += 0.015 + label_char_size*0.66;

  double Size = (size == 0) ? 0.04 : size;

  draw_string(0.5, -offset, s, Size);

  set_text_align(h,v);
  set_text_angle(a);
}
//
//******************************************************************************
//                      LABEL_Y
//******************************************************************************
//
void UCplot::label_y(char *s, double size)
{
//  Draws string s vertically centered left or right of the frame at
//    an angle of 90 degrees using the present font and text_color.

//  Save variables so there are no side effects
//
    double h = horiz_just, v = vert_just;
//
//
#ifdef _MSC_VER
    set_text_align(0,-1);
#else
    set_text_align(0,-1);
#endif 
//
// 
    int a = text_angle;
    double Size = (size == 0) ? 0.04 : size; 
//
//    
#ifdef _MSC_VER
    double offset = -0.06;
#else
	double offset =  -.14; //.015 originally
#endif
//
//    if (y_label_flag)    // y numerical labels are drawn so print on right
//    {
//    set_text_angle(270);
//    draw_string(1+offset, 0.5, s, Size);
//    }
//    else
//    {
	  set_text_angle(90);
//    draw_string(-offset, 0.5, s, Size);
	  draw_string(offset,0.5,s,Size);     // draw at left edge always...
//    }

    set_text_align(h,v);
    set_text_angle(a);
}
//
//******************************************************************************
//                       PLOT ROUTINES
//******************************************************************************
//  
void UCplot::plot()
{
    if((Y ==0)&&(fun == 0))
    {cerr << " Data Not Specified For Plot " << endl; CAMgraphicsExit();};
    if(auto_scale_flag == 1) set_range_to_min_max(); 
    create_plot(); 
} 

void UCplot::plot(double *y, long np)
{
    X = 0;
    Y = y;
    n_points = np;
    fun = 0;
    if(auto_scale_flag == 1) set_range_to_min_max(); 
    create_plot(); 
} 

void UCplot::plot(double *y, long np,  int p_arg)
{
    X        = 0;  
    Y        = y;
    n_points = np; 
    fun      = 0; 
  
    if(auto_scale_flag == 1) set_range_to_min_max(); 

    char point_type_save = get_point_type();
    int  plot_style_save = get_plot_style();  
    if(p_arg < 32) 
    { set_plot_style(p_arg); } 
    else
    { set_point_type(char(p_arg)); set_plot_style(POINTS);} 
  
    create_plot(); 
  
    set_point_type(point_type_save);
    set_plot_style(plot_style_save);
    
} 

void UCplot::plot(double *y, long np, int p_style,  int p_arg)  
{ 
    X        = 0;  
    Y        = y;
    n_points = np; 
    fun      = 0; 
  
    if(auto_scale_flag == 1) set_range_to_min_max(); 

    char point_type_save = get_point_type();
    int  plot_style_save = get_plot_style();
    set_point_type(char(p_arg));
    set_plot_style(p_style); 
  
    create_plot(); 
  
    set_point_type(point_type_save);
    set_plot_style(plot_style_save);
}

   
void UCplot::plot(double *x, double *y, long np)
{
    X = x;
    Y = y;
    n_points = np;
    fun = 0;
    if(auto_scale_flag == 1) set_range_to_min_max();
    create_plot();
}
void UCplot::plot(double *x, double *y, long np,  int p_arg)
{
    X = x;
    Y = y;
    n_points = np;
    fun = 0;
    if(auto_scale_flag == 1) set_range_to_min_max();   

    char point_type_save = get_point_type();
    int  plot_style_save = get_plot_style();    
    if(p_arg < 32) 
    { set_plot_style(p_arg);} 
    else
    { set_point_type(char(p_arg)); set_plot_style(POINTS);} 
  
    create_plot(); 
  
    set_point_type(point_type_save);
    set_plot_style(plot_style_save);
}
void UCplot::plot(double *x, double *y, long np, int p_style,  int p_arg)
{
  
    X = x;
    Y = y;
    n_points = np;
    fun = 0;
    if(auto_scale_flag == 1) set_range_to_min_max();  

    char point_type_save = get_point_type();
    int  plot_style_save = get_plot_style();    
    set_point_type(char(p_arg));
    set_plot_style(p_style); 
  
    create_plot(); 
  
    set_point_type(point_type_save);
    set_plot_style(plot_style_save);
} 
    
void UCplot::plot(double (*f)(double x))
{
    X = 0;
    Y = 0;
    n_points = n_fun_points;
    fun = f;
    create_plot();
}  
 
void UCplot::plot(double (*f)(double x), int p_arg)
{
    X = 0;
    Y = 0;
    n_points = n_fun_points;
    fun = f;

    char point_type_save = get_point_type();
    int  plot_style_save = get_plot_style();    
    if(p_arg < 32) 
    { set_plot_style(p_arg);} 
    else
    { set_point_type(char(p_arg)); set_plot_style(POINTS);}  
  
    create_plot(); 
  
    set_point_type(point_type_save);
    set_plot_style(plot_style_save);
    
}  

void UCplot::plot(double (*f)(double x), int p_style,  int p_arg)
{ 
    X = 0;
    Y = 0;
    n_points = n_fun_points;
    fun = f;
    
    char point_type_save = get_point_type();
    int  plot_style_save = get_plot_style();    
    set_point_type(char(p_arg));
    set_plot_style(p_style); 
  
    create_plot(); 
  
    set_point_type(point_type_save);
    set_plot_style(plot_style_save);
} 
  
void UCplot::plot(double (*f)(double x), double x_min, double x_max)
{
    X = 0;
    Y = 0;
    n_points = n_fun_points;
    fun = f; 

    double xmin_save;
    double xmax_save;  
      
    if(auto_scale_flag == 0)
    { xmin_save = xmin; xmax_save = xmax;} 
    
    xmin             = x_min;
    xmax             = x_max; 
    
    create_plot(); 
    
    if(auto_scale_flag == 0)
    { xmin = xmin_save;xmax = xmax_save;}
    
}

void UCplot::plot(double (*f)(double x), double x_min, double x_max,  int p_arg) 
{
    X = 0;
    Y = 0;
    n_points = n_fun_points;
    fun = f;

    char point_type_save = get_point_type();
    int  plot_style_save = get_plot_style();    
    if(p_arg < 32) 
    { set_plot_style(p_arg);} 
    else
    { set_point_type(char(p_arg)); set_plot_style(POINTS);}  
    
    double xmin_save;
    double xmax_save;  
      
    if(auto_scale_flag == 0)
    { xmin_save = xmin; xmax_save = xmax;}
        
    xmin             = x_min;
    xmax             = x_max; 
    
    create_plot(); 
    
    if(auto_scale_flag == 0)
    { xmin = xmin_save;xmax = xmax_save;}
     
    set_point_type(point_type_save);
    set_plot_style(plot_style_save);
}

void UCplot::plot(double (*f)(double x), double x_min, double x_max, int p_style,  int p_arg) 
{
    X = 0;
    Y = 0;
    n_points = n_fun_points;
    fun = f;
    
    char point_type_save = get_point_type();
    int  plot_style_save = get_plot_style();    
    set_point_type(char(p_arg));
    set_plot_style(p_style); 
    
    double xmin_save;
    double xmax_save;  
      
    if(auto_scale_flag == 0)
    { xmin_save = xmin; xmax_save = xmax;}
    
    xmin             = x_min;
    xmax             = x_max; 
    
    create_plot(); 
    
    if(auto_scale_flag == 0)
    { xmin = xmin_save;xmax = xmax_save;}
    
    set_point_type(point_type_save);
    set_plot_style(plot_style_save);
}

void UCplot::plot(double (*f)(double x), double x_min, double x_max, double y_min, double y_max)
{
    X = 0;
    Y = 0;
    n_points = n_fun_points;
    fun = f; 
    
    int auto_flag_save = get_auto_scale_flag();
    set_auto_scale_flag(AUTO_OFF);
    
    double xmin_save;
    double xmax_save;
    double ymin_save;
    double ymax_save; 
    
    if(auto_scale_flag == 0)
    { xmin_save = xmin; xmax_save = xmax;
      ymin_save = ymin; ymax_save = ymax;} 
    
    xmin             = x_min;
    xmax             = x_max;
    ymin             = y_min;
    ymax             = y_max; 
    
    create_plot(); 
    
    if(auto_scale_flag == 0)
    {ymin = ymin_save; ymax = ymax_save;
     xmin = xmin_save; xmax = xmax_save;}
     
    set_auto_scale_flag(auto_flag_save);
    
}
void UCplot::plot(double (*f)(double x), double x_min, double x_max, double y_min, double y_max,  int p_arg)
{ 
    X = 0;
    Y = 0;
    n_points = n_fun_points;
    fun = f;

    char point_type_save = get_point_type();
    int  plot_style_save = get_plot_style();    
    if(p_arg < 32) 
    { set_plot_style(p_arg);} 
    else
    { set_point_type(char(p_arg)); set_plot_style(POINTS);} 

    double xmin_save;
    double xmax_save;
    double ymin_save;
    double ymax_save; 
    
    if(auto_scale_flag == 0)
    { xmin_save = xmin; xmax_save = xmax;
      ymin_save = ymin; ymax_save = ymax;}
           
    int auto_flag_save = get_auto_scale_flag();
    set_auto_scale_flag(AUTO_OFF);

      
    xmin             = x_min;
    xmax             = x_max;
    ymin             = y_min;
    ymax             = y_max; 
    
    create_plot();
     
    set_auto_scale_flag(auto_flag_save);

    if(auto_scale_flag == 0)
    {ymin = ymin_save; ymax = ymax_save;
     xmin = xmin_save; xmax = xmax_save;}
         
    set_point_type(point_type_save);
    set_plot_style(plot_style_save);
} 

void UCplot::plot(double (*f)(double x), double x_min, double x_max, double y_min, double y_max, int p_style,  int p_arg)
{
    X = 0;
    Y = 0;
    n_points = n_fun_points;
    fun = f;
    
    char point_type_save = get_point_type();
    int  plot_style_save = get_plot_style();    
    set_point_type(char(p_arg));
    set_plot_style(p_style); 
    
    double xmin_save;
    double xmax_save;
    double ymin_save;
    double ymax_save; 
    
    if(auto_scale_flag == 0)
    { xmin_save = xmin; xmax_save = xmax;
      ymin_save = ymin; ymax_save = ymax;} 
      
    int auto_flag_save = get_auto_scale_flag();
    set_auto_scale_flag(AUTO_OFF);

    xmin             = x_min;
    xmax             = x_max;
    ymin             = y_min;
    ymax             = y_max; 
    
    create_plot(); 

    set_auto_scale_flag(auto_flag_save);

    if(auto_scale_flag == 0)
    {ymin = ymin_save; ymax = ymax_save;
     xmin = xmin_save; xmax = xmax_save;}
         
    set_point_type(point_type_save);
    set_plot_style(plot_style_save);
}
   
   
    
