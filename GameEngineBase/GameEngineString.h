#pragma once
#include <string>
#include <algorithm>

// 문자의 기본
// 숫자 매칭 57 ==> a다

// 모든 국가가 동일
// 아스키 == 1바이트 문자체계로 모든 문자는 동일하게 써요. <이안에 알파뱃이 들어가 있다.>

// 국가마다 다름
// Ansi <==> 멀티바이트
// UniCode <==> 와이드바이트 

// 국가마다 같음.
// UTF8~시리즈 => 세계의 모든 글자를 단 1가지 체계로 사용하기 위한 

// 설명 :
class GameEngineString
{
public:
	static void ToUpper(std::string& _Text) 
	{
		for (size_t i = 0; i < _Text.size(); i++)
		{
			_Text[i] = static_cast<char>(std::toupper(_Text[i]));
		}

		// std::transform(_Text.begin(), _Text.end(), _Text.begin(), std::toupper);
	}


	static std::string ToUpperReturn(const std::string& _Text)
	{
		std::string NewText = _Text;
		for (size_t i = 0; i < _Text.size(); i++)
		{
			NewText[i] = static_cast<char>(std::toupper(NewText[i]));
		}
		return NewText;
	}


	static void AnsiToUniCode(const std::string& Text, std::wstring& _Out);
	static std::wstring AnsiToUniCodeReturn(const std::string& Text);
	static void UniCodeToUTF8(const std::wstring& _Text, std::string& _Out);
	static void AnsiToUTF8(const std::string& Text, std::string& _Out);
	static std::string AnsiToUTF8Return(const std::string& Text);
	static std::wstring StringToWStringReturn(const std::string& Text);


	static bool UniCodeToAnsi(const std::wstring& _UniCode, std::string& _AnsiString);
	static bool UTF8ToUniCode(const std::string& _UTF8, std::wstring& _UniCode);

	static std::string UniCodeToAnsiReturn(const std::wstring& _UniCode);
	static std::wstring UTF8ToUniCodeReturn(const std::string& _UTF8);
	static std::string UTF8ToAnsiReturn(const std::string& _UTF8);


protected:

private:
	// constrcuter destructer
	GameEngineString();
	~GameEngineString();

	// delete Function
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;


};

