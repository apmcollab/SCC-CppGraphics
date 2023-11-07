#include "CAMgraphicsProcess.h"
#include "CAMgraphicsDriver.h"
#include "CAMplotArguments.h"
#include "CAMregionArguments.h"
#include "CAMcontourArguments.h"
#include "CAMsurfaceArguments.h"
#include "CAMtextArguments.h"
#include "CAMsetArguments.h"

#include <string>
#include <iostream>

//
//######################################################################
//
//            Chris Anderson (C) UCLA
//
//                 Sept. 17, 1996
//
//######################################################################
//
//
//
CAMgraphicsProcess::CAMgraphicsProcess(){};

void CAMgraphicsProcess::attachDriver(CAMgraphicsDriver * Od)
{
	ODriver = Od;
}

void CAMgraphicsProcess::detachDriver()
{
    ODriver  = 0;
};

void CAMgraphicsProcess::frame()
{
    if(ODriver == 0) return;
	ODriver->frame();
}

void CAMgraphicsProcess::reset()
{
    if(ODriver == 0) return;
	ODriver->reset();
}
void CAMgraphicsProcess::plot()
{
	if(ODriver == 0) return;
    CAMplotArguments Arg;
    ODriver->accept(Arg);
}

void CAMgraphicsProcess::plot(double* y, long n)
{
	if(ODriver == 0) return;
    CAMplotArguments Arg;
    Arg.callType = 1;
    Arg.n        = n;
    Arg.y_Size   = n;
    Arg.y        = y;
    ODriver->accept(Arg);
}


void CAMgraphicsProcess::plot(double *y, long n, int c)
{
	if(ODriver == 0) return;
    CAMplotArguments Arg;
    Arg.callType = 2;
    Arg.y_Size   = n;
    Arg.y        = y;
    Arg.n        = n;
    Arg.c        = char(c);
    ODriver->accept(Arg);
}

void CAMgraphicsProcess::plot(double *y, long n, int c, int s)
{
	if(ODriver == 0) return;
    CAMplotArguments Arg;
    Arg.callType = 3;
    Arg.y        = y;
    Arg.y_Size   = n;
    Arg.n        = n;
    Arg.c        = char(c);
    Arg.s        = s;
    ODriver->accept(Arg);
}

void CAMgraphicsProcess::plot(double *x, double *y, long n)
{
	if(ODriver == 0) return;
    CAMplotArguments Arg;
    Arg.callType = 11;
    Arg.x_Size   = n;
    Arg.x        = x;
    Arg.y_Size   = n;
    Arg.y        = y;
    Arg.n        = n;
    ODriver->accept(Arg);
}

void CAMgraphicsProcess::plot(double *x, double *y, long n, int c)
{
	if(ODriver == 0) return;
    CAMplotArguments Arg;
    Arg.callType = 12;
    Arg.x_Size   = n;
    Arg.x        = x;
    Arg.y_Size   = n;
    Arg.y        = y;
    Arg.n        = n;
    Arg.c        = char(c);
    ODriver->accept(Arg);
}

void CAMgraphicsProcess::plot(double* x, double* y, long n, int c, int s)
{
	if(ODriver == 0) return;
    CAMplotArguments Arg;
    Arg.callType = 13;
    Arg.x_Size   = n;
    Arg.x        = x;
    Arg.y_Size   = n;
    Arg.y        = y;
    Arg.n        = n;
    Arg.c        = char(c);
    Arg.s        = s;
    ODriver->accept(Arg);
}


void CAMgraphicsProcess::region(double *x, double *y, long n)
{
	if(ODriver == 0) return;
	CAMregionArguments Arg;
    Arg.callType = 0;
    Arg.x_Size   = n;
    Arg.x        = x;
    Arg.y_Size   = n;
    Arg.y        = y;
    Arg.n        = n;
    ODriver->accept(Arg);
}

