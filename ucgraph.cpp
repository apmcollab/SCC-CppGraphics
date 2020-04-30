//
//******************************************************************************
//                              UCGRAPH.CPP
//******************************************************************************
// 
//            SOURCE FILE FOR CLASS UCgraph
//
//********************************************************************************
//
//            David Sansot              (C) UCLA 1994,1995
//            Chris Anderson             Modifications 1995
//********************************************************************************
// 
#include "ucgraph.h"
#include <string>
#include <iostream>
using namespace std;

//
//******************************************************************************
//                         COPY CONSTRUCTOR
//******************************************************************************
// 
UCgraph::UCgraph(const UCgraph& A)
{ 
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
    if(A.font != 0)
    { font = new char[strlen(A.font) + 1];
      strcpy(font,A.font);}
    else
    {font = 0;}
//  
    text_size  = A.text_size;
    horiz_just = A.horiz_just;
    vert_just  = A.vert_just;
    text_angle = A.text_angle;
    text_color = A.text_color; 
//    
    if(A.text_rgb != 0)
    { 
      text_rgb = new double[3];
      text_rgb[0] = A.text_rgb[0];
      text_rgb[1] = A.text_rgb[1];
      text_rgb[2] = A.text_rgb[2];
    }
    else
    {text_rgb = 0;}
}  
//
//******************************************************************************
//                 UCgraph(UCdriver *driver)
//******************************************************************************
//   
UCgraph::UCgraph(UCdriver *driver)
{
  drv = driver;

  frame_l = 0.14; frame_b = 0.1;
  frame_r = 0.94; frame_t = 0.9;

  font = 0;
  text_size = 0.05;
  horiz_just = vert_just = 0;
  text_angle = 0;
  text_color = 0;
  text_rgb = 0;
}
//
//********************************************************************************
//              PUBLIC MEMBER FUNCTIONS 
//********************************************************************************
//
//
//********************************************************************************
//              DRAW_STRING
//********************************************************************************
//
void UCgraph::draw_string(double x, double y, const char* s, double size)
{ 
//
//    Draws string s using x,y as reference point in present color,
//    font, angle, and justification.  The string is drawn in the
//    size given by size unless size == 0, in which case
//    text_size is used.  The variables x, y, and size are all
//    scaled to the frame.  There are no side effects.

//    If size is specified, internal variable text_size is not changed

  double scale = ((frame_r - frame_l) < (frame_t - frame_b)) ?
  (frame_r - frame_l) : (frame_t - frame_b);
  double scaled_size = ((size) ? size : text_size)*scale;
  double scaled_x = frame_l + x*(frame_r - frame_l);
  double scaled_y = frame_b + y*(frame_t - frame_b);

  drv->text(scaled_x, scaled_y, s, font, scaled_size, text_angle,
           horiz_just, vert_just, text_color, text_rgb);
}
//
//********************************************************************************
//              TITLE
//********************************************************************************
//
void UCgraph::title(const char* s, double size)
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
//
//
    if(strcmp("CAMjavaDriver",drv->getDriverTypeName()) == 0)
    {
    draw_string(0.5, 1.1, s, (size) ? size : 0.05);
    }
    else if(strcmp("QDriver",drv->getDriverTypeName()) == 0)
    {
    draw_string(0.5, 1.1, s, (size) ? size : 0.05);
    }
    else
    {
	draw_string(0.5, 1.05, s, (size) ? size : 0.05);
    }

    set_text_align(h, v);
    set_text_angle(a);
}
//
//********************************************************************************
//              SET_FONT
//********************************************************************************
//
void UCgraph::set_font(const char* f)
{
  if (font) delete font;

  if (f)
  {
    font = new char[strlen(f) + 1];
    strcpy(font,f);
  }
  else
    font = 0;
}
//
//********************************************************************************
//              GET_FONT
//********************************************************************************
//
char* UCgraph::get_font()
{
  if (font)
  {
    char* s = new char[strlen(font) + 1];
    strcpy(s,font);
    return s;
  }
  else
    return 0;
}
//
//********************************************************************************
//              GET_GRAPHICS_LOW_COLOR
//********************************************************************************
//
int UCgraph::get_graphics_low_color(int c)
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
int UCgraph::get_graphics_low_dash(int d)
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




 
