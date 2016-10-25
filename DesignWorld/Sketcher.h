/* cpp

Date        Author      Remark
2016/05/06      Srinivas    Intail Version
HISTORY*/

#include "Object.h"
#include "Plane.h"

class Sketcher :
    public Object
{
public:
    Sketcher();
    ~Sketcher();

private:
    Plane sketchingPlane;
};

