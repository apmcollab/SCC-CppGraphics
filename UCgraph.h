//
//******************************************************************************
//                              UCGRAPH.H
//******************************************************************************
// 
//                  HEADER FILE FOR CLASS UCgraph      
//
//********************************************************************************
//
//            Initial Version             : David Sansot
//            Additions and Modifications : Chris Anderson 
//
//                            (C) UCLA 1994, 1995,2023
//********************************************************************************
//
#include <vector>
#include <string>

#ifndef UCGRAPH_
#define UCGRAPH_

#include "UCdriver.h"

class UCgraph
{
public:

//
//  Enumerated Constants
//
//  colors

    enum {BLACK, DARK_GREY, LIGHT_GREY, BLUE, LIGHT_BLUE, GREEN,
          LIGHT_GREEN, CYAN, LIGHT_CYAN, RED, LIGHT_RED, MAGENTA,
          LIGHT_MAGENTA, ORANGE, YELLOW, WHITE, USER_RGB};

    enum {DASH = 1, DOUBLE_DASH, DASH_DOT, DASH_DOUBLE_DOT, DOTS,
          USER_DASH};
//
//  Constructors
// 
	UCgraph() {initialize();}

    UCgraph(const UCgraph& A)
    {initialize(A);}

    UCgraph(UCdriver *driver)
    {
    	initialize();
    	drv = driver;
    }

    virtual ~UCgraph() {}

    void initialize()
	{
      font.clear();

      text_rgb.clear();
      text_rgb.resize(3,0.0);

      line_rgb.clear();
      line_rgb.resize(3,0.0);

      drv      = 0;

      frame_l = 0.14; frame_b = 0.1;
      frame_r = 0.94; frame_t = 0.9;

      text_size = 0.05;
      horiz_just = vert_just = 0;
      text_angle = 0;
      text_color = UCgraph::BLACK;
      line_color = UCgraph::BLACK;
	}


    void initialize(const UCgraph& A)
    {
	initialize();
//
//  Do a shallow copy of the UCdriver pointer
//
    drv = A.drv;
//
    frame_l = A.frame_l;
    frame_b = A.frame_b;
    frame_r = A.frame_r;
    frame_t = A.frame_t;
//
    font = A.font;
//
    text_size  = A.text_size;
    horiz_just = A.horiz_just;
    vert_just  = A.vert_just;
    text_angle = A.text_angle;
    text_color = A.text_color;
    text_rgb   = A.text_rgb;
    line_color = A.line_color;
    line_rgb   = A.line_rgb;
    }

//
//  Graphics Driver Manipulation Routine
//
    void set_driver_ptr(UCdriver *d) { drv = d;}
    UCdriver *get_driver_ptr() {return drv;}
//
//  Frame Manipulation Routine
//
    void   set_frame(double fl, double fr, double fb, double ft)
           { if (frame_r > frame_l && frame_t > frame_b)
           { frame_l = fl; frame_r = fr; frame_b = fb; frame_t = ft;}}
         
