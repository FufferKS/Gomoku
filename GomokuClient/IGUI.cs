using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GomokuServer;

namespace GomokuClient
{
    public interface IGUI
    {
        void DrawBoard(_field[] board);
        void DrawCurrentPlayer(_player_sign ps);
        void DrawYourPlayer(_player_sign ps);
        void DrawGameState(_game_state gameState);
        void GetCorrectInput(out int y, out int x);
    }
}
