#pragma once

#include "Lane.hpp"
#include "../geom/Vector2D.hpp"

#include "yaml-cpp/yaml.h"

#include <filesystem>
#include <string>
#include <vector>
#include <array>
#include <stdexcept>
#include <algorithm>


namespace avs {
namespace road {


class Road
{
private:
    
    float length;
    float width;
    float speed_limit;

    std::vector<Lane> lanes;
    std::vector<Shoulder> shoulders;

public:
    // ==================================================
    //  CONSTRUCTORS
    // ==================================================

    Road() = default;
    Road(const std::string &config_file)
    {
        std::filesystem::path path(config_file);
        if (path.is_relative())
        {
            throw std::invalid_argument("Relative path is used. Use absolute path instead.");
        }
        YAML::Node config = YAML::LoadFile(path);
        config = config["static"]["road"];

        length = config["length"].as<float>();
        speed_limit = config["speed_limit"].as<float>();
        
        const float right_shoulder_width = config["shoulders"]["right_shoulder"]["width"].as<float>();
        const float left_shoulder_width = config["shoulders"]["left_shoulder"]["width"].as<float>();

        // Get offset y
        float offset_y = 0.0;
        for (auto const &lane : config["lanes"])
        {
            const float lane_width = lane["width"].as<float>();
            const float lane_id = lane["id"].as<int>();
            if (lane_id > 0)
            {
                offset_y += lane_width;
            }

        }
        if (right_shoulder_width != 0.0)
        {
            offset_y += right_shoulder_width;
        }

        // Add lanes
        float offset_y_right = 0.0; // for lanes with positive ids (right lanes)
        float offset_y_left = 0.0;  // for lanes with negative ids (left/opposite lanes)
        for (auto const &lane : config["lanes"])
        {
            const float lane_width = lane["width"].as<float>();
            const float lane_id = lane["id"].as<int>();

            geom::Vector2D starting_point;
            if (lane_id > 0)
            {
                starting_point.x = 0.0;
                starting_point.y = offset_y_right - lane_width / 2 + offset_y;
                offset_y_right -= lane_width;
            }
            else
            {
                starting_point.x = length;
                starting_point.y = offset_y_left + lane_width / 2 + offset_y;
                offset_y_left += lane_width;
            }
            
            Lane new_lane(lane_id, lane_width, length, starting_point);
            lanes.push_back(new_lane);
        }

        // Add right shoulder
        if (right_shoulder_width != 0.0)
        {
            geom::Vector2D starting_point;
            starting_point.x = 0.0;
            starting_point.y = offset_y_right - right_shoulder_width / 2 + offset_y;
            offset_y_right -= right_shoulder_width;
            Shoulder new_shoulder(1, right_shoulder_width, length, starting_point);
            shoulders.push_back(new_shoulder);
        }
        // Add left shoulder
        if (left_shoulder_width != 0.0)
        {
            geom::Vector2D starting_point;
            starting_point.x = length;
            starting_point.y = offset_y_left + left_shoulder_width / 2 + offset_y;
            offset_y_left += left_shoulder_width;
            Shoulder new_shoulder(-1, left_shoulder_width, length, starting_point);
            shoulders.push_back(new_shoulder);
        }
        width = offset_y_left - offset_y_right;
    }

    // ==================================================
    //  METHODS
    // ==================================================

    float get_length() const
    {
        return length;
    }

    float get_width() const
    {
        return width;
    }

    float get_speed_limit() const
    {
        return speed_limit;
    }

    std::vector<Lane> get_lanes() const
    {
        return lanes;
    }

    Lane get_lane(const int &lane_id) const
    {
        auto it = std::find_if(lanes.begin(), lanes.end(), [lane_id]
        (const Lane &lane) -> bool {return lane.get_id() == lane_id;});
        
        return *it;
    }

    std::vector<Shoulder> get_shoulders() const
    {
        return shoulders;
    }

    Shoulder get_shoulder(const int &shoulder_id) const
    {
        auto it = std::find_if(shoulders.begin(), shoulders.end(), [shoulder_id]
        (const Shoulder &shoulder) -> bool {return shoulder.get_id() == shoulder_id;});
        
        return *it;
    }

    // ==================================================
    //  OPERATORS
    // ==================================================

    friend std::ostream &operator<<(std::ostream &out, const Road &road)
    {
        out << std::fixed << std::setprecision(2);
        out << "Road(";
        for (auto &lane : road.get_lanes())
        {
            out << "\n   " << lane;
        }
        for (auto &shoulder : road.get_shoulders())
        {
            out << "\n   " << shoulder;
        }
        out << "\n)";
        return out;
    }
};


} // namespace road
} // namespace avs