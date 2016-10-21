/* Object.h designworld

Date        Author      Remark
20-Nov-2013 srinivas    Intail Version
$HISTORY$*/

#pragma once

#include <stdio.h>


#if defined(DESIGNWORLD_EXPORT) // inside DLL
#   define DESIGNWORLDAPI   __declspec(dllexport)
#else // outside DLL
#   define DESIGNWORLDAPI   __declspec(dllimport)
#endif  // DESIGNWORLD_EXPORT

class Object
{
public:
    Object(void);
    virtual ~Object(void);
};

