#ifndef __POINT_H__
#define __POINT_H__

class point{
	public:
    static point goal;
    int x;
    int y;
    int distance;
    bool operator==(const point& rhs) const;
    bool operator!=(const point& rhs) const;
    bool operator<(const point& rhs) const;
    bool operator<=(const point& rhs) const;
    bool operator>(const point& rhs) const;
    bool operator>=(const point& rhs) const;
    point& operator=(const point& other);
};

#endif
