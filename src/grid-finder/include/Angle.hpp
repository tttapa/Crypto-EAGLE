#pragma once

#include <array>
#include <cmath>
#include <limits>
#include <ostream>
#include <uint.hpp>

template <uint>
class Angle;

struct CosSin {
    int cos;
    int sin;

    static constexpr int getScalingFactor() {
        return std::numeric_limits<int>::max() / 2;
    }

    [[nodiscard]] constexpr double cosd() const {
        return (double) cos / getScalingFactor();
    }

    [[nodiscard]] constexpr double sind() const {
        return (double) sin / getScalingFactor();
    }

    [[nodiscard]] constexpr float cosf() const {
        return (float) cos / getScalingFactor();
    }

    [[nodiscard]] constexpr float sinf() const {
        return (float) sin / getScalingFactor();
    }

    [[nodiscard]] constexpr CosSin perpendicular(bool plus90deg = true) const {
        return plus90deg ? CosSin{-sin, cos} : CosSin{sin, -cos};
    }
    [[nodiscard]] constexpr CosSin opposite() const {
        return CosSin{-cos, -sin};
    }
    [[nodiscard]] constexpr double rad() const { return std::atan2(sin, cos); }
};

inline std::ostream &operator<<(std::ostream &os, CosSin angle) {
    return os << angle.rad();
}

template <uint Resolution>
class Angle {
  private:
    uint angle_index;

  public:
    constexpr Angle() : angle_index(0) {}
    constexpr explicit Angle(uint angleIndex) : angle_index(angleIndex) {}
    constexpr explicit Angle(int angleIndex) : angle_index(angleIndex) {}
    constexpr Angle(double angle) : Angle{getIndex(angle)} {};
    constexpr Angle(long double angle) : Angle{getIndex(angle)} {};

    static constexpr uint resolution() { return Resolution; }

    [[nodiscard]] constexpr operator CosSin() const {
        return {cosines[angle_index], sines[angle_index]};
    }

    [[nodiscard]] constexpr explicit operator double() const { return rad(); }

    [[nodiscard]] constexpr double rad() const { return getAngle(angle_index); }
    [[nodiscard]] constexpr double deg() const { return rad() * 180 / M_PI; }

    [[nodiscard]] constexpr uint getIndex() const { return angle_index; }

    [[nodiscard]] constexpr int cos() const { return cosines[angle_index]; }

    [[nodiscard]] constexpr int sin() const { return sines[angle_index]; }

    [[nodiscard]] constexpr double cosd() const {
        return (double) cos() / CosSin::getScalingFactor();
    }

    [[nodiscard]] constexpr double sind() const {
        return (double) sin() / CosSin::getScalingFactor();
    }

    [[nodiscard]] constexpr float cosf() const {
        return (float) cos() / CosSin::getScalingFactor();
    }

    [[nodiscard]] constexpr float sinf() const {
        return (float) sin() / CosSin::getScalingFactor();
    }

    [[nodiscard]] constexpr Angle opposite() const { return *this + M_PI; }

    [[nodiscard]] constexpr Angle perpendicular(bool plus90deg = true) const {
        return plus90deg ? *this + Angle(resolution() / 4)
                         : *this + Angle(3 * resolution() / 4);
    }

    [[nodiscard]] constexpr Angle operator+(Angle rhs) const {
        return normalize(this->angle_index + rhs.angle_index);
    }

    [[nodiscard]] constexpr Angle operator/(uint divisor) const {
        return angle_index / divisor;
    }

    constexpr bool operator==(Angle rhs) const {
        return this->angle_index == rhs.angle_index;
    }

    [[nodiscard]] static constexpr Angle normalize(uint angle_index) {
        if (angle_index >= Resolution)
            angle_index -= Resolution;
        return Angle(angle_index);
    }

    constexpr static Angle average(Angle first_angle, Angle last_angle) {
        auto first = first_angle.angle_index;
        auto last  = last_angle.angle_index;
        if (first > last)
            last += resolution();
        uint angle = (first + last) / 2;
        return normalize(angle);
    }

    static constexpr int cos(uint angleIndex) {
        return std::round(std::cos(step() * angleIndex) *
                          CosSin::getScalingFactor());
    }

    static constexpr int sin(uint angleIndex) {
        return std::round(std::sin(step() * angleIndex) *
                          CosSin::getScalingFactor());
    }

    static constexpr uint getIndex(double angle) {
        return round(angle / step());
    }

    static constexpr double getAngle(uint angleIndex) {
        return angleIndex * step();
    }

    static constexpr double step() { return 2 * M_PI / Resolution; }

    static constexpr std::array<int, Resolution> calculateCosLut() {
        std::array<int, Resolution> cosines = {};
        for (uint i = 0; i < Resolution; ++i)
            cosines[i] = cos(i);
        return cosines;
    }

    static constexpr std::array<int, Resolution> calculateSinLut() {
        std::array<int, Resolution> sines = {};
        for (uint i = 0; i < Resolution; ++i)
            sines[i] = sin(i);
        return sines;
    }

    static constexpr std::array<int, Resolution> cosines = calculateCosLut();
    static constexpr std::array<int, Resolution> sines   = calculateSinLut();
};

using angle_t = Angle<360>;

template <uint Resolution>
std::ostream &operator<<(std::ostream &os, Angle<Resolution> angle) {
    return os << angle.deg() << "°";
}

template <uint Resolution>
constexpr bool operator==(Angle<Resolution> lhs, CosSin rhs) {
    return lhs.cos() == rhs.cos && lhs.sin() == rhs.sin;
}

template <uint Resolution>
constexpr bool operator==(CosSin lhs, Angle<Resolution> rhs) {
    return lhs.cos == rhs.cos() && lhs.sin == rhs.sin();
}