using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Gomoku
{

    public interface IGUI
    {
        void DrawBoard(field[,] board);
        void DrawCurrentPlayer(game_state gameState);
        void GetCorrectInput(out int y, out int x);
    }
}