void CAMgraphicsProcess::region(double *x, double *y, long n, int color, double *rgb)
{
	if(ODriver == 0) return;
	CAMregionArguments Arg;
    Arg.callType = 1;
    Arg.x_Size   = n;
    Arg.x        = x;
    Arg.y_Size   = n;
    Arg.y        = y;
    Arg.n        = n;
    Arg.col      = color;
    Arg.rgb      = rgb;
    ODriver->accept(Arg);
}

void CAMgraphicsProcess::contour()
{
	if(ODriver == 0) return;
    CAMcontourArguments Arg;
    ODriver->accept(Arg);
};

void CAMgraphicsProcess::contour(double *z, long m, long n)
{
	if(ODriver == 0) return;
    CAMcontourArguments Arg ;
    Arg.callType = 1;

    Arg.z_Size   = m*n;
    Arg.z        = z;
    Arg.m        = m;
    Arg.n        = n;
    ODriver->accept(Arg);

};
void CAMgraphicsProcess::contour(double *z, long m, long n, int n_c)
{
	if(ODriver == 0) return;
    CAMcontourArguments Arg;
    Arg.callType = 2;

    Arg.z_Size   = m*n;
    Arg.z        = z;
    Arg.m        = m;
    Arg.n        = n;
    Arg.n_c      = n_c;
    ODriver->accept(Arg);
};
void CAMgraphicsProcess::contour(double *z, long m, long n, double c_inc)
{
	if(ODriver == 0) return;
    CAMcontourArguments Arg;
    Arg.callType = 3;
    
    Arg.z_Size   = m*n;
    Arg.z        = z;
    Arg.m        = m;
    Arg.n        = n;
    Arg.c_inc    = c_inc;
    ODriver->accept(Arg);
};
void CAMgraphicsProcess::contour(double *z, long m, long n, double c_min, double c_max)
{
	if(ODriver == 0) return;
    CAMcontourArguments Arg;
    Arg.callType = 4;

    Arg.z_Size   = m*n;
    Arg.z        = z;
    Arg.m        = m;
    Arg.n        = n;

    Arg.c_min    = c_min;
    Arg.c_max    = c_max;
    ODriver->accept(Arg);

};
void CAMgraphicsProcess::contour(double *z, long m, long  n, int n_c, double c_min, double c_max)
{
	if(ODriver == 0) return;
    CAMcontourArguments Arg;
    Arg.callType = 5;

    Arg.z_Size   = m*n;
    Arg.z        = z;
    Arg.m        = m;
    Arg.n        = n;
    Arg.c_min    = c_min;
    Arg.c_max    = c_max;
    Arg.n_c      = n_c;
    ODriver->accept(Arg);
};

void CAMgraphicsProcess::contour(double* z, long m, long n, double c_inc, double c_min, double c_max)
{
	if(ODriver == 0) return;
    CAMcontourArguments Arg;
    Arg.callType = 6;

    Arg.z_Size   = m*n;
    Arg.z        = z;
    Arg.m        = m;
    Arg.n        = n;

    Arg.c_min    = c_min;
    Arg.c_max    = c_max;
    Arg.c_inc    = c_inc;
    ODriver->accept(Arg);
};


void CAMgraphicsProcess::contour(double *z, long m, long n, double* c_values, int n_c)
{
	if(ODriver == 0) return;
    CAMcontourArguments Arg;
    Arg.callType = 7;

    Arg.z_Size   = m*n;
    Arg.z        = z;
    Arg.m        = m;
    Arg.n        = n;

    Arg.n_c      = n_c;

    Arg.c_values_Size = n_c;
    Arg.c_values      = c_values;
    ODriver->accept(Arg);
};


void CAMgraphicsProcess::setContourLineColor(int colorIndex)
{
	if(ODriver == 0) return;
    CAMcontourArguments Arg;
    Arg.callType = 8;
    Arg.defaultColor = colorIndex;
    ODriver->accept(Arg);
};



