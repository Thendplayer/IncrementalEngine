#ifndef _Math_H
#define _Math_H

#define LENGTH(a,b) sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z))
#define DEG2RAD(x) x*XM_PI/180.0f
#define RAD2DEG(x) x*180.0f/XM_PI

#endif