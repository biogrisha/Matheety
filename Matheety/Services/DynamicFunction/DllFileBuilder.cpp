#include "DllFileBuilder.h"

void DllFileBuilder::AddFunction(const std::string& signature, const std::string& body)
{
    m_functions.push_back({ signature, body });
}

void DllFileBuilder::GenerateFiles(const std::string& filePath, const std::string& fileName)
{
    GenerateHFile(filePath, fileName);
    GenerateCppFile(filePath, fileName);
}

void DllFileBuilder::GenerateHFile(const std::string& filePath, const std::string& fileName)
{
    std::string content = "#ifndef " + fileName + "\n"
        "#define "+ fileName +"\n"
        "#ifdef __cplusplus\n"
        "extern \"C\"\n"
        "{\n"
        "#endif\n";


    for (auto& pr : m_functions)
    {
        content += "__declspec (dllexport) " + pr.funcSignature + ";\n";
    }
    content += "#ifdef __cplusplus\n"
        "}\n"
        "#endif\n"
        "#endif\n";

    std::ofstream outfile(filePath+ fileName + ".h");

    outfile << content << std::endl;

    outfile.close();
}

void DllFileBuilder::GenerateCppFile(const std::string& filePath, const std::string& fileName)
{

    std::string content =
        "#include \""+ fileName +".h\"\n"
        "#include <math.h>\n";

    for (auto& pr : m_functions)
    {
        content += pr.funcSignature + "\n";
        content += "{\n";
        content += pr.funcBody+"\n";

        content += "}\n";
    }

    std::ofstream outfile(filePath + fileName + ".cpp");

    outfile << content << std::endl;

    outfile.close();
}
