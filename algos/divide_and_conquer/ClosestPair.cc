// Closest Pair
// give N d-dimension points, find the closest two point

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <random>
#include <iterator>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

typedef pair<double, double> point_t;
typedef pair<point_t, point_t> point_pair_t;

double DistanceOfTwo(point_t x, point_t y) {
  return sqrt(pow(x.first - y.first, 2) + pow(x.second - y.second, 2));
}

pair<double, point_pair_t> ClosestBruteForce(vector<point_t>& points) {
  if (points.size() < 2) {
    return {-1, {{0, 0}, {0, 0}}};
  }
  auto min_distance = abs(DistanceOfTwo(points[0], points[1]));
  point_pair_t min_points = {points[0], points[1]};
  for (auto i = points.begin(); i != points.end()-1; ++i)
    for (auto j = i+1; j != points.end(); ++j) {
      auto new_distance = abs(DistanceOfTwo(*i, *j));
      if (new_distance < min_distance) {
        min_distance = new_distance;
        min_points.first = *i;
        min_points.second = *j;
      }
    }
  return {min_distance, min_points};
}

pair<double, point_pair_t> ClosestPair(vector<point_t>& xp, vector<point_t>& yp) {
  if (xp.size() < 3)
    return ClosestBruteForce(xp);
  vector<point_t> xl, xr, yl, yr;
  auto size = xp.size();
  copy(xp.begin(), xp.begin() + size/2, back_inserter(xl));
  copy(xp.begin() + size/2, xp.end(), back_inserter(xr));
  double xm = xp[size/2].first;
  copy_if(yp.begin(), yp.end(), back_inserter(yl), [&xm](const point_t& p) {
      return p.first < xm;
    });
  copy_if(yp.begin(), yp.end(), back_inserter(yr), [&xm](const point_t& p) {
      return p.first >= xm;
    });
  assert(xl.size() == yl.size());
  assert(yr.size() == yr.size());
  pair<double, point_pair_t> left_result = ClosestPair(xl, yl);
  pair<double, point_pair_t> right_result = ClosestPair(xr, yr);
  auto minor = left_result.first <= right_result.first ? left_result : right_result;
  vector<point_t> ys;
  copy_if(yp.begin(), yp.end(), back_inserter(ys), [&minor, &xm](const point_t& p) {
      return abs(p.first - xm) < minor.first;
    });
  auto result = minor;
  for (auto i = ys.begin(); i != ys.end()-1; ++i) {
    for (auto j = i + 1; j != ys.end() && (j->second - i->second) < minor.first; ++j) {
      auto left_middle = abs(DistanceOfTwo(*j, *i));
      if (left_middle < result.first) {
        result = {left_middle, {*j, *i}};
      }
    }
  }
  return result;
}

pair<double, point_pair_t> ClosestPair(vector<point_t>& data) {
  vector<point_t> xp(data), yp(data);
  sort(xp.begin(), xp.end(), [](const point_t& a, const point_t& b) {
      return a.first < b.first;
    });
  sort(yp.begin(), yp.end(), [](const point_t& a, const point_t& b) {
      return a.second < b.second;
    });
  return ClosestPair(xp, yp);
}



void Shuffle(vector<double>& data) {
  srand(time(0));
  for (int i = data.size()-1; i >= 1; --i) {
    int j = rand() % (i+1);
    using std::swap;
    swap(data[i], data[j]);
  }
}


int main() {
  srand(time(nullptr));
  vector<point_t> data;
  for (int i = 0; i < 20; ++i) {
    data.push_back({rand() % 50, rand() % 50});
  }
  
  //  sort(data.begin(), data.end());
  //  auto last = unique(data.begin(), data.end());
  //  data.erase(last, data.end());

  //  Shuffle(data);

  for (auto& p : data) {
    cout << "[" << p.first << ", " << p.second << "] ";
  }
  cout << '\n';

  auto result = ClosestPair(data);
  cout << "Closest Points: (" << result.second.first.first << ", " << result.second.first.second << ")\t" << "("
       << result.second.second.first << ", " << result.second.second.second << ")\n";
  cout << "Closest Distance: " << result.first << '\n';

  return 0;
}
