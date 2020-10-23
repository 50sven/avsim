#pragma once

#include "../road/Road.hpp"
#include "../entity/Obstacle.hpp"
#include "../entity/Agent.hpp"
#include "../geom/Math.hpp"

#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cmath>


namespace avs {
namespace utils {

class World;

class Renderer
{
private:
    sf::RenderWindow window;
    sf::RenderTexture background_texture;

    float road_width;
    float road_length;

    float extend_x = 128.0f;    // extends the road layout to left and right

    int scale_x = 10;           // 1 pixel = 10cm
    int scale_y = scale_x;

    void setup_scenario(const road::Road &road, std::vector<entity::Obstacle> &obstacles)
    {
        background_texture.clear(sf::Color::Black);

        std::vector<road::Lane> lanes = road.get_lanes();
        std::vector<road::Shoulder> shoulders = road.get_shoulders();

        // Add lanes
        for (auto &lane : lanes)
        {
            float l = scale_x * (lane.get_length() +  2 * extend_x);
            float w = scale_y * lane.get_width();
            geom::Vector2D start = lane.get_center();
            sf::RectangleShape rectangle(sf::Vector2f(l, w));
            rectangle.setOrigin(l / 2, w / 2);
            rectangle.setPosition(l / 2, scale_y * start.y);
            if (lane.get_id() < 0)
            {
                rectangle.setFillColor(sf::Color(255, 0, 0));
            }
            else
            {
                rectangle.setFillColor(sf::Color(0, 255, 0));
            }
            
            background_texture.draw(rectangle);
        }

        // Add shoulders
        for (auto &shoulder : shoulders)
        {
            float l = scale_x * (shoulder.get_length() + 2 * extend_x);
            float w = shoulder.get_width();
            geom::Vector2D start = shoulder.get_center();
            sf::RectangleShape rectangle(sf::Vector2f(l, scale_y * w));
            rectangle.setOrigin(l / 2, scale_y * w / 2);
            rectangle.setPosition(l / 2, scale_y * (start.y));
            rectangle.setFillColor(sf::Color(50, 50, 50));
            background_texture.draw(rectangle);

            sf::RectangleShape line(sf::Vector2f(l, scale_y * 0.2f));
            line.setOrigin(0.0f, scale_y * 0.2f / 2);
            line.setPosition(0.0f, scale_y * (start.y + geom::Math::sign(shoulder.get_id()) * w / 2));
            background_texture.draw(line);
        }

        // Add lane markings
        for(auto it = lanes.begin(); it < lanes.end() - 1; it++)
        {
            float l = it->get_length() + 2 * extend_x;
            float w = it->get_width();
            geom::Vector2D start = it->get_center();
            for (int i = 0; i < int(l / 6.0); i++)
            {
                sf::RectangleShape line(sf::Vector2f(scale_x * 3.0f, scale_y * 0.2f));
                line.setOrigin(scale_x * -(int(l) % 6), 0.2f / 2);
                line.setPosition(scale_x * i * (3.0f + 3.0f), scale_y * (start.y + w / 2));
                background_texture.draw(line);
            }
        }

        // Add obstacles
        for (auto &obstacle : obstacles)
        {
            float l = scale_x * obstacle.get_size().x;
            float w = scale_y * obstacle.get_size().y;
            geom::Vector2D center = obstacle.get_location();
            sf::RectangleShape rectangle(sf::Vector2f(l, w));
            rectangle.setOrigin(l / 2, w / 2);
            rectangle.setPosition((l / 2 + scale_x * (center.x + extend_x)), scale_y * (center.y));
            rectangle.setFillColor(sf::Color(0, 0, 0));
            background_texture.draw(rectangle);
        }

        sf::View view(sf::Vector2f(scale_x * (road_length / 2 + extend_x), scale_y * road_width / 2),
                      sf::Vector2f(scale_x * (road_length + extend_x / 2), -window.getSize().y));
        background_texture.setView(view);
    }

public:

    Renderer() = default;

    void init(const road::Road &road, std::vector<entity::Obstacle> &obstacles)
    {
        road_length = road.get_length();
        road_width = road.get_width();

        window.create(sf::VideoMode(1000, scale_y * road_width), "World Visualization");
        window.setFramerateLimit(25);

        background_texture.create(scale_x * (road_length + 2 * extend_x),
                                  scale_y * road_width);

        setup_scenario(road, obstacles);
    }


    void draw(const std::vector<entity::Agent> &agents)
    {
        window.clear(sf::Color::Black);

        sf::Sprite sprite(background_texture.getTexture());
        window.draw(sprite);

        float offset_x = scale_x * extend_x;
        float offset_y = scale_y * road_width;

        std::vector<float> x_poses;
        float ci = 1.0;
        for (auto &agent : agents)
        {
            float l = agent.get_size().x;
            float w = agent.get_size().y;
            geom::Vector2D center = agent.get_location();
            sf::RectangleShape rectangle(sf::Vector2f(scale_x * l, scale_y * w));
            if (agent.get_forward_vector().x == -1)
            {
                rectangle.setOrigin(scale_x * l / 2, scale_y * w / 2);
                rectangle.setPosition(offset_x + scale_x * (center.x),
                                      offset_y - scale_y * center.y);
                x_poses.push_back(center.x);
            }
            else
            {
                rectangle.setOrigin(scale_x * l / 2, scale_y * w / 2);
                rectangle.setPosition(offset_x + scale_x * center.x,
                                      offset_y - scale_y * center.y);
                x_poses.push_back(center.x);
            }
            rectangle.setFillColor(sf::Color(0, 0, int(255 * ci)));
            window.draw(rectangle);
            ci -= 0.1;
        }

        float left = *std::min_element(x_poses.begin(), x_poses.end());
        float right = *std::max_element(x_poses.begin(), x_poses.end());

        float view_center = scale_x * ((right + left) / 2 + extend_x);
        float view_zoom = std::clamp(1.0f + (scale_x * (right - left + 10.0f) - window.getSize().x) / window.getSize().x,
                                     1.0f, road_length / 100.0f);
        sf::View view(sf::Vector2f(view_center, scale_y * road_width / 2),
                      sf::Vector2f(window.getSize().x, window.getSize().y));
        view.zoom(view_zoom);
        window.setView(view);

        window.display();
    }

};


} // namespace utils
} // namespace avs