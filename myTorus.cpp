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
			double cosV = cos(v), sinV = sin(v), cosW = cos(w),sinW = sin(w),
				cosVdV = cos(v + dv), sinVdV = sin(v+dv), cosWdW = cos(w+dw),sinWdW = sin(w+dw);

			glNormal3d((outer + rr * cosV) * cosW - (outer + inner * cosV) * cosW, (outer + rr * cosV) * sinW - (outer + inner * cosV) * sinW,(rr * sinV - inner * sinV));
			glVertex3d((outer + inner * cosV) * cosW,(outer + inner * cosV) * sinW, inner * sinV);
			glNormal3d((outer + rr * cosVdV) * cosWdW - (outer + inner * cosVdV) * cosWdW, (outer + rr * cosVdV) * sinWdW - (outer + inner * cosVdV) * sinWdW, rr * sinVdV - inner * sinVdV);
			glVertex3d((outer + inner * cosVdV) * cosWdW, (outer + inner * cosVdV) * sinWdW, inner * sinVdV);
			v += dv;
		} // inner loop
		glEnd();
		w += dw;
	} //outer loop
}


myTorus::~myTorus(void)
{
}
