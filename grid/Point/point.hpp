#ifndef POINT_H
#define POINT_H

	class Point{
		public:
			Point();
			~Point();
			Point(float xp, float yp);
			static float distance(const Point& a, const Point& b);
			float distFrmOrg() const;
			float getXcord() const;
			float getYcord() const;
			float randFloatCord() const;

		private:
			float x;
			float y;
	};
#endif