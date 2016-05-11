#include "BSpline.h"


BSpline::BSpline()
{
}


BSpline::~BSpline()
{
}


//BSpline routines

double DistanceBetweenPoints(double* pdFirst, double* pdEnd)
{
    double dist = 0.0;

    dist = sqrt((pdEnd[0] - pdFirst[0])*(pdEnd[0] - pdFirst[0]) +
        (pdEnd[1] - pdFirst[1])*(pdEnd[1] - pdFirst[1]) +
        (pdEnd[2] - pdFirst[2])*(pdEnd[2] - pdFirst[2]));

    //dist = sqrt(sqr(pdEnd[0]-pdFirst[0])+ sqr(pdEnd[1]-pdFirst[1])+ sqr(pdEnd[2]-pdFirst[2]));

    return dist;
}

// Finding Min, Max from given array using (bubble) sorting method.
void FindMinMax(double * const pdSourceArr, int iSize, double &dMaxValue, double &dMinValue)
{
    double *pdArr = new double[iSize];

    for (int i = 0; i < iSize; i++)
        pdArr[i] = pdSourceArr[i];

    //int iSize = sizeof pdArr / sizeof( double );
    double dTemp = 0.0;
    for (int i = 0; i < iSize - 1; ++i)
    {
        for (int j = i + 1; j < iSize; ++j)
        {
            if (pdArr[i] >  pdArr[j])
            {
                dTemp = pdArr[i];
                pdArr[i] = pdArr[j];
                pdArr[j] = dTemp;
            }
        }
    }

    dMinValue = pdArr[0];
    dMaxValue = pdArr[iSize - 1];

    if (pdArr) delete[] pdArr;
}
void bspline_i(int n/*iCtrlPt*/, int k/*iOrder*/, int nSpanPt, double *pdKontVec, SPoint *pdCtrlPt, SPoint *pdCurvePt, int &iCurvePt)
{
    Matrix mCtrPts(n, THREED);

    for (int i = 0; i < n; i++)
    {
        //mCtrPts( i, 0 ) = pdCtrlPt[i].x;
        //mCtrPts( i, 1 ) = pdCtrlPt[i].y;
        //mCtrPts( i, 2 ) = pdCtrlPt[i].z;
        for (int j = 0; j < THREED; j++)
            mCtrPts(i, j) = pdCtrlPt[i][j];
    }

    double *X = new double[n + k + 1];
    for (int i = 1; i < n + k + 1; i++)
        X[i] = pdKontVec[i - 1];

    Matrix N((n + k /*-1*/), k + 1);
    iCurvePt = 0;
    double d = (X[n + k /*-1*/] - X[1]) / (float)(nSpanPt - 1);
    for (double t = X[1/*k*/]; t <= X[n + k/*n+1*/]; t += d)
    {
        for (int i = 1; i < (n + k); i++)
        {
            if (X[i] <= t && t < X[i + 1])
                N(i, 1) = 1;
            else
                N(i, 1) = 0;
        }

        for (int j = 2; j <= k; j++)
        {
            for (int i = 1; i < (n + k); i++)
            {
                if ((i + j) <= (n + k))
                {
                    if ((X[i + j - 1] - X[i]) != 0)
                    {
                        if ((X[i + j] - X[i + 1]) != 0)
                            N(i, j) = ((t - X[i])*N(i, j - 1) / (X[i + j - 1] - X[i])) + ((X[i + j] - t)*N(i + 1, j - 1) / (X[i + j] - X[i + 1]));
                        else
                            N(i, j) = ((t - X[i])*N(i, j - 1) / (X[i + j - 1] - X[i]));
                    }
                    else if ((X[i + j] - X[i + 1]) != 0)
                        N(i, j) = ((X[i + j] - t)*N(i + 1, j - 1) / (X[i + j] - X[i + 1]));
                    else
                        N(i, j) = 0;
                }
                else N(i, j) = 0;
            }
        }
        Matrix M(1, n);
        for (int i = 0; i < n; i++)
            M(0, i) = N(i + 1, k/*-1*/);
        Matrix mPoint = M*mCtrPts;
        //pdCurvePt[iCurvePt].x = mPoint(0, 0);
        //pdCurvePt[iCurvePt].y = mPoint(0, 1);
        //pdCurvePt[iCurvePt].z = mPoint(0, 2);
        for (int j = 0; j < THREED; j++)
            pdCurvePt[iCurvePt][j] = mPoint(0, j);
        iCurvePt++;
    }

    if (X) delete[] X;
}


