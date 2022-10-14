#pragma once
#include <math.h>
#include <Windows.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>

#include <DirectXCollision.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")


// 설명 :
class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;
	static const float DEG;
	static const float DegreeToRadian;
	static const float RadianToDegree;

	static float Lerp(float p1, float p2, float Time)
	{
		return (1.0f - Time) * p1 + Time * p2;
	}

	// 보통 누적된 시간을 Time
	static float LerpLimit(float p1, float p2, float Time)
	{
		if (1.0f <= Time)
		{
			Time = 1.0f;
		}

		return Lerp(p1, p2, Time);
	}

private:
	// constrcuter destructer
	GameEngineMath();
	~GameEngineMath();

	// delete Function
	GameEngineMath(const GameEngineMath& _Other) = delete;
	GameEngineMath(GameEngineMath&& _Other) noexcept = delete;
	GameEngineMath& operator=(const GameEngineMath& _Other) = delete;
	GameEngineMath& operator=(GameEngineMath&& _Other) noexcept = delete;


};

class float4x4;
class float4
{
public:
	// Dir
	static const float4 LEFT;
	static const float4 RIGHT;
	static const float4 UP;
	static const float4 DOWN;
	static const float4 FORWARD;
	static const float4 BACK;
	static const float4 ZERO;
	static const float4 ONE;

	// Color
	static const float4 YELLOW;
	static const float4 MAGENTA;
	static const float4 CYAN;
	static const float4 BLUE;
	static const float4 RED;
	static const float4 GREEN;
	static const float4 WHITE;
	static const float4 BLACK;

public:
	// 외적을 쓸수 있는곳
	// 마우스 클릭시 회전방향 알아낼때.
	static float4 Cross(const float4& _Left, const float4& _Right)
	{
		// DirectX::XMVector3Cross()

		float4 vResult = float4(
		(_Left.Arr1D[1] * _Right.Arr1D[2]) - (_Left.Arr1D[2] * _Right.Arr1D[1]),
		(_Left.Arr1D[2] * _Right.Arr1D[0]) - (_Left.Arr1D[0] * _Right.Arr1D[2]),
		(_Left.Arr1D[0] * _Right.Arr1D[1]) - (_Left.Arr1D[1] * _Right.Arr1D[0]),
		0.0f
		);
		return vResult;
	}

	static float4 Select(const float4& _Left, const float4& _Right, const float4& _Control)
	{
		float4 Return;

		if (_Control.x != 0.0f)
		{
			Return.x = _Right.x;
		}
		else {
			Return.x = _Left.x;
		}

		if (_Control.y != 0.0f)
		{
			Return.y = _Right.y;
		}
		else {
			Return.y = _Left.y;
		}

		if (_Control.z != 0.0f)
		{
			Return.z = _Right.z;
		}
		else {
			Return.z = _Left.z;
		}

		if (_Control.w != 0.0f)
		{
			Return.w = _Right.w;
		}
		else {
			Return.w = _Left.w;
		}

		//Return.Arr1DInt[0] = (_Left.Arr1DInt[0] & ~_Control.Arr1DInt[0]) | (_Right.Arr1DInt[0] & _Control.Arr1DInt[0]);
		//Return.Arr1DInt[1] = (_Left.Arr1DInt[1] & ~_Control.Arr1DInt[1]) | (_Right.Arr1DInt[1] & _Control.Arr1DInt[1]);
		//Return.Arr1DInt[2] = (_Left.Arr1DInt[2] & ~_Control.Arr1DInt[2]) | (_Right.Arr1DInt[2] & _Control.Arr1DInt[2]);
		//Return.Arr1DInt[3] = (_Left.Arr1DInt[3] & ~_Control.Arr1DInt[3]) | (_Right.Arr1DInt[3] & _Control.Arr1DInt[3]);
		return Return;
	}



	static float4 NormalizeReturn(const float4& _Value)
	{
		float4 Return = _Value;
		Return.Normalize();
		return Return;
	}

	static float4 ABS3DReturn(const float4& _Postion) 
	{
		return _Postion.ABS3DReturn();
	}

