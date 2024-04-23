/**
 * @file angle.cpp
 * @author Jochem Arends
 * @date 21-02-2024
 */

#include <utility/angle.h>
#include <numbers>

namespace ja {
    template<>
    angle angle::from<angle_unit::radians>(float value) {
        angle res{};
        res.m_radians = value;
        return res;
    }

    template<>
    angle angle::from<angle_unit::degrees>(float value) {
        const float radians = value * (std::numbers::pi_v<float> / 180.0f);
        return angle::from<angle_unit::radians>(radians);
    }

    float angle::degrees() const {
        return m_radians * (180.0f / std::numbers::pi_v<float>);
    }

    float angle::radians() const {
        return m_radians;
    }

    angle operator""_deg(long double degrees) {
        return angle::from<angle_unit::degrees>(static_cast<float>(degrees));
    }

    angle operator""_rad(long double radians) {
        return angle::from<angle_unit::radians>(static_cast<float>(radians));
    }
}