void BSpline_btParam(int n/*iCtrlPt*/, int k/*iOrder*/, int iSpanPt, double *pdParamRange, double *pdKontVec, SPoint *pgptCtrl, SPoint *pgptCurve, int &iCurvePt)
{
    Matrix mCtrPts(n, THREED);
    for (int i = 0; i < n; i++)
    {
        //mCtrPts(i, 0) = pgptCtrl[i].x;
        //mCtrPts(i, 1) = pgptCtrl[i].y;
        //mCtrPts(i, 2) = pgptCtrl[i].z;

        for (int j = 0; j < THREED; j++)
            mCtrPts(i, j) = pgptCtrl[i][j];
    }

    double *pdBSplnBlends = new double[n];
    double d = (pdParamRange[1] - pdParamRange[0]) / (float)(iSpanPt - 1);
    iCurvePt = 0;

    //Output file
    //std::ofstream streamOut("C:\\Documents and Settings\\srinivasreddy\\Desktop\\Bspline.txt", std::ios_base::app);
    //static int i = 0;
    //streamOut << "Bspline :" << i++;
    //streamOut.precision(13);
    //streamOut.width(20);

    for (double t = pdParamRange[0]; t < pdParamRange[1]; t += d)
    {
        BSplineBlends(t, n, k, pdKontVec, pdBSplnBlends);

        Matrix M(1, n);

        for (int i = 0; i < n; i++)
            M(0, i) = pdBSplnBlends[i];

        Matrix mPoint = M*mCtrPts;

        //pgptCurve[iCurvePt].x = mPoint(0, 0);
        //pgptCurve[iCurvePt].y = mPoint(0, 1);
        //pgptCurve[iCurvePt].z = mPoint(0, 2);

        for (int j = 0; j < THREED; j++)
            pgptCurve[iCurvePt][j] = mPoint(0, j);

        ////Output file
        //streamOut << pgptCurve[iCurvePt][0] << "\t" << pgptCurve[iCurvePt][1] <<  "\t" << pgptCurve[iCurvePt][2] << "\tat\t" << t << "\n";

        iCurvePt++;
    }

    ////Output file
    //streamOut.close();

    if (pdBSplnBlends) delete[] pdBSplnBlends;
}

void BSplineBlends(double t/*dParam*/, int n/*iCtrlPt*/, int k/*iOrder*/, double *pdKontVec, double *pdBSplnBlends)
{
    double *X = new double[n + k + 1];
    for (int i = 1; i < n + k + 1; i++)
        X[i] = pdKontVec[i - 1];

    Matrix N((n + k), k + 1);

    for (int i = 1; i < (n + k); i++)
    {
        if (X[i] <= t && t < X[i + 1])
            N(i, 1) = 1;
        else
            N(i, 1) = 0;
    }

    for (int j = 2; j <= k; j++)
    {
        for (int i = 1; i < (n + k); i++)
        {
            if ((i + j) <= (n + k))
            {
                if ((X[i + j - 1] - X[i]) != 0)
                {
                    if ((X[i + j] - X[i + 1]) != 0)
                        N(i, j) = ((t - X[i])*N(i, j - 1) / (X[i + j - 1] - X[i])) + ((X[i + j] - t)*N(i + 1, j - 1) / (X[i + j] - X[i + 1]));
                    else
                        N(i, j) = ((t - X[i])*N(i, j - 1) / (X[i + j - 1] - X[i]));
                }
                else if ((X[i + j] - X[i + 1]) != 0)
                    N(i, j) = ((X[i + j] - t)*N(i + 1, j - 1) / (X[i + j] - X[i + 1]));
                else
                    N(i, j) = 0;
            }
            else N(i, j) = 0;
        }
    }

    for (int i = 0; i < n; i++)
        pdBSplnBlends[i] = N(i + 1, k);

    if (X) delete[] X;
}

int NURBSFindKnotSpan(int nKnots, double *knots, int degree, double u,
    int &knot_span)
{
    if (u == knots[degree])
    {
        knot_span = degree;
        return 0;
    }
    if (u == knots[nKnots - degree - 1])
    {
        knot_span = nKnots - degree - 2;
        return 0;
    }

    int low, high, mid;
    low = degree;
    high = nKnots - 1 - degree;
    mid = (low + high) / 2;

    int mid_prev = 0;
    while (u < knots[mid] || u >= knots[mid + 1])
    {
        if (u < knots[mid])
            high = mid;
        else low = mid;
        mid = (low + high) / 2;
        if (mid == mid_prev)
            break;
        else
            mid_prev = mid;
    }
    knot_span = mid;

    return 1;
}


void BSplineBlends_1(double t/*dParam*/, int n/*iCtrlPt*/, int k/*iOrder*/, double *pdKontVec, double *pdBSplnBlends)
{
    double *knots = pdKontVec;

    int iDegree = k - 1;
    int iKnots = n + k;
    int iKnotSpans = iKnots - 1;
    int iSpan;

    double *N = new double[k];

    int i, l, j;
    for (i = 0; i < iKnotSpans; i++)
    {
        if (t >= knots[i] && t < knots[i + 1])
        {
            iSpan = i;
            break;
        }
    }

    double *left = new double[k];
    double *right = new double[k];
    double saved = 0;
    double temp = 0;
    i = iSpan;
    N[0] = 1.0;
    for (j = 1; j <= iDegree; j++)
    {
        left[j] = t - knots[i + 1 - j];
        right[j] = knots[i + j] - t;
        saved = 0.0;
        for (l = 0; l < j; l++)
        {
            temp = N[l] / (right[l + 1] + left[j - l]);
            N[l] = saved + right[l + 1] * temp;
            saved = left[j - l] * temp;
        }
        N[j] = saved;
    }
    delete[] left;
    delete[] right;
    double alpha = 0.0;
    j = iSpan - iDegree;
    for (i = j; i <= iSpan; i++)
    {
        pdBSplnBlends[i] = N[i - j];
    }

    delete[] N;
}

