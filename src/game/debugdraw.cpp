#include "debugdraw.h"


DebugDraw* DebugDraw::sInstance = nullptr;


DebugDraw::DebugDraw(
  const std::shared_ptr<sf::RenderTarget> &window
)
  : mWindow(window)
{
  sInstance = this;
}


sf::Color DebugDraw::GLColorToSFML(const b2Color& color, sf::Uint8 alpha)
{
  return sf::Color(
    static_cast<sf::Uint8>(color.r * 255),
    static_cast<sf::Uint8>(color.g * 255),
    static_cast<sf::Uint8>(color.b * 255),
    alpha
  );
}


sf::Vector2f DebugDraw::B2VecToSFVec(const b2Vec2 &vector)
{
   return sf::Vector2f(
      vector.x * PPM,
      vector.y * PPM
   );
}


void DebugDraw::DrawPolygon(
   const b2Vec2* vertices,
   int32 vertexCount,
   const b2Color& color
)
{
   sf::ConvexShape polygon(vertexCount);

   for(int i = 0; i < vertexCount; i++)
   {
      sf::Vector2f transformedVec = DebugDraw::B2VecToSFVec(vertices[i]);

      polygon.setPoint(
         i,
         sf::Vector2f(
            transformedVec.x,
            transformedVec.y
         )
      );
   }

   polygon.setOutlineThickness(-0.3f);
   polygon.setFillColor(sf::Color::Transparent);
   polygon.setOutlineColor(DebugDraw::GLColorToSFML(color));

   mWindow->draw(polygon);
}


void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
   sf::ConvexShape polygon(vertexCount);
   for(int i = 0; i < vertexCount; i++)
   {
      //polygon.setPoint(i, SFMLDraw::B2VecToSFVec(vertices[i]));
      sf::Vector2f transformedVec = DebugDraw::B2VecToSFVec(vertices[i]);
      polygon.setPoint(i, sf::Vector2f(std::floor(transformedVec.x), std::floor(transformedVec.y)));
      // flooring the coords to fix distorted lines on flat surfaces
   }

   // they still show up though.. but less frequently
   polygon.setOutlineThickness(-0.3f);
   polygon.setFillColor(DebugDraw::GLColorToSFML(color, 60));
   polygon.setOutlineColor(DebugDraw::GLColorToSFML(color));

   mWindow->draw(polygon);
}


void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
   sf::CircleShape circle(radius * PPM);
   circle.setOrigin(radius * PPM, radius * PPM);
   circle.setPosition(DebugDraw::B2VecToSFVec(center));
   circle.setFillColor(sf::Color::Transparent);
   circle.setOutlineThickness(-0.3f);
   circle.setOutlineColor(DebugDraw::GLColorToSFML(color));

   mWindow->draw(circle);
}


void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
   sf::CircleShape circle(radius * PPM);
   circle.setOrigin(radius * PPM, radius * PPM);
   circle.setPosition(DebugDraw::B2VecToSFVec(center));
   circle.setFillColor(DebugDraw::GLColorToSFML(color, 255 /*60*/));
   circle.setOutlineThickness(1.f);
   circle.setOutlineColor(DebugDraw::GLColorToSFML(color));

   b2Vec2 endPoint = center + radius * axis;
   sf::Vertex line[2] =
   {
      sf::Vertex(DebugDraw::B2VecToSFVec(center), DebugDraw::GLColorToSFML(color)),
      sf::Vertex(DebugDraw::B2VecToSFVec(endPoint), DebugDraw::GLColorToSFML(color)),
   };

   mWindow->draw(circle);
   mWindow->draw(line, 2, sf::Lines);
}



void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
   sf::Vertex line[] =
   {
      sf::Vertex(DebugDraw::B2VecToSFVec(p1), DebugDraw::GLColorToSFML(color)),
      sf::Vertex(DebugDraw::B2VecToSFVec(p2), DebugDraw::GLColorToSFML(color))
   };

   mWindow->draw(line, 2, sf::Lines);
}



void DebugDraw::DrawTransform(const b2Transform& xf)
{
   float lineLength = 0.4f;

   /*b2Vec2 xAxis(b2Vec2(xf.p.x + (lineLength * xf.q.c), xf.p.y + (lineLength * xf.q.s)));*/
   b2Vec2 xAxis = xf.p + lineLength * xf.q.GetXAxis();
   sf::Vertex redLine[] =
   {
      sf::Vertex(DebugDraw::B2VecToSFVec(xf.p), sf::Color::Red),
      sf::Vertex(DebugDraw::B2VecToSFVec(xAxis), sf::Color::Red)
   };

   // You might notice that the ordinate(Y axis) points downward unlike the one in Box2D testbed
   // That's because the ordinate in SFML coordinate system points downward while the OpenGL(testbed) points upward
   /*b2Vec2 yAxis(b2Vec2(xf.p.x + (lineLength * -xf.q.s), xf.p.y + (lineLength * xf.q.c)));*/
   b2Vec2 yAxis = xf.p + lineLength * xf.q.GetYAxis();
   sf::Vertex greenLine[] =
   {
      sf::Vertex(DebugDraw::B2VecToSFVec(xf.p), sf::Color::Green),
      sf::Vertex(DebugDraw::B2VecToSFVec(yAxis), sf::Color::Green)
   };

   mWindow->draw(redLine, 2, sf::Lines);
   mWindow->draw(greenLine, 2, sf::Lines);
}


DebugDraw *DebugDraw::getInstance()
{
  return sInstance;
}

