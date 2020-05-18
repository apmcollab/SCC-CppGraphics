//
//******************************************************************************
//                              UCCONTR.CPP
//******************************************************************************
// 
//                   SOURCE FILE FOR CLASS UCcontour
//
//********************************************************************************
//               David Sansot             (C) UCLA 1994
//********************************************************************************
// 
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "uccontr.h"
#include "camgraphexit.h"
//
// changed atan(Y/X) to atan2(Y,X)  cra 9/29/95
// defined external flag array classes cra 9/29/95
// changed exit(1) to CAMgraphicsExit() cra 9/24/97
//
//#ifndef __BCPLUSPLUS__
//#define __MPWcplusplus
//#endif
//******************************************************************************
//                         COPY CONSTRUCTOR
//******************************************************************************
// 
UCcontour::UCcontour(const UCcontour& A) : UC2dgraph(A)
{
//
    maxz = 0;               
    minz = 0;
    mean = 0;               
    std  = 0;      
//
    nlines   = A.nlines;                 
    numlines = A.numlines;             

    step = A.step;
    high = A.high;                
    low  = A.low;

    defaultColor = A.defaultColor;

    int i; 
    
    if (A. line_values != 0) 
    {
     line_values  = new double[numlines];
     for (i = 0; i < numlines; i++) line_values[i] = A.line_values[i];
    }
    else
    {line_values = 0;}   
    
    if (A.dash  != 0) 
    {
     dash = new short[numlines];
     for (i = 0; i < numlines; i++) dash[i] = A.dash[i];
    }
    else
    {dash = 0;} 
    
    if (A.color  != 0) 
    {
     color  = new short[numlines];
     for (i = 0; i < numlines; i++) color[i] = A.color[i];
    } 
    else
    {color = 0;}
    
    if (A.label != 0) 
    {
     label  = new short[numlines];
     for (i = 0; i < numlines; i++) label[i] = A.label[i];
    } 
    else
    {label = 0;}           

          
    scaled_frame = A.scaled_frame;
 
    auto_contour_flag = A.auto_contour_flag;  
    nlines_hold       = A.nlines_hold;        
    step_hold         = A.step_hold;          
//
//  Work variables not copied
//    
    line_values_save = 0;  
    dash_save        = 0;         
    color_save       = 0;
    label_save       = 0; 
    numlines_save    = 0;    
//
//  Output Format Flags
//      
    high_low_label_flag = A.high_low_label_flag; 
    line_label_flag     = A.line_label_flag;
    background_flag     = A.background_flag;
//
// Set Local Work Variables to Their Null Instances
//
    BitFlagArray Nullmap;
    map = Nullmap;      
    X     = 0;                 
    Y     = 0;   
    count = A.count; 
//
    Fortran_array_flag = A.Fortran_array_flag;
//
//  Data Pointers Set to Their Null Instances
//
    data    = 0;
    rows    = 0;                  
    columns = 0;  
}
//
//******************************************************************************
//                 UCcontour(UCdriver *driver)
//******************************************************************************
//
UCcontour::UCcontour(UCdriver *driver) : UC2dgraph(driver)
{
    data    = 0;
    rows    = 0;
    columns = 0;
// 
//  Initialize contour line variables 
//  
    nlines     = 0;                
    numlines   = 0;               
    step       = 0.0;
//
    high   =-1;
    low    = 0;
//
    dash        = 0;
    color       = 0;
    label       = 0;
    line_values = 0;
    
    X     = 0;
    Y     = 0;
// 
//  Format Defaults 
//  
    auto_contour_flag   = 1;
    scaled_frame        = 1;
    Fortran_array_flag  = 0;
    line_label_flag     = 0;
    high_low_label_flag = 0;
    background_flag     = 1; 

    defaultColor        = UCdriver::BLACK;
//
//  Auto contouring variable initialization
//   
    nlines_hold         = 0;
    step_hold           = 0.0;
    numlines_save       = 0;
    line_values_save    = 0;
    dash_save           = 0;
    color_save          = 0;
    label_save          = 0;
}
//
//********************************************************************************
//              CONTOURING ROUTINES FOR BASIC C DATA TYPES
//********************************************************************************
//
//
//********************************************************************************
//              CONTOURING ROUTINES
//********************************************************************************
// 
void UCcontour::contour()
{ 
//
// This routine contours existing data -
//  
    if(data == 0) 
    {cerr << " Data Not Specified For Contour " << endl; CAMgraphicsExit();};

    init_variables();
    set_range(x_value(0),x_value(rows-1),y_value(0),y_value(columns-1));

    if(auto_contour_flag == 1)
    {nlines = -10; set_nice_values(-nlines);} 
   
    else if((auto_contour_flag == 0)&&(nlines_hold  != 0 )) 
    {set_number_of_lines(nlines_hold);} 
  
    else if((auto_contour_flag == 0)&&( step_hold > 0.0 ))
    {set_line_spacing(step_hold);} 
  
    else if((auto_contour_flag == 0)&&( line_values == 0 ))
    {cerr << "Error : Auto Contouring Off and Contour Levels Are Unspecified "
        << endl; CAMgraphicsExit();}
        
    create_contour_plot();
}
void UCcontour::contour(double *data_pointer, int n, int m)
{ 
  data    = data_pointer;
  rows    = n;
  columns = m;

  init_variables();
  set_range(x_value(0),x_value(n-1),y_value(0),y_value(m-1));

  if(auto_contour_flag == 1)
  {nlines = -10; set_nice_values(-nlines);} 
   
  else if((auto_contour_flag == 0)&&(nlines_hold  != 0 )) 
  {set_number_of_lines(nlines_hold);} 
  
  else if((auto_contour_flag == 0)&&( step_hold > 0.0 ))
  {set_line_spacing(step_hold);} 
  
  else if((auto_contour_flag == 0)&&( line_values == 0 ))
  {cerr << "Error : Auto Contouring Off and Contour Levels Are Unspecified "
        << endl; CAMgraphicsExit();}
  create_contour_plot();
  
}
void UCcontour::contour(double *data_pointer, int n, int m, int n_contour)
{
    data    = data_pointer;
    rows    = n;
    columns = m;

    init_variables();
    set_range(x_value(0),x_value(n-1),y_value(0),y_value(m-1));  
    
    if(auto_contour_flag == 0) save_line_state();
    
    set_number_of_lines(n_contour);

    create_contour_plot();
    
    if(auto_contour_flag == 0) restore_line_state();
}
void UCcontour::contour(double *data_pointer, int n, int m, double increment)
{
    data    = data_pointer;
    rows    = n;
    columns = m;
    init_variables();
    set_range(x_value(0),x_value(n-1),y_value(0),y_value(m-1));

    if(auto_contour_flag == 0) save_line_state();
        
    set_line_spacing(increment); 
    
    create_contour_plot();  
    
    if(auto_contour_flag == 0) restore_line_state();
}
void UCcontour::contour(double *data_pointer, int n, int m, double low_value, double high_value)
{
    data    = data_pointer;
    rows    = n;
    columns = m;

    init_variables();
    set_range(x_value(0),x_value(n-1),y_value(0),y_value(m-1));
    
    if(auto_contour_flag == 0) save_line_state();
        
    nlines = 10;
    set_low_high(low_value,high_value);
     
    create_contour_plot();  
    
    if(auto_contour_flag == 0) restore_line_state();
}
void UCcontour::contour(double *data_pointer, int n, int m, int n_contour, double low_value, double high_value)
{
    data    = data_pointer;
    rows    = n;
    columns = m; 
  
    init_variables();
    set_range(x_value(0),x_value(n-1),y_value(0),y_value(m-1)); 

    if(auto_contour_flag == 0) save_line_state();
      
    nlines = n_contour;
  
    set_low_high(low_value,high_value);
    create_contour_plot();

    if(auto_contour_flag == 0) restore_line_state();
}
void UCcontour::contour(double *data_pointer, int n, int m, double increment, double low_value, double high_value)
{ 
    data    = data_pointer;
    rows    = n;
    columns = m;

    init_variables();
    set_range(x_value(0),x_value(n-1),y_value(0),y_value(m-1));

    if(auto_contour_flag == 0) save_line_state();
      
    nlines = 0; 
    step   = increment;
  
    set_low_high(low_value,high_value);  
    
    create_contour_plot();

    if(auto_contour_flag == 0) restore_line_state();
}
void UCcontour::contour(double *data_pointer, int n, int m, double* contour_values, int n_contour)
{
    data = data_pointer;
    rows    = n;
    columns = m;

    init_variables();
    set_range(x_value(0),x_value(n-1),y_value(0),y_value(m-1)); 
    
    if(auto_contour_flag == 0) save_line_state();
         
    numlines = n_contour;
    if (line_values != 0) delete [] line_values;
    line_values = new double[numlines];
    
    for (int i = 0; i < n_contour; i++)
    line_values[i] = contour_values[i];

    if (dash  != 0) delete [] dash;
    if (color != 0) delete []color;
    if (label != 0) delete []label;
    
    create_contour_plot();

    if(auto_contour_flag == 0) restore_line_state();
}
//******************************************************************************
//                      SET_CONTOUR_LEVEL ROUTINES
//******************************************************************************
//
void UCcontour::set_contour_level(long n_contour)
{ 
    auto_contour_flag = 0;
    nlines_hold       = int(n_contour);
    step_hold         = 0.0;
}
void UCcontour::set_contour_level(double increment)
{ 
    auto_contour_flag = 0; 
    nlines_hold       = 0;
    step_hold         = increment;
}
void UCcontour::set_contour_level(double low_value, double hi_value)
{ 
    auto_contour_flag = 0;
    step              = 0.0;
    nlines            = 10;
    nlines_hold       = 0;
    step_hold         = 0.0;
    set_low_high(low_value, hi_value); 
} 
void UCcontour::set_contour_level(long n_contour, double low_value, double hi_value)
{ 
    auto_contour_flag = 0;
    step              = 0.0;
    nlines            = int(n_contour);
    nlines_hold       = 0;
    step_hold         = 0.0;
    set_low_high(low_value, hi_value);
} 
void UCcontour::set_contour_level(double increment, double low_value, double hi_value)
{ 
    auto_contour_flag = 0;
    step              = increment;
    nlines            = 0;
    nlines_hold       = 0;
    step_hold         = 0.0;
    set_low_high(low_value, hi_value);
}
void UCcontour::set_contour_level(double* values, long n_contour)
{ 
    auto_contour_flag = 0;
    nlines_hold       = 0;
    step_hold         = 0.0;
    
    numlines          = int(n_contour);
    if (line_values != 0) delete []line_values;
    line_values = new double[numlines];
    
    for (int i = 0; i < n_contour; i++)
    line_values[i] = values[i];

    if (dash  != 0) delete [] dash;
    if (color != 0) delete []color;
    if (label != 0) delete []label;
}  

