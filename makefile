CXX          = g++
CXXFLAGS     = -g

FLTKCONFIG   = /usr/bin/fltk-config
LINKFLTK     = $(shell $(FLTKCONFIG) --ldstaticflags)
LINKFLTK_GL  = $(shell $(FLTKCONFIG) --use-gl --ldstaticflags)
LINKFLTK_IMG = $(shell $(FLTKCONFIG) --use-images --ldstaticflags)
LINKFLTK_ALL = $(shell $(FLTKCONFIG) --use-images --use-gl --ldstaticflags)

ConnectTheNumbers: bin/ConnectTheNumbers.o bin/PuzzleManager.o bin/PuzzleParser.o bin/Scoreboard.o bin/ScoreboardEntry.o bin/UserSettings.o \
	bin/FileIOUtility.o \
	bin/GameMainWindow.o bin/PuzzleboardWindow.o bin/ScoreboardWindow.o bin/GetUserInputWindow.o bin/UserPreferencesWindow.o
	$(CXX) $(CXXFLAGS) bin/*.o -o ConnectTheNumbers $(LINKFLTK_ALL)

bin/ConnectTheNumbers.o: ConnectTheNumbers.cpp
	$(CXX) $(CXXFLAGS) -IUtility -IModel -IView -c ConnectTheNumbers.cpp -o bin/ConnectTheNumbers.o

bin/PuzzleManager.o: Model/PuzzleManager.cpp Model/PuzzleManager.h
	$(CXX) $(CXXFLAGS) -IUtility -IModel -IView -c Model/PuzzleManager.cpp -o bin/PuzzleManager.o

bin/PuzzleParser.o: Model/PuzzleParser.cpp Model/PuzzleParser.h
	$(CXX) $(CXXFLAGS) -IUtility -IModel -IView -c Model/PuzzleParser.cpp -o bin/PuzzleParser.o

bin/Scoreboard.o: Model/Scoreboard.cpp Model/Scoreboard.h
	$(CXX) $(CXXFLAGS) -IUtility -IModel -IView -c Model/Scoreboard.cpp -o bin/Scoreboard.o

bin/ScoreboardEntry.o: Model/ScoreboardEntry.cpp Model/ScoreboardEntry.h
	$(CXX) $(CXXFLAGS) -IUtility -IModel -IView -c Model/ScoreboardEntry.cpp -o bin/ScoreboardEntry.o

bin/UserSettings.o: Model/UserSettings.cpp Model/UserSettings.h
	$(CXX) $(CXXFLAGS) -IUtility -IModel -IView -c Model/UserSettings.cpp -o bin/UserSettings.o

bin/FileIOUtility.o: Utility/FileIOUtility.cpp Utility/FileIOUtility.h
	$(CXX) $(CXXFLAGS) -IUtility -IModel -IView -c Utility/FileIOUtility.cpp -o bin/FileIOUtility.o

bin/GameMainWindow.o: View/GameMainWindow.cpp View/GameMainWindow.h
	$(CXX) $(CXXFLAGS) -IUtility -IModel -IView -c View/GameMainWindow.cpp -o bin/GameMainWindow.o

bin/GetUserInputWindow.o: View/GetUserInputWindow.cpp View/GetUserInputWindow.h
	$(CXX) $(CXXFLAGS) -IUtility -IModel -IView -c View/GetUserInputWindow.cpp -o bin/GetUserInputWindow.o

bin/PuzzleboardWindow.o: View/PuzzleboardWindow.cpp View/PuzzleboardWindow.h
	$(CXX) $(CXXFLAGS) -IUtility -IModel -IView -c View/PuzzleboardWindow.cpp -o bin/PuzzleboardWindow.o

bin/ScoreboardWindow.o: View/ScoreboardWindow.cpp View/ScoreboardWindow.h
	$(CXX) $(CXXFLAGS) -IUtility -IModel -IView -c View/ScoreboardWindow.cpp -o bin/ScoreboardWindow.o

bin/UserPreferencesWindow.o: View/UserPreferencesWindow.cpp View/UserPreferencesWindow.h
	$(CXX) $(CXXFLAGS) -IUtility -IModel -IView -c View/UserPreferencesWindow.cpp -o bin/UserPreferencesWindow.o

clean:
	rm -r ConnectTheNumbers bin/*
