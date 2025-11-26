# A5-biquadris

# Command List/Instructions
// Movement commands
// left / lef      : move block left
// right / ri      : move block right
// down / do       : move block down

// Rotation commands
// clockwise / cw       : rotate block 90° clockwise
// counterclockwise / ccw : rotate block 90° counterclockwise

// Block control
// drop / dr / dro      : drop current block to bottom
// I, J, L, O, S, T, Z  : replace current block (testing)

// Level control
// levelup / levelu      : increase game level
// leveldown / leveld    : decrease game level

// Random / sequence
// random                : restore randomness
// norandom file         : use sequence from file instead of random (testing)
// sequence file         : execute commands from file

// Game control
// restart               : clear board and restart game
// EOF                   : terminate game

// Notes:
// Commands accept minimal unique prefixes (lef = left)
// Numeric multipliers allowed (3left = move left 3 times), except restart, hint, random, norandom
// Invalid input should not crash program
