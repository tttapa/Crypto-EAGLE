#define TEMPLATE_GRIDFINDER

#include <Degrees.hpp>
#include <GridFinder.hpp>
#include <gtest/gtest.h>

using namespace std;

#if 0

TEST(GridFinder, getStartingPointFullLine) {
    GridFinder<4, 9> gm = {{{
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
    }}};

    auto result = gm.getStartingPoint(2);
    ASSERT_EQ(result.pixel, Pixel(2, 4));
    ASSERT_EQ(result.width, 9);
}

TEST(GridFinder, getStartingPointBottom) {
    GridFinder<4, 9> gm = {{{
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
    }}};

    auto result = gm.getStartingPoint(2);
    ASSERT_EQ(result.pixel, Pixel(2, 6));
    ASSERT_EQ(result.width, 3);
    ASSERT_EQ(result.above, true);
}

TEST(GridFinder, getStartingPointBottomBorder) {
    GridFinder<4, 9> gm = {{{
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
    }}};

    auto result = gm.getStartingPoint(2);
    ASSERT_EQ(result.pixel, Pixel(2, 7));
    ASSERT_EQ(result.width, 3);
    ASSERT_EQ(result.above, true);
}

TEST(GridFinder, getStartingPointTop) {
    GridFinder<4, 9> gm = {{{
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
    }}};

    auto result = gm.getStartingPoint(2);
    ASSERT_EQ(result.pixel, Pixel(2, 2));
    ASSERT_EQ(result.width, 3);
    ASSERT_EQ(result.above, false);
}

TEST(GridFinder, getStartingPointTopBorder) {
    GridFinder<4, 9> gm = {{{
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
    }}};

    auto result = gm.getStartingPoint(2);
    ASSERT_EQ(result.pixel, Pixel(2, 1));
    ASSERT_EQ(result.width, 3);
    ASSERT_EQ(result.above, false);
}

TEST(GridFinder, getStartingPointOtherColumnEvenLast) {
    GridFinder<4, 6> gm = {{{
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 1},
    }}};

    auto result = gm.getStartingPoint();
    ASSERT_EQ(result.pixel, Pixel(3, 4));
    ASSERT_EQ(result.width, 3);
    ASSERT_EQ(result.above, true);
}

TEST(GridFinder, getStartingPointOtherColumnEvenFirst) {
    GridFinder<4, 6> gm = {{{
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
    }}};

    auto result = gm.getStartingPoint();
    ASSERT_EQ(result.pixel, Pixel(0, 4));
    ASSERT_EQ(result.width, 3);
    ASSERT_EQ(result.above, true);
}

TEST(GridFinder, getStartingPointOtherColumnOddFirst) {
    GridFinder<5, 6> gm = {{{
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
    }}};

    auto result = gm.getStartingPoint();
    ASSERT_EQ(result.pixel, Pixel(0, 4));
    ASSERT_EQ(result.width, 3);
    ASSERT_EQ(result.above, true);
}

TEST(GridFinder, getStartingPointOtherColumnOddLast) {
    GridFinder<5, 6> gm = {{{
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
    }}};

    auto result = gm.getStartingPoint();
    ASSERT_EQ(result.pixel, Pixel(4, 4));
    ASSERT_EQ(result.width, 3);
    ASSERT_EQ(result.above, true);
}

TEST(GridFinder, getStartingPointNoWhitePixels) {
    GridFinder<5, 6> gm = {{{
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    }}};

    try {
        gm.getStartingPoint();
        FAIL();
    } catch (std::runtime_error &e) {
    }
}

#endif

TEST(GridFinder, Hough) {
    constexpr uint W = 410;
    constexpr uint H = 308;
    GridFinder<W, H> gm  = {};
    Pixel center       = {W / 2, H / 2};
    double angle       = M_PI / 7;
    BresenhamLine line = {center, angle, W, H};
    while (line.hasNext())
        gm.set(line.next());

    double resolution = 1e3;
    vector<HoughResult> houghRes;
    houghRes.reserve(resolution);
    double step = 2 * M_PI / resolution;
    for (double angle = 0; angle < 2 * M_PI; angle += step)
        houghRes.emplace_back(gm.hough(center, angle));

    double result = max_element(houghRes.begin(), houghRes.end())->angle.rad();
    double expect = angle;

    EXPECT_TRUE(abs(result - expect) <= step);
}

