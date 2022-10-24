#pragma once

// #pragma warning(push)
// #pragma warning(disable:26495)
#include "fbxsdk.h"
#pragma comment(lib, "zlib-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "libfbxsdk-md.lib")
// #pragma comment(lib, "libfbxsdk.lib")
// #pragma warning(pop)

// Ό³Έν :
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

protected:

private:
	fbxsdk::FbxManager* Manager;
	fbxsdk::FbxIOSettings* IOSetting;
	fbxsdk::FbxImporter* Importer;
	fbxsdk::FbxScene* Scene;
	fbxsdk::FbxNode* RootNode;

	fbxsdk::FbxAMatrix	ConvertMatrix;
	fbxsdk::FbxAMatrix JointMatrix;
	fbxsdk::FbxVector4 AxisVector;


};

