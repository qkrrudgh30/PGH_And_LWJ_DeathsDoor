#include "PreCompile.h"
#include "GameEngineMath.h"


const float GameEngineMath::PI = 3.141592653589793238462643383279502884197169399375105820974944f;
const float GameEngineMath::PI2 = PI * 2.0f;
const float GameEngineMath::DEG = 180.0f;

// 180을 3.14로 바꾸는건 

//                                           3.14 / 180.0f
const float GameEngineMath::DegreeToRadian = PI / DEG;
//                                    3.14 * 180 / 3.14 
const float GameEngineMath::RadianToDegree = DEG / PI;

GameEngineMath::GameEngineMath()
{
}

GameEngineMath::~GameEngineMath()
{
}

const float4 float4::LEFT = { -1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::RIGHT = { 1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::UP = { 0.0f, 1.0f, 0.0f, 1.0f };
const float4 float4::DOWN = { 0.0f, -1.0f, 0.0f, 1.0f };
const float4 float4::FORWARD = { 0.0f, 0.0f, 1.0f, 1.0f };
const float4 float4::BACK = { 0.0f, 0.0f, -1.0f, 1.0f };
const float4 float4::ZERO = { 0.0f, 0.0f, 0.0f, 0.0f };
const float4 float4::ONE = { 1.0f, 1.0f, 1.0f, 1.0f };

const float4 float4::YELLOW = { 1.0f, 1.0f, 0.0f, 1.0f };;;
const float4 float4::MAGENTA = { 1.0f, 0.0f, 1.0f, 1.0f };;
const float4 float4::CYAN = { 0.0f, 1.0f, 1.0f, 1.0f };;
const float4 float4::BLUE = { 0.0f, 0.0f, 1.0f, 1.0f };
const float4 float4::RED = { 1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::GREEN = { 0.0f, 1.0f, 0.0f, 1.0f };
const float4 float4::WHITE = { 1.0f, 1.0f, 1.0f, 1.0f };;
const float4 float4::BLACK = { 0.0f, 0.0f, 0.0f, 1.0f };;

float4 operator*(const float4& _Vector, const float4x4& _Value)
{
	return DirectX::XMVector4Transform(_Vector.DirectVector, _Value.DirectMatrix);
}

float4& operator*=(float4& _Vector, const float4x4& _Value)
{
	_Vector.DirectVector = DirectX::XMVector4Transform(_Vector.DirectVector, _Value.DirectMatrix);

	return _Vector;
}

void float4::TransformCoord(const float4x4& _Value)
{
	// DirectX::XMVector3TransformCoord
	*this = TransformCoordReturn(_Value);
}

float4 float4::TransformCoordReturn(const float4x4& _Value)
{
	float4 Return = *this;
	Return.w = 1.0f;
	DirectVector = DirectX::XMVector4Transform(Return.DirectVector, _Value.DirectMatrix);
	return Return;
}

void float4::TransformNormal(const float4x4& _Value)
{
	*this = TransformNormalReturn(_Value);
}

float4 float4::TransformNormalReturn(const float4x4& _Value)
{
	float4 Return = *this;
	Return.w = 0.0f;
	DirectVector = DirectX::XMVector4Transform(Return.DirectVector, _Value.DirectMatrix);
	return Return;
}