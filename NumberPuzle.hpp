#pragma once
#include <array>
#include <memory>
#include <vector>
#include <iostream>
#include <chrono>
#include <list>

struct Pos {
  int x = 0;
  int y = 0;
};

template<std::size_t N>
struct Board
{
  Board(std::array<std::array<char, N>, N> const& parent, Pos last_inserted_pos, char last_inserted_value) :
    last_inserted_pos_(last_inserted_pos),
    last_inserted_value_(last_inserted_value) {
    positions = parent;
    positions[last_inserted_pos.x][last_inserted_pos.y] = last_inserted_value;
  }
  std::array<std::array<char, N>, N> positions;

  char empty_fields = N * N;
  char last_inserted_value_;
  const Pos last_inserted_pos_;
};

template<class Board>
void print(Board const& board) {
  for (auto& row : board.positions) {
    for (auto& cell : row)
    {
      std::cout << (int)cell << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

template<std::size_t N>
void solve(Pos const & last_inserted_pos) {
  using namespace std::chrono;

  std::vector<Board<N>> positions;

  std::array<std::array<char, N>, N> empty;
  for (auto& row : empty) {
    for (auto& cell : row)
    {
      cell = 0;
    }
  }

  positions.emplace_back(Board<N>(empty, last_inserted_pos, 1));

  auto counter = 0ul;
  auto start = steady_clock::now();
  bool found_solution = false;
  while (!found_solution) {
    const auto current_pos = positions.back();
    positions.pop_back();

    auto const lip = current_pos.last_inserted_pos_;
    const int next_value = current_pos.last_inserted_value_ + 1;
    //can move NE
    if (lip.x + 2 < N && lip.y - 2 >= 0 && current_pos.positions[lip.x + 2][lip.y - 2] == 0) {
      positions.emplace_back(Board<N>(current_pos.positions, Pos{ lip.x + 2, lip.y - 2 }, next_value));
    found_solution = next_value == N * N;
      ++counter;
    }

    //can move NW
    if (lip.x - 2 >= 0 && lip.y - 2 >= 0 && current_pos.positions[lip.x - 2][lip.y - 2] == 0) {
      positions.emplace_back(Board<N>(current_pos.positions, Pos{ lip.x - 2, lip.y - 2 }, next_value));
    found_solution = next_value == N * N;
      ++counter;
    }

    //can move SW
    if (lip.x - 2 >= 0 && lip.y + 2 < N && current_pos.positions[lip.x - 2][lip.y + 2] == 0) {
      positions.emplace_back(Board<N>(current_pos.positions, Pos{ lip.x - 2, lip.y + 2 }, next_value));
    found_solution = next_value == N * N;
      ++counter;
    }

    //can move SE
    if (lip.x + 2 < N && lip.y + 2 < N && current_pos.positions[lip.x + 2][lip.y + 2] == 0) {
      positions.emplace_back(Board<N>(current_pos.positions, Pos{ lip.x + 2, lip.y + 2 }, next_value));
    found_solution = next_value == N * N;
      ++counter;
    }
    //can move E
    if (lip.x + 3 < N && current_pos.positions[lip.x + 3][lip.y] == 0) {
      positions.emplace_back(Board<N>(current_pos.positions, Pos{ lip.x + 3, lip.y }, next_value));
    found_solution = next_value == N * N;
      ++counter;
    }

    //can move W
    if (lip.x - 3 > 0 && current_pos.positions[lip.x - 3][lip.y] == 0) {
      positions.emplace_back(Board<N>(current_pos.positions, Pos{ lip.x - 3, lip.y }, next_value));
    found_solution = next_value == N * N;
      ++counter;
    }

    //can move N
    if (lip.y - 3 >= 0 && current_pos.positions[lip.x][lip.y - 3] == 0) {
      positions.emplace_back(Board<N>(current_pos.positions, Pos{ lip.x, lip.y - 3 }, next_value));
    found_solution = next_value == N * N;
      ++counter;
    }

    //can move S
    if (lip.y + 3 < N && current_pos.positions[lip.x][lip.y + 3] == 0) {
      positions.emplace_back(Board<N>(current_pos.positions, Pos{ lip.x, lip.y + 3 }, next_value));
    found_solution = next_value == N * N;
      ++counter;
    }
    /////

    if (counter % 17000000 == 0) {
      auto stop = steady_clock::now();
      auto diff_s = duration_cast<duration<double>>(stop - start).count();
      auto moves_per_sec = counter / diff_s;
      std::cout << "Execution time: " << diff_s << "\n";
      std::cout << "Counter: " << counter/1000000 << "M , moves per sec: " << moves_per_sec/1000000 <<  " M\n";
      std::cout << "Positions size: " << positions.size() << "\n";
      std::cout << "Max score: " << (int)positions.back().last_inserted_value_ << "\n";
      print(positions.back());
      std::cout << "\n";
    }
  }

  std::cout << " >>>>>>>>>>>>>>>>>>>>>>>>>>> FINISHED !! <<<<<<<<<<<<<<<<<<< " << counter << "\n";
  std::cout << "Counter: " << counter << "\n";
  print(positions.back());

}