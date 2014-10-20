#include "slalib.h"
#include "slamac.h"
void slaPlanel ( double date, int jform, double epoch, double orbinc,
                 double anode, double perih, double aorq, double e,
                 double aorl, double dm, double pv[6], int* jstat )
/*
**  - - - - - - - - - -
**   s l a P l a n e l
**  - - - - - - - - - -
**
**  Heliocentric position and velocity of a planet, asteroid or comet,
**  starting from orbital elements.
**
**  Given:
**     date    double     date, Modified Julian Date (JD - 2400000.5)
**     jform   int        choice of element set (1-3; Note 3)
**     epoch   double     epoch of elements (TT MJD)
**     orbinc  double     inclination (radians)
**     anode   double     longitude of the ascending node (radians)
**     perih   double     longitude or argument of perihelion (radians)
**     aorq    double     mean distance or perihelion distance (AU)
**     e       double     eccentricity
**     aorl    double     mean anomaly or longitude (radians, jform=1,2 only)
**     dm      double     daily motion (radians, jform=1 only)
**
**  Returned:
**     pv      double[6]  heliocentric x,y,z,xdot,ydot,zdot of date,
**                         J2000 equatorial triad (AU,AU/s)
**     jstat   int*       status:  0 = OK
**                                -1 = illegal jform
**                                -2 = illegal e
**                                -3 = illegal aorq
**                                -4 = illegal dm
**                                -5 = numerical error
**
**  Called:  slaEl2ue, slaUe2pv
**
**  Notes
**
**  1  DATE is the instant for which the prediction is required.  It is
**     in the TT timescale (formerly Ephemeris Time, ET) and is a
**     Modified Julian Date (JD-2400000.5).
**
**  2  The elements are with respect to the J2000 ecliptic and equinox.
**
**  3  Three different element-format options are available:
**
**     Option jform=1, suitable for the major planets:
**
**     epoch  = epoch of elements (TT MJD)
**     orbinc = inclination i (radians)
**     anode  = longitude of the ascending node, big omega (radians)
**     perih  = longitude of perihelion, curly pi (radians)
**     aorq   = mean distance, a (AU)
**     e      = eccentricity, e (range 0 to <1)
**     aorl   = mean longitude L (radians)
**     dm     = daily motion (radians)
**
**     Option jform=2, suitable for minor planets:
**
**     epoch  = epoch of elements (TT MJD)
**     orbinc = inclination i (radians)
**     anode  = longitude of the ascending node, big omega (radians)
**     perih  = argument of perihelion, little omega (radians)
**     aorq   = mean distance, a (AU)
**     e      = eccentricity, e (range 0 to <1)
**     aorl   = mean anomaly M (radians)
**
**     Option jform=3, suitable for comets:
**
**     epoch  = epoch of perihelion (TT MJD)
**     orbinc = inclination i (radians)
**     anode  = longitude of the ascending node, big omega (radians)
**     perih  = argument of perihelion, little omega (radians)
**     aorq   = perihelion distance, q (AU)
**     e      = eccentricity, e (range 0 to 10)
**
**  4  Unused elements (DM for jform=2, aorl and dm for jform=3) are
**     not accessed.
**
**  5  The reference frame for the result is with respect to the mean
**     equator and equinox of epoch J2000.
**
**  6  The algorithm was originally adapted from the EPHSLA program
**     of D.H.P.Jones (private communication, 1996).  The method is
**     based on Stumpff's Universal Variables.
**
**  Reference:  Everhart, E. & Pitkin, E.T., Am.J.Phys. 51, 712, 1983.
**
**  Last revision:   18 March 1999
**
**  Copyright P.T.Wallace.  All rights reserved.
*/
{
   double u[13];
   int j;



/* Validate elements and convert to "universal variables" parameters. */
   slaEl2ue ( date, jform,
              epoch, orbinc, anode, perih, aorq, e, aorl, dm, u, &j );

/* Determine the position and velocity. */
   if ( !j ) {
      slaUe2pv ( date, u, pv, &j );
      if ( j ) j = -5;
   }

/* Wrap up. */
   *jstat = j;

}
