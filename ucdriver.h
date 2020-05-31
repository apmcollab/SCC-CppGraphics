//
//###########################################################################
//                              UCDRIVER.H
//###########################################################################
// 
//                  HEADER FILE FOR CLASS UCdriver          
//
//###########################################################################
//
//            Initial Version             : David Sansot
//            Additions and Modifications : Chris Anderson 
//
//                            (C) UCLA 1994, 1995, 2004
//###########################################################################
//

#ifndef UCDRIVER_
#define UCDRIVER_  

#include <string>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <cstdlib>

//
// strcpy_s is not implemented as part of C++11 (arrgh) so this macro
// inserts strcpy calls.
//

#ifdef _MSC_VER
#define COPYSTR(dst,count,src) strcpy_s(dst,count,src)
#else
#define COPYSTR(dst,count,src) strcpy(dst,src)
#endif

#define DEFAULT_INSTANCE  "graph.out"

/**
   \class UCdriver
   \brief A virtual base class for two dimensional graphics.

    This class is extended to support different output devices
    (e.g. to a display window or PostScript file). Creating higher
    level graphics classes that utilize UCdriver methods enables the
    graphics output to be rendered on multiple output devices. 
    <p>
    The input coordinates to the graphics routines are assumed to be
    in the "normalized" drawing range [0,1]x[0,1].<p>
    
<i>Source</i>: 
<A HREF="../UCdriver.h">UCdriver.h</A><p>

@author David Sansot, Chris Anderson (C) UCLA 1994-2009
@version 1/31/09 
*/
class UCdriver
{

public:

//
//###########################################################################
//                      CONSTRUCTOR       
//###########################################################################

/** 
    Constructor, implements appropriate low level initialization for 
    the graphics system.

    The character string argument allows one to pass a name 
    (such as a file name) to the initialization routines.
    There is a default definition for this constructor 
    i.e. it is not a virtual function.

    
    @param s A character string to be 
    passed to initialization routine (e.g. a file name). 
*/
UCdriver(const char *s = 0)
{
    instance = 0;
    if (s)
    {
      instance = new char[strlen(s) + 1];
      //strcpy(instance,s);
      COPYSTR(instance,strlen(s) + 1,s);
    }
    else
    {
      instance = new char[strlen(DEFAULT_INSTANCE) + 1];
      //strcpy(instance,DEFAULT_INSTANCE);
      COPYSTR(instance,strlen(DEFAULT_INSTANCE) + 1,DEFAULT_INSTANCE);
    }
    dTypeName = 0;
    setDriverTypeName("UCdriver");
};
//
//###########################################################################
//                          DESTRUCTOR       
//###########################################################################
//
/**
    Destructor, shuts down, or cleans up, the graphics system. 
*/ 
virtual ~UCdriver(){if(instance != 0) delete [] instance; if(dTypeName != 0) delete [] dTypeName;};
    
//
//###########################################################################
//                          SETDRIVERTYPENAME
//###########################################################################
//
/**
    Sets the name of the graphics driver. The default driver name is "UCdriver". 
    @param dName Character string specifying the driver name. 
*/ 
virtual void setDriverTypeName(const char* dName)
{
    if(dTypeName != 0) delete [] dTypeName;
    if((dName != 0)&&(strlen(dName) != 0))
    {
    dTypeName = new char[strlen(dName) + 1];
    }
    //strcpy(dTypeName,dName);
    COPYSTR(dTypeName,strlen(dName) + 1,dName);
}
/**
    Returns the name of the graphics driver. 
*/ 
virtual const char* getDriverTypeName()
{
 return dTypeName;
}
 
//
//###########################################################################
//                          LINE       
//###########################################################################
//
/**
    Draws a line between the points (x1, y1) and (x2,y2).  
    
    <p>
    @param x1 The x-coordinate of 1st point (a value in [0,1])

    @param y1 The y-coordinate of 1st point (a value in [0,1])

    @param x2 The x-coordinate of 2nd point (a value in [0,1])

    @param y2 The y-coordinate of 2nd point (a value in [0,1])

    @param dash_pattern One of the enumerated dash constants. 
    A value of 0 (default) for dash_pattern corresponds to a solid line. 
    If equal to USER_DASH then the parameter user_pattern sets the dash pattern.

    @param user_pattern The last two bytes of this parameter are used to 
    represent the dash pattern if dash_pattern = USER_DASH.

    @param width  The width of the line as a fraction of the drawing window
    width.  For example, in the PostScript representation the
    default is 0.001.  Passing a value of 0 for width causes the
    default to be used.

    @param color One of the enumerated color constants values 
    specifying the color of the line. 
    If color == 0 the default color is used. 
    If color == USER_RGB then the parameter RGB is used to set the color.  
    
    @param RGB a three element double array with values between
    0 and 255 specifying the red, green and blue components of the color. 
    This parameter is only used if color == USER_RGB. 

*/
virtual void line(double x1, double y1, double x2, double y2,
                  int dash_pattern, unsigned user_pattern, double width,
                  int color, double *RGB) = 0; 

//
//###########################################################################
//                          LINES       
//###########################################################################
//
/**
    Draws a connected set of line segments. The segment endpoints 
    are specified by (X[0],Y[0]), (X[1],Y[1]), ..., (X[npoints-1],Y[npoint-1]). 
  
    <p>
    @param X A double array of the x-coordinates of the segment endpoints (values in [0,1])

    @param Y A double array of the y-coordinates of the segment endpoints (values in [0,1])

    @param npoints The number of segment endpoints (typically the size of the X and Y arrays).

    @param dash_pattern One of the enumerated dash constants. 
    A value of 0 (default) for dash_pattern corresponds to a solid line. 
    If equal to USER_DASH then the parameter user_pattern sets the dash pattern.

    @param user_pattern The last two bytes of this parameter are used to 
    represent the dash pattern if dash_pattern = USER_DASH.

    @param width  The width of the line as a fraction of the drawing window
    width.  For example, in the PostScript representation the
    default is 0.001.  Passing a value of 0 for width causes the
    default to be used.

    @param color One of the enumerated color constants values 
    specifying the color of the line. 
    If color == 0 the default color is used. 
    If color == USER_RGB then the parameter RGB is used to set the color.  
    
    @param RGB A three element double array with values between
    0 and 255 specifying the red, green and blue components of the color.  
*/
virtual void lines(double *X, double *Y, long npoints,
                  int dash_pattern, unsigned user_pattern, double width,
                  int color, double *RGB) = 0;

//
//###########################################################################
//                          POINT       
//###########################################################################
//
/**
    Draws the character c at a point.  

    <p>
    @param x  The x-coordinate of the point (a value in [0,1])

    @param y  The y-coordinate of the point (a value in [0,1])

    @param c  The character to be drawn

    @param font A character string specifying the font to be used. 
    If font == 0 the default font is used. 

    @param size  The relative size of the character with respect to 
    the drawing window. If size == 0, the default size value is used. 

    @param color One of the enumerated color constants values 
    specifying the color of the line. 
    If color == 0 the default color is used. 
    If color == USER_RGB then the parameter RGB is used to set the color.  
    
    @param RGB A three element double array with values between
    0 and 255 specifying the red, green and blue components of the color.  
 
*/
virtual void point(double x, double y, char c, const char *font,
                     double size, int color, double *RGB) = 0;
//
//###########################################################################
//                          POINTS       
//###########################################################################
//  
/**
  Draws the character c at a collection of points. The coordinates of the points
  are specfied by the values in the X and Y arrays; e.g. 
  (X[0],y[0]), (X[1],Y[1]), ..., (X[npoint-1],Y[npoints-1]).

    <p>
    @param X A double array of the x-coordinates of point locations (values in [0,1])

    @param Y A double array of the y-coordinates of point locations (values in [0,1])

    @param npoints The number of points (typically the size of the X and Y arrays).

    @param c The character to be drawn

    @param font A character string specifying the font to be used. 
    If font == 0 the default font is used. 

    @param size  The relative size of the character with respect to 
    the drawing window. If size == 0, the default size value is used. 

    @param color One of the enumerated color constants values 
    specifying the color of the line. 
    If color == 0 the default color is used. 
    If color == USER_RGB then the parameter RGB is used to set the color.  
    
    @param RGB a three element double array with values between
    0 and 255 specifying the red, green and blue components of the color.  
 

*/
  
virtual void points(double *X, double *Y, long npoints, char c,
                      const char *font, double size, int color,
                      double *RGB) = 0;

//
//###########################################################################
//                          TEXT       
//###########################################################################
//
/**
    Draws the string s at the reference point (x,y). 
    
    <p>
    @param x  The x-coordinate of the point (a value in [0,1])

    @param y  The y-coordinate of the point (a value in [0,1])

    @param s  A character string containing the characters to be drawn. 

    @param font A character string specifying the font to be used. 
    If font == 0 the default font is used. 

    @param size  The relative size of the characters with respect to 
    the drawing window. If size == 0, the default size value is used. 

    @param rotation The rotation of the string about the
    reference point in a counterclockwise direction. The angle is 
    specified in degrees.

    @param horiz_just The horizontal alignment of the string about the
    reference point. A values of 0 causes the string to be horizontally 
    centered about the reference point. A value of -1 causes the left 
    edge of the string to be lined up with the reference point, a 
    value of 1 lines up the right edge, and any other value the
    interpolation of these.  For example,  -0.5 causes the reference point
    to be located a forth of the string from the left edge of the
    string. Alignment is performed before any rotation.

    @param vert_just The vertical alignment of the string about the
    reference point. A values of 0 causes the
    string to be vertically centered about the reference point.
    A value of -1 causes the top  edge of the string to be lined up with 
    the reference point, a value of 1 lines up the bottom edge, 
    and any other value the interpolation of these.  
    For example,  -0.5 causes the reference point to be located a forth of 
    the string from the top edge of the string. 
    Alignment is performed before any rotation.
    
    @param color One of the enumerated color constants values 
    specifying the color of the line. 
    If color == 0 the default color is used. 
    If color == USER_RGB then the parameter RGB is used to set the color.  
    
    @param RGB A three element double array with values between
    0 and 255 specifying the red, green and blue components of the color.  

*/
virtual void text(double x, double y, const char *s, const char *font,
                    double size, double rotation, double horiz_just,
                    double vert_just, int color, double *RGB) = 0;
/**
    Draws a filled polygonal region whose vertices are 
    are specified by (X[0],Y[0]), (X[1],Y[1]), ..., (X[npoints-1],Y[npoint-1]),(X[0],Y[0]) 

    Note : The first point is not repeated in the polygonal list. 
  
    <p>
    @param X A double array of the x-coordinates of the polygon vertices (values in [0,1])

    @param Y A double array of the y-coordinates of the polygon vertices (values in [0,1])

    @param npoints The number of segment endpoints (typically the size of the X and Y arrays).
    
    @param RGB A three element double array with values between
    0 and 255 specifying the red, green and blue components of the color.  
*/
virtual void region(double *X, double *Y, long npoints, double *RGB) = 0;


//
//###########################################################################
//                          FRAME()      
//###########################################################################
//
/**
   Clears the screen or advances the page.
*/
virtual void frame() = 0; 
//
//###########################################################################
//                      ENUMERATED CONSTANTS       
//###########################################################################
//
//                        Dash patterns 
//
/**
SOLID, DASH, DOUBLE_DASH, DASH_DOT,DASH_DOUBLE_DOT,DOTS, USER_DASH
*/
  enum dashConstants{SOLID, DASH, 
  DOUBLE_DASH, DASH_DOT,DASH_DOUBLE_DOT,DOTS, USER_DASH};

//                           Colors 
/** 
BLACK, DARK_GREY, LIGHT_GREY, BLUE, LIGHT_BLUE, GREEN,
LIGHT_GREEN, CYAN, LIGHT_CYAN,  RED, LIGHT_RED, MAGENTA,LIGHT_MAGENTA, ORANGE,
YELLOW, WHITE, USER_RGB.
*/
  enum colorConstants{BLACK, DARK_GREY, LIGHT_GREY, BLUE, LIGHT_BLUE, GREEN,
        LIGHT_GREEN, CYAN, LIGHT_CYAN, RED, LIGHT_RED, MAGENTA,
        LIGHT_MAGENTA, ORANGE, YELLOW, WHITE, USER_RGB};

protected :

  char *instance;          //  The name of the instance.  In the case of the
                           //  PostScript driver, this is used as the file
                           //  name.

  char *dTypeName;         //   Name of the driver class

};
#endif 