void UCcontour::set_default_color(int colorIndex)
{
	defaultColor = colorIndex;
}

//
//******************************************************************************
//                      INTERNAL HELPER FUNCTIONS
//******************************************************************************
//
//
//******************************************************************************
//                      INIT_VARIABLES
//******************************************************************************
//
void UCcontour::init_variables()
{  
//  This routine :
//
//  Allocates storage for the buffer arrays X and Y 
//
//  Initializes the internal variables map and count 
//
//  Computes  
//
//  minz : the minimum of the data 
//  minz : the maximum of the data
//  mean : the average of the data
//  std  : the standard deviation of the data
//
//
// 
//  Initialize internally used variables  
//
    map.Init((rows-1)*(columns-1)*2);
//    
    if(X != 0) delete [] X;
    if(Y != 0) delete [] Y;
//    
	X = new double[2*rows*columns];
	Y = new double[2*rows*columns];
//
    count = 0;

    double *dptr = data;
    maxz = minz = *dptr;

    double  z, sum = 0, sum2 = 0;
    for (int i = 0; i < rows*columns; i++, dptr++)
    {
        z = *dptr;

        if (z > maxz) maxz = z;
        else if (z < minz) minz = z;

        sum += z;
        sum2 += z*z;
    }

    mean = sum/(rows*columns);
    std = sqrt((sum2 - sum*mean)/(rows*columns -1));   
}
//
//******************************************************************************
//                      SET_NUMBER_OF_LINES 
//******************************************************************************
//
void UCcontour::set_number_of_lines(int num)
{
  nlines = num;

  if (nlines == 0)
    nlines = -12;

  if (nlines < 0)
  {
    int n = int(floor((maxz-minz)/(high-low) + 0.5));
    if (n < 1) n = 1;
    
    if (!set_nice_values(-nlines*n))
    {
      cerr << "\nUCcontour::set_nice_values() called from "
           << "set_number_of_lines.\n";
      CAMgraphicsExit();
    }
  }
  else
  {
    if (!set_even_values(nlines))
    {
      cerr << "\nUCcontour::set_even_values() called from "
           << "set_number_of_lines.\n";
      CAMgraphicsExit();
    }
  }

  if (dash) delete []dash;
  if (color) delete []color;
  if (label) delete []label;
}
//
//******************************************************************************
//                      SET_LINE_SPACING 
//******************************************************************************
//
void UCcontour::set_line_spacing(double inc)
{
  step = inc;
  nlines = 0;
  
  double start, temp;

  if (high > low)
  {
    numlines = int(floor((high-low)/step)) + 1;
    start = low;
  }
  else
  {
    int n = 0;
    start = 0;

    if (minz < 0)
      while (start - step >= minz) start -= step;
    else
      while (start <= minz) start += step;
    
    temp = start;
    while (temp < maxz) {n++; temp += step;}

    numlines = n;
  }

  if (line_values) delete []line_values;
  line_values = new double[numlines];

  for (int i = 0; i < numlines; i++)
    line_values[i] = start + i*step;

  if (dash) delete []dash;
  if (color) delete []color;
  if (label) delete []label;
}
//
//******************************************************************************
//                      SET_LOW_HIGH
//******************************************************************************
//
void UCcontour::set_low_high(double l, double h)
{
  low  = l;
  high = h;

// recalculate line_values  

  if (nlines != 0) set_number_of_lines(nlines);
  else set_line_spacing(step);
}

