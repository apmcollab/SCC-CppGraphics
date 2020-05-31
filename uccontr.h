//
//******************************************************************************
//                              UCCONTR.H
//******************************************************************************
// 
//                  HEADER FILE FOR CLASS UCcontour             
//
//********************************************************************************
//
//            Initial Version             : David Sansot
//            Additions and Modifications : Chris Anderson 
//
//                            (C) UCLA 1994
//********************************************************************************
//
#ifndef UCCONTOUR_
#define UCCONTOUR_

#include "uc2dgrph.h"  

class UCcontour : public UC2dgraph
{
public:
// 
//  Constuctors  
//
//  Copy Constructor
//
    UCcontour(const UCcontour& A);
//
    UCcontour(UCdriver *dr);
//    
    ~UCcontour()
    { 
    if(line_values != 0) delete [] line_values; 
    if(dash        != 0) delete [] dash;
    if(color       != 0) delete [] color;
    if(label       != 0) delete [] label; 
    if(X           != 0) delete [] X;
    if(Y           != 0) delete [] Y;
    };
//
//  Contouring routines
//
    void contour();   
    void show(){contour();};
//    
    void contour(double *data_pointer, int n, int m);
    void contour(double *data_pointer, int n, int m, int n_contour);
    void contour(double *data_pointer, int n, int m, double increment);
    void contour(double *data_pointer, int n, int m, double low_value, double high_value);
    void contour(double *data_pointer, int n, int m, int n_countour, double low_value, double high_value);
    void contour(double *data_pointer, int n, int m, double increment, double low_value, double high_value);
    void contour(double *data_pointer, int n, int m, double* contour_values, int n_contour);   
//
//  Contour Format and Level Manipulation Routines
//
    void set_auto_contour(int flag_value){auto_contour_flag = flag_value;};
    int  get_auto_contour(){return auto_contour_flag;};
    
    void turn_on_auto_contour(){auto_contour_flag = 1;};
    void turn_off_auto_contour(){auto_contour_flag = 0;};
    
    void set_line_label_flag(int flag_value){line_label_flag = flag_value;};
    int  get_line_label_flag(){return line_label_flag;};
   
    void turn_on_line_label(){line_label_flag = 1;};
    void turn_off_line_label(){line_label_flag = 0;};
           
    void turn_on_high_low_labels() {high_low_label_flag = 1;};
    void turn_off_high_low_labels() {high_low_label_flag = 0;};

    void turn_on_background() {background_flag = 1;}
	void turn_off_background() {background_flag = 0;}
    int  get_background_flag() {return background_flag;}


    void turn_on_Fortran_array_flag() {Fortran_array_flag = 1;}
	void turn_off_Fortran_array_flag() {Fortran_array_flag = 0;}
    int  get_Fortran_array_flag(){return Fortran_array_flag;}

    void turn_on_scaled_frame() {scaled_frame = 1;}
    void turn_off_scaled_frame() {scaled_frame = 0;}  

    void set_default_color(int colorIndex = UCdriver::BLACK);
//
//  Contour Level Selection
//
    void set_contour_level(long n_contour);
    void set_contour_level(int n_contour){set_contour_level(long(n_contour));};
    
    void set_contour_level(double increment);
    void set_contour_level(float increment){set_contour_level(double(increment));};

    void set_contour_level(double low_value, double high_value);
    void set_contour_level(long n_contour, double low_value, double high_value); 
    void set_contour_level(double increment, double low_value, double high_value);
    void set_contour_level(double* values, long n_contour);  



protected: 
//
//  Internal BitFlagArray Class
//
    class BitFlagArray
    {
    protected:
    unsigned char *array;         
    int size;
    int num_of_char;     

    public:

    BitFlagArray();
    BitFlagArray(int s);
    ~BitFlagArray() {if(array != 0) delete [] array;}
    void Init(int s);
    void Clear(short status = 0);
    void TurnOn(int entry);
    void TurnOff(int entry);
    int Status(int entry);
    }; 
//
//  Internal Data Variables
//
    int defaultColor;           // Color default for contour lines (one of CAMgraphics color enum's except CAMgraphics::USER_RGB)

