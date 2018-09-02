#pragma once
#include "GomokuServerRoomFactory.h"
#include "GomokuServerTypeInfo_h.h"
#include "Locks.h"

class GomokuServerRoom : public IGomokuServerRoom
{
public:
	GomokuServerRoom();
	~GomokuServerRoom();
	// Inherited via IGomokuServerRoom
	virtual HRESULT QueryInterface(REFIID riid, void ** ppvObject) override;
	virtual ULONG AddRef(void) override;
	virtual ULONG Release(void) override;
	//
	virtual HRESULT JoinGame(player_sign * pi) override;
	virtual HRESULT GetCurrentPlayer(player_sign * cp) override;
	virtual HRESULT GetBoard(field board[B_SIZE_Y][B_SIZE_X]) override;
	virtual HRESULT MakeAMove(move_result * mr, player_sign * pi, int * y, int * x) override;
	virtual HRESULT GetGameState(game_state * gs) override;
private:
	bool CheckWin(player_sign ps, int y, int x);
	bool CheckWinField(player_sign ps, int iy, int ix, int * howManyInARow);
	move_result SetField(player_sign ps, int y, int x);
	void SwapTurns();
	bool FieldIsValid(int y, int x);

	ULONG m_refCount;
	//
	field		m_board[B_SIZE_Y][B_SIZE_X] = {EMPTY};
	int			m_numOfJoinedPlayers = 0;
	player_sign m_currentPlayer;
	game_state	m_gameState;
};