//
//******************************************************************************
//                      SET_LINE_VALUE
//******************************************************************************
//
void UCcontour::set_line_value(int line, double value)
{
  if (line > numlines)
  {
    cerr << "\nUCcontour::set_line_value(): argument 0 out of "
         << "range -- Exiting\n";
    CAMgraphicsExit();
  }

  line_values[line-1] = value;

  step = -1;
}

//
//******************************************************************************
//                      GET_LINE_VALUE
//******************************************************************************
//
double UCcontour::get_line_value(int line)
{
  if (line > numlines)
  {
    cerr << "\nUCcontour::get_line_value(): argument 0 out of "
         << "range -- Exiting\n";
    CAMgraphicsExit();
  }
 
  return line_values[line-1];
}

//
//******************************************************************************
//                      SET_LINE_DASH_PATTERN
//******************************************************************************
//
void UCcontour::set_line_dash_pattern(int line, short d)
{
  if (line > numlines)
  {
    cerr << "\nUCcontour::set_line_dash_pattern(): argument 0 out of "
         << "range -- Exiting\n";
    CAMgraphicsExit();
  }

  if (!dash)
  {
	dash = new short[numlines];
    for (int i = 0; i < numlines; i++)
      dash[i] = 0;
  }

  dash[line-1] = d;
}
//
//******************************************************************************
//                      GET_LINE_DASH_PATTERN
//******************************************************************************
//
int UCcontour::get_line_dash_pattern(int line)
{
  if (line > numlines)
  {
    cerr << "\nUCcontour::get_line_dash_pattern(): argument 0 out of "
         << "range -- Exiting\n";
    CAMgraphicsExit();
  }

  if (!dash) 
    return 0;
  else
    return dash[line-1];
}