TEST(GridFinder, findLineAngleAccurate) {
    constexpr uint W = 410;
    constexpr uint H = 308;
    GridFinder<W, H> gm  = {};
    Pixel center       = {W / 2, H / 2};
    double angle       = M_PI / 7;
    BresenhamLine line = {center, angle, W, H};
    while (line.hasNext())
        gm.set(line.next());

    double result = gm.findLineAngleAccurate(center).angle.rad();
    double expect = angle;

    EXPECT_NEAR(result, expect, angle_t::step());
}

TEST(GridFinder, findLineAngleAccurateZero) {
    constexpr uint W = 410;
    constexpr uint H = 308;
    GridFinder<W, H> gm  = {};
    Pixel center       = {W / 2, H / 2};
    double angle       = 0;
    BresenhamLine line = {center, angle, W, H};
    while (line.hasNext())
        gm.set(line.next());

    double result = gm.findLineAngleAccurate(center).angle.rad();
    double expect = angle;

    EXPECT_NEAR(result, expect, angle_t::step());
}

TEST(GridFinder, findLineAngleAccuratePI) {
    constexpr uint W = 410;
    constexpr uint H = 308;
    GridFinder<W, H> gm  = {};
    Pixel center       = {W / 2, H / 2};
    double angle       = M_PI;
    BresenhamLine line = {center, angle, W, H};
    while (line.hasNext())
        gm.set(line.next());

    double result = gm.findLineAngleAccurate(center).angle.rad();
    double expect = angle;

    EXPECT_NEAR(result, expect, angle_t::step());
}

TEST(GridFinder, findLineAngleAccuratePI2) {
    constexpr uint W = 410;
    constexpr uint H = 308;
    GridFinder<W, H> gm  = {};
    Pixel center       = {W / 2, H / 2};
    double angle       = M_PI_2;
    BresenhamLine line = {center, angle, W, H};
    while (line.hasNext())
        gm.set(line.next());

    double result = gm.findLineAngleAccurate(center).angle.rad();
    double expect = angle;

    EXPECT_NEAR(result, expect, angle_t::step());
}

TEST(GridFinder, findLineAngleAccurateMinusPI2) {
    constexpr uint W = 410;
    constexpr uint H = 308;
    GridFinder<W, H> gm  = {};
    Pixel center       = {W / 2, H / 2};
    double angle       = 2 * M_PI - M_PI_2;
    BresenhamLine line = {center, angle, W, H};
    while (line.hasNext())
        gm.set(line.next());

    double result = gm.findLineAngleAccurate(center).angle.rad();
    double expect = angle;

    EXPECT_NEAR(result, expect, angle_t::step());
}

TEST(GridFinder, findLineAngleAccuratePI4) {
    constexpr uint W = 410;
    constexpr uint H = 308;
    GridFinder<W, H> gm  = {};
    Pixel center       = {W / 2, H / 2};
    double angle       = M_PI_4;
    BresenhamLine line = {center, angle, W, H};
    while (line.hasNext())
        gm.set(line.next());

    double result = gm.findLineAngleAccurate(center).angle.rad();
    double expect = angle;

    EXPECT_NEAR(result, expect, angle_t::step());
}

TEST(GridFinder, findLineAngleAccurateRandomAngle) {
    constexpr uint W = 410;
    constexpr uint H = 308;
    GridFinder<W, H> gm  = {};
    Pixel center       = {W / 2, H / 2};
    double angle       = 23.0 / 17;
    BresenhamLine line = {center, angle, W, H};
    while (line.hasNext())
        gm.set(line.next());

    double result = gm.findLineAngleAccurate(center).angle.rad();
    double expect = angle;

    EXPECT_NEAR(result, expect, angle_t::step());
}

TEST(GridFinder, findLineAngleAccurateRange110) {
    constexpr uint W = 160;
    constexpr uint H = 90;
    GridFinder<W, H> gm  = {};
    Pixel center       = {W / 2, H / 2};
    double angle       = 110_deg;
    BresenhamLine line = {center, angle, W, H};
    while (line.hasNext())
        gm.set(line.next());

    // gm.print(cout);

    double result =
        gm.findLineAngleAccurateRange<angle_t::resolution() / 8>(center, angle)
            .angle.rad();
    double expect = angle;

    EXPECT_NEAR(result, expect, angle_t::step());
}

