//
//******************************************************************************
//                              UCDRIV_PS.H
//******************************************************************************
// 
//                  HEADER FILE FOR CLASS UCdriver_ps          
//
//********************************************************************************
//
//            Initial Version             : David Sansot
//            Small Modifications         : Chris Anderson 
//
//                            (C) UCLA 1994, 1995
//********************************************************************************
//
#ifndef UCDRIVER__PS_
#define UCDRIVER__PS_

#include "camgraphimpexp.h"

#include <fstream>

#include "ucdriver.h"

#define DEFAULT_LINE_WIDTH  0.001
#define DEFAULT_FONT  "Times-Roman"
#define DEFAULT_FONT_SIZE .05

#define PICTURE_WIDTH   468 // in points -- 72 points = 1 inch
#define PICTURE_HEIGHT  468

class __IMPEXP__ UCdriver_ps : public UCdriver
{
public:

    UCdriver_ps(const char* s = 0);
    ~UCdriver_ps();

    void lines(double *x, double *y, long npoints, int dash_pattern,
           unsigned user_pattern, double width, int color, double *RGB);

    void line(double x1, double y1, double x2, double y2,
            int dash_pattern, unsigned user_pattern, double width,
            int color, double *RGB);

    void point(double x, double y, char p, const char* font, double size,
             int color, double *RGB);
    void points(double *X, double *Y, long np, char p, const char* font,
              double size, int color, double *RGB);

    void text(double x, double y, const char* s, const char* font, double size,
            double rotation, double horiz_just, double vert_just,
            int color, double *RGB);

    void region(double *X, double *Y, long npoints, double *RGB);

    void frame();
//
//  Make All of the Data and Routines of This Class Public To Facilitate
//  Incorporation in Other Routines Which Require PostScript Output
//
//  Internal Data
//
    std::ofstream fout;

// variables and flags for internal use   

    int page;

    short page_not_setup;
    short page_not_framed;

    short line_not_stroked;
    double last_x;
    double last_y;

    short pres_color;
    double pres_RGB[3];
    short pres_dash;
    int pres_user_pattern;
    double pres_line_width;

    char* pres_font;
    double pres_font_size;
//
// Internal Helper Functions
//
    void setup_page();
    void do_dash(int dash_pattern, int user_pattern);
    void do_line_width(double width);
    void do_color(int color, double *RGB);
    void do_font(const char* f, double s);
    void stroke_line();
};
#endif
 
