#pragma once
#include <iostream>
#include <string>
#include <exception>
#include <memory>
#include <boost/locale.hpp>
#include <Helpers/Helpers.h>
#include "DllFileBuilder.h"

class FF_DllFolderManager
{
public:
	static void ClearMainFolder();
	static std::string& GetFullPath()
	{
		if (m_fullPath.empty())
		{

			m_fullPath = Helpers::GetAppPath();
			m_fullPath = m_fullPath + "\\" + m_folderName + "\\";
		}
		return m_fullPath;
	}

	static std::string& GetStartFileName()
	{
		return m_startFileName;
	}
private:
	static std::string m_folderName;
	static std::string m_fullPath;
	static std::string m_startFileName;
};


template<typename Ret, typename... Args>
class DynamicFunction
{
public:
	typedef Ret(*DynFunc)(Args...);
	DynamicFunction(DynFunc ptr, bool* isDllLoaded) :m_funcPtr(ptr), m_isDllLoaded(isDllLoaded)
	{

	}
	Ret operator()(Args...args) const
	{
		if (!(*m_isDllLoaded))throw std::exception("Function pointer is invalid. Dll is freed");
		return m_funcPtr(args...);
	}
	bool IsLoaded()
	{
		return *m_isDllLoaded;
	}
private:
	bool* m_isDllLoaded;
	DynFunc m_funcPtr;
};

struct DllHandle
{
	DllHandle(LPCWSTR filename)
		: h(LoadLibrary(filename)) {}
	~DllHandle() 
	{
		if (h)
		{
			FreeLibrary(h);
		}
	}
	const HINSTANCE Get() const { return h; }

private:
	HINSTANCE h;
};

class DynamicFunctionFabric
{
private:
	int GetId()
	{
		static int id = 0;
		return id++;
	}
public:
	DynamicFunctionFabric() {}
	~DynamicFunctionFabric();
	void AddFunction(const std::string& signature, const std::string& body);
	void Build();

	template<typename Ret, typename... Args>
	DynamicFunction<Ret, Args...> LoadFunction(const std::string& functionName)
	{
		if (!dllHndl)//If it is a second loading then dllHndl is erased in the Build() function above
		{
			std::string dllPath = m_filePath + m_fileName + ".dll";
			std::wstring wdllPath = boost::locale::conv::to_utf<wchar_t>(dllPath, "UTF-8");

			dllHndl.reset(new DllHandle(LPCWSTR(wdllPath.c_str())));

			if(dllHndl->Get())
				m_isLoaded = true;
		}

		DynamicFunction<Ret, Args...> resFunc(reinterpret_cast<DynamicFunction<Ret, Args...>::DynFunc>(
			GetProcAddress(dllHndl->Get(), functionName.c_str())), &m_isLoaded);
		

		return resFunc;
	}
private:
	DllFileBuilder m_fileBuilder;
	std::unique_ptr<DllHandle> dllHndl;
	bool m_isLoaded = false;
	std::string m_fileName = "DynFunc"+std::to_string(GetId());
	std::string m_filePath = FF_DllFolderManager::GetFullPath() + m_fileName + "\\";
};