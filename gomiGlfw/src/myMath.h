#pragma once
#ifndef _MYMATH_
#define _MYMATH_
#include <algorithm>
#endif

using namespace std;

typedef struct float3 { float x; float y; float z; float3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {} };

typedef struct float2 { float x; float y; float2(float _x, float _y) : x(_x), y(_y) {} };
typedef struct float4 { float x; float y; float z; float w; float4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {} };
typedef struct int2 { int x; int y; int2(int _x, int _y) : x(_x), y(_y) {} };
typedef struct int3 { int x; int y; int z; int3(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {} };
typedef struct int4 { int x; int y; int z; int w; int4(int _x, int _y, int _z, int _w) : x(_x), y(_y), z(_z), w(_w) {} };
typedef struct UV { float U; float V; UV(float _u, float _v) : U(_u), V(_v) {} };

typedef struct VertexColorData {

	float x; float y; float z; float r; float g; float b; float U; float V;

	VertexColorData(float _x, float _y, float _z, float _r, float _g, float _b, float _u, float _v) : x(_x), y(_y), z(_z), r(_r), g(_g), b(_b), U(_u), V(_v)
	{

	}
};
typedef struct VertexData {

	float x; float y; float z; float U; float V;

	VertexData(float _x, float _y, float _z, float _u, float _v) : x(_x), y(_y), z(_z), U(_u), V(_v)
	{
	
	}
};


