#include "BenchinePCH.h"
#include "Debugging/DebugRenderer.h"

//POINTS
#pragma region Points
void DebugRenderer::DrawPoint(const float x, const float y, const float pointSize)
{
	glPointSize(pointSize);
	glBegin(GL_POINTS);
	{
		glVertex2f(x, y);
	}
	glEnd();
}

void DebugRenderer::DrawPoint(const glm::vec2& p, const float pointSize)
{
	DrawPoint(p.x, p.y, pointSize);
}

void DebugRenderer::DrawPoints(const std::vector<glm::vec2>& vertices, const float pointSize)
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
#pragma endregion Points

//LINES
#pragma region Lines
void DebugRenderer::DrawLine(const glm::vec2& start, const glm::vec2& end, const float lineWidth)
{
	DrawLine(start.x, start.y, end.x, end.y, lineWidth);
}

void DebugRenderer::DrawLine(const float x1, const float y1, const float x2, const float y2, const float lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	{
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}
	glEnd();
}
#pragma endregion Lines

//RECTS
#pragma region Rects
void DebugRenderer::DrawRect(const FRect& rect, const float lineWidth)
{
	DrawRect(rect.x, rect.y, rect.width, rect.height, lineWidth);
}

void DebugRenderer::DrawRect(const glm::vec2& bottomLeft, const float width, const float height, const float lineWidth)
{
	DrawRect(bottomLeft.x, bottomLeft.y, width, height, lineWidth);
}

void DebugRenderer::DrawRect(const float left, const float bottom, const float width, const float height, const float lineWidth)
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

void DebugRenderer::FillRect(const glm::vec2& bottomLeft, const float width, const float height)
{
	FillRect(bottomLeft.x, bottomLeft.y, width, height);
}

void DebugRenderer::FillRect(const float left, const float bottom, const float width, const float height)
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

/*Centered*/
void DebugRenderer::DrawRectC(const FRect& rect, const float lineWidth)
{
	DrawRect(rect.x, rect.y, rect.width, rect.height, lineWidth);
}

void DebugRenderer::DrawRectC(const glm::vec2& center, const float width, const float height, const float lineWidth)
{
	DrawRect(center.x, center.y, width, height, lineWidth);
}

void DebugRenderer::DrawRectC(const float x, const float y, const float width, const float height, const float lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(x - width / 2.f, y - height / 2.f);
		glVertex2f(x + width / 2.f, y - height / 2.f);
		glVertex2f(x + width / 2.f, y + height / 2.f);
		glVertex2f(x - width / 2.f, y + height / 2.f);
	}
	glEnd();
}

void DebugRenderer::FillRectC(const FRect& rect)
{
	FillRect(rect.x, rect.y, rect.width, rect.height);
}

void DebugRenderer::FillRectC(const glm::vec2& center, const float width, const float height)
{
	FillRect(center.x, center.y, width, height);
}

void DebugRenderer::FillRectC(const float x, const float y, const float width, const float height)
{
	glBegin(GL_POLYGON);
	{
		glVertex2f(x - width / 2.f, y - height / 2.f);
		glVertex2f(x + width / 2.f, y - height / 2.f);
		glVertex2f(x + width / 2.f, y + height / 2.f);
		glVertex2f(x - width / 2.f, y + height / 2.f);
	}
	glEnd();
}
#pragma endregion Rects

//CIRCLES
#pragma region Circles
void DebugRenderer::DrawEllipse(const FEllipse& ellipse, const float lineWidth)
{
	DrawEllipse(ellipse.center.x, ellipse.center.y, ellipse.radX, ellipse.radY, lineWidth);
}

void DebugRenderer::DrawEllipse(const glm::vec2& center, const float radX, const float radY, const float lineWidth)
{
	DrawEllipse(center.x, center.y, radX, radY, lineWidth);
}

void DebugRenderer::DrawEllipse(const float centerX, const float centerY, const float radX, const float radY, const float lineWidth)
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

void DebugRenderer::FillEllipse(const glm::vec2& center, const float radX, const float radY)
{
	FillEllipse(center.x, center.y, radX, radY);
}

void DebugRenderer::FillEllipse(const float centerX, const float centerY, const float radX, const float radY)
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
#pragma endregion Circles

//ARCS
#pragma region Arcs
void DebugRenderer::DrawArc(const glm::vec2& center, const float radX, const float radY, const float fromAngle, const float tillAngle, const float lineWidth)
{
	DrawArc(center.x, center.y, radX, radY, fromAngle, tillAngle, lineWidth);
}

void DebugRenderer::DrawArc(const float centerX, const float centerY, const float radX, const float radY, const float fromAngle, const float tillAngle, const float lineWidth)
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

void DebugRenderer::FillArc(const glm::vec2& center, const float radX, const float radY, const float fromAngle, const float tillAngle)
{
	FillArc(center.x, center.y, radX, radY, fromAngle, tillAngle);
}

void DebugRenderer::FillArc(const float centerX, const float centerY, const float radX, const float radY, const float fromAngle, const float tillAngle)
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
#pragma endregion Arcs

//POLYGONS
#pragma region Polygons
void DebugRenderer::DrawPolygon(const Polygon2D& vertices, const bool closed, const float lineWidth)
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
#pragma endregion Polygons