void BSplineBlends_2(double u/*dParam*/, int iCtrlPt, int iOrder, double *pdKontVec, double *pdBSplnBlends, int iDervs, double **pdBlendDervs)
{
    double *pdK = pdKontVec;

    int iDegree = iOrder - 1;
    int iKnots = iCtrlPt + iOrder;
    int iKnotSpans = iKnots - 1;
    int iSpan = 0;

    double **N = new double*[iOrder];
    for (int i = 0; i < iOrder; i++)
        N[i] = new double[iCtrlPt];

    for (int i = 0; i < iOrder; i++)
        for (int j = 0; j < iCtrlPt; j++)
            N[i][j] = 0.0;

    for (int k = 0; k < iKnotSpans; k++)
    {
        if (u >= pdK[k] && u < pdK[k + 1])
        {
            iSpan = k;
            N[0][iSpan] = 1.0;
            break;
        }
    }

    for (int d = 1; d <= iDegree; d++)
    {
        N[d][iSpan - d] = (pdK[iSpan + 1] - u) / (pdK[iSpan + 1] - pdK[(iSpan - d) + 1])*N[d - 1][(iSpan - d) + 1];
        for (int i = iSpan - d + 1; i <= (iSpan - 1); i++)
        {
            N[d][i] = (u - pdK[i]) / (pdK[i + d] - pdK[i])*N[d - 1][i] + (pdK[i + d + 1] - u) / (pdK[i + d + 1] - pdK[i + 1])*N[d - 1][i + 1];
        }
        N[d][iSpan] = (u - pdK[iSpan]) / (pdK[iSpan + d] - pdK[iSpan])*N[d - 1][iSpan];
    }

    //Get maximum derivative index and set zero derivatives
    iDervs = (iDegree < iDervs ? iOrder : ++iDervs);
    double **dN = new double*[iDervs];

    for (int i = 0; i < iDervs; i++)
        dN[i] = new double[iCtrlPt];

    for (int i = 0; i < iDervs; i++)
        for (int j = 0; j < iCtrlPt; j++)
            dN[i][j] = 0.0;

    for (int i = 0; i < iCtrlPt; i++)
    {
        dN[0][i] = N[iDegree][i];
        if (pdBSplnBlends) pdBSplnBlends[i] = N[iDegree][i];
        if (pdBlendDervs) pdBlendDervs[0][i] = N[iDegree][i];
    }

    for (int d = 1; d < iDervs; d++)
    {
        for (int k = iDegree; k > 0; k--)
        {
            N[k][iSpan - k] = k / (pdK[iSpan + 1] - pdK[(iSpan - k) + 1])*N[k - 1][(iSpan - k) + 1];
            for (int i = iSpan - k + 1; i <= (iSpan - 1); i++)
            {
                N[k][i] = k / (pdK[i + k] - pdK[i])*N[k - 1][i] + k / (pdK[i + k + 1] - pdK[i + 1])*N[k - 1][i + 1];
            }
            N[k][iSpan] = k / (pdK[iSpan + k] - pdK[iSpan])*N[k - 1][iSpan];
        }
        for (int i = 0; i < iCtrlPt; i++)
        {
            dN[d][i] = N[iDegree][i];
            if (pdBlendDervs[d]) pdBlendDervs[d][i] = N[iDegree][i];
        }
    }

    if (dN)
    {
        for (int i = 0; i < iDervs; i++)
            delete[] dN[i];
        delete[] dN;
    }

    if (N)
    {
        for (int i = 0; i < iOrder; i++)
            delete[] N[i];
        delete[] N;
    }
}

void GetBSplineKnotPoints(int iCtrlPt, int iOrder, double  *pdKnotVec, SPoint *pgptCtrlPt, SPoint *pgptKnotPt)
{
    double *pdBSplnBlends = new double[iCtrlPt];

    Matrix mCtrPts(iCtrlPt, THREED);

    for (int i = 0; i < iCtrlPt; i++)
    {
/*
        mCtrPts(i, 0) = pgptCtrlPt[i].x;
        mCtrPts(i, 1) = pgptCtrlPt[i].y;
        mCtrPts(i, 2) = pgptCtrlPt[i].z;*/

        for (int j = 0; j < THREED; j++)
            mCtrPts(i, j) = pgptCtrlPt[i][j];
    }

    for (int i = 0; i < (iCtrlPt + iOrder); i++)
    {
        double t = pdKnotVec[i];
        if (!IsPeriodic(iCtrlPt, iOrder, pdKnotVec))
        {
            if (i >= iCtrlPt)
                t = t * 0.999999999;
        }
        else if (i == (iCtrlPt + iOrder - 1))
            t = t * 0.999999999;
        BSplineBlends(t, iCtrlPt, iOrder, pdKnotVec, pdBSplnBlends);

        Matrix M(1, iCtrlPt);

        for (int l = 0; l < iCtrlPt; l++)
            M(0, l) = pdBSplnBlends[l];

        Matrix mPoint = M*mCtrPts;
/*
        pgptKnotPt[i].x = mPoint(0, 0);
        pgptKnotPt[i].y = mPoint(0, 1);
        pgptKnotPt[i].z = mPoint(0, 2);*/


        for (int j = 0; j < THREED; j++)
            pgptKnotPt[i][j] = mPoint(0, j);
    }

    if (pdBSplnBlends) delete[] pdBSplnBlends;
}

