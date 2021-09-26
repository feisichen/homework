#pragma once
//点绘制
void setPixel(cv::Mat& background, int x, int y, uchar color = 255) {
	uchar* data = background.ptr<uchar>(((background.rows - 1) / 2) - y, x + ((background.cols - 1) / 2));
	*data = color;
}
//直线绘制
void LineDDA(cv::Mat& background, int x1, int y1, int x2, int y2, uchar color = 255) {
	int dx, dy, step;
	float ox, oy, incx, incy;
	dx = x2 - x1;
	dy = y2 - y1;
	step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	ox = static_cast<float>(x1);
	oy = static_cast<float>(y1);
	incx = float(dx) / float(step);
	incy = float(dy) / float(step);
	for (int i = 0; i <= step; i++) {
		setPixel(background, static_cast<int>(ox + 0.5), static_cast<int>(oy + 0.5), color);
		ox += incx;
		oy += incy;
	}
}
void LineMid(cv::Mat& background, int x1, int y1, int x2, int y2, uchar color = 255) {
	if (x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	int x = x1, y = y1;
	int a = y1 - y2, b = x2 - x1, c = x1 * y2 - x2 * y1;                                                                   //ֱ直线方程 50 50 -250
	int u = a * b < 0 ? 1 : 0;
	setPixel(background, x, y, color);
	if (abs(a) <= abs(b)) { //|k|<=1                                                                                                  //斜率大于0时u=1，反之=0
		int delta0 = u == 1 ? a + a + b : a + a - b, delta1 = u == 1 ? a + a : a + a - b - b, delta2 = u == 1 ? a + a + b + b : a + a; //变化量 50 0 100
		while (x < x2) {
			if (delta0 < 0) {
				x++, y += u;
				delta0 += delta2;
			}
			else {
				x++, y += u - 1;
				delta0 += delta1;
			}
			setPixel(background, x, y,color);
		}
	}
	else {
		int delta0 = u == 1 ? b + b + a : -b - b + a, delta1 = u == 1 ? b + b + a + a : -b - b, delta2 = u == 1 ? b + b : -b - b + a + a;
		int d = u == 1 ? 1 : -1;
		while (abs(y - y2) > 0) {
			if (delta0 < 0) { //k>0时x不动，k<0时x+1
				y += d, x += 1 - u;
				delta0 += delta2;
			}
			else {
				y += d, x += u;
				delta0 += delta1;
			}
			setPixel(background, x, y,color);
		}
	}
}
void Bresenham(cv::Mat& background, int x1, int y1, int x2, int y2, uchar color = 255) {
	int dx = x2 - x1, dy = y2 - y1;
	int x = x1, y = y1;
	setPixel(background,x, y,color);
	int ux = dx > 0 ? 1 : -1;
	int uy = dy > 0 ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);
	if (dx > dy) {
		int p = 2 * dy - dx;
		for (int i = 0; i < abs(dx); ++i) {
			if (p < 0) {
				x += ux;
				p = p + 2 * dy;
			}
			else {
				x += ux;
				y += uy;
				p = p + 2 * dy - 2 * dx;
			}
			setPixel(background,x, y,color);
		}
	}
	else {
		int p = 2 * dx - dy;
		for (int i = 0; i < abs(dy); ++i) {
			if (p < 0) {
				y += uy;
				p = p + 2 * dx;
			}
			else {
				x += ux;
				y += uy;
				p = p + 2 * dx - 2 * dy;
			}
			setPixel(background, x, y, color);
		}
	}
}

//圆绘制
void Circomplete(cv::Mat& background, int x, int X, int y, int Y, uchar color = 255) {
	setPixel(background, x + X, y + Y, color);
	setPixel(background, x + X, y - Y, color);
	setPixel(background, x - X, y + Y, color);
	setPixel(background, x - X, y - Y, color);
	setPixel(background, x - Y, y + X, color);
	setPixel(background, x + Y, y + X, color);
	setPixel(background, x - Y, y - X, color);
	setPixel(background, x + Y, y - X, color);
}
void CircleDDA(cv::Mat& background, int x, int y, int r, uchar color = 255) {
	int X, Y, end;
	end = static_cast<int>(ceil((static_cast<float>(r) / sqrt(2))));
	for (X = 0; X <= end; X++) {
		Y = static_cast<int>(round(sqrt(r * r - X * X)));
		Circomplete(background, x, X, y, Y, color);
	}
}
void CircleMid(cv::Mat& background, int x, int y, int r, uchar color = 255) {
	int X = 0, Y = r;
	int p = 1 - r;
	Circomplete(background, x, X, y, Y, color);
	while (X < Y) {
		if (p < 0) {
			Circomplete(background, x, ++X, y, Y, color);
			p = p + 2 * X + 1;
		}
		else {
			Circomplete(background, x, ++X, y, --Y, color);
			p = p + 2 * X + 1 - 2 * Y;
		}
	}
}
//椭圆绘制
void Ellcomplete(cv::Mat& background, int x, int X, int y, int Y, uchar color = 255) {
	setPixel(background, x + X, y + Y, color);
	setPixel(background, x + X, y - Y, color);
	setPixel(background, x - X, y + Y, color);
	setPixel(background, x - X, y - Y, color);
}
void EllipeMid(cv::Mat& background, int x, int y, int a, int b, uchar color = 255) {
	int X = 0, Y = b;
	int d1 = b * b - a * a * b + ((a * a) >> 2);
	Ellcomplete(background, x, X, y, Y, color);
	while (b * b * (X + 1) < a * a * (Y - 0.5)) {
		if (d1 < 0) {
			d1 += b * b * (2 * X + 3);
			++X;
		}
		else {
			d1 += b * b * (2 * X + 3) + a * a * (-2 * Y + 2);
			++X;
			--Y;
		}
		Ellcomplete(background, x, X, y, Y, color);
	}
	int d2 = b * b * (X * X + X) + b * b + a * a * (Y - 1) * (Y - 1) - a * a * b * b;
	while (Y > 0) {
		if (d2 < 0) {
			d2 += b * b * (2 * X + 2) + a * a * (-2 * Y + 3);
			++X;
			--Y;
		}
		else {
			d2 += a * a * (-2 * Y + 3);
			--Y;
		}
		Ellcomplete(background, x, X, y, Y, color);
	}
}