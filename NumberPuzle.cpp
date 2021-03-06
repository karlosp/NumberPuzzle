// NumberPuzle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NumberPuzle.hpp"
#include <chrono>
#include <functional>
#include <string>

static auto time_it = [](std::function<void()>  f) {
  using namespace std::chrono;
  auto start = steady_clock::now();
  f();
  auto stop = steady_clock::now();

  auto diff = stop - start;

  std::string time_unit = " s";
  double time_diff = duration_cast<duration<double>>(stop - start).count();
  if (diff < seconds(1)) {
    time_unit = " ms";
    time_diff = duration_cast<duration<double, std::milli>>(stop - start).count();
  }

  std::cout << "Duration: " << time_diff << time_unit << "\n";
};

int main()
{
  auto f5 = []() {solve<5>(Pos{ 1,3 }); };
  time_it(f5);

  auto f10 = []() {solve<10>(Pos{ 1,9 }); };
  time_it(f10);
  return 0;
}