void CAMgraphicsProcess::surface()
{
	if(ODriver == 0) return;
    CAMsurfaceArguments Arg;
    ODriver->accept(Arg);

};

void CAMgraphicsProcess::surface(double* z, long  m, long n)
{
	if(ODriver == 0) return;
    CAMsurfaceArguments Arg;
    Arg.callType = 1;
    Arg.z_Size   = m*n;
    Arg.z        = z;
    Arg.m        = m;
    Arg.n        = n;

    ODriver->accept(Arg);

};

void CAMgraphicsProcess::surface(double *z, long m, long n, double* x, double* y)
{
	if(ODriver == 0) return;
    CAMsurfaceArguments Arg;
    Arg.callType = 2;

    Arg.z_Size   = m*n;
    Arg.z        = z;
    Arg.m        = m;
    Arg.n        = n;

    Arg.x_Size = m;
    Arg.y_Size = n;
    Arg.x = x;
    Arg.y = y;
    ODriver->accept(Arg);

};

void CAMgraphicsProcess::drawString(double x, double y, const char* S)
{
	if(ODriver == 0) return;
    CAMtextArguments Arg;
    Arg.callType = 1;

    Arg.s_Size   = (long)strlen(S)+1;
    Arg.s          = S;

    Arg.x        =       x;
    Arg.y        =       y;
    Arg.size     =    -1.0;
    ODriver->accept(Arg);
};

void CAMgraphicsProcess::drawString(double x, double y, const char* S, double size)
{
	if(ODriver == 0) return;
    CAMtextArguments Arg;
    Arg.callType = 1;

    Arg.s_Size     = (long)strlen(S)+1;
    Arg.s          = S;

    Arg.x        =       x;
    Arg.y        =       y;
    Arg.size     =    size;
    ODriver->accept(Arg);
};

void CAMgraphicsProcess::title(const char* S)
{
	if(ODriver == 0) return;
    CAMtextArguments Arg;
    Arg.callType = 2;

    Arg.s_Size     = (long)strlen(S)+1;
    Arg.s          = S;
    Arg.size       =  -1.0;
    ODriver->accept(Arg);
};

void CAMgraphicsProcess::title(const char* S, double size)
{
	if(ODriver == 0) return;
    CAMtextArguments Arg;
    Arg.callType = 2;

    Arg.s_Size     = (long)strlen(S)+1;
    Arg.s          = S;
    Arg.size       = size;
    ODriver->accept(Arg);
};

void CAMgraphicsProcess::labelX(const char* S)
{
	if(ODriver == 0) return;
    CAMtextArguments Arg;
    Arg.callType = 3;

    Arg.s_Size     = (long)strlen(S)+1;
    Arg.s          = S;
    Arg.size       = -1.0;
    ODriver->accept(Arg);
};

void CAMgraphicsProcess::labelX(const char* S, double size)
{
	if(ODriver == 0) return;
    CAMtextArguments Arg;
    Arg.callType = 3;
 
    Arg.s_Size     = (long)strlen(S)+1;
    Arg.s          = S;
    Arg.size       = size;

    ODriver->accept(Arg);
};

void CAMgraphicsProcess::labelY(const char* S)
{
	if(ODriver == 0) return;
    CAMtextArguments Arg;
    Arg.callType = 4;

    Arg.s_Size     = (long)strlen(S)+1;
    Arg.s          = S;
    Arg.size       = -1.0;
    ODriver->accept(Arg);
};

void CAMgraphicsProcess::labelY(const char* S, double size)
{
	if(ODriver == 0) return;
    CAMtextArguments Arg;
    Arg.callType = 4;

    Arg.s_Size     = (long)strlen(S)+1;
    Arg.s          = S;
    Arg.size       = size;
    ODriver->accept(Arg);
};

CAMsetArguments getNull(long i)
{
	CAMsetArguments Arg;
    Arg.callType = i;
    return Arg;
}

