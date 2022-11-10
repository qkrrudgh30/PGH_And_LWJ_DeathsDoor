#pragma once
#include <map>
#include <list>
#include <string>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineString.h>

//class MyLock
//{
//public:
//	std::mutex& LockInst;
//
//public:
//	MyLock(std::mutex& _Lock)
//		: LockInst(_Lock)
//	{
//		LockInst.lock();
//	}
//
//	~MyLock()
//	{
//		LockInst.unlock();
//	}
//};

// 설명 :
template<typename ResType>
class GameEngineRes : public GameEngineNameObject
{
public:
	void SetPath(const std::string& _Path)
	{
		Path = _Path;
	}

	std::string GetPath()
	{
		return Path;
	}

	bool IsOriginal() 
	{
		return Original;
	}

	// constrcuter destructer
	GameEngineRes() 
		: Original(true)
	{
	}
	virtual ~GameEngineRes() {}

	// delete Function
	GameEngineRes(const GameEngineRes& _Other) 
		: Original(false)
	{

	}

	GameEngineRes(GameEngineRes&& _Other) noexcept = delete;
	GameEngineRes& operator=(const GameEngineRes& _Other) = delete;
	GameEngineRes& operator=(GameEngineRes&& _Other) noexcept = delete;

	static std::shared_ptr < ResType> Find(const std::string& _Name)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);

		typename std::map<std::string, std::shared_ptr < ResType>>::iterator Iter;

		{
			std::lock_guard<std::mutex> LockInst(NamedResLock);
			Iter = NamedRes.find(UpperName);

			if (NamedRes.end() == Iter)
			{
				return nullptr;
			}
		}
		
		return Iter->second;
	}

	static void ResourcesDestroy() 
	{
		UnNamedRes.clear();
		NamedRes.clear();
		//for (auto& Res : UnNamedRes)
		//{
		//	delete Res;
		//}

		//for (auto& Res : NamedRes)
		//{
		//	delete Res.second;
		//}
	}

protected:
	static std::shared_ptr < ResType> CreateResName(const std::string& _Name = "")
	{
		if (NamedRes.end() != NamedRes.find(GameEngineString::ToUpperReturn(_Name)))
		{
			MsgBoxAssertString("같은 이름의 리소스를 또 생성했습니다." + _Name);
		}

		std::shared_ptr < ResType> Res = CreateRes(_Name);

		std::lock_guard<std::mutex> LockInst(NamedResLock);
		NamedRes.insert(std::make_pair(Res->GetNameCopy(), Res));
		return Res;
	}

	static std::shared_ptr < ResType> CreateResUnName()
	{
		std::shared_ptr < ResType> Res = CreateRes();
		std::lock_guard<std::mutex> LockInst(UnNamedResLock);
		UnNamedRes.push_back(Res);
		return Res;
	}

	static std::shared_ptr<ResType> CreateRes(const std::string& _Name = "")
	{
		std::string Name = GameEngineString::ToUpperReturn(_Name);

		std::shared_ptr<ResType> NewRes = std::make_shared<ResType>();
		NewRes->SetName(Name);

		return NewRes;
	}

	bool Original;
	std::string Path;

private:
	static std::map<std::string, std::shared_ptr<ResType>> NamedRes;
	static std::list<std::shared_ptr<ResType>> UnNamedRes;

	static std::mutex NamedResLock;
	static std::mutex UnNamedResLock;

};

template<typename ResType>
std::map<std::string, std::shared_ptr<ResType>> GameEngineRes<ResType>::NamedRes;

template<typename ResType>
std::list<std::shared_ptr<ResType>> GameEngineRes<ResType>::UnNamedRes;

template<typename ResType>
std::mutex GameEngineRes<ResType>::NamedResLock;

template<typename ResType>
std::mutex GameEngineRes<ResType>::UnNamedResLock;


