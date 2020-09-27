#ifndef DEMO_SHADER_CONSTANTS_H
#define DEMO_SHADER_CONSTANTS_H

#include <string>

static const std::string DEMO_CONSTANTS_TOTAL_TIME = "TOTAL_TIME";
static const std::string DEMO_CONSTANTS_DELTA_TIME = "DELTA_TIME";

static const std::string DEMO_CONSTANTS_PROJECTION = "PROJECTION";
static const std::string DEMO_CONSTANTS_VIEW = "VIEW";

static const std::string DEMO_CONSTANTS_MODEL = "MODEL";
static const std::string DEMO_CONSTANTS_NORMAL_MODEL = "NORMAL_MODEL";

static const std::string DEMO_CONSTANTS_CAMERA_POSITION = "CAMERA_POSITION";
static const std::string DEMO_CONSTANTS_CAMERA_FORWARD = "CAMERA_FORWARD";

static const std::string DEMO_NUM_ACTIVE_POINT_LIGHTS = "NUM_ACTIVE_POINT_LIGHTS";
static const std::string DEMO_NUM_ACTIVE_DIRECTIONAL_LIGHTS = "NUM_ACTIVE_DIRECTIONAL_LIGHTS";


static const int MAX_NUM_POINT_LIGHTS = 20;
static const int MAX_NUM_DIRECTIONAL_LIGHTS = 4;

#endif // DEMO_SHADER_CONSTANTS_H