void CAMgraphicsProcess::setFrame(double left, double right, double bottom, double top)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
    Arg.callType = 10;

    Arg.d_Size   = 4;
    double d[4];
    d[0] = left;
    d[1] = right;
    d[2] = bottom;
    d[3] = top;
    Arg.d = d;

    ODriver->accept(Arg);
}
void CAMgraphicsProcess::subplotOn(long m, long n)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
    Arg.callType = 11;

    long i[2];
    i[0] = m;
    i[1] = n;
    Arg.i_Size   = 2;
    Arg.i        = i;
    ODriver->accept(Arg);
}
void CAMgraphicsProcess::subplot(long m, long n)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
    Arg.callType = 12;

    long i[2];
    i[0] = m;
    i[1] = n;
    Arg.i_Size   = 2;
    Arg.i        = i;

    ODriver->accept(Arg);
}

void CAMgraphicsProcess::subplotOff()
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
    Arg.callType = 13;
    ODriver->accept(Arg);
}

void CAMgraphicsProcess::axisAutoScaleOn()
{
	if(ODriver == 0) return;
    ODriver->accept(getNull(21));
}

void CAMgraphicsProcess::axisAutoScaleOff()
{
	if(ODriver == 0) return;
    ODriver->accept(getNull(22));
}

void CAMgraphicsProcess::setAxisRange(double xmin, double xmax, double ymin, double ymax)
{
	if(ODriver == 0) return;
   	CAMsetArguments Arg;
   	Arg.callType = 23;

    Arg.d_Size   = 4;
    double d[4];
    d[0] = xmin;
    d[1] = xmax;
    d[2] = ymin;
    d[3] = ymax;
    Arg.d = d;
    ODriver->accept(Arg);
}
void CAMgraphicsProcess::drawAxis()
{
	if(ODriver == 0) return;
    ODriver->accept(getNull(24));
}
void CAMgraphicsProcess::setTicks(long Mx, long mx, long Nx, long nx)
{
	if(ODriver == 0) return;
   	CAMsetArguments Arg;
   	Arg.callType = 25;

    Arg.i_Size   = 4;
    long i[4];
    i[0]  = Mx; i[1] = mx;
    i[2]  = Nx; i[3] = nx;
    Arg.i = i;

    ODriver->accept(Arg);
}
void CAMgraphicsProcess::setXTicks(long Mx, long mx)
{
	if(ODriver == 0) return;
   	CAMsetArguments Arg;
   	Arg.callType = 26;

    Arg.i_Size   = 2;
    long i[2];
    i[0]  = Mx; i[1] = mx;
    Arg.i = i;

    ODriver->accept(Arg);
}

void CAMgraphicsProcess::setYTicks(long Nx, long nx)
{
	if(ODriver == 0) return;
   	CAMsetArguments Arg;
   	Arg.callType = 27;

    Arg.i_Size   = 2;
    long i[2];
    i[0]  = Nx; i[1] = nx;
    Arg.i = i;

    ODriver->accept(Arg);
}
void CAMgraphicsProcess::xAxisOn(){if(ODriver == 0) return;ODriver->accept(getNull(28));}
void CAMgraphicsProcess::xAxisOff(){if(ODriver == 0) return;ODriver->accept(getNull(29));}
void CAMgraphicsProcess::yAxisOn(){if(ODriver == 0) return;ODriver->accept(getNull(30));}
void CAMgraphicsProcess::yAxisOff(){if(ODriver == 0) return;ODriver->accept(getNull(31));}
void CAMgraphicsProcess::axisOn(){if(ODriver == 0) return;ODriver->accept(getNull(32));}
void CAMgraphicsProcess::axisOff(){if(ODriver == 0) return;ODriver->accept(getNull(33));}
void CAMgraphicsProcess::xLabelsOn(){if(ODriver == 0) return;ODriver->accept(getNull(34));}
void CAMgraphicsProcess::xLabelsOff(){if(ODriver == 0) return;ODriver->accept(getNull(35));}
void CAMgraphicsProcess::yLabelsOn(){if(ODriver == 0) return;ODriver->accept(getNull(36));}
void CAMgraphicsProcess::yLabelsOff(){if(ODriver == 0) return;ODriver->accept(getNull(37));}
void CAMgraphicsProcess::labelsOn(){if(ODriver == 0) return;ODriver->accept(getNull(38));}
void CAMgraphicsProcess::labelsOff(){if(ODriver == 0) return;ODriver->accept(getNull(39));}


