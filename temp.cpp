#include <iostream>
#using namespace std;

class Logger {
  static void LogDebug(const string& message) { cout << message << endl; }

  static void LogUnimplementedMethodReal(const string& method_name) {
    LogDebug("Unimplemented method: " + method_name);
  }

}
#define LogUnimplementedMethod Logger::LogUnimplementedMethodReal(__FUNCTION__)

int main (int argc, char* argv[]) {
  Logger::LogUnimplementedMethod;
  return 0;
}
