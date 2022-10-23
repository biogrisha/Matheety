#pragma once
enum class EObjectTypes //Every object pool have one-to-one correspondence with ObjectType. 
	//Also EObjectTypes designates position of object pool in the array in the ObjectPoolManager
{
	Line,
	Last
};

enum class EPrimitiveTypes//Types for VertexPrimitive
{
	Line,
	Point,
	Area,
	Last
};