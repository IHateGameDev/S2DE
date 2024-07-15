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

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
          states.transform *= getTransform();
          states.texture = &m_tileset;
          target.draw(m_vertices, states);
        }

        void updateVertices()
        {
          for (unsigned int i = 0; i < m_width; ++i)
          {
            for (unsigned int j = 0; j < m_height; ++j)
            {
              updateTile(i, j);
            }
          }
        }

        void updateTile(unsigned int x, unsigned int y)
        {
          int tileNumber = m_tiles[x + y * m_width];

          if (tileNumber == -1)
            return;

          int tu = tileNumber % (m_tileset.getSize().x / m_tileSize.x);
          int tv = tileNumber / (m_tileset.getSize().x / m_tileSize.x);

          sf::Vertex* quad = &m_vertices[(x + y * m_width) * 4];

          setQuadPositions(quad, x, y);
          setQuadTexCoords(quad, tu, tv);
        }

        void setQuadPositions(sf::Vertex* quad, unsigned int x, unsigned int y)
        {
          quad[0].position = sf::Vector2f(x * m_tileSize.x, y * m_tileSize.y);
          quad[1].position = sf::Vector2f((x + 1) * m_tileSize.x, y * m_tileSize.y);
          quad[2].position = sf::Vector2f((x + 1) * m_tileSize.x, (y + 1) * m_tileSize.y);
          quad[3].position = sf::Vector2f(x * m_tileSize.x, (y + 1) * m_tileSize.y);
        }

        void setQuadTexCoords(sf::Vertex* quad, int tu, int tv)
        {
          quad[0].texCoords = sf::Vector2f(tu * m_tileSize.x, tv * m_tileSize.y);
          quad[1].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, tv * m_tileSize.y);
          quad[2].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, (tv + 1) * m_tileSize.y);
          quad[3].texCoords = sf::Vector2f(tu * m_tileSize.x, (tv + 1) * m_tileSize.y);
        }

      public:
        bool load(const std::string& tileset, sf::Vector2u tileSize, const std::vector<int>& tiles, unsigned int width = 50u, unsigned int height = 50u)
        {
          if (!m_tileset.loadFromFile(tileset))
            return false;

          m_tileSize = tileSize;
          m_width = width;
          m_height = height;
          m_tiles = tiles;

          m_vertices.setPrimitiveType(sf::Quads);
          m_vertices.resize(width * height * 4);

          updateVertices();

          return true;
        }

        void setTile(unsigned int x, unsigned int y, int tileNumber)
        {
          if (x >= m_width || y >= m_height)
            return;

          m_tiles[x + y * m_width] = tileNumber;
          updateTile(x, y);
        }

        int getTile(unsigned int x, unsigned int y) const
        {
          if (x >= m_width || y >= m_height)
            return -1;

          return m_tiles[x + y * m_width];
        }
    };
}

#endif // !TILEMAP_HPP