    int nlines;                 // Number of contour lines
    int numlines;               // True number of contour lines
                                // If nlines > 0 then nlines = numlines
                                // If nlines < 0 then abs(nlines) is approximate number of
                                //   lines and numlines is number of lines.

    double step;                // Spacing between contour lines.  If < 0
                                //   step has no meaning.

    double high;                // If high > low then only contour lines
    double low;                 //   between high and low are drawn.

    double *line_values;        // Array of numlines elements holding the
                                //   values of the contour lines.

    short *dash;                // Array of length numlines holding the dash
                                //   pattern at each level.

    short *color;               // Array of length numlines holding the color
                                //   of each level

    short *label;               // Array of length numlines holding what to do
                                //   at each level.
                                //        0 - nothing drawn
                                //        1 - draw lines without labels
                                //        2 - draw labels without lines
                                //        3 - draw both


    double maxz;               // Minimum and maximum values of data
    double minz;

    double mean;               // Mean of data
    double std;                // Standard deviation


    short scaled_frame;        // If true points are evenly spaced within
							   //  the frame.  If false the contour fills
							   //  up the whole frame.
	double frame_r_save;
	double frame_l_save;
	double frame_t_save;
	double frame_b_save;
//
//  Implementation Variables for Auto Contouring
//  
	int   auto_contour_flag;   // If true - do automatic level selection

    int     nlines_hold;       // Storage for values when auto_contour
                               // is off and levels are specified by
    double  step_hold;         // number of contour lines or increment
    
    double* line_values_save;  // Pointers and data to be used when saving line style
    short*  dash_save;         // state
    short*  color_save;
    short*  label_save; 
    long    numlines_save;
//
//  Output Format Flags
//      
    short  high_low_label_flag; // If true draw high-low labels 
    
    int    line_label_flag;     // If true, then label the individual lines

    short  background_flag;     // If true draw background
//
// Enumerated types, flags, and variables used internally
//
    BitFlagArray map;          // Map of points already drawn

    double *X;                 // Array of point values for drawing
    double *Y;                 // lines.   
    
    int count;

    short Fortran_array_flag;  // If true then data is in Fortran array
                               //   format, else data is in C array format.
//
//  Internal Helper Functions
//
    void   create_contour_plot();
    void   follow_line(long triang, int side, int level);
    int    save_point(long triang, int side, int level);
    void   mark_in_use(long triang); 
    int    triangle_in_use(long triang);
    double get_value(long triang, int corner);
    int    get_neighbor(int exit_side, long &triang, int &side);
    double value(int row, int column);
    double x_value(int row);
    double y_value(int col);
	void   scale_frame();
	void   save_frame();
    void   restore_frame();
    void   init_variables();
    int    set_nice_values(int n);
    int    set_even_values(int n);
//
//  Routines specific to UCdriver   
//    
    void  draw_lines(int level);
    void  draw_background();
    void  draw_high_low_labels();
    int   get_low_graphics_dash(int d);
    int   get_low_graphics_color(int c);
//
//  Auto contouring functions
//  
    void  save_line_state();
    void  restore_line_state();
//
//  Additional Helper Functions (protected for now - may be exposed later)
//
    void set_number_of_lines(int num);
    int  get_number_of_lines() { return numlines;}

    void set_line_spacing(double inc);
    double get_line_spacing() { return step;}

    void set_low_high(double l, double h);
    void get_low_high(double &l, double &h) { l = low; h = high;}

    void set_line_value(int line, double value);
    double get_line_value(int line);

    void set_line_dash_pattern(int line, short dash_pattern);
    int get_line_dash_pattern(int line);

    void set_line_color(int line, short col);
    int get_line_color(int line);

    void set_line_labels(int line, short flag);
    int get_line_labels(int line);

    void set_line(int line, double value, short dash_pattern, 
                short col, short flag);

    void set_label_format(char *s); 
//
//  Pointers to External Data : These are local "work variable" pointers.
//
//  The copy constructor and assignment operator (=) for the class
//  DO NOT copy the value of pointers nor the data associated 
//  with these pointers.  
//
    double *data;              // The array to be contoured
//
    int rows;                  // The dimensions of data
    int columns;
  
};
#endif
 
