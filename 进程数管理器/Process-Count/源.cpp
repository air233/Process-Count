#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<Windows.h>
#include<TlHelp32.h>
#include<comdef.h>
#include<stdlib.h>
#pragma warning(disable:4996)

std::string WcharToChar(const wchar_t* wp, size_t m_encode = CP_ACP)
{
	std::string str;
	int len = WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
	char    *m_char = new char[len + 1];
	WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	str = m_char;
	delete m_char;
	return str;
}

int main()
{
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		std::cout << "获取当前进程失败！";
	}
	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	std::vector <std::string> process;
	
	

	while (bMore)
	{
		process.push_back( WcharToChar(pe32.szExeFile));
		bMore = ::Process32Next(hProcessSnap, &pe32);
	
	}
	::CloseHandle(hProcessSnap);
	
	for (size_t i=0;i<process.size();i++)
	{
		//printf("%s\n", process[i]);
		std::cout << process[i] << std::endl;
	}
	std::cout <<"总进程数："<< process.size() << std::endl;
	system("pause");
	return 0;
}