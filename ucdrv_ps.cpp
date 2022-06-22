//
//******************************************************************************
//                              UCDRIV_PS.CPP
//******************************************************************************
// 
//            SOURCE FILE FOR CLASS UCdriver_ps
//
//********************************************************************************
//            David Sansot                (C) UCLA 1994
//
//            Chris Anderson         Modifications 8/30/2000
//
//                                   Removed bounding frame, and set lower left
//                                   corner of bounding box to (0,0) to avoid 
//                                   problems converting the PostScript to gif's
//
//                                   Modifications 10/07/2002
//                                   Changed the page counting so that  
//                                   ghostview wouldn't complain. 
//    
//                                   Modifications 4/08/04
//                                   Fixed font string allocation bug. Enabled
//                                   the specification of default font using a 
//                                   null string in addition to a 0 valued pointer.
//                                   Corrected problems with default font size.
//
//********************************************************************************
//  
#include "ucdrv_ps.h"
#include "camgraphexit.h"
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
#include <cmath>

//
// strcpy_s is not implemented as part of C++11 (arrgh) so this macro
// inserts strcpy calls.
//

#ifdef _MSC_VER
#define COPYSTR(dst,count,src) strcpy_s(dst,count,src)
#else
#define COPYSTR(dst,count,src) strcpy(dst,src)
#endif
//
//******************************************************************************
//                         UCdriver_ps(char *s)
//******************************************************************************
//
UCdriver_ps::UCdriver_ps(const char *s) : UCdriver(s)
{
  //  Initialize internally used variables
  page = 0;
  page_not_setup = 1;
  page_not_framed = 0;
  line_not_stroked = 0;
  last_x = last_y = 0;
  pres_color = pres_dash = 0;
  pres_RGB[0] = pres_RGB[1] = pres_RGB[2] = 0;
  pres_user_pattern = 0;
  pres_line_width = DEFAULT_LINE_WIDTH;

  pres_font = 0;
  pres_font_size  = DEFAULT_FONT_SIZE;


//  Set up file and write need info to file

// Open file for output
  fout.open(instance);
  fout.precision(4);  //  Set precision to 5 decimal places

  if (!fout)
  {
    std::cerr << "Trouble opening file for graphics output - Exiting \n";
    CAMgraphicsExit();
  }

    //  Get the time to add to the file
  struct tm *t_ptr;
  time_t t = time(0);
  t_ptr = localtime(&t);

    //  This stuff determines the bounding box
  int lmarg = (612 - PICTURE_WIDTH)/2;
  int bmarg = (792 - PICTURE_HEIGHT)/2;

    //  Write header
  fout
   << "%!PS-Adobe-3.0 \n"
   << "%%Creator: UCLA++ Class Libraries PostScript Driver"  << std::endl;
  fout
   << "%%CreationDate: " << asctime(t_ptr)
   << "%%Title: " << instance << std::endl
   //
   // remove the bounding box margin (it messes up conversion to gif's)
   // CRA 8/30/2000
   // << "%%BoundingBox: " << lmarg << " " << bmarg << " "

   << "%%BoundingBox: " << 0 << " " << 0 << " "
                        << int(lmarg + PICTURE_WIDTH) << " "
                        << int(bmarg + PICTURE_HEIGHT) << std::endl;
  fout << "%%Orientation: Portrait" 
   << "%%Pages: (atend) \n"
   << "%%EndComments " << std::endl << std::endl; 

    //  Write prolog
  fout
   << "%%BeginProlog \n"
   << "/UC_Dict 50 dict def \n"
   << "UC_Dict begin \n"
   << "   %  Renaming of routines for saving file space \n"
   << "/c { closepath } def \n"
   << "/gr { grestore } def \n"
   << "/gs { gsave } def \n"
   << "/l { lineto } def \n";
  fout << "/m { moveto } def \n"
   << "/n { newpath } def \n"
   << "/r { rotate } def \n"
   << "/s { stroke } def \n"
   << "/sd { setdash } def \n"
   << "/sh { show } def \n"
   << "/slw { setlinewidth } def \n"
   << "/sw { stringwidth } def \n"
   << "/t { translate } def \n" << std::endl;

  fout
   << "   %  Routine scales and set the font - space saver \n"
   << "   %    input - font, font_size  :  output - none \n"
   << "/fssf { exch findfont exch scalefont setfont } def \n";

  fout
   << "   %  Routine determines the height and depth of a char \n"
   << "   %    input - char  :  output - lly, ury \n"
   << "/ch { \n"
   << "  gs n \n"
   << "  0 0 m \n"
   << "  false charpath \n"
   << "  flattenpath \n"
   << "  pathbbox \n"
   << "  exch pop \n"
   << "  3 -1 roll pop \n"
   << "  gr \n"
   << "} def \n";

  fout
   << "   %  Routine determines height and depth of a string \n"
   << "   %    input - string, output - bot, top \n"
   << "/strh { \n"
   << "  /lly 0.0 def \n"
   << "  /ury 0.0 def \n"
   << "  { \n"
   << "    ( ) dup 0 4 -1 roll put \n"
   << "    ch \n"
   << "    dup ury gt \n"
   << "      { /ury exch def } \n"
   << "      { pop } ifelse \n"
   << "    dup lly lt \n"
   << "      { /lly exch def } \n"
   << "      { pop } ifelse \n"
   << "  } forall \n"
   << "  lly ury \n"
   << "} def \n";

  fout
   << "   %  Routines for determining offsets used for justification \n"
   << "   %    input - factor, string,  output - offset \n"
   << "/xoff { sw pop 2 div mul } def \n"
   << "/yoff { strh add 2 div mul } def \n" << std::endl;

  fout
   << "end % end UC_Dict \n" << std::endl;

  fout
   << "/UC_Page_Begin { UC_Dict begin /UC_State save def } def \n"
   << "/UC_Page_End { UC_State restore end } def \n";

  fout << "%%EndProlog \n \n" << std::endl;
}
//
//******************************************************************************
//                         ~UCdriver_ps
//******************************************************************************
//
UCdriver_ps::~UCdriver_ps()
{
  if (line_not_stroked) stroke_line();

  if (page_not_framed) frame();

  // Changed 10/07/02 
  // because it seemed to want the Pages after EOF marker
  // fout << "%%Pages: " << page << std::endl;
  // fout << "%%EOF";

  fout << "%%EOF"  << std::endl;
  fout << "%%Pages: " << page << std::endl;

  fout.close(); 

  if (pres_font) delete [] pres_font;
}
//
//******************************************************************************
//                         LINES
//******************************************************************************
//
void UCdriver_ps::lines (double *x, double *y, long npoints,
                          int dash_pattern, unsigned user_pattern,
                          double width, int color, double *RGB)
{
  if (npoints < 2)             //  Not enough points
    return;

  if (page_not_setup)          //  set up defaults
    setup_page();

  if (line_not_stroked) stroke_line();

  if (width == 0) width = DEFAULT_LINE_WIDTH;

    // Set up dash pattern
  if (dash_pattern != pres_dash)   // dash_pattern == 0 means solid line
    do_dash(dash_pattern, user_pattern);

  if (width != pres_line_width)
    do_line_width(width);

  if (color != pres_color || color == USER_RGB)
    do_color(color, RGB);

  fout << "n \n";
  fout << *x << " " << *y << " m \n";
  x++;
  y++;

  while (--npoints)
  {
    fout << *x << " " << *y << " l \n";
    x++;
    y++;
  }

  fout << "s \n \n";
}
//
//******************************************************************************
//                         LINE
//******************************************************************************
//
void UCdriver_ps::line(double x1, double y1, double x2, double y2,
                        int dash_pattern, unsigned user_pattern, double width,
                        int color, double *RGB)
{
  if (page_not_setup)          //  set up defaults
    setup_page();

  if (width == 0) width = DEFAULT_LINE_WIDTH;

  if (dash_pattern != pres_dash || dash_pattern == USER_DASH)
    do_dash(dash_pattern, user_pattern);

  if (width != pres_line_width)
    do_line_width(width);

  if (color != pres_color || color == USER_RGB)
    do_color(color, RGB);


  if (line_not_stroked)
  {
    if (last_x != x1 || last_y != y1)
    {
      stroke_line();
      fout << x1 << " " << y1 << " m \n";
    }
  }
  else
    fout << x1 << " " << y1 << " m \n";

  fout << x2 << " " << y2 << " l \n";

  last_x = x2;
  last_y = y2;
  line_not_stroked = 1;
}
//
//******************************************************************************
//                         TEXT
//******************************************************************************
//
void UCdriver_ps::text(double x, double y, const char *s, const char *font,
                       double size, double rotation, double horiz_just,
                       double vert_just, int color, double *RGB)
{
  if (page_not_setup)          //  set up defaults
    setup_page();

  if (line_not_stroked) stroke_line();

  if (color != pres_color || color == USER_RGB)
    do_color(color, RGB);

  do_font(font, size);

  if (rotation)
  {
    fout << "gs \n";
    fout << x << " " << y << " t \n";
    fout << rotation << " r \n";
    fout << -(horiz_just+1) << " (" << s << ") xoff \n";
    fout << -(vert_just+1) << " (" << s << ") yoff \n";
    fout << "m (" << s << ") sh \n";
    fout << "gr \n \n";
  }
  else
  {
    fout << x << " " << horiz_just+1
         << " (" << s << ") xoff sub \n";
    fout << y << " " << vert_just+1
         << " (" << s << ") yoff sub \n";
    fout << "m (" << s << ") sh \n \n";
  }
}
//
//******************************************************************************
//                        POINT
//******************************************************************************
//
void UCdriver_ps::point(double x, double y, char p, const char *font,
                           double size, int color, double *RGB)
{
  if (page_not_setup)          //  set up defaults
    setup_page();

  if (color != pres_color || color == USER_RGB)
    do_color(color, RGB);

  if (line_not_stroked) stroke_line();

  do_font(font,size);

  fout << x << " (" << p << ") sw pop 2 div sub \n";
  fout << y << " (" << p << ") ch add 2 div sub m ("
       << p << ") sh \n \n";
}
//
//******************************************************************************
//                         POINTS
//******************************************************************************
//
void UCdriver_ps::points(double *X, double *Y, long np, char p,
                        const char *font, double size, int color, double *RGB)
{
  if (page_not_setup)          //  set up defaults
    setup_page();

  if (color != pres_color || color == USER_RGB)
    do_color(color, RGB);

  if (line_not_stroked) stroke_line();

  do_font(font,size);

  fout << "/x (" << p << ") sw pop 2 div def % x offset \n";
  fout << "/y (" << p << ") ch add 2 div def % y offset \n";

  for (int i = 0; i < np; i++)
  {
    fout << X[i] << " x sub " << Y[i] << " y sub m ("
         << p << ") sh \n";
  }

  fout << std::endl;
}
//
//******************************************************************************
//                         FRAME
//******************************************************************************
//
void UCdriver_ps::frame()
{
  if (line_not_stroked) stroke_line();

  fout << "UC_Page_End \n";
  fout << "showpage \n \n";

  page_not_setup = 1;       // set to true
  page_not_framed = 0;      // set to false
}
//
//******************************************************************************
//                        HELPER MEMBER FUNCTIONS
//******************************************************************************
//
//******************************************************************************
//                        SETUP_PAGE
//******************************************************************************
//
void UCdriver_ps::setup_page()
{ 
  int lmarg = (612 - PICTURE_WIDTH)/2;
  int bmarg = (792 - PICTURE_HEIGHT)/2;
  page++;
  fout << "%%Page: " << page << " " << page << std::endl;
  fout << "%%BeginPageSetup " << std::endl;
  fout << "UC_Page_Begin " << std::endl;
  fout << lmarg << " " << bmarg << " t " << std::endl;      // move origin
  fout << int(PICTURE_WIDTH) << " " << int(PICTURE_HEIGHT) << " scale " << std::endl;  // normalize window

  fout << "0.004 slw" << std::endl;
//
// Don't draw a bounding rectangle
// CRA 8/30/2000

//fout << "n 0 0 m 0 1 l 1 1 l 1 0 l c clip s" << std::endl;

  fout << "0 0 m" << std::endl;
  last_x = last_y = 0;
  line_not_stroked = 0;

  fout << "0 setlinecap 0 setlinejoin " << std::endl;
  fout << DEFAULT_LINE_WIDTH << " slw " << std::endl;

  fout << "%%EndPageSetup " << std::endl << std::endl;

  pres_color = pres_dash = 0;
  pres_line_width = DEFAULT_LINE_WIDTH;

  if (pres_font)
  {
    delete [] pres_font;
    pres_font = 0;
  }
  pres_font_size = 0;

  page_not_setup = 0;     // set flag to false
  page_not_framed = 1;
}
//
//******************************************************************************
//                         DO_DASH
//******************************************************************************
//
void UCdriver_ps::do_dash(int dash_pattern, int user_pattern)
{
    if (dash_pattern == USER_DASH && user_pattern == pres_user_pattern)
      return;

    if (line_not_stroked) stroke_line();

    switch (dash_pattern)
    {
      case SOLID:
        if (pres_dash == DASH_DOT || pres_dash == DASH_DOUBLE_DOT
             || pres_dash == DOTS)
          fout << "0 setlinecap \n";

        fout << "[] 0 sd \n";
        break;

      case DASH:
        if (pres_dash == DASH_DOT || pres_dash == DASH_DOUBLE_DOT
             || pres_dash == DOTS)
          fout << "0 setlinecap \n";
        fout << "[ 0.01 0.01 ] 0 sd \n";
        break;

      case DOUBLE_DASH:
        if (pres_dash == DASH_DOT || pres_dash == DASH_DOUBLE_DOT
             || pres_dash == DOTS)
          fout << "0 setlinecap \n";
        fout << "[ 0.01 0.005 0.01 0.012 ] 0 sd \n";
        break;

      case DASH_DOT:
        fout << "1 setlinecap \n"
             << " [ 0.01 0.01 0 0.01 ] 0 sd \n";
        break;

      case DASH_DOUBLE_DOT:
        fout << "1 setlinecap \n"
             << "[ 0.01 0.01 0 0.005 0 0.01] 0 sd \n";
        break;

      case DOTS:
        fout << "1 setlinecap \n"
             << "[ 0 0.005 ] 0 sd \n";
        break;

      case USER_DASH:
      {
        if (pres_dash == DASH_DOT || pres_dash == DASH_DOUBLE_DOT
             || pres_dash == DOTS)
          fout << "0 setlinecap \n";

        pres_user_pattern = user_pattern;

        int old = 1, count = 0;
        double length = 0;
     
        fout << "[ ";

        for (int i = 15; i >=0; i--)
        {
          if (((user_pattern >> i)&1) == old)  
          {
            length += 0.005;
          }
          else
          {
            fout << length << " ";
            count++;
            length = 0.005;
            old = !old;
          }
        }

        fout << length << " ";
        count ++;

        if (count%2)  // count is odd
          fout << "0 ";

        fout << "] 0 sd \n";

        break;
      }
            
    }  // switch

    pres_dash = dash_pattern;
}
//
//******************************************************************************
//                         DO_LINE_WIDTH
//******************************************************************************
//
void UCdriver_ps::do_line_width(double width)
{
  if (line_not_stroked) stroke_line();

  fout << width << " slw \n";
  pres_line_width = width;
}
//
//******************************************************************************
//                         DO_COLOR
//******************************************************************************
//
void UCdriver_ps::do_color(int color, double *RGB)
{
  if (color == USER_RGB && RGB[0] == pres_RGB[0] && 
      RGB[1] == pres_RGB[1] && RGB[2] == pres_RGB[2])
    return;

  if (line_not_stroked) stroke_line();

  switch (color)
  {
    case BLACK:
      fout << "0 0 0 setrgbcolor \n";
      break;

    case DARK_GREY:
      fout << "0.5 0.5 0.5 setrgbcolor \n";
      break;

    case LIGHT_GREY:
      fout << "0.75 0.75 0.75 setrgbcolor \n";
      break;

    case BLUE:
      fout << "0 0 0.75 setrgbcolor \n";
      break;

    case LIGHT_BLUE:
      fout << "0 0 1 setrgbcolor \n";
      break;

    case GREEN:
      fout << "0 0.75 0 setrgbcolor \n";
      break; 

    case LIGHT_GREEN:
      fout << "0 1 0 setrgbcolor \n";
      break; 

    case CYAN:
      fout << "0 0.75 0.75 setrgbcolor \n";
      break; 

    case LIGHT_CYAN:
      fout << "0 1 1 setrgbcolor \n";
      break; 

    case RED:
      fout << "0.75 0 0 setrgbcolor \n";
      break; 

    case LIGHT_RED:
      fout << "1 0 0 setrgbcolor \n";
      break; 

    case MAGENTA:
      fout << "0.75 0 0.75 setrgbcolor \n";
      break; 

    case LIGHT_MAGENTA:
      fout << "1 0 1 setrgbcolor \n";
      break; 

    case ORANGE:
      fout << "1 0.5 0 setrgbcolor \n";
      break; 

    case YELLOW:
      fout << "1 1 0 setrgbcolor \n";
      break; 

    case USER_RGB:
      fout << RGB[0] << " " << RGB[1] << " " << RGB[2] << " setrgbcolor \n";
      pres_RGB[0] = RGB[0];
      pres_RGB[1] = RGB[1];
      pres_RGB[2] = RGB[2];
      break;
  }

  pres_color = color;
}
//
//******************************************************************************
//                         DO_FONT
//******************************************************************************
//
void UCdriver_ps::do_font(const char *f, double s)
{
  if(std::abs(s) < 10e-08) s = DEFAULT_FONT_SIZE;
  if(f != 0) {if(strlen(f) == 0) f = 0;}
  if(f)
  {
    if ( !pres_font || s != pres_font_size || (strcmp(f,pres_font)))
    {
      if(pres_font != 0) delete [] pres_font;
      pres_font = new char[strlen(f)+1];

      //strcpy(pres_font,f);
      COPYSTR(pres_font,strlen(f)+1,f);

      pres_font_size = s;

      fout << "/" << f << " " << s << " fssf \n";
    }
  }
  else
  {
    if (pres_font)
    {
      delete [] pres_font;
      pres_font = 0;
      pres_font_size = s;

      fout << "/" << DEFAULT_FONT << " " << s << " fssf \n";
    }
    else if (pres_font_size != s)
    {
      pres_font_size = s;
      fout << "/" << DEFAULT_FONT << " " << s << " fssf \n";
    }
  }
}
//
//******************************************************************************
//                         STROKE_LINE
//******************************************************************************
//
void UCdriver_ps::stroke_line()
{
  fout << "s \n \n";
  line_not_stroked = 0;
}
//
//******************************************************************************
//                          REGION
//******************************************************************************
//
void UCdriver_ps::region(double *X, double *Y, long npoints, double *RGB)
{
// To do 
}

  
 