void GetBSplineDataPoints(int iCtrlPt, int iOrder, double *pdParamRange, double  *pdKnotVec, eBSplineFitMethod methodBsplineFit, SPoint *pgptCtrlPt, SPoint *pgptDataPt)
{
    double *pdBSplnBlends = new double[iCtrlPt];

    Matrix mCtrPts(iCtrlPt, THREED);
    for (int i = 0; i < iCtrlPt; i++)
    {

        mCtrPts(i, 0) = pgptCtrlPt[i].x;
        mCtrPts(i, 1) = pgptCtrlPt[i].y;
        mCtrPts(i, 2) = pgptCtrlPt[i].z;

        //for (int j = 0; j < THREED; j++)
        //    mCtrPts(i, j) = pgptCtrlPt[i][j];
    }

    double dFirst[3] = { 0 };
    double dEnd[3] = { 0 };
    double *D = new double[iCtrlPt];
    for (int i = 0; i < iCtrlPt; i++)
        D[i] = 0.0;
    for (int k = 1; k < iCtrlPt; k++)
    {
        if (k)
        {
            for (int i = 0; i < 3; i++)
                dFirst[i] = pgptCtrlPt[k - 1][i];
            for (int i = 0; i < 3; i++)
                dEnd[i] = pgptCtrlPt[k][i];

            D[k] = DistanceBetweenPoints(dFirst, dEnd);
        }
    }


    double a = pdParamRange[0];
    double b = pdParamRange[1];

    for (int k = 0; k < iCtrlPt; k++)
    {
        double d = 0.0;
        double Dmax = 0.0;
        double t = 0.0;

        if (methodBsplineFit == BSPLINE_FIT_UNIFORMSPACE)
            t = a + (b - a)*k / (iCtrlPt - 1);
        else if (methodBsplineFit == BSPLINE_FIT_CHORDLENGTH)
        {
            for (int i = 0; i < k + 1; i++)
                d = d + D[i];
            for (int i = 0; i < iCtrlPt; i++)
                Dmax += D[i];
            t = a + (b - a)*(d / Dmax);
        }
        else if (methodBsplineFit == BSPLINE_FIT_CENTRIPETAL)
        {
            for (int i = 0; i < k + 1; i++)
                d = d + sqrt(D[i]);
            for (int i = 0; i < iCtrlPt; i++)
                Dmax += sqrt(D[i]);
            t = a + (b - a)*(d / Dmax);
        }

        if (k == (iCtrlPt - 1))
            t = t * 0.9999999999;

        BSplineBlends(t, iCtrlPt, iOrder, pdKnotVec, pdBSplnBlends);

        Matrix M(1, iCtrlPt);

        for (int i = 0; i < iCtrlPt; i++)
            M(0, i) = pdBSplnBlends[i];

        Matrix mPoint = M*mCtrPts;

        pgptDataPt[k].x = mPoint(0, 0);
        pgptDataPt[k].y = mPoint(0, 1);
        pgptDataPt[k].z = mPoint(0, 2);

        for (int j = 0; j < THREED; j++)
            pgptDataPt[k][j] = mPoint(0, j);
    }
}

void OpenUniformKnotVector(int nCtrlPt, int iOrder, double *pdKontVec, bool bNorm)
{
    int n = nCtrlPt - 1;
    int k = iOrder;
    for (int j = 0; j < (n + k + 1); j++)
    {
        if (j < k)
            pdKontVec[j] = 0;
        if (k <= j && j <= n)
            pdKontVec[j] = j - k + 1;
        if (n + 1 <= j && j <= n + k)
            pdKontVec[j] = n - k + 2;
    }
    if (bNorm)
    {
        double d = pdKontVec[n + k];
        for (int i = 0; i < (n + k + 1); i++)
            pdKontVec[i] = pdKontVec[i] / d;
    }
}

void PeriodicKnotVector(int nCtrlPt, int iOrder, double *pdKontVec, bool bNorm)
{
    int n = nCtrlPt - 1;
    int k = iOrder;
    for (int i = 0; i < (n + k + 1); i++) //periodic knot vector
        pdKontVec[i] = i;

    double d = pdKontVec[n + k];

    if (bNorm)
    {
        for (int i = 0; i < (n + k + 1); i++)
            pdKontVec[i] = pdKontVec[i] / d;
    }
}

int IsPeriodic(int iCtrlPt, int iOrder, double *pdKnotVec)
{
    int n = iCtrlPt;
    int k = iOrder;
    int iFlag = 0;
    for (int i = 1, j = n + k - 1; i < k; i++, j--)
    {
        if (pdKnotVec[i] == pdKnotVec[i - 1] && pdKnotVec[j] == pdKnotVec[j - 1])
            iFlag = 0;
        else
        {
            iFlag = 1;
            break;
        }
    }
    return iFlag;
}

