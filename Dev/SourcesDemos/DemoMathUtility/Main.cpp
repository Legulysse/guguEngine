////////////////////////////////////////////////////////////////
// Includes

#include "Gugu/Common.h"

#include "Gugu/Math/MathUtility.h"
#include "Gugu/Math/Random.h"
#include "Gugu/Math/UDim.h"

#include <map>
#include <set>

using namespace gugu;

////////////////////////////////////////////////////////////////
// File Implementation

int main(int argc, char* argv[])
{
#if defined(GUGU_ENV_VISUAL )

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#endif

    //----------------------------------------------
    
    // Common
    double fDegreesA = ToDegrees(Math::Pi);
    double fRadianA = ToRadians(180.f);
    float fDegreesB = ToDegreesf(Math::Pi);
    float fRadiansB = ToRadiansf(180.f);

    int iPowerA = Power(5, 3);
    int iPowerB = Power(5, 0);
    float fPowerC = Power(2.f, -2);
    
    int iClampA = Clamp(15, 10, 20);
    int iClampB = Clamp(5, 10, 20);
    int iClampC = Clamp(25, 10, 20);
    int iClampD = ClampUnordered(15, 20, 10);
    int iClampE = ClampUnordered(5, 20, 10);
    int iClampF = ClampUnordered(25, 20, 10);

    bool bIsInRangeA = IsInRange(15, 10, 20);
    bool bIsInRangeB = IsInRange(5, 10, 20);
    bool bIsInRangeC = IsInRange(25, 10, 20);
    bool bIsInRangeD = IsInRangeUnordered(15, 20, 10);
    bool bIsInRangeE = IsInRangeUnordered(5, 20, 10);
    bool bIsInRangeF = IsInRangeUnordered(25, 20, 10);

    int iDistanceA = Distance(25, 35);
    int iDistanceB = Distance(35, 25);
    int iDistanceC = Distance(-5, 5);
    int iDistanceD = Distance(5, -5);
    int iDistanceE = Distance(-35, -25);

    int iLerpA = Lerp(20, 30, 0.f);
    int iLerpB = Lerp(20, 30, 0.5f);
    int iLerpC = Lerp(200000000, 300000000, 1.f);
    int iLerpD = Lerp(20, 30, 2.f);

    float fInverseLerpA = InverseLerp(20, 30, 25);
    float fInverseLerpB = InverseLerp(20, 30, 40);
    float fInverseLerpC = InverseLerp(20, 30, 0);

    int iLerpRemapA = RemapLerp(20, 30, 1, 5, 25);
    int iLerpRemapB = RemapLerp(20, 30, 1, 5, 40);
    int iLerpRemapC = RemapLerp(20, 30, 1, 5, 0);

    // Vectors
    Vector2f kVectorNormalized(10.f, 20.f);
    kVectorNormalized = Normalize(kVectorNormalized);

    Vector2f kVectorRotated(10.f, 20.f);
    kVectorRotated = Rotate(kVectorRotated, Math::PiDivTwo);

    float fLengthA = Length(kVectorNormalized);
    float fLengthB = Length(kVectorRotated);
    float fSqrLengthA = LengthSquare(kVectorNormalized);
    float fSqrLengthB = LengthSquare(kVectorRotated);

    // Random
    std::map<int, int> kResultsA;
    std::set<float> kResultsB;
    std::map<int, int> kResultsC;
    std::set<float> kResultsD;

    for (int i = 0; i < 10000; ++i)
    {
        kResultsA[GetRandom(10)] += 1;
    }
    for (int i = 0; i < 10000; ++i)
    {
        kResultsB.insert(GetRandomf(10.f));
    }
    for (int i = 0; i < 10000; ++i)
    {
        kResultsC[GetRandom(-5, 5)] += 1;
    }
    for (int i = 0; i < 10000; ++i)
    {
        kResultsD.insert(GetRandomf(-5.f, 5.f));
    }

    int minA = kResultsA.begin()->first;
    int maxA = kResultsA.rbegin()->first;
    float minB = *kResultsB.begin();
    float maxB = *kResultsB.rbegin();
    int minC = kResultsC.begin()->first;
    int maxC = kResultsC.rbegin()->first;
    float minD = *kResultsD.begin();
    float maxD = *kResultsD.rbegin();

    // UDim
    UDim dimA(UDim::HALF);
    dimA += 1.f;
    UDim dimB = dimA + 1.f;

    UDim2 dim2A(UDim2::POSITION_CENTER);
    dim2A += Vector2f(5.f, 10.f);
    UDim2 dim2B = dim2A + Vector2f(5.f, 10.f);

    UDim2 dim2C = UDim2::POSITION_BOTTOM_RIGHT + Vector2f(-10.f, -10.f);

    //----------------------------------------------

    return 0;
}
