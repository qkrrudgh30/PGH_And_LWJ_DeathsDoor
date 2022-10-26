#pragma once

// #pragma warning(push)
// #pragma warning(disable:26495)
#include "fbxsdk.h"
#pragma comment(lib, "zlib-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "libfbxsdk-md.lib")
// #pragma comment(lib, "libfbxsdk.lib")
// #pragma warning(pop)

#include <functional>


struct FBXNodeInfo
{
public:
	std::string_view Name;
	fbxsdk::FbxNode* Node;
};

// 설명 :
class GameEngineFBX
{
public:
	// constrcuter destructer
	GameEngineFBX();
	~GameEngineFBX();

	// delete Function
	GameEngineFBX(const GameEngineFBX& _Other) = delete;
	GameEngineFBX(GameEngineFBX&& _Other) noexcept = delete;
	GameEngineFBX& operator=(const GameEngineFBX& _Other) = delete;
	GameEngineFBX& operator=(GameEngineFBX&& _Other) noexcept = delete;

	std::vector<FBXNodeInfo> CheckAllNode();

protected:
	// FBXSDK의 매쉬 로드 인터페이스를 생성하고 로드를 준비한다.
	bool CreateFBXSystemInitialize(const std::string& _Path);

	void FBXConvertScene();

	void FBXInfoDebugFunction(fbxsdk::FbxNode* _RootNode);

	// 기하 컨버트
	float4x4 FbxMatTofloat4x4(const fbxsdk::FbxAMatrix& _BaseTrans);
	fbxsdk::FbxAMatrix float4x4ToFbxAMatrix(const float4x4& _MATRIX);
	float4 FbxVecTofloat4(const fbxsdk::FbxVector4& _BaseVector);
	float4 FbxVecToTransform(const fbxsdk::FbxVector4& _BaseVector);
	float4 FbxQuaternionTofloat4(const fbxsdk::FbxQuaternion& _BaseVector); \

	void RecursiveAllNode(fbxsdk::FbxNode* _Node, std::function<void(fbxsdk::FbxNode*)> _Function = nullptr);

	fbxsdk::FbxManager* Manager;
	fbxsdk::FbxIOSettings* IOSetting;
	fbxsdk::FbxImporter* Importer;
	fbxsdk::FbxScene* Scene;
	fbxsdk::FbxNode* RootNode;

	fbxsdk::FbxAMatrix	ConvertMatrix;
	fbxsdk::FbxAMatrix JointMatrix;
	fbxsdk::FbxVector4 AxisVector;

private:


};