//BSpline Fit using Chord length approximation technique.
void BSplineFit(int nCtrlPt, int iOrder, double *pdParamRange, double *pdKnotVec, int nDataPt, eBSplineFitMethod methodBsplineFit, SPoint *pgptData, SPoint *pgptCtrl)
{
    Matrix mDataPts(nDataPt, THREED);
    for (int i = 0; i < nDataPt; i++)
        for (int j = 0; j < THREED; j++)
            mDataPts(i, j) = pgptData[i][j];

    double *pdBSplnBlends = new double[nCtrlPt];
    Matrix M(nDataPt, nCtrlPt);
    double tmax = pdParamRange[1];//nCtrlPt-iOrder+1;

    double dFirst[3] = { 0 };
    double dEnd[3] = { 0 };
    double *D = new double[nDataPt];
    for (int i = 0; i < nDataPt; i++)
        D[i] = 0.0;
    for (int k = 1; k < nDataPt; k++)
    {
        if (k)
        {
            for (int i = 0; i < 3; i++)
                dFirst[i] = pgptData[k - 1][i];
            for (int i = 0; i < 3; i++)
                dEnd[i] = pgptData[k][i];

            D[k] = DistanceBetweenPoints(dFirst, dEnd);
        }
    }


    double a = pdParamRange[0];
    double b = pdParamRange[1];
    double *t = new double[nDataPt];
    for (int i = 0; i < nDataPt; i++)
        t[i] = 0.0;

    for (int k = 0; k < nDataPt; k++)
    {
        double d = 0.0;
        double Dmax = 0.0;

        if (methodBsplineFit == BSPLINE_FIT_UNIFORMSPACE)
            t[k] = a + (b - a)*k / (nCtrlPt - 1);
        else if (methodBsplineFit == BSPLINE_FIT_CHORDLENGTH)
        {
            for (int i = 0; i < k + 1; i++)
                d = d + D[i];
            for (int i = 0; i < nDataPt; i++)
                Dmax += D[i];
            t[k] = a + (b - a)*(d / Dmax);
        }
        else if (methodBsplineFit == BSPLINE_FIT_CENTRIPETAL)
        {
            for (int i = 0; i < k + 1; i++)
                d = d + sqrt(D[i]);
            for (int i = 0; i < nDataPt; i++)
                Dmax += sqrt(D[i]);
            t[k] = a + (b - a)*(d / Dmax);
        }
    }

    //Knot Vector Generation As suggested by de Boor
    for (int i = 0; i < iOrder; i++)
        pdKnotVec[i] = a;
    for (int j = 1; j <= (nCtrlPt - iOrder); j++)
    {
        double u = 0.0;
        for (int i = j; i <= (j + iOrder - 2); i++)
            u = u + t[i];
        pdKnotVec[j + iOrder - 1] = u / (iOrder - 1);
    }
    for (int i = nCtrlPt; i < (nCtrlPt + iOrder); i++)
        pdKnotVec[i] = b;

    for (int k = 0; k < nDataPt; k++)
    {
        if (k == (nDataPt - 1))
            t[k] = t[k] * 0.9999999999;

        BSplineBlends(t[k], nCtrlPt, iOrder, pdKnotVec, pdBSplnBlends);

        for (int i = 0; i < nCtrlPt; i++)
            M(k, i) = pdBSplnBlends[i];
    }

    Matrix Mt = M.TransposeMat();

    Matrix MtM = Mt*M;

    Matrix MtM_i = MtM.InverseMat();

    //This is for checking Matrix multiplication -code can be deleted
    Matrix MI = MtM * MtM_i;
    double dDet = MI.MatrixDet();
    MI = MtM_i * MtM;
    dDet = MI.MatrixDet();
    //end

    Matrix mPoint = MtM_i * Mt * mDataPts;

    for (int l = 0; l < nCtrlPt; l++)
        for (int j = 0; j < THREED; j++)
            pgptCtrl[l][j] = mPoint(l, j);

    if (pdBSplnBlends) delete[] pdBSplnBlends;
}

void BSplineFitEndTangents(int nCtrlPt, int iOrder, double *pdParamRange, double *pdKontVec, int nDataPt, Vector *pFirstDerivatives, eBSplineFitMethod methodBsplineFit, SPoint *pgptData, SPoint *pgptCtrl)
{
    int iDegree = iOrder - 1;
    Matrix mDataPts(nDataPt, THREED);
    for (int i = 0; i < nDataPt; i++)
        for (int j = 0; j < THREED; j++)
            mDataPts(i, j) = pgptData[i][j];

    double *pdBSplnBlends = new double[nCtrlPt];
    Matrix M(nDataPt, nCtrlPt);
    double tmax = pdParamRange[1];//nCtrlPt-iOrder+1;

    double dFirst[3] = { 0 };
    double dEnd[3] = { 0 };
    double *D = new double[nDataPt];
    for (int i = 0; i < nDataPt; i++)
        D[i] = 0.0;
    for (int k = 1; k < nDataPt; k++)
    {
        if (k)
        {
            for (int i = 0; i < 3; i++)
                dFirst[i] = pgptData[k - 1][i];
            for (int i = 0; i < 3; i++)
                dEnd[i] = pgptData[k][i];

            D[k] = DistanceBetweenPoints(dFirst, dEnd);
        }
    }

    double a = pdParamRange[0];
    double b = pdParamRange[1];
    double *t = new double[nDataPt];
    for (int i = 0; i < nDataPt; i++)
        t[i] = 0.0;

    for (int k = 0; k < nDataPt; k++)
    {
        double d = 0.0;
        double Dmax = 0.0;

        if (methodBsplineFit == BSPLINE_FIT_UNIFORMSPACE)
            t[k] = a + (b - a)*k / (nCtrlPt - 1);
        else if (methodBsplineFit == BSPLINE_FIT_CHORDLENGTH)
        {
            for (int i = 0; i < k + 1; i++)
                d = d + D[i];
            for (int i = 0; i < nDataPt; i++)
                Dmax += D[i];
            t[k] = a + (b - a)*(d / Dmax);
        }
        else if (methodBsplineFit == BSPLINE_FIT_CENTRIPETAL)
        {
            for (int i = 0; i < k + 1; i++)
                d = d + sqrt(D[i]);
            for (int i = 0; i < nDataPt; i++)
                Dmax += sqrt(D[i]);
            t[k] = a + (b - a)*(d / Dmax);
        }
    }

    int n = 2 * (nDataPt - 1) + 1; //No. of linear equation

    //Knot vector generation only for degree 2 or 3
    for (int i = 0; i < iOrder; i++)
    {
        pdKontVec[i] = t[0];
        pdKontVec[n + i] = t[nDataPt - 1];
    }

    int j = iOrder;
    switch (iDegree)
    {
    case 2:

        pdKontVec[iOrder] = 0.5*(t[1] + t[0]);

        for (int i = 1; i < (nDataPt - 1); i++)
        {
            pdKontVec[++j] = t[i];
            pdKontVec[++j] = 0.5*(t[i] + t[i + 1]);
        }
        break;

    case 3:

        if ((nDataPt - 1) > 1)
        {
            pdKontVec[iOrder] = 0.5*(t[1] + t[0]);
            pdKontVec[n] = 0.5*(t[nDataPt - 1] + t[nDataPt - 2]);
        }

        double alf = 1.0 / 3.0;
        double bet = 2.0 / 3.0;
        for (int i = 1; i < nDataPt - 2; i++)
        {
            pdKontVec[++j] = bet*t[i] + alf*t[i + 1];
            pdKontVec[++j] = alf*t[i] + bet*t[i + 1];
        }
        break;
    }



    Matrix Mt = M.TransposeMat();

    Matrix MtM = Mt*M;

    Matrix MtM_i = MtM.InverseMat();

    //This is for checking Matrix multiplication -code can be deleted
    Matrix MI = MtM * MtM_i;
    double dDet = MI.MatrixDet();
    MI = MtM_i * MtM;
    dDet = MI.MatrixDet();
    //end

    Matrix mPoint = MtM_i * Mt * mDataPts;

    for (int l = 0; l < nCtrlPt; l++)
        for (int j = 0; j < THREED; j++)
            pgptCtrl[l][j] = mPoint(l, j);

    if (pdBSplnBlends) delete[] pdBSplnBlends;
}