	static float VectorXYtoDegree(const float4& _Postion, const float4& _Target)
	{
		return VectorXYtoRadian(_Postion, _Target) * GameEngineMath::RadianToDegree;
	}

	static float VectorXYtoRadian(const float4& _Postion, const float4& _Target)
	{
		float4 Dir = _Target - _Postion;
		Dir.Normalize();
		// cos(90) => 1.5
		// acos(1.5) => 90
		float Angle = acosf(Dir.x);

		if (_Postion.y > _Target.y)
		{
			Angle = GameEngineMath::PI2 - Angle;
		}

		return Angle;
	}

	static float4 DegreeToDirection2D(float _Degree)
	{
		return RadianToDirection2D(_Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 RadianToDirection2D(float _Radian)
	{
		return { cosf(_Radian) , sinf(_Radian)  };
	}

	static float4 VectorRotationToDegreeZAxis(const float4& _Value, float _Degree)
	{
		return VectorRotationToRadianZAxis(_Value, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 VectorRotationToRadianZAxis(const float4& _Value, float _Radian)
	{
		float4 Rot;
		Rot.x = _Value.x * cosf(_Radian) - _Value.y * sinf(_Radian);
		Rot.y = _Value.x * sinf(_Radian) + _Value.y * cosf(_Radian);
		Rot.z = _Value.z;
		return Rot;
	}

	static float4 VectorRotationToDegreeYAxis(const float4& _Value, float _Degree)
	{
		return VectorRotationToRadianYAxis(_Value, _Degree * GameEngineMath::DegreeToRadian);
	}

	static float4 VectorRotationToRadianYAxis(const float4& _Value, float _Radian)
	{
		float4 Rot;
		Rot.x = _Value.x * cosf(_Radian) - _Value.z * sinf(_Radian);
		Rot.z = _Value.x * sinf(_Radian) + _Value.z * cosf(_Radian);
		Rot.y = _Value.y;
		return Rot;
	}


	static float4 VectorRotationToDegreeXAxis(const float4& _Value, float _Degree)
	{
		return VectorRotationToRadianXAxis(_Value, _Degree * GameEngineMath::DegreeToRadian);
	}

	// [][] * cosf   -sinf
	// [][]   sinf   cosf

	static float4 VectorRotationToRadianXAxis(const float4& _Value, float _Radian)
	{
		float4 Rot;
		Rot.z = _Value.z * cosf(_Radian) - _Value.y * sinf(_Radian);
		Rot.y = _Value.z * sinf(_Radian) + _Value.y * cosf(_Radian);
		Rot.x = _Value.x;
		return Rot;
	}

	static float4 Lerp(const float4& p1, const float4& p2, float Time)
	{
		return p1 * (1.0f - Time) + p2 * Time;
	}

	// 보통 누적된 시간을 Time
	static float4 LerpLimit(const float4& p1, const float4& p2, float Time)
	{
		if (0.0f >= Time)
		{
			Time = 0.0f;
		}

		if (1.0f <= Time)
		{
			Time = 1.0f;
		}

		return Lerp(p1, p2, Time);
	}

	//           []
	//           []
	//           []
	// [][][][]  []

	static float DotProduct3D(const float4& _Left, const float4& _Right)
	{
		// DirectX::XMVector3Dot
		float fValue = _Left.x * _Right.x + _Left.y * _Right.y + _Left.z * _Right.z;
		return fValue;
	}


public:
	union 
	{
		struct 
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};

		struct
		{
			float PosX;
			float PosY;
			float SizeX;
			float SizeY;
		};

		struct
		{
			int IntValueX;
			int IntValueY;
			int IntValueZ;
			int IntValueW;
		};


		float Arr1D[4];

		int Arr1DInt[4];

		DirectX::XMFLOAT3 DirectFloat3;
		DirectX::XMFLOAT4 DirectFloat4;
		DirectX::XMVECTOR DirectVector;
	};

public:
	bool IsZero2D() const
	{
		return x == 0.0f && y == 0.0f;
	}

	UINT GetUIntColor() const
	{
		UINT Int;
		char* ColorPtr = reinterpret_cast<char*>(&Int);
		ColorPtr[0] = static_cast<int>(x * 255.0f); // 1.0f * 255.0f
		ColorPtr[1] = static_cast<int>(y * 255.0f);
		ColorPtr[2] = static_cast<int>(z * 255.0f);
		ColorPtr[3] = static_cast<int>(w * 255.0f);

		return Int;
	}

	int uix() const
	{
		return static_cast<unsigned int>(x);
	}

	int uiy() const
	{
		return static_cast<unsigned int>(y);
	}


	int ix() const
	{
		return static_cast<int>(x);
	}

	int iy() const
	{
		return static_cast<int>(y);
	}

	int iz() const
	{
		return static_cast<int>(z);
	}

	int iw() const
	{
		return static_cast<int>(w);
	}

	POINT GetConvertWindowPOINT() 
	{
		return POINT(ix(), iy());
	}


	float hx() const
	{
		return x * 0.5f;
	}

	float hy() const
	{
		return y * 0.5f;
	}

	float hz() const
	{
		return z * 0.5f;
	}

	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}

	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	float4 Half() const
	{
		return { x * 0.5f, y * 0.5f , z * 0.5f, 1.0f };
	}

	float4 ABS3DReturn() const
	{
		return float4(fabsf(x), fabsf(y), fabsf(z));
	}

	float Length() const
	{
		// sqrtf 제곱근 구해줍니다.
		return sqrtf((x * x) + (y * y) + (z * z));
	}

	void Normalize()
	{
		float Len = Length();
		if (0 == Len)
		{
			return;
		}

		x /= Len;
		y /= Len;
		z /= Len;

		// sqrtf 제곱근 구해줍니다.
		return;
	}

	float4 NormalizeReturn() const
	{
		float4 Return = *this;
		Return.Normalize();
		return Return;
	}

	void Range2D(float _Max)
	{
		Normalize();

		x *= _Max;
		y *= _Max;
		return;
	}

	operator DirectX::XMFLOAT4() const
	{
		return DirectFloat4;
	}

	operator DirectX::XMFLOAT3() const
	{
		return DirectFloat3;
	}

	float& operator[](int _Index)
	{
		return Arr1D[_Index];
	}

	
	float4 operator-(const float4& _Other) const
	{
		return { x - _Other.x, y - _Other.y, z - _Other.z, 1.0f };
	}

	float4 operator-() const
	{
		return { -x, -y, -z, 1.0f };
	}

	float4 operator+(const float4& _Other) const
	{
		return { x + _Other.x, y + _Other.y, z + _Other.z, 1.0f };
	}

	float4 operator*(const float _Value) const
	{
		return DirectX::XMVectorMultiply(DirectVector, float4(_Value).DirectVector);
	}

	float4 operator*(const float4& _Value) const
	{
		return DirectX::XMVectorMultiply(DirectVector, _Value.DirectVector);
	}

	float4 operator/(const float _Value) const
	{
		return DirectX::XMVectorDivide(DirectVector, float4(_Value).DirectVector);
	}

	float4& operator/=(const float _Value)
	{
		DirectVector = DirectX::XMVectorDivide(DirectVector, float4(_Value).DirectVector);

		return *this;
	}

	float4 operator/(const float4& _Value) const
	{
		return DirectX::XMVectorDivide(DirectVector, _Value.DirectVector);
	}

	float4& operator+=(const float4& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;

		return *this;
	}

	float4& operator-=(const float4& _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
		z -= _Other.z;

		return *this;
	}

	float4& operator*=(const float _Other)
	{
		x *= _Other;
		y *= _Other;
		z *= _Other;

		return *this;
	}


	float4& operator*=(const float4& _Other)
	{
		x *= _Other.x;
		y *= _Other.y;
		z *= _Other.z;

		return *this;
	}

	float4 DegreeRotationToQuaternionReturn() const
	{
		float4 Rot = *this;
		Rot *= GameEngineMath::DegreeToRadian;
		Rot.DirectVector =  DirectX::XMQuaternionRotationRollPitchYawFromVector(Rot.DirectVector);
		return Rot;
	}

	bool CompareInt2D(const float4& _Value) const
	{
		return ix() == _Value.ix() && iy() == _Value.iy();
	}

	bool CompareInt3D(const float4& _Value) const
	{
		return ix() == _Value.ix() &&
			iy() == _Value.iy() &&
			iz() == _Value.iz();
	}

	bool CompareInt4D(const float4& _Value) const
	{
		return ix() == _Value.ix() &&
			iy() == _Value.iy() &&
			iz() == _Value.iz() &&
			iw() == _Value.iw();
	}


	float4 RotationToDegreeZ(float _Degree)
	{
		return RotationToRadianZAXis(_Degree * GameEngineMath::DegreeToRadian);
	}

	float4 RotationToRadianZAXis(float _Radian)
	{
		*this = VectorRotationToRadianZAxis(*this, _Radian);
		return *this;
	}

	POINT ToWinAPIPOINT() const
	{
		POINT NewPoint;
		NewPoint.x = ix();
		NewPoint.y = iy();
		return NewPoint;
	}

	void TransformCoord(const float4x4& _Value);

	float4 TransformCoordReturn(const float4x4& _Value);

	void TransformNormal(const float4x4& _Value);

	float4 TransformNormalReturn(const float4x4& _Value);


public:
	float4()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{

	}
	float4(float _Value)
		: x(_Value), y(_Value), z(_Value), w(_Value)
	{

	}


	float4(float _x, float _y)
		: x(_x), y(_y), z(0.0f), w(1.0f)
	{

	}
	float4(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z), w(1.0f)
	{

	}
	float4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{

	}

	float4(const DirectX::XMVECTOR& _Vector)
		: DirectVector(_Vector)
	{

	}



};

struct GameEngineRect
{
public:
	float4 Pos;
	float4 Scale;

public:
	float4 CenterLeftTopPoint() const
	{
		return { static_cast<float>(CenterLeft()), static_cast<float>(CenterTop()) };
	}

	float4 CenterLeftBotPoint() const
	{
		return { static_cast<float>(CenterLeft()), static_cast<float>(CenterBot()) };
	}

	float4 CenterRightTopPoint() const
	{
		return { static_cast<float>(CenterRight()), static_cast<float>(CenterTop()) };
	}

	float4 CenterRightBotPoint() const
	{
		return { static_cast<float>(CenterRight()), static_cast<float>(CenterBot()) };
	}

	int CenterLeft() const
	{
		return Pos.ix() - Scale.hix();
	}

	int CenterRight() const
	{
		return Pos.ix() + Scale.hix();
	}

	int CenterTop() const
	{
		return Pos.iy() - Scale.hiy();
	}

	int CenterBot() const
	{
		return Pos.iy() + Scale.hiy();
	}

	bool OverLap(const GameEngineRect& _Other)
	{
		if (CenterBot() < _Other.CenterTop())
		{
			return false;
		}

		if (CenterTop() > _Other.CenterBot())
		{
			return false;
		}

		if (CenterRight() < _Other.CenterLeft())
		{
			return false;
		}

		if (CenterLeft() > _Other.CenterRight())
		{
			return false;
		}

		return true;
	}

public:
	GameEngineRect(float4 _Pos, float4 _Scale)
		: Pos(_Pos)
		, Scale(_Scale)
	{

	}
};

class float4x4
{
public:
	union
	{
		float Arr1D[16];
		float Arr2D[4][4];
		float4 ArrV[4];
		DirectX::XMMATRIX DirectMatrix;
	};

public:
	float4x4(const DirectX::XMMATRIX& _DirectMatrix)
		: DirectMatrix(_DirectMatrix)
	{
	}

	float4x4() 
	{
		Identity();
	}

public:
	void ZeroCheck() 
	{
		for (size_t i = 0; i < 16; i++)
		{
			if (Arr1D[i] <= FLT_EPSILON)
			{
				Arr1D[i] = 0.0f;
			}
		}
	}

	void Identity()
	{
		DirectMatrix = DirectX::XMMatrixIdentity();

		//memset(Arr1D, 0, sizeof(float) * 16);
		//Arr2D[0][0] = 1.0f;
		//Arr2D[1][1] = 1.0f;
		//Arr2D[2][2] = 1.0f;
		//Arr2D[3][3] = 1.0f;
	}

	void Scale(const float4& _Value)
	{
		// Identity();

		DirectMatrix = DirectX::XMMatrixScaling(_Value.x, _Value.y, _Value.z);

		//Arr2D[0][0] = _Value.x;
		//Arr2D[1][1] = _Value.y;
		//Arr2D[2][2] = _Value.z;
		//Arr2D[3][3] = 1.0f;
	}

	void Position(const float4& _Value)
	{
		DirectMatrix = DirectX::XMMatrixTranslationFromVector(_Value.DirectVector);

		// Identity();
		//Arr2D[3][0] = _Value.x;
		//Arr2D[3][1] = _Value.y;
		//Arr2D[3][2] = _Value.z;
		//Arr2D[3][3] = 1.0f;
	}

	void RotationXDegree(const float _Value)
	{
		RotationXRadian(_Value);
	}

	void RotationXRadian(const float _Value)
	{
		Arr2D[1][1] = cosf(_Value);
		Arr2D[1][2] = sinf(_Value);
		Arr2D[2][1] = -sinf(_Value);
		Arr2D[2][2] = cosf(_Value);
	}

	void RotYDegree(const float _Value)
	{
		RotationYRadian(_Value);
	}

	void RotationYRadian(const float _Value)
	{
		Arr2D[0][0] = cosf(_Value);
		Arr2D[0][2] = -sinf(_Value);
		Arr2D[2][0] = sinf(_Value);
		Arr2D[2][2] = cosf(_Value);
	}

	void RotationZDegree(const float _Value)
	{
		RotationZRadian(_Value * GameEngineMath::DegreeToRadian);
	}

	void RotationZRadian(const float _Value)
	{
		Arr2D[0][0] = cosf(_Value);
		Arr2D[0][1] = sinf(_Value);
		Arr2D[1][0] = -sinf(_Value);
		Arr2D[1][1] = cosf(_Value);
	}

	void RotationDegree(const float4& _Value)
	{
		RotationRadian(_Value * GameEngineMath::DegreeToRadian);
	}

	void RotationRadian(const float4& _Value)
	{
		DirectMatrix = DirectX::XMMatrixRotationRollPitchYawFromVector(_Value.DirectVector);

		//float4x4 XRot;
		//float4x4 YRot;
		//float4x4 ZRot;
		//XRot.RotationXRadian(_Value.x);
		//YRot.RotationYRadian(_Value.y);
		//ZRot.RotationZRadian(_Value.z);

		//*this = XRot * YRot * ZRot;
	}

	void ViewPort(float _Width, float _Height, float _Left, float _Right, float _ZMin, float _ZMax)
	{

		// 크기 자전 이동 뷰 투영 뷰포트 => 모니터에
		//                                마우스포지션은
		//                       * 마우스포지션은

		//             -1~1사이의 값이
		//            640
		Arr2D[0][0] = _Width / 2.0f;
		Arr2D[0][1] = 0.0f;
		Arr2D[0][2] = 0.0f;
		Arr2D[0][3] = 0.0f;

		Arr2D[1][0] = 0.0f;
		Arr2D[1][1] = -_Height / 2.0f;
		Arr2D[1][2] = 0.0f;
		Arr2D[1][3] = 0.0f;

		Arr2D[2][0] = 0.0f;
		Arr2D[2][1] = 0.0f;
		Arr2D[2][2] = 1.0f / 2.0f;
		Arr2D[2][3] = 0.0f;

		Arr2D[3][0] = _Width * 0.5f + _Left;
		Arr2D[3][1] = _Height * 0.5f + _Right;
		Arr2D[3][2] = 1.0f / 2.0f;
		Arr2D[3][3] = 1.0f;
	}

	// Fov to Degree
	void PerspectiveFovLH(float _FovDegree, float _Width, float _Height, float _Near, float _Far)
	{

		DirectMatrix = DirectX::XMMatrixPerspectiveFovLH(_FovDegree * GameEngineMath::DegreeToRadian * 0.5f, _Width / _Height, _Near, _Far);

		////assert(NearZ > 0.f && FarZ > 0.f);
		////assert(!XMScalarNearEqual(FovAngleY, 0.0f, 0.00001f * 2.0f));
		////assert(!XMScalarNearEqual(AspectRatio, 0.0f, 0.00001f));
		////assert(!XMScalarNearEqual(FarZ, NearZ, 0.00001f));

		////float    SinFov;
		////float    CosFov;
		//// XMScalarSinCos(&SinFov, &CosFov, 0.5f * FovAngleY);

		////               45                                 
		//float Tan = tanf(_FovDegree * GameEngineMath::DegreeToRadian * 0.5f);
		//float fRange = _Far / (_Far - _Near);

		//// z가 무슨 z죠?

		//Arr2D[0][0] = 1.0f / (Tan * (_Width / _Height)); // / z
		//Arr2D[0][1] = 0.0f;
		//Arr2D[0][2] = 0.0f;
		//Arr2D[0][3] = 0.0f;

		//Arr2D[1][0] = 0.0f;
		//Arr2D[1][1] = 1.0f / Tan;
		//Arr2D[1][2] = 0.0f;
		//Arr2D[1][3] = 0.0f;

		//Arr2D[2][0] = 0.0f;
		//Arr2D[2][1] = 0.0f;
		//Arr2D[2][2] = fRange;
		//Arr2D[2][3] = 1.0f;

		////    150
		////[x][y][150][1] * [1][0][0][0] = [][][][150]
		////                 [0][1][0][0]
		////                 [0][0][1][1]
		////                 [0][0][0][0]

		//Arr2D[3][0] = 0.0f;
		//Arr2D[3][1] = 0.0f;
		//Arr2D[3][2] = -fRange * _Near;
		//Arr2D[3][3] = 0.0f;
	}

	void OrthographicLH(float _Width, float _Height, float _Near, float _Far)
	{
		 // DirectX::XMMatrixOrthographicLH(_Width, _Height, _Near, _Far);

		//assert(!XMScalarNearEqual(ViewWidth, 0.0f, 0.00001f));
		//assert(!XMScalarNearEqual(ViewHeight, 0.0f, 0.00001f));
		//assert(!XMScalarNearEqual(FarZ, NearZ, 0.00001f));

		float fRange = 1.0f / (_Far - _Near);

		Arr2D[0][0] = 2.0f / _Width;
		Arr2D[0][1] = 0.0f;
		Arr2D[0][2] = 0.0f;
		Arr2D[0][3] = 0.0f;

		Arr2D[1][0] = 0.0f;
		Arr2D[1][1] = 2.0f / _Height;
		Arr2D[1][2] = 0.0f;
		Arr2D[1][3] = 0.0f;

		Arr2D[2][0] = 0.0f;
		Arr2D[2][1] = 0.0f;
		Arr2D[2][2] = fRange;
		Arr2D[2][3] = 0.0f;

		Arr2D[3][0] = 0.0f;
		Arr2D[3][1] = 0.0f;
		Arr2D[3][2] = -fRange * _Near;
		Arr2D[3][3] = 1.0f;
	}

	//               바라보고 있는 위치
	void LookToLH(const float4& _EyePostion, const float4& _EyeFocus, const float4& _Up)
	{
		// DirectX::XMMatrixLookAtLH

		// float4 EyeDir = (_EyeFocus - _EyePostion);
		// EyeDir.Normalize();

		LookAtLH(_EyePostion, (_EyeFocus - _EyePostion), _Up);
	}

	void LookAtLH(const float4& _EyePostion, const float4& _EyeDir, const float4& _Up)
	{

		// DirectX::XMMatrixLookAtLH
		// View

		//assert(!XMVector3Equal(EyeDirection, XMVectorZero()));
		//assert(!XMVector3IsInfinite(EyeDirection));
		//assert(!XMVector3Equal(UpDirection, XMVectorZero()));
		//assert(!XMVector3IsInfinite(UpDirection));

		//XMVECTOR R2 = XMVector3Normalize(EyeDirection);
		// 길이 1짜리 벡터로 만들고
		float4 R2 = float4::NormalizeReturn(_EyeDir);

		//XMVECTOR R0 = XMVector3Cross(UpDirection, R2);
		//R0 = XMVector3Normalize(R0);
		
		// 혹시나 넣어준 사람이 길이를 1로 만들지 않고 넣어줬을수 있으니까.
		// 길이 1짜리 벡터로 만들고
		float4 R0 = float4::Cross(_Up, R2);
		R0.Normalize();

		//XMVECTOR R1 = XMVector3Cross(R2, R0);
		// 길이가 1인 벡터 2개를 외적하면 무조건 길이 1짜리 벡터가 나온다.
		float4 R1 = float4::Cross(R2, R0);

		//XMVECTOR NegEyePosition = XMVectorNegate(EyePosition);
		float4 NegEyePosition = -_EyePostion;

		//XMVECTOR D0 = XMVector3Dot(R0, NegEyePosition);
		//XMVECTOR D1 = XMVector3Dot(R1, NegEyePosition);
		//XMVECTOR D2 = XMVector3Dot(R2, NegEyePosition);
		// 
		float D0Value = float4::DotProduct3D(R0, NegEyePosition);
		float D1Value = float4::DotProduct3D(R1, NegEyePosition);
		float D2Value = float4::DotProduct3D(R2, NegEyePosition);

		float4 D0 = { D0Value , D0Value , D0Value , D0Value };
		float4 D1 = { D1Value , D1Value , D1Value , D1Value };
		float4 D2 = { D2Value , D2Value , D2Value , D2Value };

		//XMMATRIX M;
		// g_XMSelect1110
		// 0xff, 0xff, 0xff, 00

		// 전치행렬
		// 대각선 기준으로 뒤바꾸는것.
		// [R0.x][R0.y][R0.z][D0.w]   [R0.x][R1.x][R2.x][   0]
		// [R1.x][R1.y][R1.z][D1.w]	> [R0.y][R1.y][R2.y][   0]
		// [R2.x][R2.y][R2.z][D2.w]	  [R0.z][R1.z][R2.z][   0]
		// [0   ][0   ][0   ][   1]	  [D0.w][D1.w][D2.w][   1]

		// 90 => ~90도 하려면 회전행렬을 전치하면 된다.

		float4 Control = {0xff, 0xff , 0xff , 0};
		float4x4 Mat;
		Mat.ArrV[0] = float4::Select(D0, R0, Control);
		Mat.ArrV[1] = float4::Select(D1, R1, Control);
		Mat.ArrV[2] = float4::Select(D2, R2, Control);
		Mat.ArrV[3] = float4(0.0f, 0.0f, 0.0f, 1.0f);

		//M.r[0] = XMVectorSelect(D0, R0, g_XMSelect1110.v);
		//M.r[1] = XMVectorSelect(D1, R1, g_XMSelect1110.v);
		//M.r[2] = XMVectorSelect(D2, R2, g_XMSelect1110.v);
		//M.r[3] = g_XMIdentityR3.v;

		Mat.Transpose();

		//M = XMMatrixTranspose(M);

		*this = Mat;

		//return M;


		// 뷰 행렬을 만들어주는 함수에요.
		// DirectX::XMMatrixLookAtLH()
	}

	void Inverse()
	{
		DirectMatrix = DirectX::XMMatrixInverse(nullptr, DirectMatrix);
	}

	float4x4 InverseReturn()
	{
		DirectX::XMMATRIX Result = DirectX::XMMatrixInverse(nullptr, DirectMatrix);
		return Result;
	}

	

	void Transpose()
	{
		float4x4 This = *this;
		Identity();

		for (size_t y = 0; y < 4; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				Arr2D[x][y] = This.Arr2D[y][x];
			}
		}
	}

	
public: // 연산자
	float4x4 operator*(const float4x4& _Value) 
	{
		return DirectX::XMMatrixMultiply(DirectMatrix, _Value.DirectMatrix);
	}
};

float4 operator*(const float4& _Vector, const float4x4& _Value);
float4& operator*=(float4& _Vector, const float4x4& _Value);

