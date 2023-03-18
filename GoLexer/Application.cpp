#include "Application.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstdio>
#include <string>
#include "GoLexer.h"

inline std::string Utf16ToUtf8(std::wstring const& Data)
{
	DWORD kFlags = WC_ERR_INVALID_CHARS;
	if (Data.size() > static_cast<size_t>((std::numeric_limits<int>::max)()))
	{
		return {};
	}
	int Reserve = WideCharToMultiByte(CP_UTF8, kFlags, Data.c_str(), static_cast<int>(Data.size()), nullptr, 0, nullptr, nullptr);
	if (Reserve == 0)
	{
		DWORD dwError = GetLastError();
		// THROW(david): Throw error
		return{};
	}

	std::string Output;
	Output.resize(Reserve);
	int Result = WideCharToMultiByte(CP_UTF8, kFlags, Data.c_str(), static_cast<int>(Data.size()), &Output[0], static_cast<int>(Output.size()), nullptr, nullptr);
	if (Result == 0)
	{
		DWORD dwError = GetLastError();
		return {};
	}
	return Output;

}

size_t utf8len(std::string const& text)
{
	size_t len = 0;
	// TODO(david): probably need more verification and understanding
	for (auto& chr : text)
	{
		if ((chr & 0xc0) != 0x80) len++;
	}
	return len;
}


int wmain(int argc, wchar_t** argv)
{

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	if (argc < 2)
	{
		return 1;
	}
	HANDLE Example = CreateFile(L"GolangExample01.go", GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	DWORD ExampleSize = GetFileSize(Example, nullptr);
	LPVOID ExampleBuffer = VirtualAlloc(nullptr, ExampleSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (ExampleBuffer)
	{
		DWORD ExampleReadSize;
		if (!ReadFile(Example, ExampleBuffer, ExampleSize, &ExampleReadSize, nullptr))
		{
			return 3;
		}
		puts("");
		GoLexer lexer((char*)ExampleBuffer);
		lexer.Next();
		VirtualFree(ExampleBuffer, 0, MEM_RELEASE);
	}
	CloseHandle(Example);

	printf("File size %d\n", ExampleSize);

	std::string Arg = Utf16ToUtf8(argv[1]);
	printf("========\n");
	printf("PRINTOUT: %s\n", Arg.c_str());
	printf("utf8 len %zu\n", utf8len(Arg));


	char* ptr = Arg.data();
	for (; *ptr != '\0'; ptr++)
	{
		printf("%c %d\n", *ptr, (int)(unsigned char)*ptr);
	}

	printf("========\n");

	
	return 0;
}