void BSplineFirstDervativeBlends(double t/*dParam*/, int n/*iCtrlPt*/, int k/*iOrder*/, double *pdKontVec, double *pdDerivativeBlends)
{
    double *X = new double[n + k + 1];
    for (int i = 1; i < n + k + 1; i++)
        X[i] = pdKontVec[i - 1];

    Matrix N((n + k), k + 1);

    for (int i = 1; i < (n + k); i++)
    {
        if (X[i] <= t && t < X[i + 1])
            N(i, 1) = 1;
        else
            N(i, 1) = 0;
    }

    for (int j = 2; j <= k; j++)
    {
        for (int i = 1; i < (n + k); i++)
        {
            if ((i + j) <= (n + k))
            {
                if ((X[i + j - 1] - X[i]) != 0)
                {
                    if ((X[i + j] - X[i + 1]) != 0)
                        N(i, j) = ((t - X[i])*N(i, j - 1) / (X[i + j - 1] - X[i])) + ((X[i + j] - t)*N(i + 1, j - 1) / (X[i + j] - X[i + 1]));
                    else
                        N(i, j) = ((t - X[i])*N(i, j - 1) / (X[i + j - 1] - X[i]));
                }
                else if ((X[i + j] - X[i + 1]) != 0)
                    N(i, j) = ((X[i + j] - t)*N(i + 1, j - 1) / (X[i + j] - X[i + 1]));
                else
                    N(i, j) = 0;
            }
            else N(i, j) = 0;
        }
    }

    //Derivative part

    Matrix dN((n + k), k + 1);

    for (int i = 1; i < (n + k); i++)
    {
        dN(i, 1) = 0;
    }

    for (int j = 2; j <= k; j++)
    {
        for (int i = 1; i < (n + k); i++)
        {
            if ((i + j) <= (n + k))
            {
                if ((X[i + j - 1] - X[i]) != 0)
                {
                    if ((X[i + j] - X[i + 1]) != 0)
                        dN(i, j) = ((N(i, j - 1) + ((t - X[i])*dN(i, j - 1))) / (X[i + j - 1] - X[i])) + ((((X[i + j] - t)*dN(i + 1, j - 1)) - N(i + 1, j - 1)) / (X[i + j] - X[i + 1]));
                    else
                        dN(i, j) = ((N(i, j - 1) + ((t - X[i])*dN(i, j - 1))) / (X[i + j - 1] - X[i]));
                }
                else if ((X[i + j] - X[i + 1]) != 0)
                    dN(i, j) = ((((X[i + j] - t)*dN(i + 1, j - 1)) - N(i + 1, j - 1)) / (X[i + j] - X[i + 1]));
                else
                    dN(i, j) = 0;
            }
            else dN(i, j) = 0;
        }
    }

    for (int i = 0; i < n; i++)
        pdDerivativeBlends[i] = dN(i + 1, k);

    if (X) delete[] X;
}

