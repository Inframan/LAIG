#include "myTorus.h"


myTorus::myTorus(float inner, float outer, int slices, int loops)
{
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;
}

void myTorus::draw()
{
	double pi = acos(-1.0);
	float rr = 1.5f * inner;

	double dv = 2 * pi / loops;
	double dw = 2 * pi / slices;

	double v = 0.0f;
	double w = 0.0f;

// outer loop
	while (w < 2 * pi + dw) {
		v = 0.0f;
		glBegin(GL_TRIANGLE_STRIP);
		// inner loop
		while (v < 2 * pi + dv) {
			glNormal3d(
					(outer + rr * cos(v)) * cos(w)
							- (outer + inner * cos(v)) * cos(w),
					(outer + rr * cos(v)) * sin(w)
							- (outer + inner * cos(v)) * sin(w),
					(rr * sin(v) - inner * sin(v)));
			glVertex3d((outer + inner * cos(v)) * cos(w),
					(outer + inner * cos(v)) * sin(w), inner * sin(v));
			glNormal3d(
					(outer + rr * cos(v + dv)) * cos(w + dw)
							- (outer + inner * cos(v + dv)) * cos(w + dw),
					(outer + rr * cos(v + dv)) * sin(w + dw)
							- (outer + inner * cos(v + dv)) * sin(w + dw),
					rr * sin(v + dv) - inner * sin(v + dv));
			glVertex3d((outer + inner * cos(v + dv)) * cos(w + dw),
					(outer + inner * cos(v + dv)) * sin(w + dw),
					inner * sin(v + dv));
			v += dv;
		} // inner loop
		glEnd();
		w += dw;
	} //outer loop
}
   


myTorus::~myTorus(void)
{
}
