/**
 * @file angle.cpp
 * @author Jochem Arends
 * @date 21-02-2024
 */

#include <utility/angle.h>
#include <numbers>

namespace ja {
    double angle::degrees() const {
        return m_radians * (180.0 / std::numbers::pi);
    }

    double angle::radians() const {
        return m_radians;
    }

    angle operator""_rad(long double radians) {
        angle res{};
        res.m_radians = radians;
        return res;
    }

    angle operator""_deg(long double degrees) {
        angle res{};
        res.m_radians = degrees * (std::numbers::pi / 180.0);
        return res;
    }
}

