module export Level;

import <vector>;
import <cstdlib>;

export class Level {
    int howHeavy;

    public:
    Level() {}
    virtual char getNextBlockType() = 0;  // Returns BlockType ('I', 'J', 'L', 'O', 'S', 'Z', 'T')
    virtual int getHowHeavy();
    virtual ~Level() = default;
}
// int randomNum = rand() % 100;