//
//******************************************************************************
//                      SET_LINE_COLOR
//******************************************************************************
//
void UCcontour::set_line_color(int line, short c)
{
  if (line > numlines)
  {
    cerr << "\nUCcontour::set_line_color(): argument 0 out of "
         << "range -- Exiting\n";
    CAMgraphicsExit();
  }

  if (!color)
  {
	color = new short[numlines];
    for (int i = 0; i < numlines; i++)
      color[i] = defaultColor;
  }
  color[line-1] = c;
}
//
//******************************************************************************
//                      GET_LINE_COLOR
//******************************************************************************
//
int UCcontour::get_line_color(int line)
{
  if (line > numlines)
  {
    cerr << "\nUCcontour::get_line_color(): argument 0 out of "
         << "range -- Exiting\n";
    CAMgraphicsExit();
  }
  
  if (!color)
    return defaultColor;
  else
    return color[line-1];
}
//
//******************************************************************************
//                      SET_LINE_LABELS
//******************************************************************************
//
void UCcontour::set_line_labels(int line, short f)
{
  if (line > numlines)
  {
    cerr << "\nUCcontour::set_line_labels(): argument 0 out of "
         << "range -- Exiting\n";
    CAMgraphicsExit();
  }

  if (!label)
  {
	label = new short[numlines];
    for (int i = 0; i < numlines; i++)
      label[i] = (i%5 == 2) ? 3 : 1;
  }

  label[line-1] = f;
}
//
//******************************************************************************
//                      GET_LINE_LABELS
//******************************************************************************
//
int UCcontour::get_line_labels(int line)
{
  if (line > numlines)
  {
    cerr << "\nUCcontour::get_line_labels(): argument 0 out of "
         << "range -- Exiting\n";
    CAMgraphicsExit();
  }
 
  if (!label)
    return ( ((line-1)%5 == 2) ? 3 : 1);
  else
    return label[line-1];
}

