#include "stdafx.h"
#include "Arc.h"

ArcDraw::ArcDraw()
{
}


ArcDraw::~ArcDraw()
{
}

void ArcDraw::draw(int x, int y, float r, float sAngle, float eAngle, int lineWidth, Color &color, RenderWindow &window) {
	// ---------- DRAWS AN ARC BASED ON PARAMETERS ----------
	float previousAngle = sAngle;
	for (int i = sAngle; i <= eAngle; i += 5) { // DRAWS ANGLED LINES
		if (i != sAngle) {
			if ((previousAngle < 90) || (previousAngle > 270)) {
				float angle1Radians = (PI / 180) * previousAngle;
				float angle2Radians = (PI / 180) * i;

				float x1 = sin(angle1Radians) * r;
				float y1 = cos(angle1Radians) * r;

				float x2 = sin(angle2Radians) * r;
				float y2 = cos(angle2Radians) * r;

				float length = sqrt((x2 - x1) * (x2 - x1) + (y1 - y2) * (y1 - y2));
				float rotateAngle = atan((y1 - y2) / (x2 - x1));

				// ---------- SFML DOES NOT HAVE A LINE FUNCTION- SO USING A SMALL RECTANGLE AND SETTING IT'S ROTATION ----------
				RectangleShape line(Vector2f(length, lineWidth));
				line.setOrigin(Vector2f(0, lineWidth / 2));
				line.setFillColor(color);
				line.rotate((180 / PI) * rotateAngle);

				line.setPosition(Vector2f(x + x1, y - y1));

				window.draw(line);
			}
			else if (previousAngle < 180) { // ABOVE METHOD DOES NOT WORK WITH ALL PART OF THE ARC
				float angle1Radians = (PI / 180) * (previousAngle - 90);
				float angle2Radians = (PI / 180) * (i - 90);

				float x1 = cos(angle1Radians) * r;
				float y1 = sin(angle1Radians) * r;

				float x2 = cos(angle2Radians) * r;
				float y2 = sin(angle2Radians) * r;

				float length = sqrt((x1 - x2) * (x1 - x2) + (y2 - y1) * (y2 - y1));
				float rotateAngle = atan((x1 - x2) / (y2 - y1));

				RectangleShape line(Vector2f(length, lineWidth));
				line.setOrigin(Vector2f(0, lineWidth / 2));
				line.setFillColor(color);
				line.rotate((180 / PI) * rotateAngle + 90);

				line.setPosition(Vector2f(x + x1, y + y1));

				window.draw(line);
			}
			else {
				float angle1Radians = (PI / 180) * (previousAngle - 180);
				float angle2Radians = (PI / 180) * (i - 180);

				float x1 = sin(angle1Radians) * r;
				float y1 = cos(angle1Radians) * r;

				float x2 = sin(angle2Radians) * r;
				float y2 = cos(angle2Radians) * r;

				float length = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
				float rotateAngle = atan((x1 - x2) / (y1 - y2));

				RectangleShape line(Vector2f(length, lineWidth));
				line.setOrigin(0, lineWidth / 2);
				line.setFillColor(color);
				line.rotate((180 / PI) * rotateAngle + 270);

				line.setPosition(Vector2f(x - x1, y + y1));

				window.draw(line);
			}

			previousAngle = i;
		}
		
	}
}
