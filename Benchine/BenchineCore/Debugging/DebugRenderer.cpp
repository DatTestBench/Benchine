#include "BenchinePCH.h"
#include "Debugging/DebugRenderer.h"

//POINTS
void DebugRenderer::DrawPoint(float x, float y, float pointSize)
{
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	{
		glVertex2f(x, y);
	}
	glEnd();
}

void DebugRenderer::DrawPoint(const glm::vec2& p, float pointSize)
{
	DrawPoint(p.x, p.y, pointSize);
}

void DebugRenderer::DrawPoints(const std::vector<glm::vec2>& vertices, float pointSize)
{
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	{
		for (auto& vertex : vertices)
		{
			glVertex2f(vertex.x, vertex.y);
		}
	}
	glEnd();
}

//LINES
void DebugRenderer::DrawLine(const glm::vec2& start, const glm::vec2& end, float lineWidth)
{
	DrawLine(start.x, start.y, end.x, end.y, lineWidth);
}

void DebugRenderer::DrawLine(float x1, float y1, float x2, float y2, float lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	{
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}
	glEnd();
}

//RECTS
void DebugRenderer::DrawRect(const FRect& rect, float lineWidth)
{
	DrawRect(rect.x, rect.y, rect.width, rect.height, lineWidth);
}

void DebugRenderer::DrawRect(const glm::vec2& bottomLeft, float width, float height, float lineWidth)
{
	DrawRect(bottomLeft.x, bottomLeft.y, width, height, lineWidth);
}

void DebugRenderer::DrawRect(float left, float bottom, float width, float height, float lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(left, bottom);
		glVertex2f(left + width, bottom);
		glVertex2f(left + width, bottom + height);
		glVertex2f(left, bottom + height);
	}
	glEnd();
}

void DebugRenderer::FillRect(const FRect& rect)
{
	FillRect(rect.x, rect.y, rect.width, rect.height);
}

void DebugRenderer::FillRect(const glm::vec2& bottomLeft, float width, float height)
{
	FillRect(bottomLeft.x, bottomLeft.y, width, height);
}

void DebugRenderer::FillRect(float left, float bottom, float width, float height)
{
	glBegin(GL_POLYGON);
	{
		glVertex2f(left, bottom);
		glVertex2f(left + width, bottom);
		glVertex2f(left + width, bottom + height);
		glVertex2f(left, bottom + height);
	}
	glEnd();
}

//CIRCLES
void DebugRenderer::DrawEllipse(const FEllipse& ellipse, float lineWidth)
{
	DrawEllipse(ellipse.center.x, ellipse.center.y, ellipse.radX, ellipse.radY, lineWidth);
}

void DebugRenderer::DrawEllipse(const glm::vec2& center, float radX, float radY, float lineWidth)
{
	DrawEllipse(center.x, center.y, radX, radY, lineWidth);
}

void DebugRenderer::DrawEllipse(float centerX, float centerY, float radX, float radY, float lineWidth)
{
	float dAngle = radX > radY ? glm::pi<float>() / radX : glm::pi<float>() / radY;

	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	{
		for (float angle = 0.f; angle < 2.f * glm::pi<float>(); angle += dAngle)
		{
			glVertex2f(centerX + radX * cos(angle), centerY + radY * sin(angle));
		}
	}
	glEnd();
}

void DebugRenderer::FillEllipse(const FEllipse& ellipse)
{
	FillEllipse(ellipse.center.x, ellipse.center.y, ellipse.radX, ellipse.radY);
}

void DebugRenderer::FillEllipse(const glm::vec2& center, float radX, float radY)
{
	FillEllipse(center.x, center.y, radX, radY);
}

void DebugRenderer::FillEllipse(float centerX, float centerY, float radX, float radY)
{
	float dAngle = radX > radY ? glm::pi<float>() / radX : glm::pi<float>() / radY;

	glBegin(GL_POLYGON);
	{
		for (float angle = 0.f; angle < 2.f * glm::pi<float>(); angle += dAngle)
		{
			glVertex2f(centerX + radX * cos(angle), centerY + radY * sin(angle));
		}
	}
	glEnd();
}

//ARCS
void DebugRenderer::DrawArc(const glm::vec2& center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth)
{
	DrawArc(center.x, center.y, radX, radY, fromAngle, tillAngle, lineWidth);
}

void DebugRenderer::DrawArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth)
{
	if (fromAngle > tillAngle)
	{
		Logger::Log<LEVEL_WARNING>("DebugRenderer::DrawArc()") << "fromAngle > tillAngle, arc can not be drawn";
		return;
	}

	float dAngle = radX > radY ? glm::pi<float>() / radX : glm::pi<float>() / radY;

	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);
	{
		for (float angle = fromAngle; angle < tillAngle; angle += dAngle)
		{
			glVertex2f(centerX + radX * cos(angle), centerY + radY * sin(angle));
		}
		glVertex2f(centerX + radX * cos(tillAngle), centerY + radY * sin(tillAngle));
	}
	glEnd();
}

void DebugRenderer::FillArc(const glm::vec2& center, float radX, float radY, float fromAngle, float tillAngle)
{
	FillArc(center.x, center.y, radX, radY, fromAngle, tillAngle);
}

void DebugRenderer::FillArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle)
{
	if (fromAngle > tillAngle)
	{
		Logger::Log<LEVEL_WARNING>("DebugRenderer::FillArc") << "fromAngle > tillAngle, arc can not be drawn.";
		return;
	}
	float dAngle = radX > radY ? glm::pi<float>() / radX : glm::pi<float>() / radY;

	glBegin(GL_POLYGON);
	{
		glVertex2f(centerX, centerY);
		for (float angle = fromAngle; angle < tillAngle; angle += dAngle)
		{
			glVertex2f(centerX + radX * cos(angle), centerY + radY * sin(angle));
		}
		glVertex2f(centerX + radX * cos(tillAngle), centerY + radY * sin(tillAngle));
	}
	glEnd();
}

//POLYGONS
void DebugRenderer::DrawPolygon(const Polygon2D& vertices, bool closed, float lineWidth)
{
	glLineWidth(lineWidth);
	closed ? glBegin(GL_LINE_LOOP) : glBegin(GL_LINE_STRIP);
	{
		for (auto& vertex : vertices)
		{
			glVertex2f(vertex.x, vertex.y);
		}
	}
	glEnd();
}

void DebugRenderer::FillPolygon(const Polygon2D& vertices)
{
	glBegin(GL_POLYGON);
	{
		for (auto& vertex : vertices)
		{
			glVertex2f(vertex.x, vertex.y);
		}
	}
	glEnd();
}
