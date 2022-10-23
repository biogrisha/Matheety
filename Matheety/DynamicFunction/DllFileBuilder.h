#pragma once
#include <iostream>
#include <fstream> 
#include <vector>
#include <map>

struct FunctionContent
{
	std::string funcSignature;
	std::string funcBody;
};

class DllFileBuilder
{
public:
	void AddFunction(const std::string& signature, const std::string& body);
	void GenerateFiles(const std::string& filePath, const std::string& fileName);
private:
	std::vector<FunctionContent> m_functions;


	void GenerateHFile(const std::string& filePath, const std::string& fileName);
	void GenerateCppFile(const std::string& filePath, const std::string& fileName);

};