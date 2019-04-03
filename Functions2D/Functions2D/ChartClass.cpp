#include <wx/dc.h>
#include <memory>

#include "ChartClass.h"
#include "vecmat.h"

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c)
{
	cfg = std::move(c);
	x_step = 200;

	//m_defaultMatrix.data[0][0] = 1.0;
	//m_defaultMatrix.data[1][1] = 1.0;
}

void ChartClass::Set_Range()
{
	double xmin = 9999.9, xmax = -9999.9, ymin = 9999.9, ymax = -9999.9;
	double x, y, step;
	int i;

	xmin = cfg->Get_x_start();
	xmax = cfg->Get_x_stop();

	step = (cfg->Get_x_stop() - cfg->Get_x_start()) / (double)x_step;
	x = cfg->Get_x_start();

	for (i = 0; i <= x_step; i++)
	{
		y = GetFunctionValue(x);
		if (y > ymax) ymax = y;
		if (y < ymin) ymin = y;
		x = x + step;
	}

	y_min = ymin;
	y_max = ymax;
	x_min = xmin;
	x_max = xmax;
}

double ChartClass::GetFunctionValue(double x)
{
	if (cfg->Get_F_type() == 1) return x * x;
	if (cfg->Get_F_type() == 2) return 0.5*exp(4 * x - 3 * x*x);
	return x + sin(x*4.0);
}

void ChartClass::Draw(wxDC *dc, int w, int h)
{
	if (cfg->Get_x0() < cfg->Get_x1() && cfg->Get_y0() < cfg->Get_y1()) {
		dc->SetBackground(wxBrush(RGB(255, 255, 255)));
		dc->Clear();
		dc->SetPen(wxPen(RGB(255, 0, 0)));
		dc->DrawRectangle(10, 10, w - 20, h - 20);
		dc->SetClippingRegion(wxRect(10, 10, w - 20, h - 20));

		Matrix transformedMatrix;
		if (cfg->RotateScreenCenter())
			transformedMatrix = rotateMatrix(w, h) * translateMatrix() * scaleMatrix(w, h);
		else
			transformedMatrix = translateMatrix() * rotateMatrix(w, h) * scaleMatrix(w, h);

		DrawChartAxis(transformedMatrix, dc, h);
		DrawChartFunction(transformedMatrix, dc, h);
	}
}

double ChartClass::Get_Y_min()
{
	Set_Range();
	return y_min;
}

double ChartClass::Get_Y_max()
{
	Set_Range();
	return y_max;
}

void ChartClass::line2d(wxDC* dc, Matrix t, double x1, double y1, double x2, double y2, int h)
{
	Vector start, end;
	start.Set(x1, y1);
	end.Set(x2, y2);

	start = t * start;
	end = t * end;

	dc->DrawLine(wxPoint(start.GetX(), h - start.GetY()), wxPoint(end.GetX(), h - end.GetY()));
}

Matrix ChartClass::translateMatrix() const
{
	Matrix translatedMatrix;

	translatedMatrix.data[0][0] = translatedMatrix.data[1][1] = 1;
	translatedMatrix.data[0][2] = cfg->Get_dX();
	translatedMatrix.data[1][2] -= cfg->Get_dY();

	return translatedMatrix;
}

Matrix ChartClass::rotateMatrix(int w, int h) const
{
	Matrix rotationMatrix;
	float x, y;

	float cosA = cos(cfg->Get_Alpha() * M_PI / -180.0);
	float sinA = sin(cfg->Get_Alpha() * M_PI / -180.0);

	rotationMatrix.data[0][0] = rotationMatrix.data[1][1] = cosA;
	rotationMatrix.data[0][1] = sinA;
	rotationMatrix.data[1][0] = -sinA;

	if (cfg->RotateScreenCenter()) {
		x = w / 2.0;
		y = h / 2.0;
	}
	else {
		Matrix tmpMatrix = scaleMatrix(w, h);
		x = tmpMatrix.data[0][2];
		y = tmpMatrix.data[1][2];
	}

	rotationMatrix.data[0][2] = x * (1 - cosA) + y * (-sinA);
	rotationMatrix.data[1][2] = x * sinA + y * (1 - cosA);

	return rotationMatrix;
}

