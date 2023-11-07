//
//******************************************************************************
//                              UCPLOT.H
//******************************************************************************
// 
//                  HEADER FILE FOR CLASS UCplot            
//
//********************************************************************************
//
//            Initial Version             : David Sansot
//            Additions and Modifications : Chris Anderson 
//
//                            (C) UCLA 1994, 1995
//********************************************************************************
//
#ifndef UCPLOT_
#define UCPLOT_
#include "uc2dgrph.h"

class UCplot : public UC2dgraph
{

public:
//
//  Constructors

// 
//  Copy Constructor
//
    UCplot(const UCplot& A); 
//
//  Constructors With UCdriver Association  
//
    UCplot(UCdriver *d);
//
//  Plot Commands for standard C Data Types
// 
    void plot();
    void plot(double *y, long np); 
    void plot(double *y, long np, int p_arg);
    void plot(double *y, long np, int p_style, int p_arg);  
//   
    void plot(double *x, double *y, long np);
    void plot(double *x, double *y, long np, int p_arg);
    void plot(double *x, double *y, long np, int p_style,  int p_arg); 
//    
    void plot(double (*f)(double x));   
    void plot(double (*f)(double x), int p_arg);
    void plot(double (*f)(double x), int p_style,  int p_arg); 
//   
    void plot(double (*f)(double x), double x_min, double x_max);
    void plot(double (*f)(double x), double x_min, double x_max, int p_arg); 
    void plot(double (*f)(double x), double x_min, double x_max, int p_style,  int p_arg); 
//
    void plot(double (*f)(double x), double x_min, double x_max, double y_min, double y_max);
    void plot(double (*f)(double x), double x_min, double x_max, double y_min, double y_max, int p_arg); 
    void plot(double (*f)(double x), double x_min, double x_max, double y_min, double y_max, int p_style,  int p_arg); 

//
    void region(double *x, double *y, long npoints);
    void region(double *x, double *y, long npoints, int color, double *RGB);
//
    void frame(){drv->frame();};
//
//  Auto Scaling
//  
    void set_auto_scale_flag(int auto_flag){auto_scale_flag = auto_flag;};
    int  get_auto_scale_flag(){return auto_scale_flag;};
//
    void axis(int auto_flag){auto_scale_flag = auto_flag;}
    void axis(double x_min, double x_max, double y_min, double y_max)
    {xmin = x_min; xmax = x_max; ymin = y_min; ymax = y_max; 
     auto_scale_flag = AUTO_OFF;}
//
//  Access Ticks 
//
    void set_ticks(int xmj, int xmn, int ymj, int ymn)
        {majorx = xmj; minorx = xmn; majory = ymj; minory = ymn;}        
    void set_x_ticks(int xmj, int xmn)
        {majorx = xmj; minorx = xmn;}        
    void set_y_ticks(int ymj, int ymn)
        {majory = ymj; minory = ymn;}

    void get_ticks(int &xmj, int &xmn, int &ymj, int &ymn)
        {xmj = majorx; xmn = minorx; ymj = majory; ymn = minory;}
    void get_x_ticks(int &xmj, int &xmn)
        {xmj = majorx; xmn = minorx;}
    void get_y_ticks(int &ymj, int &ymn)
        {ymj = majory; ymn = minory;}
//
//  Access Numerical label format 
//
    void set_label_format(int t, int w, int p)
        {label_type = t; label_width = w; label_precision = p;}
    void set_label_type(int t) {label_type = t;}
    void set_label_width(int w) {label_width = w;}
    void set_label_precision(int p) {label_precision = p;}
    void set_label_char_size(double s) {label_char_size = s;}

    void get_label_format(int &t, int &w, int &p)
        {t = label_type; w = label_width; p = label_precision;}
    int get_label_type() {return label_type;}
    int get_label_width() {return label_width;}
    int get_label_precision() {return label_precision;}
    double get_label_char_size() {return label_char_size;}
//
//  Turn on or off axis and labels
//
    void turn_on_x_axis() {x_axis_flag = 1;}
    void turn_on_y_axis() {y_axis_flag = 1;}
	void turn_on_axis() {x_axis_flag = y_axis_flag = 1;}

    void turn_off_x_axis() {x_axis_flag = 0;}
    void turn_off_y_axis() {y_axis_flag = 0;}
	void turn_off_axis() {x_axis_flag = y_axis_flag = 0;}

	int  get_x_axis_flag(){return x_axis_flag;}
	int  get_y_axis_flag(){return y_axis_flag;}
	int  get_axis_flag(){return x_axis_flag*y_axis_flag;}


    void turn_on_x_labels() {x_label_flag = 1;}
    void turn_on_y_labels() {y_label_flag = 1;}
    void turn_on_label() {x_label_flag = y_label_flag = 1;}

    void turn_off_x_labels() {x_label_flag = 0;}
    void turn_off_y_labels() {y_label_flag = 0;}
	void turn_off_label() {x_label_flag = y_label_flag = 0;}

	int  get_x_label_flag(){return x_label_flag;}
	int  get_y_label_flag(){return y_label_flag;}
	int  get_label_flag(){return x_label_flag*y_label_flag;}

//
//  Draw Axis
//    
    void draw_x_axis();
	void draw_y_axis();
	void draw_axis()
	{
	if (x_axis_flag) draw_x_axis();
	if (y_axis_flag) draw_y_axis();
	}
//
//  Set and Get type of axis
//
    void set_x_axis_type(int t) {x_axis_type = t;}
    void set_y_axis_type(int t) {y_axis_type = t;}

