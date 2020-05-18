#ifndef _Math_Utils_H
#define _Math_Utils_H

#define PI 3.14159265358979323846

#define LENGTH(a,b) sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z))
#define DEG2RAD(x) x*PI/180.0f
#define RAD2DEG(x) x*180.0f/PI

#endif