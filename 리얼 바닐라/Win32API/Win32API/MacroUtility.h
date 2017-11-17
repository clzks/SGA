#pragma once

// 랜덤 값 생성
inline int GetRandom(int max)
{
	return rand() % max;
}

// 최소값과 최대값 사이의 랜덤 값 생성(최소, 최대값 포함)
inline int GetRandom(int min, int max)
{
	// 0 ~ 5 : 5 - 0 + 1 => 0 ~ 5
	// 5 ~ 9 : 9 - 5 + 1 => 0 ~ 4 + 5 => 5 ~ 9
	return rand() % (max - min + 1) + min;
}

//선 그리기
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}
//점4개를 통한 선으로 사각형 그리기
inline void LineMakeRectangle(HDC hdc, int x, int y, int width, int height)
{
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + width, y);
	LineTo(hdc, x + width, y - height);
	LineTo(hdc, x, y - height);
	LineTo(hdc, x, y);
	

}

//렉트 만들기
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}


//렉트 센터점에 만들기
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

inline RECT RectMakeCenter(RECT rt, int width, int height)
{
	RECT rc;
	rc.left = (rt.right + rt.left) / 2 - width / 2;
	rc.top = (rt.top + rt.bottom) / 2 - height / 2;
	rc.right = rc.left + width;
	rc.bottom = rc.top + height;

	return rc;
}

//렉트 구조체로 사각형 그리기
inline void RectangleMake(HDC hdc, RECT rt)
{
	Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
}

