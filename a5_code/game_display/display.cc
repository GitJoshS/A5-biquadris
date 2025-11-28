export module Display;

import <vector>;
import Player;

using namespace std;

export class Display {
    protected:
        vector<Player*> players;
    public:
        Display(vector<Player*> players);

        virtual void render() = 0;
};