//
//******************************************************************************
//                      SET_LINE
//******************************************************************************
//
void UCcontour::set_line(int line, double value, short d, short c,
                         short f)
{
  if (line > numlines)
  {
    cerr << "\nUCcontour::set_line(): argument 0 out of "
         << "range -- Exiting\n";
    CAMgraphicsExit();
  }

  set_line_value(line,value);
  set_line_dash_pattern(line,d);
  set_line_color(line,c);
  set_line_labels(line,f);
}
//
//******************************************************************************
//                      CREATE_CONTOUR_PLOT
//******************************************************************************
//
void UCcontour::create_contour_plot()
{ 
//
// 
//
  if (scaled_frame)
  {
   save_frame();
   scale_frame();
  }

  double first, second, z;
  long n1 = 2*(rows-1);
  long n2 = n1*(columns-1);

  for (int level = 0; level < numlines; level++)
  {
      // Clear flags
    map.Clear();

    z = line_values[level];


	  //  Check edges first for incoming lines

	long triang;

	for (triang = 0; triang < n1; triang += 2)
    {
	  if (get_value(triang,0) >= z && get_value(triang,1) < z)
		follow_line(triang,0,level);
    }

    for (triang = (n1 - 1); triang < n2; triang += n1)
    {
      if (get_value(triang,0) >= z && get_value(triang,1) < z)
        follow_line(triang,0,level);
    }

    for (triang = (n2 - 1); triang > (n2 - n1); triang -= 2)
    {
      if (get_value(triang,1) >= z && get_value(triang,2) < z)
        follow_line(triang,1,level);
    }

    for (triang = (n2 - n1); triang >= 0; triang -= n1)
    {
      if (get_value(triang,2) >= z && get_value(triang,0) < z)
        follow_line(triang,2,level);
    }


      //  Now check rest of triangles

    for (triang = 0; triang < n2; triang++)
    {
      if (!triangle_in_use(triang))   //  Triangle hasn't been passed through
      {
        second = get_value(triang, 0);

        for (int i = 0; i < 3; i++)
        {
          first = second;
          second = get_value(triang, (i == 2) ? 0 : i+1);

          if (first >= z && second < z)
          {
            follow_line(triang, i, level);
            i = 4;
          }
        }           

        mark_in_use(triang);
      }
    }
  }

    //  Add stuff like drawing info labels and background here
  if (background_flag) draw_background();
  if (high_low_label_flag) draw_high_low_labels();
  if (scaled_frame)
  {
   restore_frame();
  }
}
//
//******************************************************************************
//                      FOLLOW_LINE
//******************************************************************************
//
void UCcontour::follow_line(long triang, int side, int level)
{
  double val, z = line_values[level];
  int exit_side;

  count = 0;

  for (;;)   // loop until something breaks
  {
	if (!save_point(triang, side, level))
    {
      // Something went wrong  -  probably divide by 0 error
      if (count) draw_lines(level);
      return;
    }

	if (triangle_in_use(triang))  // Reached a closed contour
    {
      if (count) draw_lines(level);
      return;
    }
    
	mark_in_use(triang);

	val = get_value(triang, (side+2)%3);

	exit_side = (val < z) ? (side+2)%3 : (side+1)%3;

	if (!get_neighbor(exit_side, triang, side))  //  Reached end of grid
    {
      save_point(triang, exit_side, level);
	  if (count) draw_lines(level);
	  return;
    }

  } // for
}
//
//******************************************************************************
//                      SAVE_POINT
//******************************************************************************
//
int UCcontour::save_point(long triang, int side, int level)
{
  double last = get_value(triang, side);
  double next = get_value(triang, (side + 1)%3);

  if (last == next)
  {
	cerr << "\nUCcontour::save_point(): potential divide-by-zero!\n";
	return 0;
  }


  double z = line_values[level];
  double ds = (last - z)/(last - next);



  int row, col;

  row = int((triang/2)%(rows-1));
  col = int((triang/2)/(rows-1));

//  cout << row << "  " << col << endl;
//  if((row == 19)&&(col == 2)) getchar();

  double xd, yd;

  if (triang & 1)   // if triang is odd
	switch (side)
    {
      case 0:  xd = x_value(row+1);
               yd = y_value(col) + ds*(y_value(col+1) - y_value(col));
               break;
      case 1:  xd = x_value(row+1) - ds*(x_value(row+1) - x_value(row));
               yd = y_value(col+1);
               break;
	  case 2:  xd = x_value(row) + ds*(x_value(row+1) - x_value(row));
			   yd = y_value(col+1) - ds*(y_value(col+1) - y_value(col));
			   break;
	}
  else
	switch (side)
    {
	  case 0:  xd = x_value(row) + ds*(x_value(row+1) - x_value(row));
			   yd = y_value(col);
			   break;
      case 1:  xd = x_value(row+1) - ds*(x_value(row+1) - x_value(row));
               yd = y_value(col) + ds*(y_value(col+1) - y_value(col));
               break;
      case 2:  xd = x_value(row);
               yd = y_value(col+1) - ds*(y_value(col+1) - y_value(col));
               break;
    }

  X[count] = frame_2_screen_x(normalize_x(xd));
  Y[count] = frame_2_screen_y(normalize_y(yd));

  count++;

  return 1;
}
//
//******************************************************************************
//                      GET_NEIGHBOR
//******************************************************************************
//
int UCcontour::get_neighbor(int exit_side, long &triang, int &side)
{
    // Check to see if we go over edge
  int num = 2*(rows-1);

  if ((triang%num == (num - 1)) && (exit_side == 0))  return 0;
  if ((!(triang&1)) && (triang < num) && (exit_side == 0)) return 0;
  if ((triang%num == 0) && (exit_side == 2)) return 0;
  if ((triang&1) && (triang > num*(columns-2)) && exit_side == 1) return 0;


    //  Regular cases
  if (triang&1)  // if odd
    switch (exit_side)
    {
      case 0: triang++; side = 2; break;
      case 1: triang += (num - 1); side = 0; break;
      case 2: triang--; side = 1; break;
    }
  else
    switch (exit_side)
    {
      case 0: triang += (1 - num); side = 1; break;
      case 1: triang++; side = 2; break;
      case 2: triang--; side = 0; break;
    } 
  return 1; 
}
//
//******************************************************************************
//                      MARK_IN_USE
//******************************************************************************
//
void UCcontour::mark_in_use(long triang)
{
  if (triang >= 2*(rows-1)*(columns-1)) return;

  map.TurnOn(int(triang));
}
//
//******************************************************************************
//                      FACE_IN_USE
//******************************************************************************
//
int UCcontour::triangle_in_use(long triang)
{
  if (triang >= 2*(rows-1)*(columns-1)) return 1;

  return map.Status(int(triang));
}
//
//******************************************************************************
//                      GET_VALUE
//******************************************************************************
//
double UCcontour::get_value(long triang, int corner)
{
  int row, col;
  row = int((triang/2)%(rows-1));
  col = int((triang/2)/(rows-1));

  if (triang&1)
    switch (corner)
    {
      case 0:  row++; break;
      case 1:  row++; col++; break;
      case 2:  col++; break;
    }
  else
    switch (corner)
    {
      case 0: break;
      case 1: row++; break;
      case 2: col++; break;
    }

  return value(row, col);  
}  
//
//******************************************************************************
//                      DRAW_LINES
//******************************************************************************
//
void UCcontour::draw_lines(int level)
{
  short d = (dash) ? get_low_graphics_dash(dash[level]) : 0;

  short c = (color) ? get_low_graphics_color(color[level]) : defaultColor;

  short f = (label) ? label[level] : ((level%3==1) ? 3 : 1);
//
  if(line_label_flag == 0) f = 1;
//
  int cnt = 0;
  double ang,x,y;
  char lab[256];
  char format[256];

  if (f == 2 || f == 3)           // Labels are going to be drawn.  Make 
  {                               //   labels at least two sig digits
    int first_dig;
//
//  since labels in fixed precision - limit number of small digits
//
    double line_value = line_values[level];
    if(fabs(line_value) < .0001) 
    {
    line_value = 0.00;
    sprintf(format,"%%%d.%df",6,4);
    sprintf(lab,format,line_value); 
    }
    else
    {
//    
    if (line_value != 0)
      first_dig = int(floor(log10(fabs(line_value)))) + 1;
    else
      first_dig = 0;

    int field, dec;

    if (first_dig > 2) 
      { field = first_dig;  dec = 0; }
    else if (first_dig > 0)
      { field = 4;  dec = 3 - first_dig; }
    else
      { dec = -(first_dig - 2);  field = dec + 2; }

    if (line_value < 0) field++;

    sprintf(format,"%%%d.%df",field,dec);
    sprintf(lab,format,line_value);
       
    } 
  }

  int mul = int(floor(double(((rows+columns)/2 + 9)/15)));
  if (mul < 1) mul = 1;
    
  switch (f)
  {
    case 1:   // draw just lines
      drv->lines(X,Y,count,d,0,0,c,0);
      break;

    case 2:   // draw just labels
    {
      while ((count - cnt) > 3*mul)
      {
        ang = 
		atan2((Y[cnt+3*mul] - Y[cnt+1*mul]),(X[cnt+3*mul] - X[cnt+1*mul]));
        ang = 180*ang/3.14159265359;   // convert to degrees

        drv->text(X[cnt+2*mul],Y[cnt+2*mul],lab,0,(frame_r-frame_l)*0.02,
                       int(ang),0,0,c,0);
        
        cnt += 3*mul;
      }

      break;
    }

    case 3:   // draw both
    {
      while ((count-cnt) > 6*mul)
      {
        drv->lines(&X[cnt],&Y[cnt],4*mul+1,d,0,0,c,0);

        x = (X[cnt+4*mul] + X[cnt+6*mul])/2;
		y = (Y[cnt+4*mul] + Y[cnt+6*mul])/2;
		ang = atan2((Y[cnt+4*mul]-Y[cnt+6*mul]),(X[cnt+4*mul]-X[cnt+6*mul]));
        ang = 180*ang/3.14159265359;   // convert to degrees

        drv->text(x,y,lab,0,(frame_r-frame_l)*0.02,
                       int(ang),0,0,c,0);
 
        cnt += 6*mul;
      }

      drv->lines(&X[cnt],&Y[cnt],count-cnt,d,0,0,c,0);
      break;
    }
  }
}
//
//******************************************************************************
//                      DRAW_BACKGROUND
//******************************************************************************
//
void UCcontour::draw_background()
{
                // draw frame

  double A[5]; A[0] = A[1] = A[4] = frame_l; A[2] = A[3] = frame_r;
  double B[5]; B[0] = B[3] = B[4] = frame_b; B[1] = B[2] = frame_t;

  drv->lines(A,B,5,0,0,0,0,0);


                // draw ticks
  double len = scale_to_frame_width(0.015);

  double x,y;
  int i;
  for (i = 1; i < rows-1; i++)
  {
    x = frame_2_screen_x(normalize_x(x_value(i)));
    drv->line(x,frame_b,x,frame_b+len,0,0,0,0,0);
    drv->line(x,frame_t,x,frame_t-len,0,0,0,0,0);
  }
  for (i = 1; i < columns-1; i++)
  {
    y = frame_2_screen_y(normalize_y(y_value(i)));
    drv->line(frame_l,y,frame_l+len,y,0,0,0,0,0);
    drv->line(frame_r,y,frame_r-len,y,0,0,0,0,0);
  }
}
//
//******************************************************************************
//                      DRAW_HIGH_LOW_LABELS
//******************************************************************************
//
void UCcontour::draw_high_low_labels()
{
  double x,y,val;
  char lab[256], format[256];

  for (int r = 1; r < rows - 1; r++)
    for (int c = 1; c < columns - 1; c++)
    {
      val = value(r,c);

      if (val > value(r-1,c-1) && val > value(r-1,c) && 
          val > value(r-1,c+1) && val > value(r,c-1) &&
          val > value(r,c+1)   && val > value(r+1,c-1) &&
          val > value(r+1,c)   && val > value(r+1,c+1))
      {

        x = frame_2_screen_x(normalize_x(x_value(r)));
        y = frame_2_screen_y(normalize_y(y_value(c)));

        int first_dig = 
            (val != 0) ? (int(floor(log10(fabs(val)))) + 1) : 0;

        int field, dec;

        if (first_dig > 2) 
          { field = first_dig;  dec = 0; }
        else if (first_dig > 0)
          { field = 4;  dec = 3 - first_dig; }
        else
          { dec = -(first_dig - 2);  field = dec + 2; }

        if (val < 0) field++;
//
//      limit printing of lots of zeros
//        
        if(fabs(val) < .0001) 
        {field = 6; dec = 4;}

        sprintf(format,"%%%d.%df",field,dec);
        sprintf(lab,format,val);
       
        drv->text(x,y,"H",0,scale_to_frame_width(0.03),0,1,0,0,0);
        drv->text(x,y,lab,0,scale_to_frame_width(0.02),0,-1,1,0,0);
      }
      else if (val < value(r-1,c-1) && val < value(r-1,c) && 
               val < value(r-1,c+1) && val < value(r,c-1) &&
               val < value(r,c+1)   && val < value(r+1,c-1) &&
               val < value(r+1,c)   && val < value(r+1,c+1))
      {
        x = frame_2_screen_x(normalize_x(x_value(r)));
        y = frame_2_screen_y(normalize_y(y_value(c)));

        int first_dig = 
            (val != 0) ? (int(floor(log10(fabs(val)))) + 1) : 0;
        int field, dec;

        if (first_dig > 2) 
          { field = first_dig;  dec = 0; }
        else if (first_dig > 0)
          { field = 4;  dec = 3 - first_dig; }
        else
          { dec = -(first_dig - 2);  field = dec + 2; }

        if (val < 0) field++;
//
//      limit printing of lots of zeros
//        
        if(fabs(val) < .0001) 
        {field = 6; dec = 4;}
//        
        sprintf(format,"%%%d.%df",field,dec);
        sprintf(lab,format,val);

        drv->text(x,y,"L",0,scale_to_frame_width(0.03),0,1,0,0,0);
        drv->text(x,y,lab,0,scale_to_frame_width(0.02),0,-1,1,0,0);
      }
    }
}
//
//******************************************************************************
//                      VALUE
//******************************************************************************
//
double UCcontour::value(int row, int column)
{
  if (Fortran_array_flag)
  {
    return data[column*rows + row];
  }
  else
  {
    return data[row*columns + column];
  }
}

