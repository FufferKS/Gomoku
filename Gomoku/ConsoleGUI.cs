using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Gomoku
{
    class ConsoleGUI : IGUI
    {
        public void DrawBoard(field[,] board)
        {
            int size = (int)Math.Sqrt(board.Length);
            Console.SetCursorPosition(0, 5);
            DrawLine(size);
            for (int y = 0; y < size; y++)
            {
                Console.Write('|');
                for (int x = 0; x < size; x++)
                {
                    char toWrite = GetStateChar(board[y, x].state);
                    Console.Write(toWrite);
                }
                Console.Write('|');
                Console.Write('\n');
            }
            DrawLine(size);
        }
        
        private char GetStateChar(field_state state)
        {
            switch (state)
            {
                case field_state.FREE:
                    return ' ';
                case field_state.PLAYER_O:
                    return 'O';
                case field_state.PLAYER_X:
                    return 'X';
                default:
                    return 'E';
            }
        }
        private void DrawLine(int length)
        {
            Console.Write(' ');
            for (int x = 0; x < length; x++)
            {
                Console.Write('-');
            }
            Console.Write('\n');
        }

        public void DrawCurrentPlayer(game_state gameState)
        {
            Console.SetCursorPosition(10, 1);
            char c =  GetStateChar((field_state)gameState);
            Console.WriteLine("Current Player : {0}", c);
        }

        public void GetCorrectInput(out int y, out int x)
        {
            bool isCorrectY = false, isCorrectX = false;
            do
            {
                var numbers = Console.ReadLine();
                var numberList = numbers.Split(' ');
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
            } while ((isCorrectY && isCorrectX) == false);
        }
    }
}
