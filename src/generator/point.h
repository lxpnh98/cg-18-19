using namespace std;

class Point {

private:
	float x, y, z;
    float nx, ny, nz;
    float ti, tj;

public:
	Point() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
        this->nx = this->ny = this->nz = 0;
        this->ti = this->tj = 0;
	}
	Point(float a, float b, float c) {
		this->x = a;
		this->y = b;
		this->z = c;
        this->nx = this->ny = this->nz = 0;
        this->ti = this->tj = 0;
	}
	Point(float a, float b, float c, float nx, float ny, float nz, float ti, float tj) {
		this->x = a;
		this->y = b;
		this->z = c;
        this->nx = nx;
        this->ny = ny;
        this->nz = nz;
        this->ti = ti;
        this->tj = tj;
	}
	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	float getZ() {
		return z;
	}
	float getNX() {
		return nx;
	}
	float getNY() {
		return ny;
	}
	float getNZ() {
		return nz;
	}
	float getTI() {
		return ti;
	}
	float getTJ() {
		return tj;
	}
};
