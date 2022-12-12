#pragma once
#include <GameEngineCore/GameEngineLevel.h>

enum
{
	eAnimationDir,
	eAnimatorDir,
	eStaticDir,
	eEndDir
};

// Ό³Έν :
class GameEngineDirectory;
class ContentsLevel : public GameEngineLevel
{
	friend class LoadingUI;
	friend class EditGUIWindow;

public:
	// constrcuter destructer
	ContentsLevel();
	~ContentsLevel();

	// delete Function
	ContentsLevel(const ContentsLevel& _Other) = delete;
	ContentsLevel(ContentsLevel&& _Other) noexcept = delete;
	ContentsLevel& operator=(const ContentsLevel& _Other) = delete;
	ContentsLevel& operator=(ContentsLevel&& _Other) noexcept = delete;

	std::shared_ptr<class ContentsBlur>	 GetContentsBlur() { return msptrContentsBlur; }
	std::shared_ptr<class ContentsBloom> GetContentsBloom() { return msptrContentsBloom; }

	void SetLightData(unsigned int _uOnOffLight, float _fDiffuseLightIntensity, float _fAmbientLightIntensity, float _fSpecularLightIntensity, float _fSpecularLightPower)
	{
		if (1u == _uOnOffLight)
		{
			_fDiffuseLightIntensity = 1.f;
			_fAmbientLightIntensity = 0.f;
			_fSpecularLightIntensity = 0.f;
			_fSpecularLightPower = 1.f;
		}

		mwptrLightForLevel.lock()->GetLightData().DifLightPower = _fDiffuseLightIntensity;
		mwptrLightForLevel.lock()->GetLightData().AmbLightPower = _fAmbientLightIntensity;
		mwptrLightForLevel.lock()->GetLightData().SpcLightPower = _fSpecularLightIntensity;
		mwptrLightForLevel.lock()->GetLightData().SpcPow = _fSpecularLightPower;
	}

protected:
	void PlacePathOn(const std::string& _strFolderName);
	void LoadFBXFiles();

	void LoadCreaturesFromFile(const std::string& _strFolderName);

private:
	void LoadFBXMesiesOfAnimator();
	void LoadFBXMesiesOfStatic();
	void LoadAnimationsOfAnimator();

	void LoadResources();
	void LoadResources2();

public:
	static std::string mstrNextLevelName;
	static std::string mstrPrevLevelName;
	static std::map<std::string, bool> mmapPrimitiveInitialized;

protected:
	static std::atomic<unsigned int> muFBXLoadedCount;
	std::vector<GameEngineDirectory> mvecDirectories;
	bool mbPrimitiveInitialized;
	std::shared_ptr<class LoadingUI> mpLoadingUI;

	std::shared_ptr<class GameEngineCameraActor> msptrBlurCameraActor;
	std::shared_ptr<class GameEngineCameraActor> msptrBloomCameraActor;

	std::shared_ptr<class ContentsBlur>  msptrContentsBlur;
	std::shared_ptr<class ContentsBloom> msptrContentsBloom;

	std::weak_ptr<class GameEngineLight> mwptrLightForLevel;

private:
	std::vector<std::string> mstrvecAnimationFileNames;
	std::vector<std::string> mstrvecAnimatorMeshFileNames;
	std::vector<std::string> mstrvecAnimatorMeshFileNamesForEdit;
	std::vector<std::string> mstrvecStaticMeshFileNames;
	std::vector<std::string> mstrvecStaticMeshFileNamesForEdit;

	size_t muAllResourcesCount;
	size_t muAllAnimatorCount;
	size_t muAllStaticCount;
	size_t muAllAnimationCount;
	size_t muMyThreadCount;
	size_t muLines;
	size_t muRemains;
	size_t muAnimationStartIndex;
	std::vector<std::string> mstrvecAllResourcePaths;
	static std::vector<std::string> mstrvecAllResourceNames;

};