void CAMgraphicsProcess::setXAxisType(int t)
{
	if(ODriver == 0) return;
	CAMsetArguments Arg;
    Arg.callType = 40;

    Arg.i_Size = 1;
    long i[1];
	i[0] = t;
    Arg.i = i;

    ODriver->accept(Arg);
}
void CAMgraphicsProcess::setYAxisType(int t)
{
	if(ODriver == 0) return;
	CAMsetArguments Arg;
    Arg.callType  = 41;

    Arg.i_Size = 1;
    long i[1];
	i[0] = t;
    Arg.i = i;

    ODriver->accept(Arg);
}
void CAMgraphicsProcess::setIntercepts(double x, double y)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 42;

    Arg.d_Size   = 2;
    double d[2];
    d[0] = x;
    d[1] = y;
    Arg.d = d;

    ODriver->accept(Arg);
}
void CAMgraphicsProcess::setXIntercept(double x)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 43;

    Arg.d_Size   = 1;
    double d[1];
    d[0] = x;
    Arg.d = d;

    ODriver->accept(Arg);
}
void CAMgraphicsProcess::setYIntercept(double y)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 44;

    Arg.d_Size   = 1;
    double d[1];
    d[0] = y;
    Arg.d = d;

    ODriver->accept(Arg);
}

void CAMgraphicsProcess::setAxisColor(int iColor)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
    Arg.callType  = 45;

    Arg.i_Size = 1;
    long i[1];
	i[0] = iColor;
    Arg.i = i;

    ODriver->accept(Arg);
}
void CAMgraphicsProcess::setAxisColor(double* rgb)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 46;

    Arg.d_Size   = 3;
    double d[3];
    d[0] = rgb[0]; d[1] = rgb[1]; d[2] = rgb[2];
    Arg.d = d;

    ODriver->accept(Arg);
}

void CAMgraphicsProcess::setAxisLabelType(int t)
{
	if(ODriver == 0) return;
	CAMsetArguments Arg;
    Arg.callType  = 47;

    Arg.i_Size = 1;
    long i[1];
	i[0] = t;
    Arg.i = i;

    ODriver->accept(Arg);
}

void CAMgraphicsProcess::setAxisLabelWidth(int w)
{
	if(ODriver == 0) return;
	CAMsetArguments Arg;
    Arg.callType  = 48;

    Arg.i_Size = 1;
    long i[1];
	i[0] = w;
    Arg.i = i;

    ODriver->accept(Arg);
}
void CAMgraphicsProcess::setAxisLabelPrecision(int p)
{
    if(ODriver == 0) return;
	CAMsetArguments Arg;
    Arg.callType  = 49;

    Arg.i_Size = 1;
    long i[1];
	i[0] = p;
    Arg.i = i;

    ODriver->accept(Arg);
}
void CAMgraphicsProcess::setAxisLabelCharSize(double size)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 50;

    Arg.d_Size   = 1;
    double d[1];
    d[0] = size;
    Arg.d = d;

    ODriver->accept(Arg);
}
void CAMgraphicsProcess::setAxisLabelFormat(int t , int w, int p)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 51;

    Arg.i_Size   = 3;
    long i[3];
    i[0] = t; i[1] = w; i[2] = p;
    Arg.i = i;

    ODriver->accept(Arg);
}

