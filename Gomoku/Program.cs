using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Gomoku
{
    public enum field_state
    {
        FREE = 0,
        PLAYER_O = 11,
        PLAYER_X = 12,
        ERROR = 255
    }
    public enum game_state
    {
        RUNNING,
        PLAYER_1 = 11,
        PLAYER_2 = 12,
        FINISHED
    }
#if (PLAYER_1 != PLAYER_O)
    #error game_state and field_state need to in sync
#endif
    public struct field
    {
        public field_state state;
    }
    class Program
    {
        static void Main(string[] args)
        {
            HotSeatServer server = new HotSeatServer();
            ConsoleGUI gui = new ConsoleGUI();

            gui.DrawBoard(server.GetBoard());
            PlayerInfo player1 = server.StartGame();
            PlayerInfo player2 = server.StartGame();
            PlayerInfo currentPlayer = player1;

            int y, x;
            move_result result;
            do
            {
                do
                {
                    gui.GetCorrectInput(out y, out x);
                    result = server.MakeAMove(currentPlayer, y, x);
                    gui.DrawBoard(server.GetBoard());
                    gui.DrawCurrentPlayer(server.GetCurrentPlayer());
                } while (result == move_result.FAIL);
                currentPlayer = currentPlayer.playerNumber == game_state.PLAYER_1 ? player2 : player1;
            } while (server.GetGameState() != game_state.FINISHED);


            Console.ReadKey();
        }
    }
}