TEST(GridFinder, findLineAngleAccurateRange20) {
    constexpr uint W = 160;
    constexpr uint H = 90;
    GridFinder<W, H> gm  = {};
    Pixel center       = {W / 2, H / 2};
    double angle       = 20_deg;
    BresenhamLine line = {center, angle, W, H};
    while (line.hasNext())
        gm.set(line.next());

    // gm.print(cout);

    double result =
        gm.findLineAngleAccurateRange<angle_t::resolution() / 8>(center, angle)
            .angle.rad();
    double expect = angle;

    EXPECT_NEAR(result, expect, angle_t::step());
}

TEST(GridFinder, findLineAngleAccurateRange340) {
    constexpr uint W = 160;
    constexpr uint H = 90;
    GridFinder<W, H> gm  = {};
    Pixel center       = {W / 2, H / 2};
    angle_t angle       = 340_deg;
    BresenhamLine line = {center, angle, W, H};
    while (line.hasNext())
        gm.set(line.next());

    // gm.print(cout);

    angle_t result =
        gm.findLineAngleAccurateRange<angle_t::resolution() / 8>(center, angle)
            .angle;
    angle_t expect = angle;

    EXPECT_EQ(result, expect);
}

TEST(GridFinder, getWidth) {
    GridFinder<9, 7> gm = {{{
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 0, 1, 1, 0, 1, 1, 1},
        {1, 0, 0, 1, 1, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
    }}};

    angle_t angle = 0_deg;
    Pixel pixel  = {0, 3};

    GridFinder<9, 7> gm_draw = {};
    BresenhamLine l        = {pixel, angle, 9, 7};
    while (l.hasNext())
        gm_draw.set(l.next());
    gm_draw.print(cout) << endl;
    gm.print(cout);

    uint result = gm.getWidthAtPointOnLine(pixel, angle);
    uint expect = 3;
    // (7, 5) has a width of 3, starting from the base line through (7, 3)

    EXPECT_EQ(result, expect);
}

TEST(GridFinder, getWidth45) {
    GridFinder<9, 9> gm = {{{
        {1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 0, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 1, 1, 1},
    }}};

    angle_t angle = 45_deg;

    Pixel pixel = {0, 0};

    GridFinder<9, 9> gm_draw = {};
    BresenhamLine l        = {pixel, angle, 9, 9};
    while (l.hasNext())
        gm_draw.set(l.next());
    gm_draw.print(cout) << endl;
    gm.print(cout);

    uint result = gm.getWidthAtPointOnLine(pixel, angle, 9);
    uint expect = 3;
    // (7, 5) has a width of 3, starting from the base line through (7, 3)

    EXPECT_EQ(result, expect);
}

TEST(GridFinder, getWidth135) {
    GridFinder<9, 9> gm = {{{
        {0, 0, 0, 0, 0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 1, 1, 1},
        {0, 0, 1, 0, 1, 1, 1, 1, 1},
        {0, 0, 0, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0, 0, 0, 0},
    }}};

    angle_t angle = 135_deg;

    Pixel pixel = {8, 0};

    GridFinder<9, 9> gm_draw = {};
    BresenhamLine l        = {pixel, angle, 9, 9};
    while (l.hasNext())
        gm_draw.set(l.next());
    gm_draw.print(cout) << endl;
    gm.print(cout);

    uint result = gm.getWidthAtPointOnLine(pixel, angle, 9);
    uint expect = 3;
    // (7, 5) has a width of 3, starting from the base line through (7, 3)

    EXPECT_EQ(result, expect);
}

TEST(GridFinder, getWidth225) {
    GridFinder<9, 9> gm = {{{
        {1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 1, 1, 1},
    }}};

    angle_t angle = 225_deg;

    Pixel pixel = {8, 8};

    GridFinder<9, 9> gm_draw = {};
    BresenhamLine l        = {pixel, angle, 9, 9};
    while (l.hasNext())
        gm_draw.set(l.next());
    gm_draw.print(cout) << endl;
    gm.print(cout);

    uint result = gm.getWidthAtPointOnLine(pixel, angle, 9);
    uint expect = 3;
    // (7, 5) has a width of 3, starting from the base line through (7, 3)

    EXPECT_EQ(result, expect);
}

