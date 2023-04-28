#include "ComplexPlane.h"


ComplexPlane::ComplexPlane(float aspectRatio) //constructor
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);
	m_view.setCenter(0.0, 0.0);
	m_zoomCount = 0;
}

void ComplexPlane::zoomIn() //self explanatory
{
	m_zoomCount++;
	double x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	double y = BASE_HEIGHT * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(x, y);
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	double x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	double y = BASE_HEIGHT * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(x, y);
}

void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(coord);
}

View ComplexPlane::getView()
{
	return m_view;
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
	m_mouseLocation = coord;
}

void ComplexPlane::loadText(Text& text)
{
	stringstream out;
	out << "Mandelbrot Set" << '\n' << "Center: (" << m_view.getCenter().x << ", "
		<< m_view.getCenter().y << ")" << '\n' << 
		"Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")" << '\n' <<
		"Left-click to Zoom in" << '\n' << "Right-click to Zoom out" << '\n';
	text.setString(out.str());

}

size_t ComplexPlane::countIterations(Vector2f coord)
{
	complex<float> c(coord.x, coord.y);
	complex<float> z(0, 0);
	for (size_t i = 0; i < MAX_ITER; i++)
	{
		z = z * z + c;
		if (abs(z) > 2.0)
		{
			return i;
		}

	}
	return MAX_ITER;

}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count != MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else
	{
		r = 25;
		g = 150;
		b = 255;
	}
}