//
//******************************************************************************
//                      X_VALUE
//******************************************************************************
//
double UCcontour::x_value(int row)
{
  return double(row);
}
//
//******************************************************************************
//                      Y_VALUE
//******************************************************************************
//
double UCcontour::y_value(int col)
{
  return double(col);
}
//
//******************************************************************************
//                      SET_NICE_VALUES
//******************************************************************************
//
int UCcontour::set_nice_values(int n)
{ 
//
// This routine determines a nice set of contour lines - the number is
// approximately n.
//
// This routine sets :
//
// numlines     (actual number of contours)
// step         (step between contours)
// line_values  (values associated with contours)
//
// determine `nice' step
//
// Fixed std = 0 temporarily  CRA 4/96
//
  if(fabs(std) < 1.0e-15)
  {
  step     = 0.0;
  numlines = 1;
  if (line_values) delete []line_values;
  line_values    = new double[1];
  line_values[0] = mean;
  }
  else
  {
  step = 4.0*std/n;
  double p = pow(10.0, floor(log10(step)));
  step = p*floor((step +p/2.0)/p);
 
  double lev;
  if (maxz*minz < 0)
    lev = step*floor(mean/step);
  else
    lev = step*floor(minz/step);
     

  double lowval = (high < low) ? minz : low;


// find first level over lowest value 

  while (lev - step > lowval)
    lev -= step;
  while (lev < lowval)
    lev += step;

// determine number of lines  

  double hival = (high < low) ? maxz : high;
  int c = 0;
  double l = lev;
  while (l < hival)
  {
    c++;
    l+=step;
  } 

  numlines = c;

  if (line_values) delete []line_values;
  line_values = new double[numlines];

  for (int i = 0; i < numlines; i++)
    line_values[i] = lev + i*step;
  }
  return(1);
}
//
//******************************************************************************
//                      SET_EVEN_VALUES
//******************************************************************************
//
int UCcontour::set_even_values(int n)
{
  numlines = n;

  if (line_values) delete []line_values;
  line_values = new double[numlines];

  double start;
  if (high < low)
  {
    step = (maxz - minz)/(nlines+1);
    start = minz + step;
  }
  else
  {
    step = (high-low)/(nlines-1);
    start = low;
  }

  for (int i = 0; i < nlines; i++)
    line_values[i] = start + i*step;
 
  return(1);
}

