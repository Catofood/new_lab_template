// Шаблон тестов для C++ (Windows)
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

struct TestResult {
  std::string name;
  bool passed;
  std::string message;
};

TestResult testExecutableExists() {
  TestResult result;
  result.name = "Проверка исполняемого файла";
  
  // Путь относительно build/tests/
  DWORD attr = GetFileAttributesA("..\\Release\\lab.exe");
  result.passed = (attr != INVALID_FILE_ATTRIBUTES);
  result.message = result.passed ? "Файл найден" : "Файл не найден";
  
  return result;
}

TestResult testProgramLaunches() {
  TestResult result;
  result.name = "Проверка запуска";
  
  STARTUPINFOA si = {};
  PROCESS_INFORMATION pi = {};
  si.cb = sizeof(si);
  
  BOOL success = CreateProcessA(
    "..\\Release\\lab.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi
  );
  
  if (success) {
    Sleep(2000);
    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);
    result.passed = (exitCode == STILL_ACTIVE);
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
  } else {
    result.passed = false;
  }
  
  result.message = result.passed ? "Программа работает" : "Ошибка запуска";
  return result;
}

int main() {
  std::vector<TestResult> results;
  
  results.push_back(testExecutableExists());
  results.push_back(testProgramLaunches());
  
  int passed = 0;
  for (const auto& r : results) {
    std::cout << "[" << (r.passed ? "PASS" : "FAIL") << "] " 
              << r.name << ": " << r.message << std::endl;
    if (r.passed) passed++;
  }
  
  std::cout << "Пройдено: " << passed << "/" << results.size() << std::endl;
  return (passed == results.size()) ? 0 : 1;
}
