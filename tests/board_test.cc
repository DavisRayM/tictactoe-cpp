#include <board.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("default constructor state", "[Move]") {
  Move move;
  REQUIRE(move.x == -1);
  REQUIRE(move.y == -1);
}

TEST_CASE("constructor initializes variables", "[Move]") {
  int x = 35;
  int y = 25;
  Move move(x, y);

  REQUIRE(move.x == x);
  REQUIRE(move.y == y);
}

TEST_CASE("default constructor state", "[Board]") {
  Board board;
  Token expectedState[3][3] = {
      {Token::EMPTY, Token::EMPTY, Token::EMPTY},
      {Token::EMPTY, Token::EMPTY, Token::EMPTY},
      {Token::EMPTY, Token::EMPTY, Token::EMPTY},
  };

  for (int r = 0; r < 3; ++r)
    for (int c = 0; c < 3; ++c) REQUIRE(board.state[r][c] == Token::EMPTY);
}

TEST_CASE("play valid move is successful", "[Board, Board::Play]") {
  Board board;
  REQUIRE(board.Play(0, 2, Token::X, nullptr));
  REQUIRE(board.Play(2, 0, Token::X, nullptr));
}

TEST_CASE("play invalid move is unsuccessful", "[Board, Board::Play]") {
  Board board;
  REQUIRE(!board.Play(-1, 0, Token::X, nullptr));
  REQUIRE(!board.Play(0, -1, Token::X, nullptr));
  REQUIRE(!board.Play(3, 0, Token::X, nullptr));
  REQUIRE(!board.Play(0, 3, Token::X, nullptr));
}

TEST_CASE("play stores valid move in returned board", "[Board, Board::Play]") {
  Board board;
  Board actualBoard;
  int x = 0, y = 1;
  Token player = Token::X;

  board.Play(x, y, player, &actualBoard);
  REQUIRE(player == actualBoard.state[x][y]);
}

TEST_CASE("play ensures previous generation content is stored",
          "[Board, Board::Play]") {
  Board board;
  Board actualBoard;
  int x = 0, y = 1, x2 = 0, y2 = 0;
  Token player = Token::X;

  board.state[x][y] = player;
  board.Play(x2, y2, Token::CIRCLE, &actualBoard);
  REQUIRE(player == actualBoard.state[x][y]);
}

TEST_CASE("WinState returns ongoing win condition",
          "[Board, Board::WinState]") {
  Board board;
  REQUIRE(board.WinState() == BoardWinState::ONGOING);

  board.state[0][0] = Token::X;
  REQUIRE(board.WinState() == BoardWinState::ONGOING);
}

TEST_CASE("WinState returns draw win condition", "[Board, Board::WinState]") {
  Board board;

  board.state[0][0] = Token::X;
  board.state[0][1] = Token::CIRCLE;
  board.state[0][2] = Token::CIRCLE;

  board.state[1][0] = Token::CIRCLE;
  board.state[1][1] = Token::X;
  board.state[1][2] = Token::X;

  board.state[2][0] = Token::X;
  board.state[2][1] = Token::CIRCLE;
  board.state[2][2] = Token::CIRCLE;
  REQUIRE(board.WinState() == BoardWinState::DRAW);
}

TEST_CASE("WinState returns correct player win condition",
          "[Board, Board::WinState]") {
  Board board;
  BoardWinState expectedStateX = BoardWinState::X_WIN;
  BoardWinState expectedStateCircle = BoardWinState::CIRCLE_WIN;

  SECTION("works for circle user") {
    board.state[0][0] = Token::CIRCLE;
    board.state[0][1] = Token::CIRCLE;
    board.state[0][2] = Token::CIRCLE;

    REQUIRE(board.WinState() == expectedStateCircle);
  }

  SECTION("works for X user") {
    board.state[0][0] = Token::X;
    board.state[0][1] = Token::X;
    board.state[0][2] = Token::X;

    REQUIRE(board.WinState() == expectedStateX);
  }

  SECTION("row wins count") {
    board.state[1][0] = Token::X;
    board.state[1][1] = Token::X;
    board.state[1][2] = Token::X;

    REQUIRE(board.WinState() == expectedStateX);
  }

  SECTION("column wins count") {
    board.state[0][1] = Token::X;
    board.state[1][1] = Token::X;
    board.state[2][1] = Token::X;

    REQUIRE(board.WinState() == expectedStateX);
  }

  SECTION("left-right diagonal wins count") {
    board.state[0][0] = Token::X;
    board.state[1][1] = Token::X;
    board.state[2][2] = Token::X;

    REQUIRE(board.WinState() == expectedStateX);
  }

  SECTION("right-left diagonal wins count") {
    board.state[0][2] = Token::X;
    board.state[1][1] = Token::X;
    board.state[2][0] = Token::X;

    REQUIRE(board.WinState() == expectedStateX);
  }
}

TEST_CASE("ValidMoves returns valid moves for the current board",
          "[Board, Board::ValidMoves]") {
  Board board;

  SECTION("initial board has all valid moves") {
    auto moves = board.ValidMoves();
    for (int i = 0; i < 3; i++)
      for (int y = 0; y < 3; y++) {
        REQUIRE(moves[i * 3 + y].x == i);
        REQUIRE(moves[i * 3 + y].y == y);
      }
    REQUIRE(moves.size() == 9);
  }

  SECTION("returns based on current board state") {
    board.state[0][0] = Token::X;
    auto moves = board.ValidMoves();

    REQUIRE(moves.size() == 8);
  }
}

TEST_CASE("GetLines returns expected lines", "[Board, Board::GetLines]") {
  Board board;
  REQUIRE(board.GetLines().size() == 8);
}