//
//******************************************************************************
//                      GET_LOW_GRAPHICS_DASH
//******************************************************************************
//
int UCcontour::get_low_graphics_dash(int d)
{
  int nd;

  switch (d)
  {
    case DASH:            nd = drv->DASH;            break;
    case DOUBLE_DASH:     nd = drv->DOUBLE_DASH;     break;
    case DASH_DOT:        nd = drv->DASH_DOT;        break;
    case DASH_DOUBLE_DOT: nd = drv->DASH_DOUBLE_DOT; break;
    case DOTS:            nd = drv->DOTS;            break;
    default:              nd = 0;                  break;  // solid line
  }

  return nd;
}
//
//******************************************************************************
//                      GET_LOW_GRAPHICS_COLOR
//******************************************************************************
//
int UCcontour::get_low_graphics_color(int c)
{
  int nc;

  switch (c)
  {
    case BLACK:         nc = drv->BLACK;         break;
    case DARK_GREY:     nc = drv->DARK_GREY;     break;
    case LIGHT_GREY:    nc = drv->LIGHT_GREY;    break;
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
    default:            nc = 0;  /* BLACK */     break;
  }

  return nc;
}
//
//******************************************************************************
//                      SCALE FRAME ROUTINES
//******************************************************************************
//
void UCcontour::save_frame()
{
	frame_r_save = frame_r;
	frame_l_save = frame_l;
	frame_t_save = frame_t;
	frame_b_save = frame_b;
}
void UCcontour::restore_frame()
{
	frame_r = frame_r_save;
	frame_l = frame_l_save;
	frame_t = frame_t_save;
	frame_b = frame_b_save;
}
void UCcontour::scale_frame()
{
  double num1 = (frame_r - frame_l)/(xmax - xmin);
  double num2 = (frame_t - frame_b)/(ymax - ymin);

  if (num1 < num2)
  {
    double ydiff = ((frame_t - frame_b) - (ymax - ymin)*num1)/2;
   
    frame_t -= ydiff;
    frame_b += ydiff;
  }
  else if (num2 < num1)
  {
    double xdiff = ((frame_r - frame_l) - (xmax - xmin)*num2)/2;

    frame_r -= xdiff;
    frame_l += xdiff;
  }
} 
//
//******************************************************************************
//                      SAVE_LINE_STATE
//******************************************************************************
//
void UCcontour::save_line_state()
{
//
//  This routine saves the line style information 
//  
    int i;
    numlines_save = int(numlines);
    if (line_values  != 0) 
    {
     line_values_save  = new double[numlines];
     for (i = 0; i < numlines; i++) line_values_save[i] = line_values[i];
    }   
    
    if (dash  != 0) 
    {
     dash_save  = new short[numlines];
     for (i = 0; i < numlines; i++) dash_save[i] = dash[i];
    } 
    
    if (color  != 0) 
    {
     color_save  = new short[numlines];
     for (i = 0; i < numlines; i++) color_save[i] = color[i];
    } 
    
    if (label != 0) 
    {
     label_save  = new short[numlines];
     for (i = 0; i < numlines; i++) label_save[i] = label[i];
    }
} 
//
//******************************************************************************
//                      RESTORE_LINE_STATE
//******************************************************************************
//
void UCcontour::restore_line_state()
{
//
//  This routine restores the line style information 
//  
    numlines = int(numlines_save);
    int i;
    if (line_values_save  != 0) 
    {
     if(line_values != 0) delete [] line_values;
     line_values  = new double[numlines];
     for (i = 0; i < numlines; i++) line_values[i] = line_values_save[i];
     delete [] line_values_save;
    }   
    
    if (dash_save  != 0) 
    {
     if(dash != 0) delete [] dash;
     dash = new short[numlines];
     for (i = 0; i < numlines; i++) dash[i] = dash_save[i];
     delete [] dash_save;
    } 
    
    if (color_save  != 0) 
    { 
     if(color != 0) delete [] color;
     color  = new short[numlines];
     for (i = 0; i < numlines; i++) color[i] = color_save[i];
     delete [] color_save;
    } 
    
    if (label_save != 0) 
    { 
     if(label != 0) delete [] label;
     label  = new short[numlines];
     for (i = 0; i < numlines; i++) label[i] = label_save[i];
     delete [] label_save;
    } 
    numlines_save = 0;
} 
#ifndef __MPWcplusplus
//
//******************************************************************************
// INTERNAL BitFlagArray SOURCE (For compilers that tolerate nested class names)
//******************************************************************************
//
UCcontour::BitFlagArray::BitFlagArray()
{
  array = 0;
  size = 0;
  num_of_char = 0;
}
UCcontour::BitFlagArray::BitFlagArray(int s)
{
  size = s;

  num_of_char = (size - 1)/8 + 1;
  array = new unsigned char[num_of_char];
}
void UCcontour::BitFlagArray::Init(int s)
{
  size = s;
  num_of_char = (size - 1)/8 + 1;

  if (array != 0) delete [] array;
  array = new unsigned char[num_of_char];

  Clear();
}
void UCcontour::BitFlagArray::Clear(short status)
{
  if (status)        //  Turn on all the bits
    for (unsigned char *p = array; p < array+num_of_char; p++) *p = 255;
  else               //  Turn off all the bits
    for (unsigned char *q = array; q < array+num_of_char; q++) *q = 0;
}
void UCcontour::BitFlagArray::TurnOn(int entry)
{
  if (entry >= size) return;

  array[entry/8] |= (1 << (7 - entry%8));
}
void UCcontour::BitFlagArray::TurnOff(int entry)
{
  if (entry >= size) return;

  array[entry/8] &= (255 ^ (1 << (7 - entry%8)));
}
int UCcontour::BitFlagArray::Status(int entry)
{
  if (entry >= size) return -1;

  if (array[entry/8] & (1 << (7 - entry%8)))
    return 1;
  else
    return 0;
}
#else
//
//******************************************************************************
// INTERNAL BitFlagArray SOURCE (For compilers that don't like nested class names)
//******************************************************************************
//
BitFlagArray::BitFlagArray()
{
  array = 0;
  size = 0;
  num_of_char = 0;
}
BitFlagArray::BitFlagArray(int s)
{
  size = s;

  num_of_char = (size - 1)/8 + 1;
  array = new unsigned char[num_of_char];
}
void BitFlagArray::Init(int s)
{
  size = s;
  num_of_char = (size - 1)/8 + 1;

  if (array != 0) delete [] array;
  array = new unsigned char[num_of_char];

  Clear();
}
void BitFlagArray::Clear(short status)
{
  if (status)        //  Turn on all the bits
    for (unsigned char *p = array; p < array+num_of_char; p++) *p = 255;
  else               //  Turn off all the bits
    for (unsigned char *q = array; q < array+num_of_char; q++) *q = 0;
}
void BitFlagArray::TurnOn(int entry)
{
  if (entry >= size) return;

  array[entry/8] |= (1 << (7 - entry%8));
}
void BitFlagArray::TurnOff(int entry)
{
  if (entry >= size) return;

  array[entry/8] &= (255 ^ (1 << (7 - entry%8)));
}
int BitFlagArray::Status(int entry)
{
  if (entry >= size) return -1;

  if (array[entry/8] & (1 << (7 - entry%8)))
    return 1;
  else
    return 0;
}
#endif  

 
