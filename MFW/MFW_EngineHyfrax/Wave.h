#pragma  once
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

namespace Hydrax{ namespace Noise
{

/** @class Wave Wave.h Noise/Wave/Wave.h
 * @brief A wave defined by the direction, amplitude, period, and optionally phase.
 */
class  Wave
{
public:
    /** Default constructor
     * @param dir Direction of the wave.
     * @param A Amplitude of the wave (m).
     * @param T Period of the wave (s).
     * @param p Phase of the wave (rad).
     */
    Wave(Ogre::Vector2 dir, float A, float T, float p=0.f);

    /** Destructor
     */
    ~Wave();

    /** Call it each frame
        @param timeSinceLastFrame Time since last frame(delta)
     */
    void update(const Ogre::Real &timeSinceLastFrame);

    /** Get the especified x/y noise value
        @param x X Coord
        @param y Y Coord
        @return Noise value
        @remarks range [~-0.2, ~0.2]
     */
    float getValue(const float &x, const float &y);

    /** Returns direction of the wave.
     * @return Direction.
     */
    inline Ogre::Vector2 getDirection() const{return mDir;}
    /** Returns amplitude of the wave.
     * @return Amplitude.
     */
    inline float getAmplitude() const{return mA;}
    /** Returns period of the wave.
     * @return Period.
     */
    inline float getPeriod() const{return mT;}
    /** Returns phase of the wave.
     * @return Phase.
     */
    inline float getPhase() const{return mP;}
    /** Returns phase speed of the wave.
     * @return Phase speed.
     */
    inline float getSpeed() const{return mC;}
    /** Returns longitude of the wave.
     * @return Wave longitude.
     */
    inline float getLongitude() const{return mL;}

protected:


private:
    /// Elapsed time
    double mTime;

    /// Direction (must be normalised)
    Ogre::Vector2 mDir;
    /// Amplitude
    float mA;
    /// Period
    float mT;
    /// Phase
    float mP;
    /// Speed (calculated)
    float mC;
    /// Longitude (calculated)
    float mL;
    /// Angular frec.
    float mF;
    /// Dispersion factor
    float mK;
};

}}  // Namespace