    void   get_frame(double &fl, double &fr, double &fb, double &ft)
           { fl = frame_l; fr = frame_r; fb = frame_b; ft = frame_t; }
//           
//  Text Drawing routines  

void draw_string(double x, double y, std::string s, double size = 0)
{
    //
    //    Draws string s using x,y as reference point in present color,
    //    font, angle, and justification.  The string is drawn in the
    //    size given by size unless size == 0, in which case
    //    text_size is used.  The variables x, y, and size are all
    //    scaled to the frame.  There are no side effects.

    //    If size is specified, internal variable text_size is not changed

	double scale = ((frame_r - frame_l) < (frame_t - frame_b)) ? (frame_r - frame_l) : (frame_t - frame_b);
	double scaled_size = ((size) ? size : text_size)*scale;
	double scaled_x = frame_l + x*(frame_r - frame_l);
	double scaled_y = frame_b + y*(frame_t - frame_b);

	drv->text(scaled_x, scaled_y, s, font, scaled_size, text_angle,
           horiz_just, vert_just, text_color, text_rgb);
}

void title(std::string s, double size)
{

//    Title draws the string s centered above the frame in the
//    present color and font.  The string is drawn in the size
//    given by size unless size == 0, in which case 0.05 is used
//    for the size.  There are no side effects.

//  Save text variables for resetting

    double h, v;
    get_text_align(h, v);
    int a = get_text_angle();

    set_text_align(0,1);
    set_text_angle(0);

	draw_string(0.5, 1.05, s, (size) ? size : 0.05);

    set_text_align(h, v);
    set_text_angle(a);
}


//
//********************************************************************************
//              GET_GRAPHICS_LOW_COLOR
//********************************************************************************
//
int get_graphics_low_color(int c)
{
  int nc;

  switch (c)
  {
    case BLACK:         nc = drv->BLACK;         break;
    case DARK_GREY:     nc = drv->DARK_GREY;     break;
    case LIGHT_GREY:    nc = drv->LIGHT_GREY;    break;
    case BLUE:          nc = drv->BLUE;          break;
    case LIGHT_BLUE:    nc = drv->LIGHT_BLUE;    break;
    case GREEN:         nc = drv->GREEN;         break;
    case LIGHT_GREEN:   nc = drv->LIGHT_GREEN;   break;
    case CYAN:          nc = drv->CYAN;          break;
    case LIGHT_CYAN:    nc = drv->LIGHT_CYAN;    break;
    case RED:           nc = drv->RED;           break;
    case LIGHT_RED:     nc = drv->LIGHT_RED;     break;
    case MAGENTA:       nc = drv->MAGENTA;       break;
    case LIGHT_MAGENTA: nc = drv->LIGHT_MAGENTA; break;
    case ORANGE:        nc = drv->ORANGE;        break;
    case YELLOW:        nc = drv->YELLOW;        break;
    case WHITE:         nc = drv->WHITE;         break;
    case USER_RGB:      nc = drv->USER_RGB;      break;
    default:            nc = drv->BLACK;         break;
  }

  return nc;
}
//
//********************************************************************************
//              GET_GRAPHICS_LOW_DASH
//********************************************************************************
//
int get_graphics_low_dash(int d)
{
  int nd;

  switch (d)
  {
    case DASH:            nd = drv->DASH;            break;
    case DOUBLE_DASH:     nd = drv->DOUBLE_DASH;     break;
    case DASH_DOT:        nd = drv->DASH_DOT;        break;
    case DASH_DOUBLE_DOT: nd = drv->DASH_DOUBLE_DOT; break;
    case DOTS:            nd = drv->DOTS;            break;
    case USER_DASH:       nd = drv->USER_DASH;       break;
    default:              nd = 0;                    break;  // solid line
  }

  return nd;
}
//
//  Text Style Manipulation Routines
//
    
void set_font(const std::string f) {font = f;}
std::string get_font()             {return font;}

    void   set_text_size(double s) { text_size = s; }    
    double get_text_size()         { return text_size; }  
    
    void   set_text_align(double h, double v)
           { horiz_just = h; vert_just = v; }
                      
    void   get_text_align(double &h, double &v)
           { h = horiz_just; v = vert_just; }   
            
    void   set_text_angle(int a) { text_angle = a; }
    int    get_text_angle()      { return text_angle; }

    /////////////////////ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ

    void  set_text_color(int c)
    {
    	     text_color = c;
             if (text_color == USER_RGB)
             {
             text_rgb[0] = 0.0;
             text_rgb[1] = 0.0;
             text_rgb[2] = 0.0;
             }
    };
      
    int get_text_color(){ return text_color;}

    void set_text_rgb(const std::vector<double>& rgb)
    {
    	text_color = USER_RGB;
    	text_rgb   = rgb;
    }

    std::vector<double> get_text_rgb()
    {return text_rgb;};



    void set_line_color(int c)
    {
    line_color = c;
    if (line_color == USER_RGB)
    {
             line_rgb[0] = 0.0;
             line_rgb[1] = 0.0;
             line_rgb[2] = 0.0;
    }}

    int  get_line_color(){return line_color;}


    void set_line_rgb(const std::vector<double>& rgb)
    {
      line_color = USER_RGB;
      line_rgb = rgb;
    }

    std::vector<double> get_line_rgb()
    {return line_rgb;}


//
protected: 
//
//  Internal Data Elements
//  
//  Pointer to the UCdriver class or derived class   

    UCdriver *drv;

//  Frame  -  portion of the window to draw to  

    double frame_l;
    double frame_r;
    double frame_b;
    double frame_t;

//  Text drawing info 

    std::string  font;
    double  text_size;
    double  horiz_just;
    double  vert_just;
    int     text_angle;

    int               text_color;      //  One of the enumerated types below
    std::vector<double> text_rgb;      //  Color if text_color == USER_RGB

    int              line_color;       //  One of the enumerated types below
    std::vector<double> line_rgb;      //  Color if line_color == USER_RGB
//
//  Internal Helper functions
//
    double scale_to_frame_width(double x)
        { return x*(frame_r - frame_l);}
    double frame_2_screen_x(double x)
        { return (frame_l + x*(frame_r - frame_l)); }
    double scale_to_frame_height(double y)
        { return y*(frame_t - frame_b);}
    double frame_2_screen_y(double y)
        { return (frame_b + y*(frame_t - frame_b)); }  
        
};
#endif
 
