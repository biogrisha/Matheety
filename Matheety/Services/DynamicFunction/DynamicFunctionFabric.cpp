#include "DynamicFunctionFabric.h"

DynamicFunctionFabric::~DynamicFunctionFabric()
{
	dllHndl.reset();
	std::string cmd = "rd /s /q " + m_filePath;
	std::system(cmd.c_str());
	m_isLoaded = false;

}

void DynamicFunctionFabric::AddFunction(const std::string& signature, const std::string& body)
{
	m_fileBuilder.AddFunction(signature, body);
}

void DynamicFunctionFabric::Build()
{
	std::system(("mkdir " + m_filePath).c_str());
	m_fileBuilder.GenerateFiles(m_filePath, m_fileName);

	std::string filePath = m_filePath + m_fileName;

	dllHndl.reset();
	m_isLoaded = false;

	std::string buildCMD = "g++ -o " + filePath + ".dll " + filePath + ".cpp " 
		+ FF_DllFolderManager::GetFullPath()+ FF_DllFolderManager::GetStartFileName();
	std::system(buildCMD.c_str());
}

void FF_DllFolderManager::ClearMainFolder()
{

	
	std::string cmd = "if exist " + GetFullPath() + "  rd /s /q " + GetFullPath();
	std::system(cmd.c_str());
	cmd = "mkdir " + GetFullPath();
    std::system(cmd.c_str());

	std::string content = R"EntryFileDLL(
#include <windows.h>
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
  return 1;
}
int WINAPI WinMain(      
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{  
  return 0;
}
)EntryFileDLL";

    std::ofstream outfile(m_fullPath+ m_startFileName);

    outfile << content << std::endl;

    outfile.close();

}

std::string FF_DllFolderManager::m_folderName = "DynamicFunctionDlls";
std::string FF_DllFolderManager::m_fullPath;
std::string FF_DllFolderManager::m_startFileName = "DLLEntry.cpp";
