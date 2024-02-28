/**
 * @file angle.h
 * @author Jochem Arends
 * @date 21-02-2024
 */

#ifndef ANGLE_H
#define ANGLE_H

namespace ja {
    /*
     * Represents different angle units.
     */
    enum class angle_unit {
        degrees, 
        radians
    };

    using enum angle_unit;

    /**
     * Represents an angle.
     *
     * At the moment, many operations for this class are missing.
     * Will implement these once I need them. 
     */
    struct angle {
        /**
         * Constructs an angle with the value of zero.
         */
        angle() = default;

        template<angle_unit unit>
        static angle from(float value);

        /**
         * Retrieve angle in degrees.
         *
         * @return Angle in degrees.
         */
        float degrees() const;

        /**
         * Retrieve angle in radians.
         *
         * @return Angle in radians.
         */
        float radians() const;
    private:
        float m_radians{};

        friend angle operator""_deg(long double);
        friend angle operator""_rad(long double);
    };

    /**
     * Constructs an angle from degrees.
     */
    angle operator""_deg(long double degrees);

    /**
     * Constructs an angle from radians.
     */
    angle operator""_rad(long double radians);
}

#endif

