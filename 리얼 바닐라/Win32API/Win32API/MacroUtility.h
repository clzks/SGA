#pragma once

// ���� �� ����
inline int GetRandom(int max)
{
	return rand() % max;
}

// �ּҰ��� �ִ밪 ������ ���� �� ����(�ּ�, �ִ밪 ����)
inline int GetRandom(int min, int max)
{
	// 0 ~ 5 : 5 - 0 + 1 => 0 ~ 5
	// 5 ~ 9 : 9 - 5 + 1 => 0 ~ 4 + 5 => 5 ~ 9
	return rand() % (max - min + 1) + min;
}

//�� �׸���
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}
//��4���� ���� ������ �簢�� �׸���
inline void LineMakeRectangle(HDC hdc, int x, int y, int width, int height)
{
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + width, y);
	LineTo(hdc, x + width, y - height);
	LineTo(hdc, x, y - height);
	LineTo(hdc, x, y);
	

}

//��Ʈ �����
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}


//��Ʈ �������� �����
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

//��Ʈ ����ü�� �簢�� �׸���
inline void RectangleMake(HDC hdc, RECT rt)
{
	Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
}

//�簢�� �׸��� (Rectangle�Լ��̿�)
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//�� �׸��� (Ellipse�Լ��̿�)
inline void EllipseMake(HDC hdc, RECT rt)
{
	Ellipse(hdc, rt.left, rt.top, rt.right, rt.bottom);
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//�� ������ �׸��� (Ellipse�Լ��̿�)
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

// �Ÿ�(�밢�� ����) ���ϴ� �Լ�
inline float GetLength(float x1, float y1, float x2, float y2)
{
	float fLengthX = x2 - x1;
	float fLengthY = y2 - y1;

	return sqrtf(fLengthX * fLengthX + fLengthY * fLengthY);
}

// �� �� ������ ���� ���ϴ� �Լ�
inline float GetAngle(float x1, float y1, float x2, float y2)
{
	float fLengthDiagonal = GetLength(x1, y1, x2, y2);

	if (fLengthDiagonal < FLT_EPSILON) return 0;

	float fAngle = acosf((x1 - x2) / fLengthDiagonal) / PI * 180.0f;

	// ���� ���� ó��
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

// ���� ����
inline void LinearInterpolation(OUT float& x, OUT float& y,
	IN float fromX, IN float fromY, IN float toX, IN float toY, IN float t)
{
	x = fromX * (1.0f - t) + toX * t;
	y = fromY * (1.0f - t) + toY * t;
}

// ������ �
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

// ������ �
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

// 1. ���� ���� �浹 üũ (�̻� X)
inline bool CircleAndPointCollision(float circleX, float circleY, float radius, float pointX, float pointY)
{
	// ���� �߽����� ������ �Ÿ� ��� 
	float DiagonalLine = GetLength(pointX, pointY, circleX, circleY);

	// �� ���� �Ÿ��� ���� ������ ���� ũ�ų� ������ ���� �浹�� �ƴ� 
	if (DiagonalLine > radius)
		return false;
	// �� ���� �Ÿ��� ���� ���������� �۾��� ��� �浹
	else
		return true;
}

// 2. �簢���� ���� �浹 üũ (�̻� X)
inline bool RectangleAndPointCollision(float Rectangle_X, float Rectangle_Y, float Rectangle_Width, float Rectangle_Height, float Point_X, float Point_Y)
{
	if ((Rectangle_X <= Point_X && Rectangle_X + Rectangle_Width >= Point_X) && (Rectangle_Y <= Point_Y && Rectangle_Y + Rectangle_Height >= Point_Y))
		return true;
	else
		return false;
}

//3. �簢���� ���� �浹 üũ  �簢���� X,Y��ǥ�� ������ ��� 
inline bool RectangleCenterAndPointCollision(float Rectangle_X, float Rectangle_Y, float Rectangle_Width, float Rectangle_Height, float Point_X, float Point_Y)
{
	// �簢���� X�� �簢���� X+���� ���̿� ���� �־�� �ϰ�
	if (Rectangle_X - Rectangle_Width / 2 < Point_X && Rectangle_X + Rectangle_Width / 2 > Point_X
		&& Rectangle_Y - Rectangle_Height / 2 < Point_Y && Rectangle_Y + Rectangle_Height / 2 > Point_Y)
		return true;
	else
		return false;
}

//4. ���� ���� �浹 üũ
inline bool CircleAndCircleCollision(float circle1_X, float circle1_Y, float circle1_Radius, float circle2_X, float circle2_Y, float circle2_Radius)
{
	// ��1�� �߽����� ��2�� �߽������� �Ÿ� ��� 
	float DiagonalLine = GetLength(circle1_X, circle1_Y, circle2_X, circle2_Y);

	// �� ���� �������� ����
	float RadiusSum = circle1_Radius + circle2_Radius;

	// �������� ���� �� ���� �������� �Ÿ����� �۰ų� ���� ���� �浹�� �ƴ�
	if (RadiusSum <= DiagonalLine)
		return false;
	// �� ���� �Ÿ��� �������� �պ��� �������� �浹
	else
		return true;
}

//5. ���� �簢��(x,y�� ������ �� ����)�� �浹 üũ 
inline bool CircleAndRectangleCollision(float Circle_X, float Circle_Y, float Circle_Radius, float Rectangle_X, float Rectange_Y, float Rectangle_Width, float Rectangle_Height)
{
	/* �簢���� ���� �¿� ���� ������ ��ŭ ���� Ȯ�� ���Ѽ� ���� ������ �簢������ ������ ���ԵǴ��� �˻�*/
	// �������� Ȯ��
	bool Collision1 = RectangleCenterAndPointCollision(Rectangle_X - Circle_Radius / 2, Rectange_Y, Rectangle_Width + Circle_Radius, Rectangle_Height, Circle_X, Circle_Y);
	// �������� Ȯ��
	bool Collision2 = RectangleCenterAndPointCollision(Rectangle_X + Circle_Radius / 2, Rectange_Y, Rectangle_Width + Circle_Radius, Rectangle_Height, Circle_X, Circle_Y);
	// ������� Ȯ��
	bool Collision3 = RectangleCenterAndPointCollision(Rectangle_X, Rectange_Y - Circle_Radius / 2, Rectangle_Width, Rectangle_Height + Circle_Radius, Circle_X, Circle_Y);
	// �ϴ����� Ȯ��
	bool Collision4 = RectangleCenterAndPointCollision(Rectangle_X, Rectange_Y + Circle_Radius / 2, Rectangle_Width, Rectangle_Height + Circle_Radius, Circle_X, Circle_Y);

	/* �簢���� �����̿� ���� �������� �Ÿ��� ����Ͽ� radius���� ������� �浹*/
	// �»�� ������
	bool Collision5 = CircleAndPointCollision(Circle_X, Circle_Y, Circle_Radius, Rectangle_X - Rectangle_Width / 2, Rectange_Y - Rectangle_Height / 2);
	// ���� ������
	bool Collision6 = CircleAndPointCollision(Circle_X, Circle_Y, Circle_Radius, Rectangle_X + Rectangle_Width / 2, Rectange_Y - Rectangle_Height / 2);
	// ���ϴ� ������
	bool Collision7 = CircleAndPointCollision(Circle_X, Circle_Y, Circle_Radius, Rectangle_X - Rectangle_Width / 2, Rectange_Y + Rectangle_Height / 2);
	// ���ϴ� ������
	bool Collision8 = CircleAndPointCollision(Circle_X, Circle_Y, Circle_Radius, Rectangle_X + Rectangle_Width / 2, Rectange_Y + Rectangle_Height / 2);

	// 8���� �ϳ��� true�� �߻��ϸ� ���� �簢���� �浹 �Ȱ��� 
	if (Collision1 || Collision2 || Collision3 || Collision4 || Collision5 || Collision6 || Collision7 || Collision8)
		return true;
	else
		return false;
}