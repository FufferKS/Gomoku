#include "GomokuServerRoom.h"
#include "GomokuServerTypeInfo_i.c"

GomokuServerRoom::GomokuServerRoom()
{
	m_refCount				= 0;
	m_currentPlayer			= NON_INITIALIZED;
	m_gameState				= INITIAL;
	m_numOfJoinedPlayers	= 0;
	for (int y = 0; y < B_SIZE_Y; y++)
	{
		for (int x = 0; x < B_SIZE_X; x++)
		{
			m_board[y][x].fieldState = EMPTY;
		}
	}
	Lock();
}

GomokuServerRoom::~GomokuServerRoom()
{
	UnLock();
}

HRESULT GomokuServerRoom::QueryInterface(REFIID riid, void ** ppvObject)
{

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown*)(IGomokuServerRoom*)this;
		// MessageBox(NULL, "Handed out IUnknown","QI",MB_OK | MB_SETFOREGROUND);
	}

	else if (riid == IID_IGomokuServerRoom)
	{
		*ppvObject = (IGomokuServerRoom*)this;
		// MessageBox(NULL, "Handed out IEngine","QI",MB_OK | MB_SETFOREGROUND);
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	((IUnknown*)(*ppvObject))->AddRef();
	return S_OK;
}

ULONG GomokuServerRoom::AddRef(void)
{
	++m_refCount;

	return m_refCount;
}

ULONG GomokuServerRoom::Release(void)
{
	if (--m_refCount == 0)
	{
		delete this;
		return 0;
	}
	else
	{
		return m_refCount;
	}
}

HRESULT GomokuServerRoom::JoinGame(player_sign * ps)
{
	HRESULT hr;
	if (m_numOfJoinedPlayers >= 2)
	{
		hr = S_FALSE;//shouldnt happen unless client calls this twice
	}
	else
	{	
		hr = S_OK;
		*ps = m_numOfJoinedPlayers == 0 ? PLAYER_O : PLAYER_X;
		m_numOfJoinedPlayers++;
		if (m_numOfJoinedPlayers == 1)
		{
			m_gameState = WAITING_FOR_2ND_PLAYER;
		}
		if (m_numOfJoinedPlayers == 2)
		{
			m_currentPlayer = PLAYER_O;
			m_gameState = IN_PROGRESS;
		}
	}
	return hr;
}

HRESULT GomokuServerRoom::GetCurrentPlayer(player_sign * cp)
{
	*cp = m_currentPlayer;
	return S_OK;
}

HRESULT GomokuServerRoom::GetBoard(field board[B_SIZE_Y][B_SIZE_X])
{
	for (int y = 0; y < B_SIZE_Y; y++)
	{
		for (int x = 0; x < B_SIZE_X; x++)
		{
			board[y][x].fieldState = m_board[y][x].fieldState;
		}
	}
	return S_OK;
}

HRESULT GomokuServerRoom::MakeAMove(move_result * mr, player_sign * ps, int * y, int * x)
{
	*mr = FAIL;
	if (*ps == m_currentPlayer)//if the calling player is the current player
	{
		*mr = SetField(*ps, *y, *x);
		if (*mr == OK)
		{
			if (CheckWin(*ps, *y, *x))
			{
				m_gameState = FINISHED;
				//TODO co dalej?
			}
			else
			{
				SwapTurns();
			}
		}
	}

	return S_OK;
}

HRESULT GomokuServerRoom::GetGameState(game_state * gs)
{
	*gs = m_gameState;
	return S_OK;
}
//
bool GomokuServerRoom::CheckWin(player_sign ps, int y, int x)
{
	//TODO brzydka ta funkcja, jakby z tego zrobic klase to byloby ok
	// 5 is a magic number -> number of tokens in a row needed for a win
	// 4 because we want go up to that many to check
	// s-start  e-end  i-index
	int sy, ey, iy, sx, ex, ix;
	int howManyInARow = 0;
	//hor
	sx = max(0, x - 4);
	ex = min(B_SIZE_X - 1, x + 4);
	ix = sx;
	iy = y;
	howManyInARow = 0;
	for (; ix < ex; ix++)
	{
		if (CheckWinField(ps, iy, ix, &howManyInARow))
			return true;
	}
	//ver
	sy = max(0, y - 4);
	ey = min(B_SIZE_Y - 1, y + 4);
	ix = x;
	iy = sy;
	howManyInARow = 0;
	for (; iy < ey; iy++)
	{
		if (CheckWinField(ps, iy, ix, &howManyInARow))
			return true;
	}
	//diag up
	sy = min(B_SIZE_Y - 1, y + 4);
	ey = max(0, y - 4);
	sx = max(0, x - 4);
	ex = min(B_SIZE_X - 1, x + 4);
	ix = sx;
	iy = sy;
	howManyInARow = 0;
	for (; iy >= ey && ix < ex; iy--, ix++)
	{
		if (CheckWinField(ps, iy, ix, &howManyInARow))
			return true;	
	}
	//diag down
	sy = max(0, y - 4);
	ey = min(B_SIZE_Y - 1, y + 4);
	sx = max(0, x - 4);
	ex = min(B_SIZE_X - 1, x + 4);
	ix = sx;
	iy = sy;
	howManyInARow = 0;
	for (; iy < ey && ix < ex; iy++, ix++)
	{
		if (CheckWinField(ps, iy, ix, &howManyInARow))
			return true;
	}
	return false;
}
bool GomokuServerRoom::CheckWinField(player_sign ps, int iy, int ix, int* howManyInARow)//todo: ugly name, not sure what this does
{
	// 5 is a magic number -> number of tokens in a row needed for a win
	if (m_board[iy][ix].fieldState == ps)
	{
		(*howManyInARow)++;
		if (*howManyInARow == 5)
		{
			return true;
		}
	}
	else
	{
		*howManyInARow = 0;
	}
	return false;
}
move_result GomokuServerRoom::SetField(player_sign ps, int y, int x)
{
	move_result result = FAIL;
	if (FieldIsValid(y, x)
		&& (m_board[y][x].fieldState == EMPTY))
	{
		m_board[y][x].fieldState = ps;
		result = OK;
	}
	return result;
}
void GomokuServerRoom::SwapTurns()
{//ternary is ugly
	if (m_currentPlayer == PLAYER_O)
	{
		m_currentPlayer = PLAYER_X;
	}
	else
	{
		m_currentPlayer = PLAYER_O;
	}
}
bool GomokuServerRoom::FieldIsValid(int y, int x)
{
	if (y >= 0 && x >= 0 && y < B_SIZE_Y && x < B_SIZE_X)
	{
		return true;
	}
	else
	{
		return false;
	}
}