void CAMgraphicsProcess::setPlotLineStyle(int s)
{
    if(ODriver == 0) return;
	 CAMsetArguments Arg;
    Arg.callType  = 71;

    Arg.i_Size = 1;
    long i[1];
	 i[0] = s;
    Arg.i = i;

    ODriver->accept(Arg);
 }

void CAMgraphicsProcess::setPlotLineColor(int c)
{
	if(ODriver == 0) return;
	CAMsetArguments Arg;
    Arg.callType  = 72;

    Arg.i_Size = 1;
    long i[1];
	i[0] = c;
    Arg.i = i;

    ODriver->accept(Arg);
 }

void CAMgraphicsProcess::setPlotLineColor(double* rgb)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 73;

    Arg.d_Size   = 3;
    double d[3];
    d[0] = rgb[0]; d[1] = rgb[1]; d[2] = rgb[2];

    std::cout << "CAMgraphicsProcess : " << d[0] << " " << d[1] << " " << d[2] << std::endl;
    Arg.d = d;

    ODriver->accept(Arg);
}

void CAMgraphicsProcess::setPlotDashPattern(int d)
{
	if(ODriver == 0) return;
	CAMsetArguments Arg;
    Arg.callType  = 74;

    Arg.i_Size = 1;
    long i[1];
	i[0] = d;
    Arg.i = i;

    ODriver->accept(Arg);
 }
void CAMgraphicsProcess::setPlotLineWidth(double w)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 75;

    Arg.d_Size   = 1;
    double d[1];
    d[0] = w;
    Arg.d = d;

    ODriver->accept(Arg);
}

void CAMgraphicsProcess::setPlotPointType(char p)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 76;

    Arg.b_Size   = 1;
    char b[1];
    b[0] = p;
    Arg.b = b;


	//Arg.b[0] = p;
    ODriver->accept(Arg);
 }

 void CAMgraphicsProcess::setPlotPointSize(double p)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
    Arg.callType = 77;

    Arg.d_Size   = 1;
    double d[1];
    d[0] = p;
    Arg.d = d;

    ODriver->accept(Arg);
 }

 void CAMgraphicsProcess::setPlotPointFont(const char* S)
 {
 	if(ODriver == 0) return;
    CAMsetArguments Arg;
    Arg.callType = 78;

    Arg.b_Size     = (long)strlen(S)+1;
    Arg.b          = S;

    ODriver->accept(Arg);
 }

void CAMgraphicsProcess::restorePlotDefaults()
{
    setPlotLineStyle(CAMgraphicsProcess::CURVE);
    setPlotLineColor(CAMgraphicsProcess::BLACK);
    setPlotDashPattern(CAMgraphicsProcess::SOLID);
    setPlotLineWidth(0.0);
    setPlotPointType('*');
    setPlotPointSize(0.02);
}

void CAMgraphicsProcess::setContourLevel(int n_c)
{
	if(ODriver == 0) return;
	CAMsetArguments Arg;
    Arg.callType  = 91;

    Arg.i_Size = 1;
    long i[1];
	 i[0] = n_c;
    Arg.i = i;
    
    ODriver->accept(Arg);
 }

void CAMgraphicsProcess::setContourLevel(double c_inc)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 92;

    Arg.d_Size   = 1;
    double d[1];
    d[0] = c_inc;
    Arg.d = d;

    ODriver->accept(Arg);
 }


void CAMgraphicsProcess::setContourLevel(double c_min, double c_max)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 93;

    Arg.d_Size   = 2;
    double d[2];
    d[0] = c_min; d[1] = c_max;
    Arg.d = d;

    ODriver->accept(Arg);
}

