#pragma once

// ----------------------------------------------------------------------------
// Include standar libraries
// ----------------------------------------------------------------------------
#include <math.h>

// ----------------------------------------------------------------------------
// Include the hydrax prerequisites
// ----------------------------------------------------------------------------
#include "Prerequisites.h"

// ----------------------------------------------------------------------------
// Include the noise module
// ----------------------------------------------------------------------------
#include "Noise.h"

// ----------------------------------------------------------------------------
// Include the perlin noise
// ----------------------------------------------------------------------------
#include "Perlin.h"

#ifndef _HydraxDensity_
    #define _HydraxDensity_ 1025
#endif
#ifndef _HydraxGravity_
    #define _HydraxGravity_ 9.81
#endif

namespace Hydrax{ namespace Noise
{

/** @class PressurePoint PressurePoint.h Noise/PressurePoint/PressurePoint.h
 * @brief A PressurePoint defined by the origen, pressure pulse, Maximum time of perturbation
 * and wave longitude. \n
 * Pressure points can be used to add object falling at sea, or, adding sucessive point, to simulate
 * ship Kelvin wakes.
 */
class  PressurePoint
{
public:
    /** Default constructor
     * @param Orig Origin of perturbation.
     * @param p Pressure pulse (N·m). \n
     * The maximum half-amplitude of the wave will result from divide this value
     * with g*rho. So, a pressure of 10000 N·m produces 2 m waves.
     * @param T Maximum time of perturbation (s). \n
     * The effect of the perturbation will decay. When T time will be elapsed,
     * any effects will remain.
     * @param L wave length. \n
     * To objects falling, similar values to amplitude can be OK. For ships Kelvin
     * wakes probably length of the ship is a better choice.
     */
    PressurePoint(Ogre::Vector2 Orig, float p, float T, float L);

    /** Destructor
     */
    ~PressurePoint();

    /** Call it each frame
     * @param timeSinceLastFrame Time since last frame(delta)
     * @return false if the point can be deleted because time
     * elapsed is bigger than maximum time.
     */
    bool update(const Ogre::Real &timeSinceLastFrame);

    /** Get the especified x/y noise value
     * @param x X Coord
     * @param y Y Coord
     * @return Noise value
     * @remarks range [~-0.2, ~0.2]
     */
    float getValue(const float &x, const float &y);

    /** Returns origin of the PressurePoint.
     * @return Origin point.
     */
    inline Ogre::Vector2 getOrigin() const{return mPos;}
    /** Returns pressure pulse.
     * @return Pressure.
     */
    inline float getPressure() const{return mP;}
    /** Returns maximum time.
     * @return Maximum time.
     */
    inline float getMaximumTime() const{return mT;}
    /** Returns time ellapsed.
     * @return Time elapsed.
     */
    inline float getTime() const{return mTime;}
    /** Returns wave length.
     * @return Wave length.
     */
    inline float getLength() const{return mL;}

protected:


private:
    /// Elapsed time
    double mTime;

    /// Direction (must be normalised)
    Ogre::Vector2 mPos;
    /// Pressure
    float mP;
    /// Period
    float mT;
    /// Lenght
    float mL;
    /// Ampliutde
    float mA;
    /// Dispersion factor
    float mK;
    /// Speed (calculated)
    float mC;
    /// Angular frec.
    float mW;
    /// Time decay term
    float mK1;
    /// Distance decay term
    float mK2;

};

}}  // Namespace