//사각형 그리기 (Rectangle함수이용)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//원 그리기 (Ellipse함수이용)
inline void EllipseMake(HDC hdc, RECT rt)
{
	Ellipse(hdc, rt.left, rt.top, rt.right, rt.bottom);
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//원 센터점 그리기 (Ellipse함수이용)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

// 거리(대각선 길이) 구하는 함수
inline float GetLength(float x1, float y1, float x2, float y2)
{
	float fLengthX = x2 - x1;
	float fLengthY = y2 - y1;

	return sqrtf(fLengthX * fLengthX + fLengthY * fLengthY);
}

// 두 점 사이의 각도 구하는 함수
inline float GetAngle(float x1, float y1, float x2, float y2)
{
	float fLengthDiagonal = GetLength(x1, y1, x2, y2);

	if (fLengthDiagonal < FLT_EPSILON) return 0;

	float fAngle = acosf((x1 - x2) / fLengthDiagonal) / PI * 180.0f;

	// 각도 예외 처리
	if (y1 > y2)
	{
		fAngle = 360.0f - fAngle;

		if (fAngle >= 360.0f)
			fAngle -= 360.0f;
	}

	return fAngle;
}


inline RECT ViewPortMake(int x, int y, int Width, int Height)
{
	RECT rt;
	rt = RectMakeCenter(x, y, WINSIZEX, WINSIZEY);

	if (rt.left < 0)
	{
		rt.left = 0;
		rt.right = WINSIZEX;
	}
	else if (rt.right > Width)
	{
		rt.right = Width;
		rt.left = rt.right - WINSIZEX;
	}

	if (rt.top < 0)
	{
		rt.top = 0;
		rt.bottom = WINSIZEY;
	}
	else if (rt.bottom > Height)
	{
		rt.bottom = Height;
		rt.top = rt.bottom - WINSIZEY;
	}

	cout << "VPM" << rt.left << " " << rt.top << " " << rt.right << " " << rt.bottom << endl;
	return rt;
}

// 선형 보간
inline void LinearInterpolation(OUT float& x, OUT float& y,
	IN float fromX, IN float fromY, IN float toX, IN float toY, IN float t)
{
	x = fromX * (1.0f - t) + toX * t;
	y = fromY * (1.0f - t) + toY * t;
}

// 베지어 곡선
inline void BezierInterpolation(OUT float& x, OUT float& y,
	IN float fromX, IN float fromY, IN float viaX, IN float viaY, IN float toX, IN float toY, IN float t)
{
	float x1, y1, x2, y2;

	//x1 = fromX * (1.0f - t) + viaX * t;
	//y1 = fromY * (1.0f - t) + viaY * t;
	LinearInterpolation(x1, y1, fromX, fromY, viaX, viaY, t);

	//x2 = viaX * (1.0f - t) + toX * t;
	//y2 = viaY * (1.0f - t) + toY * t;
	LinearInterpolation(x2, y2, viaX, viaY, toX, toY, t);

	//x = x1 * (1.0f - t) + x2 * t;
	//y = y1 * (1.0f - t) + y2 * t;
	LinearInterpolation(x, y, x1, y1, x2, y2, t);
}

// 베지어 곡선
inline void BezierInterpolation2(OUT float& x, OUT float& y,
	IN float fromX, IN float fromY, IN float viaX, IN float viaY, IN float toX, IN float toY, IN float t)
{
	float x1, y1, x2, y2, x3, y3;

	float viaX2 = viaX;
	float viaY2 = fromY + fromY - viaY;

	LinearInterpolation(x1, y1, fromX, fromY, viaX, viaY, t);
	LinearInterpolation(x2, y2, viaX, viaY, viaX2, viaY2, t);
	LinearInterpolation(x3, y3, viaX2, viaY2, toX, toY, t);

	BezierInterpolation(x, y, x1, y1, x2, y2, x3, y3, t);
}

// 1. 원과 점의 충돌 체크 (이상 X)
inline bool CircleAndPointCollision(float circleX, float circleY, float radius, float pointX, float pointY)
{
	// 원의 중심점과 점과의 거리 계산 
	float DiagonalLine = GetLength(pointX, pointY, circleX, circleY);

	// 두 점의 거리가 원의 반지름 보다 크거나 같으면 아직 충돌이 아님 
	if (DiagonalLine > radius)
		return false;
	// 두 점의 거리가 원의 반지름보다 작아질 경우 충돌
	else
		return true;
}

// 2. 사각형과 점의 충돌 체크 (이상 X)
inline bool RectangleAndPointCollision(float Rectangle_X, float Rectangle_Y, float Rectangle_Width, float Rectangle_Height, float Point_X, float Point_Y)
{
	if ((Rectangle_X <= Point_X && Rectangle_X + Rectangle_Width >= Point_X) && (Rectangle_Y <= Point_Y && Rectangle_Y + Rectangle_Height >= Point_Y))
		return true;
	else
		return false;
}

//3. 사각형과 점의 충돌 체크  사각형의 X,Y좌표가 중점일 경우 
inline bool RectangleCenterAndPointCollision(float Rectangle_X, float Rectangle_Y, float Rectangle_Width, float Rectangle_Height, float Point_X, float Point_Y)
{
	// 사각형의 X와 사각형의 X+넓이 사이에 점이 있어야 하고
	if (Rectangle_X - Rectangle_Width / 2 < Point_X && Rectangle_X + Rectangle_Width / 2 > Point_X
		&& Rectangle_Y - Rectangle_Height / 2 < Point_Y && Rectangle_Y + Rectangle_Height / 2 > Point_Y)
		return true;
	else
		return false;
}

//4. 원과 원의 충돌 체크
inline bool CircleAndCircleCollision(float circle1_X, float circle1_Y, float circle1_Radius, float circle2_X, float circle2_Y, float circle2_Radius)
{
	// 원1의 중심점과 원2의 중심점과의 거리 계산 
	float DiagonalLine = GetLength(circle1_X, circle1_Y, circle2_X, circle2_Y);

	// 두 원의 반지름을 합함
	float RadiusSum = circle1_Radius + circle2_Radius;

	// 반지름의 합이 두 원의 중점과의 거리보다 작거나 같을 경우는 충돌이 아님
	if (RadiusSum <= DiagonalLine)
		return false;
	// 두 원의 거리가 반지름의 합보다 작을경우는 충돌
	else
		return true;
}

//5. 원과 사각형(x,y가 센터일 때 기준)의 충돌 체크 
inline bool CircleAndRectangleCollision(float Circle_X, float Circle_Y, float Circle_Radius, float Rectangle_X, float Rectange_Y, float Rectangle_Width, float Rectangle_Height)
{
	/* 사각형을 상하 좌우 원의 반지름 만큼 각각 확장 시켜서 원의 중점이 사각형내부 범위에 포함되는지 검사*/
	// 좌측으로 확장
	bool Collision1 = RectangleCenterAndPointCollision(Rectangle_X - Circle_Radius / 2, Rectange_Y, Rectangle_Width + Circle_Radius, Rectangle_Height, Circle_X, Circle_Y);
	// 우측으로 확장
	bool Collision2 = RectangleCenterAndPointCollision(Rectangle_X + Circle_Radius / 2, Rectange_Y, Rectangle_Width + Circle_Radius, Rectangle_Height, Circle_X, Circle_Y);
	// 상단으로 확장
	bool Collision3 = RectangleCenterAndPointCollision(Rectangle_X, Rectange_Y - Circle_Radius / 2, Rectangle_Width, Rectangle_Height + Circle_Radius, Circle_X, Circle_Y);
	// 하단으로 확장
	bool Collision4 = RectangleCenterAndPointCollision(Rectangle_X, Rectange_Y + Circle_Radius / 2, Rectangle_Width, Rectangle_Height + Circle_Radius, Circle_X, Circle_Y);

	/* 사각형의 귀퉁이와 원의 중점과의 거리를 계산하여 radius보다 작을경우 충돌*/
	// 좌상단 귀퉁이
	bool Collision5 = CircleAndPointCollision(Circle_X, Circle_Y, Circle_Radius, Rectangle_X - Rectangle_Width / 2, Rectange_Y - Rectangle_Height / 2);
	// 우상단 귀퉁이
	bool Collision6 = CircleAndPointCollision(Circle_X, Circle_Y, Circle_Radius, Rectangle_X + Rectangle_Width / 2, Rectange_Y - Rectangle_Height / 2);
	// 좌하단 귀퉁이
	bool Collision7 = CircleAndPointCollision(Circle_X, Circle_Y, Circle_Radius, Rectangle_X - Rectangle_Width / 2, Rectange_Y + Rectangle_Height / 2);
	// 우하단 귀퉁이
	bool Collision8 = CircleAndPointCollision(Circle_X, Circle_Y, Circle_Radius, Rectangle_X + Rectangle_Width / 2, Rectange_Y + Rectangle_Height / 2);

	// 8개중 하나라도 true가 발생하면 원과 사각형이 충돌 된거임 
	if (Collision1 || Collision2 || Collision3 || Collision4 || Collision5 || Collision6 || Collision7 || Collision8)
		return true;
	else
		return false;
}