#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>

namespace stde
{
  class TileMap : public sf::Drawable, public sf::Transformable
  {
    private:
      sf::VertexArray m_vertices;
      sf::Texture m_tileset;
      std::vector<int> m_tiles;
      sf::Vector2u m_tileSize;
      unsigned int m_width;
      unsigned int m_height;

      void updateVertices()
      {
        for (unsigned int i = 0; i < m_width; ++i)
          for (unsigned int j = 0; j < m_height; ++j)
            updateVertex(i, j);
      }

      void updateVertex(unsigned int i, unsigned int j)
      {
        int tileNumber = m_tiles[i + j * m_width];

        if (tileNumber == -1)
        {
          sf::Vertex* triangles = &m_vertices[(i + j * m_width) * 6];
          for (int k = 0; k < 6; ++k)
            triangles[k] = sf::Vertex();
          return;
        }

        int tu = tileNumber % (m_tileset.getSize().x / m_tileSize.x);
        int tv = tileNumber / (m_tileset.getSize().x / m_tileSize.x);

        sf::Vertex* triangles = &m_vertices[(i + j * m_width) * 6];

        triangles[0].position = sf::Vector2f(i * m_tileSize.x, j * m_tileSize.y);
        triangles[1].position = sf::Vector2f((i + 1) * m_tileSize.x, j * m_tileSize.y);
        triangles[2].position = sf::Vector2f(i * m_tileSize.x, (j + 1) * m_tileSize.y);
        triangles[3].position = sf::Vector2f(i * m_tileSize.x, (j + 1) * m_tileSize.y);
        triangles[4].position = sf::Vector2f((i + 1) * m_tileSize.x, j * m_tileSize.y);
        triangles[5].position = sf::Vector2f((i + 1) * m_tileSize.x, (j + 1) * m_tileSize.y);

        triangles[0].texCoords = sf::Vector2f(tu * m_tileSize.x, tv * m_tileSize.y);
        triangles[1].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, tv * m_tileSize.y);
        triangles[2].texCoords = sf::Vector2f(tu * m_tileSize.x, (tv + 1) * m_tileSize.y);
        triangles[3].texCoords = sf::Vector2f(tu * m_tileSize.x, (tv + 1) * m_tileSize.y);
        triangles[4].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, tv * m_tileSize.y);
        triangles[5].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, (tv + 1) * m_tileSize.y);
      }

      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
      {
        states.transform *= getTransform();

        states.texture = &m_tileset;

        target.draw(m_vertices, states);
      }

    public:
      bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
      {
        if (!m_tileset.loadFromFile(tileset))
          return false;

        m_tileSize = tileSize;
        m_width = width;
        m_height = height;

        m_tiles.resize(width * height);
        std::copy(tiles, tiles + (width * height), m_tiles.begin());

        m_vertices.setPrimitiveType(sf::Triangles);
        m_vertices.resize(width * height * 6);

        updateVertices();

        return true;
      }

      int getTile(unsigned int x, unsigned int y) const
      {
        if (x < m_width && y < m_height)
          return m_tiles[x + y * m_width];
        return -2;
      }

      void setTile(unsigned int x, unsigned int y, int tileNumber)
      {
        if (x < m_width && y < m_height)
        {
          m_tiles[x + y * m_width] = tileNumber;
          updateVertex(x, y);
        }
      }
  };
}

#endif // !TILEMAP_HPP