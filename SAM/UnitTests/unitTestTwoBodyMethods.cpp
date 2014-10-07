/*    
 * Copyright (c) 2014, K. Kumar (me@kartikkumar.com)
 * All rights reserved.
 */

#define REAL double

#include <catch.hpp>

#include <SAM/twoBodyMethods.hpp>

namespace sam
{
namespace unit_tests
{

TEST_CASE( "Convert semi-major axis to mean motion", "[semi-major-axis-to-mean-motion]")
{
    // Reference: http://en.wikipedia.org/wiki/Geostationary_orbit.

    // Set satellite mass [kg].
    const REAL satelliteMass = 1.0e3;

    // Set gravitational parameter of Earth [m^3 s^-2].
    const REAL earthGravitationalParameter = 6.67259e-11 * 5.9736e24;

    // Set distance between Earth center and satellite [m].
    const REAL distanceBetweenSatelliteAndEarth = 4.2164e7;

    // Set expected mean motion [rad/s].
    const REAL expectedMeanMotion = 7.2921e-5;

    // Compute mean motion.
    const REAL meanMotion = computeKeplerMeanMotion(
        distanceBetweenSatelliteAndEarth, earthGravitationalParameter, satelliteMass );

    // Check if computed mean motion matches expected value.
    REQUIRE( meanMotion == Approx( expectedMeanMotion ).epsilon( 1.0e-7 ) );
}

TEST_CASE( "Compute circular velocity", "[circular-velocity]" )
{
    SECTION( "Test zero-semi-major-axis error" )
    {
        REQUIRE_THROWS( computeCircularVelocity( 0.0, 0.0 ) );
    }
    
    SECTION( "Test orbits around the Earth" )
    {
        // Reference data obtained from Wertz (2001).

        // Set Earth equatorial radius [m].
        const REAL earthRadius = 6378136.0;

        // Set Earth's gravitational parameter [m^3 s^-2].
        const REAL earthGravitationalParameter = 3.98600441e14;

        // Set altitudes [km].
        const REAL altitudes[ 5 ] = { 0.0, 200.0, 500.0, 1000.0, 35786.0};

        // Set expected circular velocities [km/s].
        const REAL expectedCircularVelocities[ 5 ] = {7.905, 7.784, 7.613, 7.350, 3.075};

        for ( unsigned int i = 0; i < 5; i++ )
        {
            // Compute circular velocity [m/s].
            const REAL computedCircularVelocity 
                = computeCircularVelocity( 
                    earthRadius + altitudes[ i ] * 1.0e3, earthGravitationalParameter ); 

            //! Check if computed circular velocity matches expected value.
            REQUIRE( ( computedCircularVelocity / 1.0e3 )
                     == Approx( expectedCircularVelocities[ i ] ).epsilon( 1.0e-4 ) );
        }
    }
}

} // namespace unit_tests
} // namespace sam

/*!
 * References
 *  Vallado, D. A., McClain, W. D. Fundamentals of astrodynamics and applications, 2nd Edition,
 *   Kluwer Academic Publishers, The Netherlands, 2004. 
 *  Wertz, J.R. Mission Geometry: Orbit and Constellation Design and Management, Mircocosm Press,
 *   El Segundo, CA, 2001.
 */