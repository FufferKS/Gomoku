using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Gomoku
{
    public struct PlayerInfo
    {
        public int playerGID;
        public game_state playerNumber;
    }
    class HotSeatServer : IServer//for demo testing
    {
        game_state gameState = game_state.RUNNING;
        private const int SIZE = 10;
        PlayerInfo currentPlayer;
        int numberOfJoinedPlayers;
        PlayerInfo[] players;
        private field[,] board;
        int boardSize;
        public HotSeatServer()
        {
            Random rnd = new Random();
            boardSize = SIZE;
            board = new field[boardSize, boardSize];
            players = new PlayerInfo[2];
            numberOfJoinedPlayers = 0;
        }
        public field[,] GetBoard()
        {
            return board;
        }

        public game_state GetCurrentPlayer()
        {
            return currentPlayer.playerNumber;
        }

        public field GetField(int y, int x)
        {
            if (FieldIsValid(y, x))
                return board[y, x];
            else return new field(); //todo robustness check for out of range
        }

        public move_result MakeAMove(PlayerInfo player, int y, int x)
        {
            move_result result = move_result.FAIL;
            if(player.playerGID == currentPlayer.playerGID)
            {
                result = SetField((field_state)player.playerNumber, y, x);
                if(result == move_result.OK)
                {
                    SwapTurns();
                    if (CheckWin((field_state)player.playerNumber, y, x))
                    {
                        gameState = game_state.FINISHED;   
                    }
                }             
            }
            return result;
        }

        public game_state GetGameState()
        {
            return gameState;
        }

        private bool CheckWin(field_state playerNumber, int y, int x)
        {
            // 5 is a magic number -> number of tokens in a row needed for a win
            // 4 because we want go up to that many to check
            // s-start  e-end  i-index
            int sy, ey, iy, sx, ex, ix;
            int howManyInARow = 0;
            //hor
            sx = Math.Max(0, x - 4);
            ex = Math.Min(boardSize-1, x + 4);
            ix = sx;
            iy = y;
            for (; ix < ex; ix++)
            {
                if (CheckWinField(playerNumber, iy, ix, ref howManyInARow))
                    return true;
            }
            //ver
            sy = Math.Max(0, y - 4);
            ey = Math.Min(boardSize - 1, y + 4);
            ix = x;
            iy = sy;
            for (; iy < ey; iy++)
            {
                if (CheckWinField(playerNumber, iy, ix, ref howManyInARow))
                    return true;
            }
            //diag up
            sy = Math.Min(boardSize - 1, y + 4);
            ey = Math.Max(0, y - 4);
            sx = Math.Max(0, x - 4);
            ex = Math.Min(boardSize - 1, x + 4);
            ix = sx;
            iy = sy;
            for (; iy >= ey; iy--)
            {
                for (; ix < ex; ix++)
                {
                    if (CheckWinField(playerNumber, iy, ix, ref howManyInARow))
                        return true;
                }
            }
            //diag down
            sy = Math.Min(0, y - 4);
            ey = Math.Max(boardSize - 1, y + 4);
            sx = Math.Max(0, x - 4);
            ex = Math.Min(boardSize - 1, x + 4);
            ix = sx;
            iy = sy;
            for (; iy > ey; iy++)
            {
                for (; ix < ex; ix++)
                {
                    if (CheckWinField(playerNumber, iy, ix, ref howManyInARow))
                        return true;
                }
            }
            return false;
        }
        private bool CheckWinField(field_state playerNumber, int iy, int ix, ref int howManyInARow)//todo: ugly name, not sure what this does
        {
            // 5 is a magic number -> number of tokens in a row needed for a win
            if (board[iy, ix].state == playerNumber)
            {
                howManyInARow++;
                if (howManyInARow == 5)
                {
                    return true;
                }

            }
            else
            {
                howManyInARow = 0;
            }
            return false;
        }

        private move_result SetField(field_state player, int y, int x)
        {
            move_result result = move_result.FAIL;
            if (FieldIsValid(y, x)
                && (board[y, x].state == field_state.FREE))
            {
                board[y, x].state = player;
                result = move_result.OK;
            }
            return result;
        }

        public PlayerInfo StartGame()
        {
            PlayerInfo info = new PlayerInfo();
            if(numberOfJoinedPlayers < 2)
            {
                Random rnd = new Random();
                info.playerNumber = numberOfJoinedPlayers == 0 ? game_state.PLAYER_1 : game_state.PLAYER_2;
                info.playerGID = ((rnd.Next()/10)*10)+numberOfJoinedPlayers;
                players[numberOfJoinedPlayers] = info;
                currentPlayer = players[0];
                numberOfJoinedPlayers++;
            }
            return info;
        }

        private bool FieldIsValid(int y, int x)
        {
            if (y >= 0 && x >= 0 && y < boardSize && x < boardSize)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        private void SwapTurns()
        {
            currentPlayer = GetOppositePlayer(currentPlayer);
        }
        private PlayerInfo GetOppositePlayer(PlayerInfo player)
        {
            if (player.playerNumber == players[0].playerNumber)
                return players[1];
            else
                return players[0];
        }
    }
}
