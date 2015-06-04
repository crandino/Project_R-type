//=================================
// include guard
#ifndef __Point2d_H__
#define __Point2d_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
//=================================
// the actual class

template <class TYPE>
class Point2d {

public:

	TYPE x, y;

	Point2d operator+ (const Point2d &p) const
	{
		Point2d tmp;
		tmp.x = x + p.x;
		tmp.y = y + p.y;
		return tmp;
	}

	Point2d operator- (const Point2d &p) const
	{
		Point2d tmp;
		tmp.x = x - p.x;
		tmp.y = y - p.y;
		return tmp;
	}

	const Point2d& operator+= (const Point2d &p)
	{
		x += p.x;
		y += p.y;
		return (*this);
	}

	const Point2d& operator-= (const Point2d &p)
	{
		x -= p.x;
		y -= p.y;
		return (*this);
	}

	bool operator== (const Point2d &p) const
	{
		return (x == p.x && y == p.y);
	}

	bool operator!= (const Point2d &p) const
	{
		return (x != p.x || y != p.y);
	}

	bool isBothZero() const
	{
		return (x == 0.0f && y == 0.0f);
	}

	void setZero()
	{
		x = y = 0;
	}

	float distanceTo(const Point2d &p) const
	{
		float fx = x - p.x;
		float fy = y - p.y;
		return sqrt((fx*fx) + (fy*fy));
	}

	bool isClosedTo(const Point2d &p, float delta) const
	{
		return (abs(p.x - x) <= delta && abs(p.y - y) <= delta);
	}

};

#endif // !__Point2d_H__
