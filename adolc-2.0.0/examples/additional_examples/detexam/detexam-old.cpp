/*----------------------------------------------------------------------------
 ADOL-C -- Automatic Differentiation by Overloading in C++
 File:     detexam-old.cpp
 Revision: $Id: detexam-old.cpp 268 2008-12-15 10:32:03Z awalther $
 Contents: computation of determinants

 Copyright (c) 2008
               Technical University Dresden
               Department of Mathematics
               Institute of Scientific Computing
  
 This file is part of ADOL-C. This software is provided as open source.
 Any use, reproduction, or distribution of the software constitutes 
 recipient's acceptance of the terms of the accompanying license file.
 
---------------------------------------------------------------------------*/

/****************************************************************************/
/*                                                                 INCLUDES */
#include <adolc/adolc.h>
#include <clock/myclock.h>


/****************************************************************************/
/*                                                           DOUBLE ROUTINE */
int n,it;
double** PA;
double pdet( int k, int m ) {
    if (m == 0)
        return 1.0;
    else {
        double* pt = PA[k-1];
        double t = 0;
        int p = 1;
        int s;
        if (k%2)
            s = 1;
        else
            s = -1;
        for (int i=0; i<n; i++) {
            int p1 = 2*p;
            if (m%p1 >= p) {
                t += *pt*s*pdet(k-1, m-p);
                s = -s;
            }
            ++pt;
            p = p1;
        }
        return t;
    }
}

/****************************************************************************/
/*                                                          ADOUBLE ROUTINE */
adouble** A;
adouble det( int k, int m ) {
    if (m == 0)
        return 1.0;
    else {
        adouble* pt = A[k-1];
        adouble t = 0;
        int p = 1;
        int s;
        if (k%2)
            s = 1;
        else
            s = -1;
        for (int i=0; i<n; i++) {
            int p1 = 2*p;
            if (m%p1 >= p) {
                t += *pt*s*det(k-1, m-p);
                s = -s;
            }
            ++pt;
            p = p1;
        }
        return t;
    }
}

/****************************************************************************/
/*                                                             MAIN PROGRAM */
int main() {
    int i, j;
    int tag = 1;

    /*--------------------------------------------------------------------------*/
    /* Input */
    fprintf(stdout,"COMPUTATION OF DETERMINANTS (old type) (ADOL-C Example)\n\n");
    fprintf(stdout,"order of matrix = ? \n");
    scanf("%d",&n);
    A  = new adouble*[n];
    PA = new double*[n];
    int n2 = n*n;
    double* a = new double[n2];
    double diag = 0;
    int m = 1;

    /*--------------------------------------------------------------------------*/
    /* Preparation */
    double* pa = a;
    for (i=0; i<n; i++) {
        m *= 2;
        PA[i] = new double[n];
        double* ppt = PA[i];
        for (j=0; j<n; j++) {
            *ppt++ = j/(1.0+i);
            *pa++  = j/(1.0+i);
        }
        diag += PA[i][i];   // val corrected to value 2/23/91
        PA[i][i] += 1.0;
        a[i*n+i] += 1.0;
    }
    diag += 1;

    /*--------------------------------------------------------------------------*/
    double t00 = myclock();                               /* 0. time (taping) */
    trace_on(tag,m);
    for (i=0; i<n; i++) {
        A[i]  = new adouble[n];
        adouble* pt = A[i];
        double* ppt = PA[i];
        for (j=0; j<n; j++)
            *pt++ <<= *ppt++;
    }
    adouble deter;
    deter = det(n,m-1);
    double detout = 0.0;
    deter >>= detout;
    trace_off();
    double t01 = myclock();
    fprintf(stdout,"\n %f =? %f should be the same \n",detout,diag);

    /*--------------------------------------------------------------------------*/
    int tape_stats[STAT_SIZE];
    tapestats(tag,tape_stats);

    fprintf(stdout,"\n    independents            %d\n",tape_stats[NUM_INDEPENDENTS]);
    fprintf(stdout,"    dependents              %d\n",tape_stats[NUM_DEPENDENTS]);
    fprintf(stdout,"    operations              %d\n",tape_stats[NUM_OPERATIONS]);
    fprintf(stdout,"    operations buffer size  %d\n",tape_stats[OP_BUFFER_SIZE]);
    fprintf(stdout,"    locations buffer size   %d\n",tape_stats[LOC_BUFFER_SIZE]);
    fprintf(stdout,"    constants buffer size   %d\n",tape_stats[VAL_BUFFER_SIZE]);
    fprintf(stdout,"    maxlive                 %d\n",tape_stats[NUM_MAX_LIVES]);
    fprintf(stdout,"    valstack size           %d\n\n",tape_stats[TAY_STACK_SIZE]);

    /*--------------------------------------------------------------------------*/
    int itu = 8-n;
    itu = itu*itu*itu*itu;
    itu = itu > 0 ? itu : 1;
    double raus;

    /*--------------------------------------------------------------------------*/
    double t10 = myclock();                             /* 1. time (original) */
    for (it = 0; it < itu; it++)
        raus = pdet(n,m-1);
    double t11 = myclock();
    double rtu = itu/(t11-t10);

    double* B = new double[n2];
    double* detaut = new double[1];

    /*--------------------------------------------------------------------------*/
    double t40 = myclock();                      /* 4. time (forward no keep) */
    for (it = 0; it < itu; it++)
        forward(tag,1,n2,0,0,a,detaut);
    double t41 = myclock();

    /*--------------------------------------------------------------------------*/
    double t20 = myclock();                         /* 2. time (forward+keep) */
    for (it = 0; it < itu; it++)
        forward(tag,1,n2,0,1,a,detaut);
    double t21 = myclock();

    double u[1];
    u[0] = 1.0;

    /*--------------------------------------------------------------------------*/
    double t30 = myclock();                              /* 3. time (reverse) */
    for (it = 0; it < itu; it++)
        reverse(tag,1,n2,0,u,B);
    double t31 = myclock();

    /*--------------------------------------------------------------------------*/
    /* output of results */
    // optional generation of tape_doc.tex
    // tape_doc(tag,1,n2,a,detaut);
    fprintf(stdout,"\n first base? :   \n");
    for (i=0; i<n; i++) {
        adouble sum = 0;
        adouble* pt;
        pt = A[i];
        for (j=0; j<n; j++)
            sum += (*pt++)*B[j];
        fprintf(stdout,"%le ",sum.value());
    }
    fprintf(stdout,"\n\n times for ");
    fprintf(stdout,"\n tracing          : \t%le",(t01-t00)*rtu);
    fprintf(stdout," units \t%le    seconds",(t01-t00));
    fprintf(stdout,"\n forward (no keep): \t%le",(t41-t40)*rtu/itu);
    fprintf(stdout," units \t%le    seconds",(t41-t40)/itu);
    fprintf(stdout,"\n forward + keep   : \t%le",(t21-t20)*rtu/itu);
    fprintf(stdout," units \t%le    seconds",(t21-t20)/itu);
    fprintf(stdout,"\n reverse          : \t%le",(t31-t30)*rtu/itu);
    fprintf(stdout," units \t%le    seconds\n",(t31-t30)/itu);

    return 1;
}

