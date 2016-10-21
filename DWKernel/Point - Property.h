/* Point.h geometry

Date        Author      Remark
20-Nov-2013 srinivas    Intail Version
$HISTORY$*/

#pragma once
#include "Geometry.h"
#include "Vector.h"

struct str_POINT {

    double *m_Coord;
    //double x, y, z, h;

    // struct {

    //    void operator = (const double &i) { str_POINT::m_Coord[0] = i; return; }
    //    operator const double &() const { return str_POINT::m_Coord[0]; }
    //}x;

    //struct {
    //    void operator = (const double &i) { str_POINT::m_Coord[1] = i;  return; }
    //    operator const double &() const { return str_POINT::m_Coord[1]; }
    //}y;

    //struct {
    //    void operator = (const double &i) { str_POINT::m_Coord[2] = i; return; }
    //    operator const double &() const { return str_POINT::m_Coord[2]; }
    //}z;

    //struct {
    //    void operator = (const double &i) { str_POINT::m_Coord[3] = i; return; }
    //    operator const double &() const { return str_POINT::m_Coord[3]; }
    //}h;


    //struct X{
    //    X(const X &i){ str_POINT::m_Coord[0] = i; }
    //    X &operator = (const double &i) { str_POINT::m_Coord[0] = i; return *this; }
    //    operator const double &() const { return str_POINT::m_Coord[0]; }
    //}x;

    //struct Y{
    //    Y(const Y &i){ str_POINT::m_Coord[1] = i; }
    //    Y &operator = (const double &i) { str_POINT::m_Coord[1] = i;  return *this; }
    //    operator const double &() const { return str_POINT::m_Coord[1]; }
    //}y;

    //struct Z{
    //    Z(const Z &i){ str_POINT::m_Coord[2] = i; }
    //    Z &operator = (const double &i) { str_POINT::m_Coord[2] = i; return *this; }
    //    operator const double &() const { return str_POINT::m_Coord[2]; }
    //}z;

    //struct H{
    //    H(const H &i){ str_POINT::m_Coord[3] = i; }
    //    H &operator = (const double &i) { str_POINT::m_Coord[3] = i; return *this; }
    //    operator const double &() const { return str_POINT::m_Coord[3]; }
    //}h;


    //inline double(&x()){ return m_Coord[0]; }
    //inline double(&y()){ return m_Coord[1]; }
    //inline double(&z()){ return m_Coord[2]; }
    //inline double(&h()){ return m_Coord[3]; }


    //inline double &x(double x){ m_Coord[0] = x; }
    //inline double &y(double y){ m_Coord[1] = y; }
    //inline double &z(double z){ m_Coord[2] = z; }
    //inline double &h(double h){ m_Coord[3] = h; }

    inline double getx(){ return m_Coord[0]; }
    inline double gety(){ return m_Coord[1]; }
    inline double getz(){ return m_Coord[2]; }
    inline double geth(){ return m_Coord[3]; }


    inline double setx(const double &x){ m_Coord[0] = x; return x;}
    inline double sety(const double &y){ m_Coord[1] = y; return y;}
    inline double setz(const double &z){ m_Coord[2] = z; return z;}
    inline double seth(const double &h){ m_Coord[3] = h; return h;}

    Property<double, str_POINT, &str_POINT::getx, &str_POINT::setx> x;
    Property<double, str_POINT, &str_POINT::gety, &str_POINT::sety> y;
    Property<double, str_POINT, &str_POINT::getz, &str_POINT::setz> z;
    Property<double, str_POINT, &str_POINT::geth, &str_POINT::seth> h;

    str_POINT()
    {
        m_Coord = new double[4];
        for (int i = 0; i < THREED; i++)
        {
            m_Coord[i] = 0;
        }
        m_Coord[FOURD] = 1;

        //x = m_Coord[0];
        //y = m_Coord[1];
        //z = m_Coord[2];
        //h = m_Coord[3];
        x(this);
        y(this);
        z(this);
        h(this);
    }

    str_POINT(double X, double Y)
    {
        m_Coord = new double[4];
        m_Coord[0] = X;
        m_Coord[1] = Y;
        m_Coord[2] = 0;
        m_Coord[3] = 1;

        //x = m_Coord[0];
        //y = m_Coord[1];
        //z = m_Coord[2];
        //h = m_Coord[3];
        x(this);
        y(this);
        z(this);
        h(this);
    }

    str_POINT(double X, double Y, double Z)
    {
        m_Coord = new double[4];
        m_Coord[0] = X;
        m_Coord[1] = Y;
        m_Coord[2] = Z;
        m_Coord[3] = 1;

        //x = m_Coord[0];
        //y = m_Coord[1];
        //z = m_Coord[2];
        //h = m_Coord[3];

        x(this);
        y(this);
        z(this);
        h(this);
    }
};

typedef str_POINT SPoint;


class Point :
    public Geometry
{
public:
    //Class Constructors
    Point(void);
    Point(const Point &Point);
    Point(SPoint point);
    Point(int iDim, double dCord[]);
    Point(double x, double y, double z=0, double h = 1);
    ~Point(void);

    double X();
    double Y();
    double Z();

    void ModifyPoint(const Point &point);
    void ModifyPoint(double x, double y, double z=0, double h=1);
    void ModifyPoint(int iDim, double dCoord[]);

    //Operator Overloading
    Point &operator =(const Point &point);
    Point operator +(Point &point);
    Point operator +(Vector &vec);
    
private:
    int m_iDimension;
    SPoint m_point;
};

