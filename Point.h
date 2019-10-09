/* Definition de la classe Point3D */

#ifndef _HEADER_POINT_H_
#define _HEADER_POINT_H_


#include <stdlib.h>
#include <math.h>


class Point3D
{
public:
   Point3D( float _x = 0, float _y = 0, float _z = 0 )
      : x(_x), y(_y), z(_z) {};
   Point3D( const Point3D& mdd )
      : x(mdd.x), y(mdd.y), z(mdd.z) {};

   const Point3D& operator=( const Point3D& mdd ) {
      x = mdd.x; y = mdd.y; z = mdd.z;
      return *this;
   }

protected:
   float x, y, z;
};

#endif
