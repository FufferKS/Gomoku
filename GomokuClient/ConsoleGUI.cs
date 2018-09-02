using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GomokuServer;

namespace GomokuClient
{

    class ConsoleGUI : IGUI
    {    
        //Wysokość formatu A5 : 210 mm = 21, 0 cm.Szerokość formatu A5 : 148 mm = 14, 8 cm.
        const int B_SIZE_Y = 42;
        const int B_SIZE_X = 30;
        public void DrawBoard(_field[] board)
        {
            Console.SetCursorPosition(0, 6);
            DrawHorizontalDigits(B_SIZE_X);
            DrawLine(B_SIZE_X);
            for (int y = 0; y < B_SIZE_Y; y++)
            {

                Console.Write((y >= 10 ? y.ToString() : "0" + y.ToString())+"|");//ugly
                for (int x = 0; x < B_SIZE_X; x++)
                {
                    char toWrite = GetStateChar(board[B_SIZE_X*y+x].fieldState);
                    Console.Write(toWrite);
                }
                Console.Write('|');
                Console.Write('\n');
            }
            DrawLine(B_SIZE_X);
        }

        private char GetStateChar(_player_sign sign)
        {
            switch (sign)
            {
                case _player_sign.EMPTY:
                    return ' ';
                case _player_sign.PLAYER_O:
                    return 'O';
                case _player_sign.PLAYER_X:
                    return 'X';
                default:
                    return 'E';
            }
        }
        private string GetStateChar(_game_state state)
        {
            switch (state)
            {
                case _game_state.INITIAL:
                    return "INITIAL               ";
                case _game_state.WAITING_FOR_2ND_PLAYER:
                    return "WAITING_FOR_2ND_PLAYER";
                case _game_state.IN_PROGRESS:
                    return "IN_PROGRESS           ";
                case _game_state.FINISHED:
                    return "FINISHED              ";
                default:
                    return "E";
            }
        }
        private void DrawLine(int length)
        {
            Console.Write("   ");
            for (int x = 0; x < length; x++)
            {
                Console.Write('-');
            }
            Console.Write('\n');
        }
        private void DrawHorizontalDigits(int length)
        {
            Console.Write("   ");
            for (int x = 0; x < length; x++)
            {
                Console.Write(x%10);
            }
            Console.Write('\n');
        }

        public void DrawCurrentPlayer(_player_sign currentPlayer)
        {
            Console.SetCursorPosition(0, 1);
            char c = GetStateChar(currentPlayer);
            Console.WriteLine("Current Player : {0}", c);
        }
        public void DrawYourPlayer(_player_sign ps)
        {
            Console.SetCursorPosition(0, 0);
            char c = GetStateChar(ps);
            Console.WriteLine("You are playing as : {0}", c);

        }
        public void DrawGameState(_game_state gameState)
        {
            Console.SetCursorPosition(0, 2);
            string s = GetStateChar(gameState);
            Console.WriteLine("Game State : {0}", s);
        }

        public void GetCorrectInput(out int y, out int x)
        {
            Console.SetCursorPosition(0, 3);
            Console.WriteLine("Input the coordinates comma seperated 'y,x' e.q '7,4'");
            bool isCorrectY = false, isCorrectX = false;
            do
            {
                Console.SetCursorPosition(0, 4);
                var numbers = Console.ReadLine();
                var numberList = numbers.Split(',');
                if (numberList.Length == 2)
                {
                    isCorrectY = int.TryParse(numberList[0], out y);
                    isCorrectX = int.TryParse(numberList[1], out x);
                }
                else
                {
                    //for compiler only, this branch is not needed 
                    y = 0;
                    x = 0;
                }
                Console.SetCursorPosition(0, 4);
                Console.WriteLine("                        ");
                Console.WriteLine("Your input was incorrect");
            } while ((isCorrectY && isCorrectX) == false);
            Console.SetCursorPosition(0, 3);
            Console.WriteLine("                                                     ");
            Console.WriteLine("                        ");
            Console.WriteLine("                        ");
        }
    }
}
