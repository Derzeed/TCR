#include <iostream>
#include <vector>
#include <math.h>
#include <tuple>
#include <algorithm>

#define eps 1e-6

using namespace std;

using coord = double;
coord pi = atan(-1);

struct Point {
  coord x, y;

  Point(){}
  Point(coord x, coord y) : x(x), y(y) {}
};

Point operator +(const Point &a, const Point &b) {
  return {a.x + b.x, a.y + b.y};
}

Point operator -(const Point &a, const Point &b) {
  return {a.x - b.x, a.y - b.y};
}

Point operator *(const coord scalar, const Point &a) {
  return {scalar*a.x, scalar*a.y};
}

coord sp(Point a, Point b) {
  return a.x*b.x + a.y*b.y;
}

coord vp(Point a, Point b) {
  return a.x*b.y - a.y*b.x;
}

Point perpendicular(Point p) {
  return {-p.y, p.x};
}

Point rotate(Point p, double rad) {
  return cos(rad)*p + sin(rad)*perpendicular(p);
}

coord dist(Point a, Point b) {
  Point tmp = b-a;
  return sqrt(tmp.x*tmp.x + tmp.y*tmp.y);
}

struct Line {
  coord a, b, c;

  Line() {}
  Line(coord a, coord b, coord c) : a(a), b(b), c(c) {
    normalize();
  }

  Line(Point p1, Point p2) {
    a = p1.y - p2.y;
    b = p2.x - p1.x;
    c = -a*p1.x - b*p1.y;
    normalize();
  }

  void normalize() {
    coord length = sqrt(a*a + b*b);
    a = a/length;
    b = b/length;
    c = c/length;

  }

  coord formula(Point p) {
    return a*p.x + b*p.y + c;
  }
};

coord dist(Line l, Point p) {
  return fabs(l.formula(p));
}

Point intersection(Line l1, Line l2) {
  return {
    (l1.b*l2.c - l2.b*l1.c)/(l1.a*l2.b - l2.a*l1.b),
    (l1.a*l2.c - l2.a*l1.c)/(l2.a*l1.b - l1.a*l2.b)
  };
}

Point proj(Line l, Point p) {
  return p - l.formula(p)*Point(l.a, l.b);
}

struct Circle {
  Point c;
  coord r;

  Circle() {}
  Circle(Point c, coord r) : c(c), r(r) {}
};

coord dist(Circle c, Line l) {
  return dist(l, c.c);
}

Line radicalAxis(Circle c1, Circle c2) {
  return {
    2*(c2.c.x - c1.c.x),
    2*(c2.c.y - c1.c.y),
    pow(c1.c.x, 2) - pow(c2.c.x, 2)
    + pow(c1.c.y, 2) - pow(c2.c.y, 2)
    + pow(c2.r, 2) - pow(c1.r, 2) 
  };
}

tuple<Point, Point> intersection(Circle c, Line l) {
  Point P = proj(l, c.c);
  Point diff = sqrt(pow(c.r, 2) - pow(dist(c.c, P), 2))*Point(-l.b, l.a);
  return make_tuple(P+diff, P-diff);
}

tuple<Point, Point> intersection(Circle c1, Circle c2) {
  return intersection(c1, radicalAxis(c1, c2));
}

tuple<Line, Line> tangentLine(Point p, Circle c) {
  return make_tuple(
    Line {p, p + rotate(c.c - p, asin(c.r/dist(c.c, p)))},
    Line {p, p + rotate(c.c - p, asin(-c.r/dist(c.c, p)))}
  );
}

tuple<Point, Point> tangentPoint(Point p, Circle c) {
  Line a, b;
  tie(a, b) = tangentLine(p, c);
  return make_tuple(
    proj(a, c.c),
    proj(b, c.c)
  );
}

tuple<Line, Line> outerTangentLine(Circle c1, Circle c2) {
  if(c1.r > c2.r) return outerTangentLine(c2, c1);
  Line a, b;
  tie(a,b) = tangentLine(c1.c, Circle(c2.c, c2.r-c1.r));
  a.c += c1.r;
  b.c += c1.r;
  a.normalize();
  b.normalize();
  return make_tuple(a, b);
}

tuple<Line, Line> innerTangentLine(Circle c1, Circle c2) {
  Line a, b;
  tie(a, b) = tangentLine(c1.c, Circle(c2.c, c2.r+c1.r));
  a.c -= c1.r;
  b.c -= c2.r;
  a.normalize();
  b.normalize();
  return make_tuple(a, b);
}

using Polygon = vector<Point>;

coord area(Polygon pol) {
  coord res = 0;
  for(int i = 0; i < pol.size(); ++i) {
    res += vp(pol[i], pol[(i+1) % pol.size()]);
  }
  return res/2;
}

coord angle(Point a, Point b) {
  return atan2(sp(a, b), vp(a, b));
}

bool isInside(Polygon pol, Point p) {
  coord sum = 0;
  for(int i = 0; i < pol.size(); ++i) {
    sum += angle(pol[i]-p, pol[(i+1) % pol.size()]-p);
  }

  return fabs(sum - 2*pi) < eps;
}

bool cmp(Point a, Point b) {
    return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool cw(Point a, Point b, Point c) {
  return vp(b-a, c-a) < 0;
}

bool ccw(Point a, Point b, Point c) {
  return !cw(a, b, c);
}

void convexHull(Polygon &a) {
  if(a.size() == 1)  return;
  sort(a.begin(), a.end(), &cmp);
  Point p1 = a[0],  p2 = a.back();
  Polygon up, down;
  up.push_back(p1);
  down.push_back(p1);
  for(int i = 1; i < a.size(); ++i) {
    if(i == a.size()-1 || cw(p1, a[i], p2)) {
      while(up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i]))
        up.pop_back();
      up.push_back(a[i]);
    }
    if(i == a.size()-1 || ccw(p1, a[i], p2)) {
      while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i]))
        down.pop_back();
      down.push_back(a[i]);
    }
  }

  a.clear();
  for(int i = 0; i < up.size(); ++i)
    a.push_back(up[i]);
  for(int i = down.size()-2; i > 0; --i)
    a.push_back(down[i]);
}

int main() {
  Line test = {{2, 1}, {0, 5}};
  Line test2 = {{1, 0}, {5, 0}};
  //cout << test.a << " " << test.b << " " << test.c << endl;
  //cout << test2.a << " " << test2.b << " " << test2.c << endl;
  Point inter = intersection(test, test2);
  //cout << inter.x << ", " << inter.y << endl;
  Point inter2;
  tie(inter, inter2) = intersection({{0, 0}, 5}, test);
  cout << inter.x << ", " << inter.y << endl;
  cout << inter2.x << ", " << inter2.y << endl;
  tie(inter, inter2) = intersection({{0, 0}, 5}, {{0, 4}, 3});
  Point a = proj({0, 8, -16}, {0, 0});
  cout << a.x << ":" << a.y << endl;
  cout << inter.x << ", " << inter.y << endl;
  cout << inter2.x << ", " << inter2.y << endl;

  tie(inter, inter2) = tangentPoint({0, 0}, {{0, 5}, 3});
  cout << inter.x << " <> " << inter.y << endl;
  cout << inter2.x << " <> " << inter2.y << endl;

  cout << test.formula({0, 2}) << endl;
  cout << test.formula({2, 0}) << endl;

  Polygon pol = {{2, 2}, {1, 1}, {2, 0}, {0, 0}, {0, 2}};
  convexHull(pol);
  for(auto p : pol) cout << p.x << "," << p.y << "  ";
  cout << endl;
  return 0;
}