#pragma once

#include "Matrix.h"

// CGeomEntity command target

class CGeomEntity
{
    CGeomEntity( );
    CGeomEntity( const CGeomEntity& ge ) {}; // copy sonstructor		//To aviod complie errors, CObject declares
    CGeomEntity& operator =( const CGeomEntity& ge ){ return *this; };  // copy constructor and assignment operator as private.
    virtual ~CGeomEntity( );
public:
    virtual void Draw( ) = 0;
    virtual void Serialize( CArchive& ar );
    eGeometry GetGeometryType(){ return m_eGeomType; };

    void SetSelectionStatus(bool bSelected = true);
    bool GetSelectionStatus();

    void SetHiddenStatus(bool bHidden = true);
    bool GetHiddenStatus();

    COLORREF SetEntityColor(COLORREF setColor);

    unsigned int GetID();

private:
    bool m_bSelected;
    bool m_bHidden;
    COLORREF m_clrCurveColor;
    unsigned int m_ID;
};

class CGeomPoint : public CGeomEntity
{
    short m_Dim;
    double m_Coord[4];
public:
    CGeomPoint( );
    CGeomPoint( int iDim, double Coord[] );
    CGeomPoint( double x, double y, double z );
    virtual ~CGeomPoint( );

    void Draw( );
    static CGeomPoint CptToGeomPt( CPoint pt );
    static CPoint GeomPtToCpt( CGeomPoint* dpt );

    virtual void Serialize( CArchive& ar );
};

class CDoublePoint : public CGeomEntity
{
    DECLARE_SERIAL( CDoublePoint )
public:
    double x;
    double y;
    double z;
public:
    CDoublePoint();
    virtual ~CDoublePoint();
public:
    void Draw( ){};
    void Serialize(CArchive &ar);
};

void TransFormEntity( CGeomPoint *pgptEntity, int iCount, Matrix &matTransf, CGeomPoint *pgptTransfEntity );
void TransfToWorld( double *pdVector, Matrix &matTransf );
void DrawPoints( int nPt, double dSize, CGeomPoint *pgptKnotPt );