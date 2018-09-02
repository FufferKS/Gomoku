using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Gomoku
{
    public enum move_result
    {
        OK,
        FAIL
    }
    interface IServer
    {
        PlayerInfo StartGame();
        field[,] GetBoard();
        field GetField(int y, int x);
        game_state GetCurrentPlayer();
        move_result MakeAMove(PlayerInfo player, int y, int x);
        game_state GetGameState();
    }
}