Matrix ChartClass::scaleMatrix(int w, int h) const
{
	Matrix scaledMatrix;

	scaledMatrix.data[0][0] = w / (cfg->Get_x1() - cfg->Get_x0());
	scaledMatrix.data[1][1] = h / (cfg->Get_y1() - cfg->Get_y0());
	scaledMatrix.data[0][2] = 10.0 - scaledMatrix.data[0][0] * cfg->Get_x0();
	scaledMatrix.data[1][2] = 10.0 - scaledMatrix.data[1][1] * cfg->Get_y0();

	return scaledMatrix;
}


void ChartClass::DrawChartAxis(Matrix matrix, wxDC* dc, int h)
{
	dc->SetPen(*wxBLUE_PEN);

	double start = cfg->Get_x_start();
	double stop = cfg->Get_x_stop();

	// draw axis
	line2d(dc, matrix, start, 0, stop, 0, h);
	line2d(dc, matrix, 0, Get_Y_min(), 0, Get_Y_max(), h);

	// draw arrows on axis
	line2d(dc, matrix, stop - 0.05, 0.05, stop, 0, h);
	line2d(dc, matrix, stop - 0.05, -0.05, stop, 0, h);

	line2d(dc, matrix, 0.025, Get_Y_max() - 0.1, 0, Get_Y_max(), h);
	line2d(dc, matrix, -0.025, Get_Y_max() - 0.1, 0, Get_Y_max(), h);

	// ox measure
	Vector oxP, oxN;

	float densityP = stop / 4.0;
	float densityN = start / 2.0;

	oxP.Set(densityP, 0);
	oxN.Set(densityN, 0);

	for (int i = 1; i <= 3; i++) {
		line2d(dc, matrix, oxP.GetX() * i, -0.05, oxP.GetX() * i, 0.05, h);
	}
	line2d(dc, matrix, oxN.GetX(), -0.05, oxN.GetX(), 0.05, h);

	oxP = matrix * oxP;
	oxN = matrix * oxN;
	dc->DrawRotatedText(wxString::Format(wxT("%.2f"), densityP), wxPoint(oxP.GetX(), h - oxP.GetY()), cfg->Get_Alpha());
	dc->DrawRotatedText(wxString::Format(wxT("%.2f"), densityN), wxPoint(oxN.GetX(), h - oxN.GetY()), cfg->Get_Alpha());

	// oy measure
	Vector oyP, oyN;
	oyP.Set(0, Get_Y_max() / 2.0);
	oyN.Set(0, Get_Y_min() / 2.0);

	line2d(dc, matrix, -0.025, oyP.GetY(), 0.025, oyP.GetY(), h);
	line2d(dc, matrix, -0.025, oyN.GetY(), 0.025, oyN.GetY(), h);
	
	oyP = matrix * oyP;
	oyN = matrix * oyN;

	dc->DrawRotatedText(wxString::Format(wxT("%.2f"), Get_Y_max() / 2.0), wxPoint(oyP.GetX(), h - oyP.GetY()), cfg->Get_Alpha());
	dc->DrawRotatedText(wxString::Format(wxT("%.2f"), Get_Y_min() / 2.0), wxPoint(oyN.GetX(), h - oyN.GetY()), cfg->Get_Alpha());
}

void ChartClass::DrawChartFunction(Matrix matrix, wxDC* dc, int h)
{
	dc->SetPen(*wxGREEN_PEN);
	const double density = (cfg->Get_x1() - cfg->Get_x0()) / x_step;
	for (double x = cfg->Get_x_start(); x < cfg->Get_x_stop(); x += density) {
		line2d(dc, matrix, x, GetFunctionValue(x), x + density, GetFunctionValue(x + density), h);
	}
}

