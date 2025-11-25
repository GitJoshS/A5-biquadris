export module Player

import Board;


export class Player {
    Board* board;
    int curScore;
    int playerId;

    Player();

    int getCurScore();
    int getPlayerId();


}