#include <string>

class Session {
 public:
  Session() = default;
  Session(Session&) = delete;
  Session& operator=(Session&) = delete;
  Session(Session&&) = delete;
  Session& operator=(Session&&) = delete;



 private:
  std::string measurements; //contains the measurements while the program is running
  std::string outputFile = "Measurements";
};