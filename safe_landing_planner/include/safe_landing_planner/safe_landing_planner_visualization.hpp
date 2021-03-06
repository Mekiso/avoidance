#pragma once

#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include "safe_landing_planner.hpp"

namespace avoidance {

class SafeLandingPlannerVisualization {
 public:
  SafeLandingPlannerVisualization() = default;
  ~SafeLandingPlannerVisualization() = default;

  /**
  * @brief      initializes all publishers used for local planner visualization
  **/
  void initializePublishers(ros::NodeHandle& nh);

  /**
  * @brief injects into the SafeLandingPlannerVisualization class, all the data
  *to be visualized
  * @param[in] planner, SafeLandingPlanner class
  * @param[in] pos, current vehicle position
  * @param[in] last_pos, previous vehicle position
  **/
  void visualizeSafeLandingPlanner(const SafeLandingPlanner& planner,
                                   const geometry_msgs::Point& pos,
                                   const geometry_msgs::Point& last_pos);

 private:
  ros::Publisher local_pointcloud_pub_;
  ros::Publisher grid_pub_;
  ros::Publisher path_actual_pub_;
  ros::Publisher mean_pub_;
  ros::Publisher std_dev_pub_;

  int path_length_ = 0;

  /**
  * @brief       Visualization of the actual path of the drone and the path of
  *the waypoint
  * @params[in]  pos, location of the drone at the last timestep
  * @params[in]  last_pos, location of the drone at the previous timestep
  **/
  void publishPaths(const geometry_msgs::Point& pos,
                    const geometry_msgs::Point& last_pos);

  /**
  * @brief       Visualization of the boolean land grid
  * @params[in]  grid, grid data structure
  * @params[in]  pos, vehicle position
  * @param[in]   smoothing_size, kernel size on cell land hysteresis
  **/
  void publishGrid(const Grid& grid, const geometry_msgs::Point& pos,
                   float smoothing_size) const;

  /**
  * @brief      Visualization of the mean values grid
  * @params[in] grid, grid data structure
  **/
  void publishMean(const Grid& grid);

  /**
  * @brief      Visualization of the standard deviation values grid
  * @params[in]  grid, grid data structure
  **/
  void publishStandardDeviation(const Grid& grid);

  /**
  * @brief converts from HSV to RGB color space
  * @param[in] hsv, Hue in range [0, 360], Saturation and Value in range [0, 1]
  * @return[out] rgb, Red Blue Green, each elemnt in range [0, 1]
  */
  std::tuple<float, float, float> HSVtoRGB(std::tuple<float, float, float> hsv);
};
}
