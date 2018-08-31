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
//                            (C) UCLA 1994, 1995
//********************************************************************************
//
#ifndef _UCGRAPH_
#define _UCGRAPH_
#include "ucdriver.h"
class UCgraph
{
public: 
//
//  Constructors
// 
    UCgraph( const UCgraph& A);
    
    UCgraph(UCdriver *d);
//
    ~UCgraph()
     {if(font!=0) delete [] font; if(text_rgb !=0) delete [] text_rgb;}
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
//
    void draw_string(double x, double y, char *s, double size = 0);
    void title(char *s, double size = 0);
//
//  Text Style Manipulation Routines
//
    void   set_font(char *f);
    char*  get_font();    
    
    void   set_text_size(double s) { text_size = s; }    
    double get_text_size()         { return text_size; }  
    
    void   set_text_align(double h, double v)
           { horiz_just = h; vert_just = v; }
                      
    void   get_text_align(double &h, double &v)
           { h = horiz_just; v = vert_just; }   
            
    void   set_text_angle(int a) { text_angle = a; }
    int    get_text_angle()      { return text_angle; }

    void   set_text_color(int c, double *rgb = 0)
           { text_color = c; text_rgb = rgb; };   
      
    int    get_text_color(){ return text_color; }
    int    get_text_color(double *&rgb)
           { if (text_color == USER_RGB) rgb = text_rgb; else rgb = 0;
             return text_color; };
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

    char*   font;
    double  text_size;
    double  horiz_just;
    double  vert_just;
    int     text_angle;
    int     text_color;    //  One of the enumerated types below
    double* text_rgb;      //  Color if text_color == USER_RGB
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
        
    int get_graphics_low_color(int c);
    int get_graphics_low_dash(int d);
};
#endif
 
