#ifndef IO_HPP
#define IO_HPP

#include <string>
#include <vector>

namespace LinuxForms
{
	class IO
	{
	public:
		static void WriteAllText(const std::string& text, const std::string& filepath);
		static void WriteAllBytes(std::vector<unsigned char>& bytes, const std::string& filepath);
		static void WriteAllBytes(unsigned char* bytes, size_t length, const std::string& filepath);
		static std::string ReadAllText(const std::string& filepath);
		static std::vector<std::string> ReadAllLines(const std::string& filepath);
		static std::vector<unsigned char> ReadAllBytes(const std::string& filepath);
		static std::string ReadLastLine(const std::string& filepath);
		static long GetFileSize(const std::string& filepath);
		static bool FileExists(const std::string& filepath);
	};
}

#endif