void BSplineSecondDervativeBlends(double t/*dParam*/, int n/*iCtrlPt*/, int k/*iOrder*/, double *pdKontVec, double *pdDerivativeBlends)
{
    double *X = new double[n + k + 1];
    for (int i = 1; i < n + k + 1; i++)
        X[i] = pdKontVec[i - 1];

    Matrix N((n + k), k + 1);

    for (int i = 1; i < (n + k); i++)
    {
        if (X[i] <= t && t < X[i + 1])
            N(i, 1) = 1;
        else
            N(i, 1) = 0;
    }

    for (int j = 2; j <= k; j++)
    {
        for (int i = 1; i < (n + k); i++)
        {
            if ((i + j) <= (n + k))
            {
                if ((X[i + j - 1] - X[i]) != 0)
                {
                    if ((X[i + j] - X[i + 1]) != 0)
                        N(i, j) = ((t - X[i])*N(i, j - 1) / (X[i + j - 1] - X[i])) + ((X[i + j] - t)*N(i + 1, j - 1) / (X[i + j] - X[i + 1]));
                    else
                        N(i, j) = ((t - X[i])*N(i, j - 1) / (X[i + j - 1] - X[i]));
                }
                else if ((X[i + j] - X[i + 1]) != 0)
                    N(i, j) = ((X[i + j] - t)*N(i + 1, j - 1) / (X[i + j] - X[i + 1]));
                else
                    N(i, j) = 0;
            }
            else N(i, j) = 0;
        }
    }

    //First Derivative part

    Matrix dN((n + k), k + 1);

    for (int i = 1; i < (n + k); i++)
    {
        dN(i, 1) = 0;
    }

    for (int j = 2; j <= k; j++)
    {
        for (int i = 1; i < (n + k); i++)
        {
            if ((i + j) <= (n + k))
            {
                if ((X[i + j - 1] - X[i]) != 0)
                {
                    if ((X[i + j] - X[i + 1]) != 0)
                        dN(i, j) = ((N(i, j - 1) + ((t - X[i])*dN(i, j - 1))) / (X[i + j - 1] - X[i])) + ((((X[i + j] - t)*dN(i + 1, j - 1)) - N(i + 1, j - 1)) / (X[i + j] - X[i + 1]));
                    else
                        dN(i, j) = ((N(i, j - 1) + ((t - X[i])*dN(i, j - 1))) / (X[i + j - 1] - X[i]));
                }
                else if ((X[i + j] - X[i + 1]) != 0)
                    dN(i, j) = ((((X[i + j] - t)*dN(i + 1, j - 1)) - N(i + 1, j - 1)) / (X[i + j] - X[i + 1]));
                else
                    dN(i, j) = 0;
            }
            else dN(i, j) = 0;
        }
    }

    //Second Derivative part

    Matrix ddN((n + k), k + 1);

    for (int i = 1; i < (n + k); i++)
    {
        ddN(i, 1) = 0;
    }

    for (int j = 2; j <= k; j++)
    {
        for (int i = 1; i < (n + k); i++)
        {
            if ((i + j) <= (n + k))
            {
                if ((X[i + j - 1] - X[i]) != 0)
                {
                    if ((X[i + j] - X[i + 1]) != 0)
                        ddN(i, j) = ((dN(i, j - 1) + (dN(i, j - 1) + (t - X[i])*ddN(i, j - 1))) / (X[i + j - 1] - X[i])) + ((((X[i + j] - t)*ddN(i + 1, j - 1) - dN(i + 1, j - 1)) - dN(i + 1, j - 1)) / (X[i + j] - X[i + 1]));
                    else
                        ddN(i, j) = ((dN(i, j - 1) + (dN(i, j - 1) + (t - X[i])*ddN(i, j - 1))) / (X[i + j - 1] - X[i]));
                }
                else if ((X[i + j] - X[i + 1]) != 0)
                    ddN(i, j) = ((((X[i + j] - t)*ddN(i + 1, j - 1) - dN(i + 1, j - 1)) - dN(i + 1, j - 1)) / (X[i + j] - X[i + 1]));
                else
                    ddN(i, j) = 0;
            }
            else ddN(i, j) = 0;
        }
    }

    for (int i = 0; i < n; i++)
        pdDerivativeBlends[i] = ddN(i + 1, k);

    if (X) delete[] X;
}

void BSplineFirstDervativeAtParam(double dParam, int iCtrlPt, int iOrder, double *pdKontVec, SPoint *pgptCtrl, double *pdVector)
{
    Matrix mCtrPts(iCtrlPt, THREED);
    for (int i = 0; i < iCtrlPt; i++)
        for (int j = 0; j < THREED; j++)
            mCtrPts(i, j) = pgptCtrl[i][j];

    double* pdDerivativeBlends = new double[iCtrlPt];
    BSplineFirstDervativeBlends(dParam, iCtrlPt, iOrder, pdKontVec, pdDerivativeBlends);

    double *pdBlends = new double[iCtrlPt];
    //BSplineBlends(dParam, iCtrlPt, iOrder, pdKontVec, pdBlends);
    double **pdDervs = new double*[2];
    for (int i = 0; i < 2; i++)
        pdDervs[i] = new double[iCtrlPt];
    BSplineBlends_2(dParam, iCtrlPt, iOrder, pdKontVec, pdBlends, 1, pdDervs);

    if (pdBlends) delete[] pdBlends;
    if (pdDervs)
    {
        for (int i = 0; i < 2; i++)
            delete[] pdDervs[i];
        delete[] pdDervs;
    }

    Matrix M(1, iCtrlPt);

    for (int i = 0; i < iCtrlPt; i++)
        M(0, i) = pdDerivativeBlends[i];

    Matrix mPoint = M*mCtrPts;

    for (int j = 0; j < THREED; j++)
        pdVector[j] = mPoint(0, j);

    if (pdDerivativeBlends) delete[] pdDerivativeBlends;
}

