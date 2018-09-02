-------------------------------------------------
COM Project created for KSR 2017/2018 ETI PG.
Krzysztof Œwiêtnicki 160310.
-------------------------------------------------
Project built on Win 10 x64 as x64 app.
-------------------------------------------------
Files:
	GomokuServer:
		GomokuServer:				handling main COM activities
		GomokuServerRoom:			single COM object responsible for providing server side gameplay for two players
		GomokuServerRoomFactory:	factory for the above with a twist, 
										every other requested object is passed as a pointer to the previous one,
										this way the two indepentent clients can play the same game
		Locks:						a simple mechanism to let Server know when we can exit safely (Sources 2.)
	GomokuClient:
		IGUI:						GUI interface used by the Client
		ConsoleGUI:					GUI implementation - console based
		Klient:						Class handling logic between GUI and server
		Program:					Main, Creates COM object from GomokuServer
	Other:
		GomokuServerTypeInfo.idl:   interface definition
		GomokuServer.reg:			reg script, should be adjusted to Your paths
		GomokuClient.exe			:)
		Gomoku\x64\Debug:
			GomokuServer.tlb			type library
			GomokuServer.dll			compiled for the client via: tlbimp.exe GomokuServer.tlb /out:GomokuServer.dll
			GomokuServer.exe            :)
-------------------------------------------------
Sources:
	1. http://kaims.eti.pg.gda.pl/~goluch/lab/com_17.pdf
	2. https://www.codeproject.com/Articles/8679/Building-a-LOCAL-COM-Server-and-Client-A-Step-by-S
	3. msdn