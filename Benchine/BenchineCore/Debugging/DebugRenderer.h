#pragma once
#include "Helpers/GeneralHelpers.h"
namespace DebugRenderer
{
	//POINTS
	void DrawPoint(float x, float y, float pointSize = 1.0f);
	void DrawPoint(const glm::vec2& p, float pointSize = 1.0f);
	void DrawPoints(const std::vector<glm::vec2>& vertices, float pointSize = 1.0f);
	//LINES
	void DrawLine(float x1, float y1, float x2, float y2, float lineWidth = 1.0f);
	void DrawLine(const glm::vec2& p1, const glm::vec2& p2, float lineWidth = 1.0f);
	//RECTS
	void DrawRect(float left, float bottom, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const glm::vec2& bottomLeft, float width, float height, float lineWidth = 1.0f);
	void DrawRect(const FRect& rect, float lineWidth = 1.0f);
	void FillRect(float left, float bottom, float width, float height);
	void FillRect(const glm::vec2& bottomLeft, float width, float height);
	void FillRect(const FRect& rect);
	//CIRCLES
	void DrawEllipse(float centerX, float centerY, float radX, float radY, float lineWidth = 1.0f);
	void DrawEllipse(const glm::vec2& center, float radX, float radY, float lineWidth = 1.0f);
	void DrawEllipse(const FEllipse& ellipse, float lineWidth = 1.0f);
	void FillEllipse(float centerX, float centerY, float radX, float radY);
	void FillEllipse(const FEllipse& ellipse);
	void FillEllipse(const glm::vec2& center, float radX, float radY);
	//ARCS
	void DrawArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f);
	void DrawArc(const glm::vec2& center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth = 1.0f);
	void FillArc(float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle);
	void FillArc(const glm::vec2& center, float radX, float radY, float fromAngle, float tillAngle);
	//POLYGONS
	void DrawPolygon(const Polygon2D& vertices, bool closed = true, float lineWidth = 1.0f);
	void FillPolygon(const Polygon2D& vertices);
}