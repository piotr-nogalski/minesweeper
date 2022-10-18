#include "gtest/gtest.h"
#include "MinesweeperBoard.hpp"

struct DebugModeTestSuite : public ::testing::Test
{
    MinesweeperBoard board{1, 2, GameMode::DEBUG};
};

TEST_F(DebugModeTestSuite, shouldCreatePredefinedBoard)
{
    EXPECT_EQ(10, board.getBoardWidth());
    EXPECT_EQ(10, board.getBoardHeight());
}

TEST_F(DebugModeTestSuite, shouldLoseGameWhenRevealedMine)
{
    EXPECT_EQ(GameState::RUNNING, board.getGameState());
    board.revealField(0, 0);
    EXPECT_EQ(GameState::FINISHED_LOSS, board.getGameState());
}

TEST_F(DebugModeTestSuite, shouldGetInfoAboutMineOnRevealedField)
{
    board.revealField(0, 0);
    EXPECT_EQ('x', board.getFieldInfo(0, 0));
}

TEST_F(DebugModeTestSuite, shouldCountMinesAroundRevealedField)
{
    board.revealField(1, 0);
    board.revealField(2, 9);
    board.revealField(2, 1);
    board.revealField(6, 7);
    EXPECT_EQ(4, board.countMines(1, 0));
    EXPECT_EQ(0, board.countMines(2, 9));
    EXPECT_EQ(3, board.countMines(2, 1));
    EXPECT_EQ(2, board.countMines(6, 7));
}

TEST_F(DebugModeTestSuite, shouldKnowNumberOfMinesAroundRevealedField)
{
    board.revealField(1, 0);
    board.revealField(2, 9);
    board.revealField(2, 1);
    board.revealField(6, 7);
    EXPECT_EQ('4', board.getFieldInfo(1, 0));
    EXPECT_EQ(' ', board.getFieldInfo(2, 9));
    EXPECT_EQ('3', board.getFieldInfo(2, 1));
    EXPECT_EQ('2', board.getFieldInfo(6, 7));
}

struct FinishedStateTestSuite : public DebugModeTestSuite
{
    FinishedStateTestSuite()
    {
        board.revealField(0, 0);
    }
};

TEST_F(FinishedStateTestSuite, shouldNotRevealField)
{
    board.revealField(2, 3);
    ASSERT_FALSE(board.isRevealed(2, 3));
}

TEST_F(FinishedStateTestSuite, shouldNotToggleFlag)
{
    board.toggleFlag(2, 3);
    ASSERT_FALSE(board.hasFlag(2, 3));
}

struct SingleFieldTestSuite : public ::testing::Test
{
    MinesweeperBoard board{1, 1, GameMode::EASY};
};

TEST_F(SingleFieldTestSuite, shouldKnowNothingAboutNotRevealedField)
{
    EXPECT_EQ('_', board.getFieldInfo(0, 0));
}

TEST_F(SingleFieldTestSuite, shouldNotHaveFlagByDefault)
{
    EXPECT_FALSE(board.hasFlag(0, 0));
}

TEST_F(SingleFieldTestSuite, shouldToggleFlag)
{
    board.toggleFlag(0, 0);
    EXPECT_TRUE(board.hasFlag(0, 0));

    board.toggleFlag(0, 0);
    EXPECT_FALSE(board.hasFlag(0, 0));
}

TEST_F(SingleFieldTestSuite, shouldNotToggleFlagOnRevealedField)
{
    board.revealField(0, 0);
    board.toggleFlag(0, 0);
    ASSERT_FALSE(board.hasFlag(0, 0));
}

TEST_F(SingleFieldTestSuite, shouldRevealField)
{
    board.revealField(0, 0);
    EXPECT_TRUE(board.isRevealed(0, 0));
}

TEST_F(SingleFieldTestSuite, shouldNotRevealFlaggedField)
{
    board.toggleFlag(0, 0);
    board.revealField(0, 0);
    EXPECT_FALSE(board.isRevealed(0, 0));
}

TEST_F(SingleFieldTestSuite, shouldNotUnrevealFields)
{
    board.revealField(0, 0);
    board.revealField(0, 0);
    ASSERT_TRUE(board.isRevealed(0, 0));
}

TEST_F(SingleFieldTestSuite, shouldGetCorrectFieldInfoForFlaggedField)
{
    board.toggleFlag(0, 0);
    EXPECT_EQ('F', board.getFieldInfo(0, 0));
}

TEST_F(SingleFieldTestSuite, shouldHaveCorrectBoardSizes)
{
    EXPECT_EQ(1, board.getBoardWidth());
    EXPECT_EQ(1, board.getBoardHeight());
}

TEST_F(SingleFieldTestSuite, shouldBeInRunningStateBeforeAnyAction)
{
    EXPECT_EQ(GameState::RUNNING, board.getGameState());
}

TEST_F(SingleFieldTestSuite, shouldWinGameWhenRevealedAllFieldsWithoutMine)
{
    EXPECT_EQ(GameState::RUNNING, board.getGameState());
    board.revealField(0, 0);
    EXPECT_EQ(GameState::FINISHED_WIN, board.getGameState());
}

TEST_F(SingleFieldTestSuite, shouldHaveMinesCountEqualMinusOneForNotRevealedField)
{
    EXPECT_EQ(-1, board.countMines(0, 0));
}

struct OutsideBoardTestSuite : SingleFieldTestSuite
{};

TEST_F(OutsideBoardTestSuite, shouldReturnInfoAboutOutsideBoardField)
{
    EXPECT_EQ('#', board.getFieldInfo(4, 2));
}

TEST_F(OutsideBoardTestSuite, shouldNotHaveFlag)
{
    board.toggleFlag(4, 2);
    EXPECT_FALSE(board.hasFlag(4, 2));
}

TEST_F(OutsideBoardTestSuite, shouldHaveMinesCountEqualMinusOne)
{
    EXPECT_EQ(-1, board.countMines(4, 2));
}

TEST_F(OutsideBoardTestSuite, shouldNotRevealField)
{
    board.revealField(4, 2);
    EXPECT_FALSE(board.isRevealed(4, 2));
}

struct MineCountParams
{
    int width;
    int height;
    GameMode mode;
    int expectedMineCount;
};

struct MineCountTestSuite : public ::testing::TestWithParam<MineCountParams>
{};

TEST_P(MineCountTestSuite, shouldHaveCorrectNumberOfMinesDependingOnDifficulty)
{
    MinesweeperBoard board{GetParam().width, GetParam().height, GetParam().mode};
    EXPECT_EQ(GetParam().expectedMineCount, board.getMineCount());
}

INSTANTIATE_TEST_CASE_P(MineCountTestSuite, MineCountTestSuite, ::testing::Values(
            MineCountParams{10, 10, GameMode::EASY,   10},
            MineCountParams{10, 10, GameMode::NORMAL, 20},
            MineCountParams{10, 10, GameMode::HARD,   30},
            MineCountParams{1,  1,  GameMode::EASY,   0},
            MineCountParams{2,  15, GameMode::EASY,   3},
            MineCountParams{1,  15, GameMode::EASY,   1}
            ));

