#include "scenes/HomeScreen.hpp"
#include "scenes/TourneyScreen.hpp"
#include "scenes/AppsScreen.hpp"

// match scenes
#include "scenes/match/AutonScreen.hpp"
#include "scenes/match/DebugScreen.hpp"
#include "scenes/match/TempsScreen.hpp"

// apps scenes
#include "scenes/apps/drivetrainFriction.hpp"
#include "scenes/apps/PIDTuner.hpp"
#include "scenes/apps/Grapher.hpp"

// Define scene instances in a single translation unit to avoid multiple-definition errors
Scene HomeScreenScene = { drawHomeScreen, touchFunctionHomeScreen };
Scene AutonScreenScene = { drawAutonScreen, touchFunctionAutonScreen };
Scene TourneyScreenScene = { drawTourneyScreen, touchFunctionTourneyScreen };
Scene AppsScreenScene = { drawAppsScreen, touchFunctionAppsScreen };
Scene DebugScreenScene = { drawDebugScreen, touchFunctionDebugScreen };
Scene TempsScreenScene = { drawTempsScreen, touchFunctionTempsScreen };
Scene DrivetrainFrictionScreenScene = { drawDrivetrainFrictionScreen, touchFunctionDrivetrainFrictionScreen };
Scene PIDTunerScreenScene = { drawPIDTunerScreen, touchFunctionPIDTunerScreen };
Scene GrapherScene = { drawGrapherScreen, touchFunctionGrapherScreen };