TEST(GridFinder, getMiddleHorizontal) {
    GridFinder<9, 9> gm = {{{
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 1},
        {0, 0, 1, 0, 1, 1, 1, 1, 0},
        {1, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1},
        {0, 0, 1, 0, 1, 0, 1, 1, 1},
        {0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
    }}};

    angle_t angle = 0_deg;

    Pixel pixel = {4, 2};

    GridFinder<9, 9> gm_draw = {};
    BresenhamLine l        = {pixel, angle, 9, 9};
    while (l.hasNext())
        gm_draw.set(l.next());
    gm_draw.print(cout) << endl;
    gm.print(cout);

    Pixel result = gm.getMiddle(pixel, angle, 4)->pixel;  // TODO: check width
    Pixel expect = {4, 4};
    // Row 4 is the center of the horizontal line with thickness 7

    EXPECT_EQ(result, expect);
}

TEST(GridFinder, getMiddleVertical) {
    GridFinder<9, 9> gm = {{{
        {0, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 0},
    }}};

    angle_t angle = angle_t(M_PI_2);

    Pixel pixel = {2, 4};

    GridFinder<9, 9> gm_draw = {};
    BresenhamLine l        = {pixel, angle, 9, 9};
    while (l.hasNext())
        gm_draw.set(l.next());
    gm_draw.print(cout) << endl;
    gm.print(cout);

    Pixel result = gm.getMiddle(pixel, angle, 4)->pixel;  // TODO: check width
    Pixel expect = {4, 4};
    // Row column 4 is the center of the horizontal line with thickness 7
    // The white pixel in (0, 1) is excluded by the small max_gap of 4

    EXPECT_EQ(result, expect);
}

TEST(GridFinder, getMiddleDiagonalAbove) {
    GridFinder<9, 9> gm = {{{
        {1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 0, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 1, 1, 1},
    }}};

    angle_t angle = M_PI_4;

    Pixel pixel = {3, 5};

    GridFinder<9, 9> gm_draw = {};
    BresenhamLine l        = {pixel, angle, 9, 9};
    while (l.hasNext())
        gm_draw.set(l.next());
    gm_draw.print(cout) << endl;
    gm.print(cout);

    Pixel result = gm.getMiddle(pixel, angle, 4)->pixel;  // TODO: check width
    Pixel expect = {4, 4};

    EXPECT_EQ(result, expect);
}

TEST(GridFinder, getMiddleDiagonalBelow) {
    GridFinder<9, 9> gm = {{{
        {1, 1, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 0, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 1, 1, 1},
    }}};

    CosSin angle = angle_t(M_PI_4);

    Pixel pixel = {5, 3};

    GridFinder<9, 9> gm_draw = {};
    BresenhamLine l        = {pixel, angle, 9, 9};
    while (l.hasNext())
        gm_draw.set(l.next());
    gm_draw.print(cout) << endl;
    gm.print(cout);

    Pixel result = gm.getMiddle(pixel, angle, 4)->pixel;  // TODO: check width
    Pixel expect = {4, 4};

    EXPECT_EQ(result, expect);
}

TEST(GridFinder, getMiddleCross) {
    GridFinder<80, 80> gm = {};

    CosSin angle              = angle_t(45_deg);
    CosSin perpendicularAngle = angle.perpendicular();

    for (uint i = 0; i < 4; ++i) {
        gm.drawLine({0, i}, angle);
        gm.drawLine({i, 0}, angle);
        gm.drawLine({79, i}, perpendicularAngle);
        gm.drawLine({79 - i, 0}, perpendicularAngle);
    }

    // gm.print(cout);

    Pixel pixel  = {40, 40};
    auto middle = gm.getMiddle(pixel, angle, 4);

    cout << middle->pixel << ", " << middle->width << endl;

    EXPECT_FALSE(middle.has_value());
}

/*
TEST(GridFinder, getFirstLines) {
    GridFinder<40 + 19, 19> gm = {};

    angle_t angle = 22.5_deg;

    for (uint i = 0; i < 5; ++i) {
        gm.drawLine({0, i}, angle);
    }
    gm.print(cout);
    auto firstLine = gm.getFirstLines();

    GridFinder<40 + 19, 19> gmp = {};
    gmp.drawLine(firstLine.lineCenter, firstLine.angle);
    gmp.print(cout);

    EXPECT_EQ(firstLine.lineCenter, Pixel(9, 15));
    EXPECT_EQ(firstLine.width, 5);
    EXPECT_EQ(firstLine.angle, angle);
}
*/