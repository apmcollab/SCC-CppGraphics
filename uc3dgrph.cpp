//
//******************************************************************************
//                              UC3dgrph.cpp
//******************************************************************************
// 
//            SOURCE FILE FOR CLASS UC3dgraph
//
//********************************************************************************
//            David Sansot                (C) UCLA 1994,1995
//********************************************************************************
//
#include "uc3dgrph.h"
#include <stdlib.h>
#include <math.h>
//
//******************************************************************************
//                     SET_UP_TRANSFORMATION
//******************************************************************************
//
void UC3dgraph::set_up_transformation()
{
    // Calculate the view direction vector
  double VDx = Fx - VPx;
  double VDy = Fy - VPy;
  double VDz = Fz - VPz;

    // Calculate the length of the view direction vector
  D = std::sqrt(VDx*VDx + VDy*VDy + VDz*VDz);

    // Vector U is the up direction
  double Ux, Uy, Uz;
  Ux = Uy = 0; Uz = 1;

    // Make trans_matrix an identity matrix
  idmat(trans_matrix);

     // Translation
  trans_matrix[3]  = -VPx;
  trans_matrix[7]  = -VPy;
  trans_matrix[11] = -VPz;

    // First rotation - about y
  double p = std::sqrt(VDx*VDx + VDz*VDz);
  double m[16];

  if (p)
  {
    idmat(m);
    m[0] = VDz/p;   m[8] = VDx/p;
     m[2] = -VDx/p;  m[10] = VDz/p;
    matmult(trans_matrix,m);
  }

    // Second rotation - about x
  idmat(m);
  m[5] = p/D;    m[9] = VDy/D;
  m[6] = -VDy/D; m[10] = p/D;
  matmult(trans_matrix,m);


    // Rotate U
  if (p)
  {
    Uy = Uy*p/D - VDy*(Ux*VDx + Uz*VDz)/(p*D);
     Ux = (Ux*VDz - Uz*VDx)/p;
  }
  else
    Uy = -Uz*VDy/D;

  double w = std::sqrt(Ux*Ux + Uy*Uy);

    // Rotate about z so that the image of U points up on the screen
  if (w)
  {
    idmat(m);
    m[0] = -Uy/w;  m[4] = -Ux/w;
    m[1] = Ux/w;   m[5] = -Uy/w;
     matmult(trans_matrix,m);
  }
}
//
//******************************************************************************
//                     MATMULT
//******************************************************************************
//
void UC3dgraph::matmult(double * trans, double *m)
{
  // Function matmult multiplies two 4x4 matrices and returns the
  //   result in trans.

  double h[16];
  double *ptr1, *ptr2, sum;
  int i,j,k;

  ptr1 = h; ptr2 = trans;
  for (i = 0; i < 16; i++)
    *(ptr1++) = *(ptr2++);

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
     {
      sum = 0;
      for (k = 0; k < 4; k++)
        sum = sum + h[i + 4*k]*m[k + 4*j];
      trans[i + 4*j] = sum;
     }
}
//
//******************************************************************************
//                     IDMAT
//******************************************************************************
//
void UC3dgraph::idmat(double *m)
{
  //  Function idmat turns the 4x4 matrix m into an identity matrix

  for (int i = 0; i < 16; i++)
    m[i] = 0;

  m[0] = m[5] = m[10] = m[15] = 1;
}
//
//******************************************************************************
//                     MAP_COORDINATES
//******************************************************************************
//
void UC3dgraph::map_coordinates(double Px, double Py, double Pz,
                    double &xp, double &yp)
{
  // This function uses trans_matrix to map the world coordinates
  //   to screen coordinates

  double zp = Px*trans_matrix[8] + Py*trans_matrix[9] +
                  Pz*trans_matrix[10] + trans_matrix[11];

  xp = Px*trans_matrix[0] + Py*trans_matrix[1] +
         Pz*trans_matrix[2] + trans_matrix[3];
  xp = D*xp/zp;

  yp = Px*trans_matrix[4] + Py*trans_matrix[5] +
         Pz*trans_matrix[6] + trans_matrix[7];
  yp = D*yp/zp;
}
//
//******************************************************************************
//                     SCALE_AND_TRANSLATE
//******************************************************************************
//
void UC3dgraph::scale_and_translate(double &x, double &y)
{
    //  Function scales and translates the screen coordinated.  It
    //    also flips the y axis.
  x = xoffset + x*scale_factor;
  y = yoffset - y*scale_factor;
}

 
