#include "native_utilities.h"

#include "Windows.h"

#include <codecvt>
#include <locale>
#include "WGLRenderer.h"

using namespace evansbros;
using evansbros::byte;

const string getPathOfAssetDirectory()
{
	wchar_t pathToExecutable_UTF16[MAX_PATH];
	Microsoft::Windows::GetModuleFileNameW(nullptr, pathToExecutable_UTF16, MAX_PATH);

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	string pathToExecutable = converter.to_bytes(pathToExecutable_UTF16);
	return pathToExecutable.substr(0, pathToExecutable.find_last_of("\\"));
}

const Data loadAsset(const string assetPath)
{
	string assetLocation = getPathOfAssetDirectory() + assetPath;

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring assetLocation_UTF16 = converter.from_bytes(assetLocation.c_str());

	Microsoft::Windows::HANDLE fileHandle = Microsoft::Windows::CreateFileW(assetLocation_UTF16.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	Microsoft::Windows::LARGE_INTEGER fileSizeStruct;
	Microsoft::Windows::GetFileSizeEx(fileHandle, &fileSizeStruct);

	Microsoft::Windows::DWORD bytesRead;
	size_t fileSize = fileSizeStruct.LowPart;

	byte *fileData = new byte[fileSize];
	Microsoft::Windows::ReadFile(fileHandle, fileData, fileSize, &bytesRead, nullptr);

	Data dataObject(fileSize, fileData);

	delete[] fileData;
	Microsoft::Windows::CloseHandle(fileHandle);

	return dataObject;
}

evansbros::graphics::Renderer * getPlatformRenderer()
{
	return new graphics::WGLRenderer();
}

evansbros::graphics::Renderer * getPlatformRenderer(graphics::RenderType hint)
{
	return new graphics::WGLRenderer();
}