void CAMgraphicsProcess::setContourLevel(int n_c,double c_min, double c_max)
{
    if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 94;

    Arg.i_Size   = 1;
    long i[1];
    i[0] = n_c;
    Arg.i = i;

    Arg.d_Size   = 2;
    double d[2];
    d[0] = c_min; d[1] = c_max;
    Arg.d = d;

    ODriver->accept(Arg);
}

void CAMgraphicsProcess::setContourLevel(double c_inc,double c_min, double c_max)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 95;

    Arg.d_Size   = 3;
    double d[3];
    d[0] = c_inc; d[1] = c_min; d[2] = c_max;
    Arg.d = d;

    ODriver->accept(Arg);
}

void CAMgraphicsProcess::setContourLevel(double* c_values, int n_c)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 96;

    Arg.d_Size   = n_c;
    Arg.d        = c_values;

    Arg.i_Size   = 1;
    long i[1];
    i[0]        = n_c;
    Arg.i       = i;

    ODriver->accept(Arg);
}


void CAMgraphicsProcess::autoContourOn(){if(ODriver == 0) return;ODriver->accept(getNull(97));}
void CAMgraphicsProcess::autoContourOff(){if(ODriver == 0) return;ODriver->accept(getNull(98));}
void CAMgraphicsProcess::contourLineLabelsOn(){if(ODriver == 0) return;ODriver->accept(getNull(99));}
void CAMgraphicsProcess::contourLineLabelsOff(){if(ODriver == 0) return;ODriver->accept(getNull(100));}
void CAMgraphicsProcess::contourHighLowLabelsOn(){if(ODriver == 0) return;ODriver->accept(getNull(101));}
void CAMgraphicsProcess::contourHighLowLabelsOff(){if(ODriver == 0) return;ODriver->accept(getNull(102));}

void CAMgraphicsProcess::contourBackgroundOn(){if(ODriver == 0) return;ODriver->accept(getNull(103));}
void CAMgraphicsProcess::contourBackgroundOff(){if(ODriver == 0) return;ODriver->accept(getNull(104));}
void CAMgraphicsProcess::contourScaledFrameOn(){if(ODriver == 0) return;ODriver->accept(getNull(105));}
void CAMgraphicsProcess::contourScaledFrameOff(){if(ODriver == 0) return;ODriver->accept(getNull(106));}

void CAMgraphicsProcess::setSurfaceViewPoint(double vx, double vy ,double vz)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 121;

    Arg.d_Size   = 3;
    double d[3];
    d[0] = vx; d[1] = vy; d[2] = vz;
    Arg.d = d;
    
    ODriver->accept(Arg);
}
void CAMgraphicsProcess::setSurfaceFocus(double fx, double fy ,double fz)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 122;

    Arg.d_Size   = 3;
    double d[3];
    d[0] = fx; d[1] = fy; d[2] = fz;
    Arg.d = d;

    ODriver->accept(Arg);

}
void CAMgraphicsProcess::setSurfaceScaleFactor(double s)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 123;

    Arg.d_Size   = 1;
    double d[1];
    d[0] = s;
    Arg.d = d;

    ODriver->accept(Arg);
}

void CAMgraphicsProcess::setTextColor(int iColor)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
    Arg.callType  = 145;

    Arg.i_Size = 1;
    long i[1];
	i[0] = iColor;
    Arg.i = i;

    ODriver->accept(Arg);
}
void CAMgraphicsProcess::setTextColor(double* rgb)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 146;

    Arg.d_Size   = 3;
    double d[3];
    d[0] = rgb[0]; d[1] = rgb[1]; d[2] = rgb[2];
    Arg.d = d;

    ODriver->accept(Arg);
}

void CAMgraphicsProcess::setTextAlign(double horiz, double vert)
{
	if(ODriver == 0) return;
    CAMsetArguments Arg;
   	Arg.callType = 147;

    Arg.d_Size   = 2;
    double d[2];
    d[0] = horiz; d[1] = vert; 
    Arg.d = d;

    ODriver->accept(Arg);
}



 
