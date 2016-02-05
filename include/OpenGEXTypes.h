#pragma once

#include "OpenGEXCommon.h"

namespace OGEXParser
{
	typedef signed char				int8;
	typedef unsigned char			unsigned_int8;

	typedef short					int16;
	typedef unsigned short			unsigned_int16;

	typedef int						int32;
	typedef unsigned int			unsigned_int32;

	typedef long long				int64;
	typedef unsigned long long		unsigned_int64;

	enum UpAxisDirection
	{
		UAD_X = 0,
		UAD_Y,
		UAD_Z
	};

	enum PrimitiveType
	{
		PT_Points = 0,
		PT_Lines,
		PT_LineStrip,
		PT_Triangles,
		PT_TriangleStrip,
		PT_Quads
	};

	template<typename T>
	class Vector2DT
	{
	public:
		Vector2DT()
			: x(0)
			, y(0)
		{

		}
		union
		{
			T x;
			T y;

			T data[2];
		};
	};

	template<typename T>
	class Vector3DT
	{
	public:
		Vector3DT()
			: x(0)
			, y(0)
			, z(0)
		{

		}

		union
		{
			T x;
			T y;
			T z;

			T data[3];
		};
	};

	template<typename T>
	class Vector4DT
	{
	public:
		Vector4DT()
			: x(0)
			, y(0)
			, z(0)
			, w(0)
		{

		}

		union
		{
			T x;
			T y;
			T z;
			T w;

			T data[4];
		};
	};

	template<typename T>
	class MatrixT
	{
	public:
		T data[16];
	};

	typedef Vector2DT<float> Vector2D;
	typedef Vector3DT<float> Vector3D;
	typedef Vector4DT<float> Vector4D;
	typedef MatrixT<float> Matrix;
}