void BSplineSecondDervativeAtParam(double dParam, int iCtrlPt, int iOrder, double *pdKontVec, SPoint *pgptCtrl, double *pdVector)
{
    Matrix mCtrPts(iCtrlPt, THREED);
    for (int i = 0; i < iCtrlPt; i++)
        for (int j = 0; j < THREED; j++)
            mCtrPts(i, j) = pgptCtrl[i][j];

    double* pdDerivativeBlends = new double[iCtrlPt];
    BSplineSecondDervativeBlends(dParam, iCtrlPt, iOrder, pdKontVec, pdDerivativeBlends);

    double *pdBlends = new double[iCtrlPt];
    //BSplineBlends(dParam, iCtrlPt, iOrder, pdKontVec, pdBlends);
    double **pdDervs = new double*[3];
    for (int i = 0; i < 3; i++)
        pdDervs[i] = new double[iCtrlPt];
    BSplineBlends_2(dParam, iCtrlPt, iOrder, pdKontVec, pdBlends, 2, pdDervs);

    if (pdBlends) delete[] pdBlends;
    if (pdDervs)
    {
        for (int i = 0; i < 3; i++)
            delete[] pdDervs[i];
        delete[] pdDervs;
    }

    Matrix M(1, iCtrlPt);

    for (int i = 0; i < iCtrlPt; i++)
        M(0, i) = pdDerivativeBlends[i];

    Matrix mPoint = M*mCtrPts;

    for (int j = 0; j < THREED; j++)
        pdVector[j] = mPoint(0, j);

    if (pdDerivativeBlends) delete[] pdDerivativeBlends;
}

void BSplineDerivativeAtParam(double t/*dParam*/, int n/*iCtrlPt*/, int k/*iOrder*/, double *pdKontVec, int iNumDervs, double *pdDerivativeBlends)
{
    double *X = new double[n + k + 1];
    for (int i = 1; i < n + k + 1; i++)
        X[i] = pdKontVec[i - 1];

    Matrix N((n + k), k + 1);

    for (int i = 1; i < (n + k); i++)
    {
        if (X[i] <= t && t < X[i + 1])
            N(i, 1) = 1;
        else
            N(i, 1) = 0;
    }

    for (int j = 2; j <= k; j++)
    {
        for (int i = 1; i < (n + k); i++)
        {
            if ((i + j) <= (n + k))
            {
                if ((X[i + j - 1] - X[i]) != 0)
                {
                    if ((X[i + j] - X[i + 1]) != 0)
                        N(i, j) = ((t - X[i])*N(i, j - 1) / (X[i + j - 1] - X[i])) + ((X[i + j] - t)*N(i + 1, j - 1) / (X[i + j] - X[i + 1]));
                    else
                        N(i, j) = ((t - X[i])*N(i, j - 1) / (X[i + j - 1] - X[i]));
                }
                else if ((X[i + j] - X[i + 1]) != 0)
                    N(i, j) = ((X[i + j] - t)*N(i + 1, j - 1) / (X[i + j] - X[i + 1]));
                else
                    N(i, j) = 0;
            }
            else N(i, j) = 0;
        }
    }

    //First Derivative part

    Matrix dN((n + k), k + 1);

    for (int i = 1; i < (n + k); i++)
    {
        dN(i, 1) = 0;
    }

    for (int j = 2; j <= k; j++)
    {
        for (int i = 1; i < (n + k); i++)
        {
            if ((i + j) <= (n + k))
            {
                if ((X[i + j - 1] - X[i]) != 0)
                {
                    if ((X[i + j] - X[i + 1]) != 0)
                        dN(i, j) = ((N(i, j - 1) + ((t - X[i])*dN(i, j - 1))) / (X[i + j - 1] - X[i])) + ((((X[i + j] - t)*dN(i + 1, j - 1)) - N(i + 1, j - 1)) / (X[i + j] - X[i + 1]));
                    else
                        dN(i, j) = ((N(i, j - 1) + ((t - X[i])*dN(i, j - 1))) / (X[i + j - 1] - X[i]));
                }
                else if ((X[i + j] - X[i + 1]) != 0)
                    dN(i, j) = ((((X[i + j] - t)*dN(i + 1, j - 1)) - N(i + 1, j - 1)) / (X[i + j] - X[i + 1]));
                else
                    dN(i, j) = 0;
            }
            else dN(i, j) = 0;
        }
    }

    //Second Derivative part

    Matrix ddN((n + k), k + 1);

    for (int i = 1; i < (n + k); i++)
    {
        ddN(i, 1) = 0;
    }

    for (int j = 2; j <= k; j++)
    {
        for (int i = 1; i < (n + k); i++)
        {
            if ((i + j) <= (n + k))
            {
                if ((X[i + j - 1] - X[i]) != 0)
                {
                    if ((X[i + j] - X[i + 1]) != 0)
                        ddN(i, j) = ((dN(i, j - 1) + (dN(i, j - 1) + (t - X[i])*ddN(i, j - 1))) / (X[i + j - 1] - X[i])) + ((((X[i + j] - t)*ddN(i + 1, j - 1) - dN(i + 1, j - 1)) - dN(i + 1, j - 1)) / (X[i + j] - X[i + 1]));
                    else
                        ddN(i, j) = ((dN(i, j - 1) + (dN(i, j - 1) + (t - X[i])*ddN(i, j - 1))) / (X[i + j - 1] - X[i]));
                }
                else if ((X[i + j] - X[i + 1]) != 0)
                    ddN(i, j) = ((((X[i + j] - t)*ddN(i + 1, j - 1) - dN(i + 1, j - 1)) - dN(i + 1, j - 1)) / (X[i + j] - X[i + 1]));
                else
                    ddN(i, j) = 0;
            }
            else ddN(i, j) = 0;
        }
    }

    for (int i = 0; i < n; i++)
        pdDerivativeBlends[i] = ddN(i + 1, k);

    if (X) delete[] X;
}
