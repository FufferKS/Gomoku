using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GomokuServer;
using System.Threading;

namespace GomokuClient
{
    class Klient
    {
        //Wysokość formatu A5 : 210 mm = 21, 0 cm.Szerokość formatu A5 : 148 mm = 14, 8 cm.
        const int           B_SIZE_Y = 42;
        const int           B_SIZE_X = 30;
        GomokuServerRoom    room;
        ConsoleGUI          gui;
        _field[] board;
        _player_sign        yourPlayer;
        _player_sign        currentPs;
        _game_state         gameState;
        _move_result        moveResult;
        public Klient(GomokuServerRoom _room, ConsoleGUI _gui)
        {
            room = _room;
            gui = _gui;
            board = new _field[B_SIZE_Y * B_SIZE_X]; 
        }
        public void Play()
        {
            yourPlayer = room.JoinGame();
            WaitForGameStart();
            UpdateAll();
            MainGameLoop();
        }
        void UpdateAll()
        {
            GetAll();
            DrawAll();
        }
        void GetAll()
        {
            gameState = room.GetGameState();
            currentPs = room.GetCurrentPlayer();
            room.GetBoard(board);
        }
        void DrawAll()
        {
            gui.DrawBoard(board);
            gui.DrawGameState(gameState);
            gui.DrawCurrentPlayer(currentPs);
            gui.DrawYourPlayer(yourPlayer);
        }
        void WaitForGameStart()
        {
            gui.DrawYourPlayer(yourPlayer);
            do
            {
                gameState = room.GetGameState();
                gui.DrawGameState(gameState);
                Thread.Sleep(100);
            } while (gameState != _game_state.IN_PROGRESS);
        }
        void MainGameLoop()
        {
            do
            {
                EnemyTurnLoop();
                MyTurnLoop();

            } while (gameState == _game_state.IN_PROGRESS);
        }
        void EnemyTurnLoop()
        {
            do
            {
                currentPs = room.GetCurrentPlayer();
                gameState = room.GetGameState();
                Thread.Sleep(100);
            } while ((currentPs != yourPlayer) && (gameState == _game_state.IN_PROGRESS));

            UpdateAll();
        }
        void MyTurnLoop()
        {
            int y, x;
            if ((gameState == _game_state.IN_PROGRESS))
            {
                do
                {
                    gui.GetCorrectInput(out y, out x);
                    room.MakeAMove(out moveResult, yourPlayer, y, x);
                } while (moveResult == _move_result.FAIL);
            }
            UpdateAll();
        }
    }
    
}
