#include "./pybind11/embed.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>

namespace py = pybind11;
using namespace std::chrono_literals;

class Wrapper
{
public:
  Wrapper()
  {
    py::gil_scoped_acquire acquire;
    _obj = py::module::import("wrapper").attr("Wrapper")();
    _wrapperInit = _obj.attr("wrapperInit");
    _wrapperFini = _obj.attr("wrapperFini");

  }
  
  ~Wrapper()
  {
    _wrapperInit.release();
    _wrapperFini.release();
  }

  int wrapperInit() 
  {
    py::gil_scoped_acquire acquire;
    return _wrapperInit(nullptr).cast<int>();
  }

  void wrapperFini(int x)
  {
    py::gil_scoped_acquire acquire;
    _wrapperFini(x);
  }

  private:
  py::object _obj;
  py::object _wrapperInit;
  py::object _wrapperFini;
};
void thread_func(int iteration)
{
  Wrapper w;

  for (int i = 0; i < 1; i++)
  {
    w.wrapperInit();
    std::stringstream msg;
    msg << "iteration: " << iteration << " thread: " << std::this_thread::get_id() << std::endl;
    std::cout << msg.str();
        std::this_thread::sleep_for(100ms);
  }
}

int main() {
  py::scoped_interpreter python;
  py::gil_scoped_release release; // add this to release the GIL

  std::vector<std::thread> threads;

  for (int i = 0; i < 1; ++i)
    threads.push_back(std::thread(thread_func, 1));

  for (auto& t : threads)
    t.join();

  return 0;
}