    int get_x_axis_type() {return x_axis_type;}
    int get_y_axis_type() {return y_axis_type;}
//
//  Access the intercepts 
//
    void set_intercepts(double x, double y)
        {x_intercept = x; y_intercept = y;}
    void set_x_intercept(double x) {x_intercept = x;}
    void set_y_intercept(double y) {y_intercept = y;}

    void get_intercepts(double &x, double &y)
        {x = x_intercept; y = y_intercept;}
    double get_x_intercept() {return x_intercept;}
    double get_y_intercept() {return y_intercept;}
//
//  Access the axis color 
//
    void set_axis_color(int c) { axis_color = c; }
    void set_axis_color(double *rgb)
      { axis_rgb = rgb; axis_color = USER_RGB; }

    int get_axis_color() { return axis_color; }
    int get_axis_color(double *&rgb)
      { if (axis_color == USER_RGB) rgb = axis_rgb; else rgb = 0;
        return axis_color;}
//
//  Access plotting variables
//
    void set_line_color(int c) {line_color = c;}
    void set_line_color(double *rgb)
      { std::cout << "UCPlot.h " << rgb[0] << " " << rgb[1] << " " << rgb[2] << std::endl;
      line_rgb = rgb; line_color = USER_RGB; }
    void set_dash_pattern(int d) { line_dash_pattern = d;}
    void set_user_dash_pattern(int d)
       { user_dash_pattern = d; line_dash_pattern = USER_DASH;}
    void set_line_width(double w) { line_width = w; }
//
    int get_line_color() { return line_color;}
    int get_line_color(double *&rgb)
      { if (line_color == USER_RGB) rgb = line_rgb; else rgb = 0;
        return line_color;}
    int get_dash_pattern() { return line_dash_pattern;}
    int get_user_dash_pattern() { return user_dash_pattern;}
    double get_line_width() { return line_width;}
//
    void set_point_type(char p) { point_type = p;}
    void set_point_size(double s) { point_size = s;}
    void set_point_font(const char* s);

    int get_point_type() { return point_type;}
    double get_point_size() { return point_size;}
    std::string get_point_font();

    void set_plot_style(int s)
       { if (s==CURVE || s==POINTS || s==CURVE_AND_POINTS) plot_style=s;}
    int get_plot_style() { return plot_style;}

    void label_x(const char* s, double size = 0);
    void label_y(const char* s, double size = 0);

    void set_function_evaluation_count(long n){n_fun_points = n;}
    long get_function_evaluation_count(){return n_fun_points;}
//
//  Enumerated types
//
//  used with auto-scaling
//
    enum {AUTO_OFF, AUTO};
//
//  used for labels
//
    enum {FLOATING_POINT, SCIENTIFIC};
//
//  used with axis_type 
//
    enum {GRID, PERIMETER, FLOATING};
//
//  used with plot_style 
//
    enum {CURVE, POINTS, CURVE_AND_POINTS}; 
//
protected:
//
//  Internal Data Variables
//
//  Auto-scaling
//
    short   auto_scale_flag;
//
//  Ticks  
//
    short   majorx;
    short   majory;
    short   minorx;
    short   minory;
//
//  Label Information
//
    short   label_type;        //  Scientific or floating
    short   label_width;
    short   label_precision;
    double  label_char_size;
//
//  Axis and labels flags
//
    short   x_axis_flag;       // If true draw axis
    short   y_axis_flag;
    short   x_label_flag;      // If true draw numerical labels.
    short   y_label_flag;      // Note: labels are only drawn
                               // if axis is drawn.

    short   x_axis_type;       // Axis type - grid, floating, perimeter
    short   y_axis_type; 

    double  x_intercept;       // Intercepts used when axis are floating
    double  y_intercept;

    short   axis_color;        // = 0 means default color
    double* axis_rgb;
//
//  Line Information
//
    short   line_color;        // = 0 means use default color (black
    double* line_rgb;          //   with  UCdriver_ps module)

    short   line_dash_pattern; // = 0 means draw solid line
    int     user_dash_pattern;

    double  line_width;       // = 0 means use default width
//
//  Function Evaluation Variables 
//
    long n_fun_points;        // number of function evaluation to use
//                            // when plotting a function
//
//  Point  Information
//
    int     plot_style;        
    char    point_type;       //  The character plotted for a point
    char*   point_font;       //  The font of the character
    double  point_size;
//
//  Helper functions
//    
    void create_plot();
    void create_region_plot();

    void x_tick_mark(double xpos, double length, double ypos);
    void y_tick_mark(double ypos, double length, double xpos);
    void x_num_label(double x, double xpos, double ypos);
    void y_num_label(double y, double ypos, double xpos);

    void init_vars();

    void set_range_to_min_max();
    void set_range_to_min_max(double *XX, double* YY, long N);
    
    double* get_double_array(long length);
//
//  Pointers to External Data : These are local "work variable" pointers.
//
//  The copy constructor and assignment operator (=) for the class
//  DO NOT copy the value of pointers nor the data associated 
//  with these pointers.  
//
    double *X;
    double *Y;
    long n_points;
//
    double (*fun)(double x);
};

#endif
 
